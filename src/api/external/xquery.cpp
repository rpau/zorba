///Created: Daniel Turcanu @ IPDevel 

#include "errors/error_factory.h"
#include "xquery.h"

#include "compiler/codegen/plan_visitor.h"
#include "compiler/translator/translator.h"
#include "compiler/normalizer/normalizer.h"
#include "compiler/parsetree/parsenode_print_xml_visitor.h"
#include "compiler/parsetree/parsenode_print_dot_visitor.h"
#include "compiler/parser/xquery_driver.h"
#include "system/zorba.h"
#include "runtime/visitors/printervisitor.h"
#include "runtime/visitors/iterprinter.h"

#include "api/serialization/serializer.h"
#include "api/external/dynamic_context_wrapper.h"

#include "zorba/util/properties.h"

///to be removed: (when store api is finalized)
#include "store/naive/simple_store.h"
#include "store/naive/simple_loader.h"
#include "store/naive/store_defs.h"

#include <iostream>
#include <fstream>

using namespace std;
namespace xqp {


Zorba_XQueryBinary::Zorba_XQueryBinary(xqp_string  xquery_source_uri,
                                       const char* query_text ) :
  m_xquery_source_uri(xquery_source_uri),
  m_query_text (query_text)
{
  is_compiled = false;
  top_iterator = NULL;
  lStateSize = 0;
  internal_sctx = NULL;

  default_collator = NULL;
  // addReference();
  // xquery_registered_callback = NULL;
  // xquery_registered_param = NULL;
}

Zorba_XQueryBinary::~Zorba_XQueryBinary()
{
  delete internal_sctx;
}


bool Zorba_XQueryBinary::compile(StaticQueryContext* sctx, 
                                 bool routing_mode)
{
  Zorba* zorba = ZORBA_FOR_CURRENT_THREAD();
  zorba->current_xquery = this;
  
  try
  {
    if(is_compiled)
    {
      ZORBA_ERROR_ALERT(AlertCodes::API0004_XQUERY_ALREADY_COMPILED,
                        NULL,
                        true///continue execution
                        );
      zorba->current_xquery = NULL;
      return false;
    }

    if(!m_query_text[0])
	  {
      ZORBA_ERROR_ALERT(AlertCodes::API0001_XQUERY_STRING_IS_EMPTY,
                        NULL,
                        true///continue execution
                        );
      zorba->current_xquery = NULL;
      return false;
    }

    if (sctx) {
      internal_static_context = sctx;
      //now build the static context
      StaticContextWrapper* context_wrapper = static_cast<StaticContextWrapper*>(sctx);
      internal_sctx = context_wrapper->FillInStaticContext();//return a static_context*
    }
    else
    {
      internal_sctx = new static_context;
    }
    internal_sctx->set_entity_file_uri(m_xquery_source_uri);

    // reset the error list from error manager
    // m_error_manager.clear();///delete all alerts from list

    ///NOW COMPILE
    xquery_driver driver;
    driver.filename = m_xquery_source_uri;

    ///build up the expression tree
    driver.parse_string(m_query_text);

    parsenode* n_p = driver.get_expr();

    if (Properties::instance()->printAST())
	  {
      cout << "Parse tree:\n";
      ParseNodePrintXMLVisitor lPrintXMLVisitor(std::cout);
      lPrintXMLVisitor.print(n_p);
    }    
	
    MainModule* mm_p;
    QueryBody* qb_p;
    Expr* ex_p;

    if ((mm_p = dynamic_cast<MainModule*>(n_p))==NULL) 
	  {
      ZORBA_ERROR_ALERT(AlertCodes::XPST0003,
                        NULL, true,
                        "Parse error: expecting MainModule");
      zorba->current_xquery = NULL;
      return false;
    }

    if ((qb_p = dynamic_cast<QueryBody*>(&*mm_p->get_query_body()))==NULL) 
	  {
      ZORBA_ERROR_ALERT(AlertCodes::XPST0003,
                        NULL, true,
                        "Parse error: expecting MainModule->QueryBody");
      //UnregisterCurrentXQueryForCurrentThread( this );
      zorba->current_xquery = NULL;
      return false;
    }

    if ((ex_p = dynamic_cast<Expr*>(&*qb_p->get_expr()))==NULL) 
	  {
      ZORBA_ERROR_ALERT(AlertCodes::XPST0003,
                        NULL, true, 
                        "Parse error: expecting MainModule->QueryBody->Expr");
      zorba->current_xquery = NULL;
      return false;
    }

    if (Properties::instance ()->printNormalizedExpressions ())
      cout << "Expression tree:\n";

    rchandle<expr> e_h = translate (zorba->get_static_context(), *mm_p);
    if (e_h == NULL)
    {
      ZORBA_ERROR_ALERT(AlertCodes::API0002_COMPILE_FAILED, NULL, true);
      zorba->current_xquery = NULL;
      return false;
    }
  
    normalizer n(zorba->get_static_context());
    e_h->accept(n);

    if (Properties::instance()->printNormalizedExpressions())
      e_h->put(cout) << endl;

    ///now do code generation (generate iterator tree)

    top_iterator = codegen (e_h);

    if (Properties::instance()->printIteratorTree()) {
      cout << "Iterator tree:\n";
      XMLIterPrinter vp(std::cout);
      PrinterVisitor pv(vp);
      top_iterator->accept(pv);
    }
	
    if (top_iterator == NULL) {
      cout << "Codegen returned null";
      ZORBA_ERROR_ALERT(AlertCodes::API0002_COMPILE_FAILED, NULL, true);
      zorba->current_xquery = NULL;
      return false;
    }

    is_compiled = true;

  }
  catch(xqp_exception &)
  {
    zorba->current_xquery = NULL;
    return false;
  }
  catch(...)
  {
    zorba->current_xquery = NULL;
    throw;
  }

  zorba->current_xquery = NULL;

  return true;
}


XQueryExecution_t Zorba_XQueryBinary::createExecution( DynamicQueryContext_t dctx)
{
  // init thread
  // check if thread is inited, if not do automatic init
  // and register this xquery as the current xquery executed/compiling in this current thread
  Zorba* zorba = ZORBA_FOR_CURRENT_THREAD();
  zorba->current_xquery = this;
  // RegisterCurrentXQueryForCurrentThread( this );

  try{
  
  if(!is_compiled)
  {
    cout << "not compiled" << endl;
    ZORBA_ERROR_ALERT(AlertCodes::API0003_XQUERY_NOT_COMPILED,
                                  NULL,
                                  true///continue execution
                                  );
    zorba->current_xquery = NULL;
    return NULL;
  }

  ///compute the offsets for each iterator into the state block
  lStateSize = top_iterator->getStateSizeOfSubtree();//daniel: is this needed at every execution?
  PlanState* stateBlock = new PlanState(lStateSize);
  uint32_t lOffset = 0;
  top_iterator->setOffset(*stateBlock, lOffset);

  ///and construct the state block of state objects...
  Zorba_XQueryExecution* zorba_result = new Zorba_XQueryExecution();
  zorba_result->it_result = top_iterator;
  zorba_result->state_block = stateBlock;
  zorba_result->state_block->zorp = zorba;
  zorba_result->state_block->xqbinary = this;
//  zorba_result->state_block->xqexecution = zorba_result;
  if(dctx.get_ptr())
  {
    DynamicContextWrapper *dctx_wrapper = static_cast<DynamicContextWrapper*>(dctx.get_ptr());
    zorba_result->internal_dyn_context = dctx_wrapper->create_dynamic_context(internal_sctx);
  }
	else
	{
    zorba_result->internal_dyn_context = new dynamic_context;
	}

  zorba->current_xquery = NULL;
//  RegisterCurrentXQueryForCurrentThread( NULL );

  return zorba_result;
  }
  catch(xqp_exception &)
  {
    zorba->current_xquery = NULL;
    return NULL;
  }
  catch(...)
  {
    zorba->current_xquery = NULL;
    throw;
  }
  
  return NULL;

}

//bool Zorba_XQueryBinary::isCompiled()
//{
//  return is_compiled;
//}

//QueryPtr Zorba_XQueryBinary::clone()
//{
//}

StaticQueryContext_t Zorba_XQueryBinary::getInternalStaticContext()
{
	if(internal_static_context.get_ptr() == NULL)
		internal_static_context = new StaticContextWrapper();
  return internal_static_context;
}


bool   Zorba_XQueryBinary::serializeQuery(ostream &os)
{
  ZORBA_ERROR_ALERT(AlertCodes::XQP0015_SYSTEM_NOT_YET_IMPLEMENTED,
                    NULL,
                    true,///continue execution
                    "Zorba_XQueryBinary::serializeQuery"
                    );
  return false;
}

/*
  Register the callback for the thread specific error manager
*/
/*
void Zorba_XQueryBinary::RegisterAlertCallback(alert_callback *user_alert_callback,
                                                void *param)
{
  xquery_registered_callback = user_alert_callback;
  xquery_registered_param = param;
}
*/

Zorba_XQueryExecution::Zorba_XQueryExecution()
{
  theClosed = false;
  is_error = false;
  internal_dyn_context = NULL;
}

Zorba_XQueryExecution::~Zorba_XQueryExecution()
{
  delete state_block;
  delete internal_dyn_context;
}

void Zorba_XQueryExecution::setAlertsParam(void *alert_callback_param)
{
  this->alert_callback_param = alert_callback_param;
}

/*
  next() should be called in the same thread where the xquery was called execute()
*/
Item_t Zorba_XQueryExecution::next()
{
  if (theClosed)
  {
    return NULL;
  }

  state_block->zorp->current_xquery = state_block->xqbinary;
  state_block->zorp->current_xqueryresult = this;

  try{

  Item_t it = it_result->produceNext( *state_block );

  state_block->zorp->current_xquery = NULL;
  state_block->zorp->current_xqueryresult = NULL;

  return it;
  }
  catch(xqp_exception &)
  {
    is_error = true;
    state_block->zorp->current_xquery = NULL;
    state_block->zorp->current_xqueryresult = NULL;
    return NULL;
  }
  catch(...)
  {
    state_block->zorp->current_xquery = NULL;
    state_block->zorp->current_xqueryresult = NULL;
    throw;
  }

  return NULL;
}

void
Zorba_XQueryExecution::reset()
{
  state_block->zorp->current_xquery = state_block->xqbinary;
  state_block->zorp->current_xqueryresult = this;
	try{
  if (!theClosed)
    it_result->reset(*state_block);
	}
  catch(xqp_exception &)
	{
	}
  is_error = false;
  state_block->zorp->current_xquery = NULL;
  state_block->zorp->current_xqueryresult = NULL;
}

void
Zorba_XQueryExecution::close()
{
  state_block->zorp->current_xquery = state_block->xqbinary;
  state_block->zorp->current_xqueryresult = this;
	try
  {
    if (!theClosed)
    {
      it_result->releaseResources(*state_block); 
      //delete theStateBlock;
      theClosed = true;
    }
	}
  catch(xqp_exception &)
	{
	}
  is_error = false;
  state_block->zorp->current_xquery = NULL;
  state_block->zorp->current_xqueryresult = NULL;
}

ostream& Zorba_XQueryExecution::serialize( ostream& os )
{
  serializer *ser;
	try{
    ser = ZORBA_FOR_CURRENT_THREAD()->getDocSerializer();

  ser->serialize(this, os);
	}
  catch(xqp_exception &)
  {
	}
  return os;
}

std::ostream& Zorba_XQueryExecution::serializeXML( std::ostream& os )
{
  serializer *ser = new serializer;

	try{
  ser->serialize(this, os);
  delete ser;
	}
  catch(xqp_exception &)
  {
		delete ser;
	}
  return os;
}

std::ostream& Zorba_XQueryExecution::serializeHTML( std::ostream& os )
{
  serializer *ser = new serializer;
	try{
  ser->set_parameter("method", "html");
  ser->serialize(this, os);
  delete ser;
	}
  catch(xqp_exception &)
  {
		delete ser;
	}
  return os;
}

std::ostream& Zorba_XQueryExecution::serializeTEXT( std::ostream& os )
{
	try{
  Item_t    it;

  while(1)
  {
    it = next();
    if(!it.get_ptr())
      break;
    os << it->show() << endl;
  }
	}
  catch(xqp_exception &)
  {
	}
  return os;
}


bool Zorba_XQueryExecution::isError()
{
  return is_error;
}

void  Zorba_XQueryExecution::AbortQueryExecution()
{
  ZORBA_ERROR_ALERT(AlertCodes::XQP0015_SYSTEM_NOT_YET_IMPLEMENTED,
                    NULL,
                    true,///continue execution
                    "AbortQueryExecution"
                    );
}

/*extension from dynamic context (specific only for this execution)
bind external variable with the result from another xquery
*/
bool Zorba_XQueryExecution::SetVariable( xqp_string varname, 
                                        XQueryExecution_t item_iter )
{
	try{

  ///add to dynamic context
  if(!internal_dyn_context)
    internal_dyn_context = new dynamic_context;
  xqp_string    expanded_name;
  expanded_name = internal_dyn_context->expand_varname(state_block->xqbinary->internal_sctx, varname);
  internal_dyn_context->add_variable(expanded_name, item_iter.get_ptr());

  return true;
	}
  catch(xqp_exception &)
  {
		return false;
  }
  return false;
}

bool Zorba_XQueryExecution::SetVariable( xqp_string varname, 
																				std::istream &is )
{
	SingletonIterator		*one_item_iterator = NULL;
	PlanWrapper					*iterator_plus_state = NULL;
	try{

  if(!internal_dyn_context)
    internal_dyn_context = new dynamic_context;
  xqp_string    expanded_name;
  expanded_name = internal_dyn_context->expand_varname(state_block->xqbinary->internal_sctx, varname);

	///load the whole xml content from stream into store
  SimpleStore& store = GET_STORE();
	XmlLoader& loader = store.getXmlLoader();
  Item_t doc_item;
  doc_item = loader.loadXml(is);//consume the stream
	if(doc_item.isNull())
		return false;

	one_item_iterator = new SingletonIterator(Zorba::null_loc, doc_item);
	PlanIter_t		iter_t(one_item_iterator);
	iterator_plus_state = new PlanWrapper(iter_t);

	internal_dyn_context->add_variable(expanded_name, iterator_plus_state);

	return true;
	}
  catch(xqp_exception &)
  {
		delete one_item_iterator;
		delete iterator_plus_state;
		return false;
  }
  return false;
}

///register documents available through fn:doc() in xquery
bool Zorba_XQueryExecution::AddAvailableDocument(xqp_string docURI,
                                                Item_t docitem)
{
  ///add to dynamic context
	try{
  return false;
	}
  catch(xqp_exception &)
  {
		return false;
	}
	return false;
}

///register collections available through fn:collection() in xquery
///default collection has empty URI ""
bool Zorba_XQueryExecution::AddAvailableCollection(xqp_string collectionURI,
                                                  Collection_t collection)
{
  ///add to dynamic context
	try{
  return false;
	}
  catch(xqp_exception &)
  {
		return false;
	}
	return false;
}


}///end namespace xqp

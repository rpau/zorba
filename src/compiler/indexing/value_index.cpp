/*
 * Copyright 2006-2008 The FLWOR Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <algorithm>

#include "types/typeops.h"

#include "functions/function.h"

#include "compiler/indexing/value_index.h"
#include "compiler/api/compilercb.h"
#include "compiler/expression/flwor_expr.h"
#include "compiler/expression/fo_expr.h"
#include "compiler/expression/expr.h"
#include "compiler/codegen/plan_visitor.h"

#include "runtime/base/plan_iterator.h"

namespace zorba 
{

SERIALIZABLE_CLASS_VERSIONS(ValueIndex)
END_SERIALIZABLE_CLASS_VERSIONS(ValueIndex)


ValueIndex::ValueIndex(
    CompilerCB* ccb,
    const QueryLoc& loc,
    const store::Item_t& name)
  :
  theSctx(ccb->theRootSctx),
  theName(name),
  theIsUnique(false),
  theIsTemp(false),
  theIsAutomatic(false),
  theMethod(HASH),
  theDomainClause(new for_clause(ccb->m_cur_sctx, loc, NULL, NULL))
{ 
}
  

ValueIndex::ValueIndex(::zorba::serialization::Archiver& ar)
  :
  SimpleRCObject(ar)
{
}


void ValueIndex::serialize(::zorba::serialization::Archiver& ar)
{
  ar & theSctx;
  ar & theName;
  ar & theIsUnique;
  ar & theIsTemp;
  ar & theIsAutomatic;
  SERIALIZE_ENUM(index_method_t, theMethod);
  ar & theDomainClause;
  ar & theKeyExprs;
  ar & theKeyTypes;
  ar & theOrderModifiers;
  ar & m_creatorPatterns;
}


ValueIndex::~ValueIndex()
{
}


store::Item* ValueIndex::getName() const
{
  return theName.getp();
}


expr* ValueIndex::getDomainExpr() const 
{
  return theDomainClause->get_expr();
}


void ValueIndex::setDomainExpr(expr_t domainExpr) 
{
  theDomainClause->set_expr(domainExpr);
}


var_expr* ValueIndex::getDomainVariable() const 
{
  return theDomainClause->get_var();
}


void ValueIndex::setDomainVariable(var_expr_t domainVar)
{
  theDomainClause->set_var(domainVar);
}


const var_expr* ValueIndex::getDomainPositionVariable() const 
{
  return theDomainClause->get_pos_var();
}


void ValueIndex::setDomainPositionVariable(var_expr_t domainPosVar) 
{
  theDomainClause->set_pos_var(domainPosVar);
}


const std::vector<expr_t>& ValueIndex::getKeyExpressions() const 
{
  return theKeyExprs; 
}


void ValueIndex::setKeyExpressions(const std::vector<expr_t>& keyExprs) 
{
  theKeyExprs = keyExprs;
}


const std::vector<xqtref_t>& ValueIndex::getKeyTypes() const 
{
  return theKeyTypes; 
}


void ValueIndex::setKeyTypes(const std::vector<xqtref_t>& keyTypes) 
{
  theKeyTypes = keyTypes;
}


const std::vector<OrderModifier>& ValueIndex::getOrderModifiers() const
{
  return theOrderModifiers;
}


void ValueIndex::setOrderModifiers(const std::vector<OrderModifier>& modifiers)
{
  theOrderModifiers = modifiers;
}


/*******************************************************************************
  Check that the doman expr 
  (a) is deterministic,
  (b) does not have any free variables,
  (c) does not reference any input functions other than dc:collection()
  (d) the arg to each dc:collection is a const qname 
********************************************************************************/
void ValueIndex::analyze()
{
  std::vector<const var_expr*> varExprs;

  analyzeExprInternal(getDomainExpr(), theSources, varExprs);

  varExprs.clear();

  ulong numKeys = theKeyExprs.size();

  for (ulong i = 0; i < numKeys; ++i)
  {
    analyzeExprInternal(theKeyExprs[i].getp(), theSources, varExprs);
  }
}


void ValueIndex::analyzeExprInternal(
    const expr* e,
    std::vector<const store::Item*>& sources,
    std::vector<const var_expr*>& varExprs)
{
  if (e->get_expr_kind() == fo_expr_kind)
  {
    const fo_expr* foExpr = static_cast<const fo_expr*>(e);
    const function* func = foExpr->get_func();

    if (!func->isDeterministic())
    {
      ZORBA_ERROR_LOC_PARAM(XQP0042_INDEX_NOT_DETERMINISTIC, e->get_loc(),
                            theName->getStringValue()->c_str(), "");
    }

    if (func->isSource())
    {
      bool valid = false;

      if (func->getKind() == FunctionConsts::FN_ZORBA_COLLECTION_1)
      {
        TypeManager* tm = theSctx->get_typemanager();

        const expr* argExpr = foExpr->get_arg(0);
        const const_expr* qnameExpr = dynamic_cast<const const_expr*>(argExpr);

        if (qnameExpr != NULL)
        {
          xqtref_t valueType = tm->create_value_type(qnameExpr->get_val());

          if (TypeOps::is_subtype(*valueType, *GENV_TYPESYSTEM.QNAME_TYPE_ONE) &&
              theSctx->lookup_collection(qnameExpr->get_val()))
          {
            sources.push_back(qnameExpr->get_val());
            valid = true;
          }
        }
        else if (argExpr->get_expr_kind() == promote_expr_kind)
        {
          const promote_expr* promoteExpr = static_cast<const promote_expr*>(argExpr);

          argExpr = promoteExpr->get_input();
          const fo_expr* dataExpr = dynamic_cast<const fo_expr*>(argExpr);

          if (dataExpr != NULL &&
              dataExpr->get_func()->getKind() == FunctionConsts::FN_DATA_1)
          {
            argExpr = dataExpr->get_arg(0);
            const const_expr* qnameExpr = dynamic_cast<const const_expr*>(argExpr);

            if (qnameExpr != NULL)
            {
              xqtref_t valueType = tm->create_value_type(qnameExpr->get_val());

              if (TypeOps::is_subtype(*valueType, *GENV_TYPESYSTEM.QNAME_TYPE_ONE) &&
                  theSctx->lookup_collection(qnameExpr->get_val()))
              {
                sources.push_back(qnameExpr->get_val());
                valid = true;
              }
            }
          }
        }
      }

      if (!valid)
      {
        ZORBA_ERROR_LOC_PARAM(XQP0041_INDEX_HAS_INVALID_DATA_SOURCE, e->get_loc(),
                              theName->getStringValue()->c_str(), "");
      }
    }
    else if (func->getKind() == FunctionConsts::OP_VAR_DECLARE_1)
    {
      const const_expr* qnameExpr = dynamic_cast<const const_expr*>(foExpr->get_arg(0));
      ZORBA_ASSERT(qnameExpr != NULL);
      const store::Item* qname = qnameExpr->get_val();

      const var_expr* varExpr = static_cast<const var_expr*>(theSctx->lookup_var(qname));
      ZORBA_ASSERT(varExpr->get_kind() == var_expr::local_var);

      varExprs.push_back(varExpr);
    }
  }
  else if (e->get_expr_kind() == flwor_expr_kind ||
           e->get_expr_kind() == gflwor_expr_kind)
  {
    static_cast<const flwor_expr*>(e)->get_vars_defined(varExprs);
  }
  else if (e->get_expr_kind() == var_expr_kind)
  {
    if (e != getDomainVariable() &&
        std::find(varExprs.begin(), varExprs.end(), e) == varExprs.end())
    {
      ZORBA_ERROR_LOC_PARAM(XQP0040_INDEX_HAS_FREE_VARS, e->get_loc(),
                            theName->getStringValue()->c_str(), "");
    }
  }

  for(const_expr_iterator i = e->expr_begin_const(); !i.done(); ++i) 
  {
    analyzeExprInternal((*i), sources, varExprs);
  }
}



/*******************************************************************************

********************************************************************************/
expr* ValueIndex::getBuildExpr(CompilerCB* topCCB, const QueryLoc& loc)
{ 
  if (theBuildExpr != NULL)
    return theBuildExpr.getp();

  expr* domainExpr = getDomainExpr();
  const var_expr* dot = getDomainVariable();
  const var_expr* pos = getDomainPositionVariable();

  short sctxid = domainExpr->get_sctx_id();
  static_context* sctx = topCCB->getStaticContext(sctxid);

  //
  // Create FOR clause:
  // for $$dot at $$pos in domain_expr
  //
  expr::substitution_t subst;
  
  expr_t newdom = domainExpr->clone(subst);
  
  var_expr_t newdot = new var_expr(sctxid,
                                   dot->get_loc(),
                                   dot->get_kind(),
                                   dot->get_varname());
  var_expr_t newpos = new var_expr(sctxid,
                                   pos->get_loc(),
                                   pos->get_kind(),
                                   pos->get_varname());
  subst[dot] = newdot;
  subst[pos] = newpos;

  for_clause* fc = new for_clause(sctxid,
                                  dot->get_loc(),
                                  newdot,
                                  newdom,
                                  newpos);
  newdot->set_flwor_clause(fc);
  newpos->set_flwor_clause(fc);
  
  //
  // Create RETURN clause:
  // return index-entry-builder($$dot, field1_expr, ..., fieldN_expr)
  //
  function* f = sctx->lookup_resolved_fn(ZORBA_DDL_FN_NS,
                                         "index-entry-builder",
                                         VARIADIC_SIG_SIZE);

  expr_t domainVarExpr(new wrapper_expr(sctxid, loc, newdot.getp()));

  ulong n = theKeyExprs.size();
  std::vector<expr_t> foArgs(n+1);
  
  foArgs[0] = domainVarExpr;

  for(ulong i = 0; i < n; ++i) 
  {
    foArgs[i+1] = theKeyExprs[i]->clone(subst);
  }
  
  fo_expr_t returnExpr =  new fo_expr(sctxid, loc, f, foArgs);

  //
  // Create flwor_expr with the above FOR and RETURN clauses.
  //
  flwor_expr* flworExpr = new flwor_expr(sctxid, loc, false);
  theBuildExpr = flworExpr;
  flworExpr->set_return_expr(returnExpr.getp());
  flworExpr->add_clause(fc);

  std::string msg = "build expr for index " + theName->getStringValue()->str();

  if (topCCB->theConfig.optimize_cb != NULL)
    topCCB->theConfig.optimize_cb(theBuildExpr.getp(), msg);

  return theBuildExpr.getp();
}


/*******************************************************************************

********************************************************************************/
PlanIterator* ValueIndex::getBuildPlan(CompilerCB* topCCB, const QueryLoc& loc)
{ 
  if (theBuildPlan != NULL)
    return theBuildPlan.getp();

  expr* buildExpr = getBuildExpr(topCCB, loc);

  theBuildPlan = codegen("index", buildExpr, topCCB);

  return theBuildPlan.getp();
}


}
/* vim:set ts=2 sw=2: */

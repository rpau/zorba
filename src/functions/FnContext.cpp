/*
 *  Copyright 2006-2007 FLWOR Foundation.
 *  Authors: Tim Kraska
 */

#include "functions/FnContext.h"
#include "system/globalenv.h"
#include "runtime/fncontext/FnContextImpl.h"
#include "runtime/core/item_iterator.h"
#include "store/api/iterator.h"

namespace zorba
{

ctx_variable::ctx_variable ( const signature& sig )
  :
  function ( sig )
{
}


PlanIter_t ctx_variable::codegen (const QueryLoc& loc, std::vector<PlanIter_t>& argv, AnnotationHolder &ann ) const
{
  xqpStringStore_t varName = argv[0].cast<SingletonIterator>()->getValue()->getStringValue();
  return new CtxVariableIterator(loc, varName);
}


xqtref_t ctx_variable::type_check(signature& sig) const
{
  return GENV_TYPESYSTEM.BOOLEAN_TYPE_ONE;
}

/* end class CtxVariable */
}

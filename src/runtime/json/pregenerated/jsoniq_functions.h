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
 
// ******************************************
// *                                        *
// * THIS IS A GENERATED FILE. DO NOT EDIT! *
// * SEE .xml FILE WITH SAME NAME           *
// *                                        *
// ******************************************
#ifndef ZORBA_RUNTIME_JSON_JSONIQ_FUNCTIONS_H
#define ZORBA_RUNTIME_JSON_JSONIQ_FUNCTIONS_H


#include "common/shared_types.h"
#include "runtime/base/unarybase.h"
#include "runtime/base/binarybase.h"
#include "runtime/base/noarybase.h"
#include "runtime/base/narybase.h"


namespace zorba {

#ifdef ZORBA_WITH_JSON
/**
 * 
 * Author: 
 */
class JSONParseIterator : public NaryBaseIterator<JSONParseIterator, PlanIteratorState>
{ 
protected:
  QueryLoc theRelativeLocation; //
public:
  SERIALIZABLE_CLASS(JSONParseIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONParseIterator,
    NaryBaseIterator<JSONParseIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar)
  {
    serialize_baseclass(ar,
    (NaryBaseIterator<JSONParseIterator, PlanIteratorState>*)this);

    ar & theRelativeLocation;
  }

  JSONParseIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children,
    QueryLoc aRelativeLocation)
    : 
    NaryBaseIterator<JSONParseIterator, PlanIteratorState>(sctx, loc, children),
    theRelativeLocation(aRelativeLocation)
  {}

  virtual ~JSONParseIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 * Author: 
 */
class JSONObjectNamesIteratorState : public PlanIteratorState
{
public:
  store::Iterator_t thePairs; //

  JSONObjectNamesIteratorState();

  ~JSONObjectNamesIteratorState();

  void init(PlanState&);
  void reset(PlanState&);
};

class JSONObjectNamesIterator : public UnaryBaseIterator<JSONObjectNamesIterator, JSONObjectNamesIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONObjectNamesIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONObjectNamesIterator,
    UnaryBaseIterator<JSONObjectNamesIterator, JSONObjectNamesIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar)
  {
    serialize_baseclass(ar,
    (UnaryBaseIterator<JSONObjectNamesIterator, JSONObjectNamesIteratorState>*)this);
  }

  JSONObjectNamesIterator(
    static_context* sctx,
    const QueryLoc& loc,
    PlanIter_t& child)
    : 
    UnaryBaseIterator<JSONObjectNamesIterator, JSONObjectNamesIteratorState>(sctx, loc, child)
  {}

  virtual ~JSONObjectNamesIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 * Author: 
 */
class JSONObjectValuesIteratorState : public PlanIteratorState
{
public:
  store::Iterator_t thePairs; //

  JSONObjectValuesIteratorState();

  ~JSONObjectValuesIteratorState();

  void init(PlanState&);
  void reset(PlanState&);
};

class JSONObjectValuesIterator : public UnaryBaseIterator<JSONObjectValuesIterator, JSONObjectValuesIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONObjectValuesIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONObjectValuesIterator,
    UnaryBaseIterator<JSONObjectValuesIterator, JSONObjectValuesIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar)
  {
    serialize_baseclass(ar,
    (UnaryBaseIterator<JSONObjectValuesIterator, JSONObjectValuesIteratorState>*)this);
  }

  JSONObjectValuesIterator(
    static_context* sctx,
    const QueryLoc& loc,
    PlanIter_t& child)
    : 
    UnaryBaseIterator<JSONObjectValuesIterator, JSONObjectValuesIteratorState>(sctx, loc, child)
  {}

  virtual ~JSONObjectValuesIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 * Author: 
 */
class JSONObjectValueIterator : public BinaryBaseIterator<JSONObjectValueIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONObjectValueIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONObjectValueIterator,
    BinaryBaseIterator<JSONObjectValueIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar)
  {
    serialize_baseclass(ar,
    (BinaryBaseIterator<JSONObjectValueIterator, PlanIteratorState>*)this);
  }

  JSONObjectValueIterator(
    static_context* sctx,
    const QueryLoc& loc,
    PlanIter_t& child1, PlanIter_t& child2)
    : 
    BinaryBaseIterator<JSONObjectValueIterator, PlanIteratorState>(sctx, loc, child1, child2)
  {}

  virtual ~JSONObjectValueIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 * Author: 
 */
class JSONArraySizeIterator : public UnaryBaseIterator<JSONArraySizeIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONArraySizeIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONArraySizeIterator,
    UnaryBaseIterator<JSONArraySizeIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar)
  {
    serialize_baseclass(ar,
    (UnaryBaseIterator<JSONArraySizeIterator, PlanIteratorState>*)this);
  }

  JSONArraySizeIterator(
    static_context* sctx,
    const QueryLoc& loc,
    PlanIter_t& child)
    : 
    UnaryBaseIterator<JSONArraySizeIterator, PlanIteratorState>(sctx, loc, child)
  {}

  virtual ~JSONArraySizeIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 * Author: 
 */
class JSONArrayMemberIterator : public BinaryBaseIterator<JSONArrayMemberIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONArrayMemberIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONArrayMemberIterator,
    BinaryBaseIterator<JSONArrayMemberIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar)
  {
    serialize_baseclass(ar,
    (BinaryBaseIterator<JSONArrayMemberIterator, PlanIteratorState>*)this);
  }

  JSONArrayMemberIterator(
    static_context* sctx,
    const QueryLoc& loc,
    PlanIter_t& child1, PlanIter_t& child2)
    : 
    BinaryBaseIterator<JSONArrayMemberIterator, PlanIteratorState>(sctx, loc, child1, child2)
  {}

  virtual ~JSONArrayMemberIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 * Author: 
 */
class JSONArrayMembersIteratorState : public PlanIteratorState
{
public:
  store::Iterator_t theMembers; //

  JSONArrayMembersIteratorState();

  ~JSONArrayMembersIteratorState();

  void init(PlanState&);
  void reset(PlanState&);
};

class JSONArrayMembersIterator : public UnaryBaseIterator<JSONArrayMembersIterator, JSONArrayMembersIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONArrayMembersIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONArrayMembersIterator,
    UnaryBaseIterator<JSONArrayMembersIterator, JSONArrayMembersIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar)
  {
    serialize_baseclass(ar,
    (UnaryBaseIterator<JSONArrayMembersIterator, JSONArrayMembersIteratorState>*)this);
  }

  JSONArrayMembersIterator(
    static_context* sctx,
    const QueryLoc& loc,
    PlanIter_t& child)
    : 
    UnaryBaseIterator<JSONArrayMembersIterator, JSONArrayMembersIteratorState>(sctx, loc, child)
  {}

  virtual ~JSONArrayMembersIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 *    jsoniq:flatten function
 *  
 * Author: Zorba Team
 */
class JSONArrayFlattenIteratorState : public PlanIteratorState
{
public:
  std::stack<store::Iterator_t> theStack; //

  JSONArrayFlattenIteratorState();

  ~JSONArrayFlattenIteratorState();

  void init(PlanState&);
  void reset(PlanState&);
};

class JSONArrayFlattenIterator : public UnaryBaseIterator<JSONArrayFlattenIterator, JSONArrayFlattenIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONArrayFlattenIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONArrayFlattenIterator,
    UnaryBaseIterator<JSONArrayFlattenIterator, JSONArrayFlattenIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar)
  {
    serialize_baseclass(ar,
    (UnaryBaseIterator<JSONArrayFlattenIterator, JSONArrayFlattenIteratorState>*)this);
  }

  JSONArrayFlattenIterator(
    static_context* sctx,
    const QueryLoc& loc,
    PlanIter_t& child)
    : 
    UnaryBaseIterator<JSONArrayFlattenIterator, JSONArrayFlattenIteratorState>(sctx, loc, child)
  {}

  virtual ~JSONArrayFlattenIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 * Author: 
 */
class JSONItemAccessorIterator : public BinaryBaseIterator<JSONItemAccessorIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONItemAccessorIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONItemAccessorIterator,
    BinaryBaseIterator<JSONItemAccessorIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar)
  {
    serialize_baseclass(ar,
    (BinaryBaseIterator<JSONItemAccessorIterator, PlanIteratorState>*)this);
  }

  JSONItemAccessorIterator(
    static_context* sctx,
    const QueryLoc& loc,
    PlanIter_t& child1, PlanIter_t& child2)
    : 
    BinaryBaseIterator<JSONItemAccessorIterator, PlanIteratorState>(sctx, loc, child1, child2)
  {}

  virtual ~JSONItemAccessorIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 * Author: 
 */
class JSONItemEmptyAccessorIteratorState : public PlanIteratorState
{
public:
  store::Iterator_t thePairs; //

  JSONItemEmptyAccessorIteratorState();

  ~JSONItemEmptyAccessorIteratorState();

  void init(PlanState&);
  void reset(PlanState&);
};

class JSONItemEmptyAccessorIterator : public UnaryBaseIterator<JSONItemEmptyAccessorIterator, JSONItemEmptyAccessorIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONItemEmptyAccessorIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONItemEmptyAccessorIterator,
    UnaryBaseIterator<JSONItemEmptyAccessorIterator, JSONItemEmptyAccessorIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar)
  {
    serialize_baseclass(ar,
    (UnaryBaseIterator<JSONItemEmptyAccessorIterator, JSONItemEmptyAccessorIteratorState>*)this);
  }

  JSONItemEmptyAccessorIterator(
    static_context* sctx,
    const QueryLoc& loc,
    PlanIter_t& child)
    : 
    UnaryBaseIterator<JSONItemEmptyAccessorIterator, JSONItemEmptyAccessorIteratorState>(sctx, loc, child)
  {}

  virtual ~JSONItemEmptyAccessorIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 * Author: 
 */
class JSONNullIterator : public NoaryBaseIterator<JSONNullIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONNullIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONNullIterator,
    NoaryBaseIterator<JSONNullIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar)
  {
    serialize_baseclass(ar,
    (NoaryBaseIterator<JSONNullIterator, PlanIteratorState>*)this);
  }

  JSONNullIterator(
    static_context* sctx,
    const QueryLoc& loc)
    : 
    NoaryBaseIterator<JSONNullIterator, PlanIteratorState>(sctx, loc)
  {}

  virtual ~JSONNullIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 *      json:insert-as-first
 *    
 * Author: Zorba Team
 */
class JSONInsertAsFirstIterator : public NaryBaseIterator<JSONInsertAsFirstIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONInsertAsFirstIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONInsertAsFirstIterator,
    NaryBaseIterator<JSONInsertAsFirstIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar)
  {
    serialize_baseclass(ar,
    (NaryBaseIterator<JSONInsertAsFirstIterator, PlanIteratorState>*)this);
  }

  JSONInsertAsFirstIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<JSONInsertAsFirstIterator, PlanIteratorState>(sctx, loc, children)
  {}

  virtual ~JSONInsertAsFirstIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 *      json:insert-after
 *    
 * Author: Zorba Team
 */
class JSONInsertAfterIterator : public NaryBaseIterator<JSONInsertAfterIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONInsertAfterIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONInsertAfterIterator,
    NaryBaseIterator<JSONInsertAfterIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar)
  {
    serialize_baseclass(ar,
    (NaryBaseIterator<JSONInsertAfterIterator, PlanIteratorState>*)this);
  }

  JSONInsertAfterIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<JSONInsertAfterIterator, PlanIteratorState>(sctx, loc, children)
  {}

  virtual ~JSONInsertAfterIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 *      json:insert-before
 *    
 * Author: Zorba Team
 */
class JSONInsertBeforeIterator : public NaryBaseIterator<JSONInsertBeforeIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONInsertBeforeIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONInsertBeforeIterator,
    NaryBaseIterator<JSONInsertBeforeIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar)
  {
    serialize_baseclass(ar,
    (NaryBaseIterator<JSONInsertBeforeIterator, PlanIteratorState>*)this);
  }

  JSONInsertBeforeIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<JSONInsertBeforeIterator, PlanIteratorState>(sctx, loc, children)
  {}

  virtual ~JSONInsertBeforeIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 *      json:insert-as-last
 *    
 * Author: Zorba Team
 */
class JSONInsertAsLastIterator : public NaryBaseIterator<JSONInsertAsLastIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONInsertAsLastIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONInsertAsLastIterator,
    NaryBaseIterator<JSONInsertAsLastIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar)
  {
    serialize_baseclass(ar,
    (NaryBaseIterator<JSONInsertAsLastIterator, PlanIteratorState>*)this);
  }

  JSONInsertAsLastIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<JSONInsertAsLastIterator, PlanIteratorState>(sctx, loc, children)
  {}

  virtual ~JSONInsertAsLastIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 *      json:delete-member
 *    
 * Author: Zorba Team
 */
class JSONDeleteIterator : public NaryBaseIterator<JSONDeleteIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONDeleteIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONDeleteIterator,
    NaryBaseIterator<JSONDeleteIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar)
  {
    serialize_baseclass(ar,
    (NaryBaseIterator<JSONDeleteIterator, PlanIteratorState>*)this);
  }

  JSONDeleteIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<JSONDeleteIterator, PlanIteratorState>(sctx, loc, children)
  {}

  virtual ~JSONDeleteIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 *      json:rename
 *    
 * Author: Zorba Team
 */
class JSONRenameIterator : public NaryBaseIterator<JSONRenameIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONRenameIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONRenameIterator,
    NaryBaseIterator<JSONRenameIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar)
  {
    serialize_baseclass(ar,
    (NaryBaseIterator<JSONRenameIterator, PlanIteratorState>*)this);
  }

  JSONRenameIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<JSONRenameIterator, PlanIteratorState>(sctx, loc, children)
  {}

  virtual ~JSONRenameIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 *      json:replace-value
 *    
 * Author: Zorba Team
 */
class JSONReplaceValueIterator : public NaryBaseIterator<JSONReplaceValueIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONReplaceValueIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONReplaceValueIterator,
    NaryBaseIterator<JSONReplaceValueIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar)
  {
    serialize_baseclass(ar,
    (NaryBaseIterator<JSONReplaceValueIterator, PlanIteratorState>*)this);
  }

  JSONReplaceValueIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<JSONReplaceValueIterator, PlanIteratorState>(sctx, loc, children)
  {}

  virtual ~JSONReplaceValueIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

}
#endif
/*
 * Local variables:
 * mode: c++
 * End:
 */ 

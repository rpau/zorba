/*
 * Copyright 2006-2012 The FLWOR Foundation.
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
#include <context/uri_resolver.h>
#include "runtime/json/json_loader.h"


namespace zorba {

#ifdef ZORBA_WITH_JSON
/**
 * 
 * Author: 
 */
class JSONDecodeFromRoundtripIteratorState : public PlanIteratorState
{
public:
  zstring thePrefix; //

  JSONDecodeFromRoundtripIteratorState();

  ~JSONDecodeFromRoundtripIteratorState();

  void init(PlanState&);
  void reset(PlanState&);
};

class JSONDecodeFromRoundtripIterator : public NaryBaseIterator<JSONDecodeFromRoundtripIterator, JSONDecodeFromRoundtripIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONDecodeFromRoundtripIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONDecodeFromRoundtripIterator,
    NaryBaseIterator<JSONDecodeFromRoundtripIterator, JSONDecodeFromRoundtripIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

  JSONDecodeFromRoundtripIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<JSONDecodeFromRoundtripIterator, JSONDecodeFromRoundtripIteratorState>(sctx, loc, children)
  {}

  virtual ~JSONDecodeFromRoundtripIterator();

public:
  static void extractChildOfKind(const store::Item_t& aParent, const store::NodeKind& aKind, store::Item_t& aChild);
  bool decodeNode(const store::Item_t& aSerializedNode, const store::NodeKind& aKind, store::Item_t& aResult) const;
  bool decodeXDM(const store::Item_t& anObj, store::Item_t& aResult, JSONDecodeFromRoundtripIteratorState* aState) const;
  bool decodeObject(const store::Item_t& anObj, store::Item_t& aResult, JSONDecodeFromRoundtripIteratorState* aState) const;
  bool decodeArray(const store::Item_t& anArray, store::Item_t& aResult, JSONDecodeFromRoundtripIteratorState* aState) const;
  bool decodeItem(const store::Item_t& anItem, store::Item_t& aResult, JSONDecodeFromRoundtripIteratorState* aState) const;
  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 * Author: 
 */
class JSONEncodeForRoundtripIteratorState : public PlanIteratorState
{
public:
  zstring thePrefix; //
  store::Item_t theSerParams; //
  XQueryDiagnostics* theDiag; //

  JSONEncodeForRoundtripIteratorState();

  ~JSONEncodeForRoundtripIteratorState();

  void init(PlanState&);
  void reset(PlanState&);
};

class JSONEncodeForRoundtripIterator : public NaryBaseIterator<JSONEncodeForRoundtripIterator, JSONEncodeForRoundtripIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONEncodeForRoundtripIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONEncodeForRoundtripIterator,
    NaryBaseIterator<JSONEncodeForRoundtripIterator, JSONEncodeForRoundtripIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

  JSONEncodeForRoundtripIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<JSONEncodeForRoundtripIterator, JSONEncodeForRoundtripIteratorState>(sctx, loc, children)
  {}

  virtual ~JSONEncodeForRoundtripIterator();

public:
  bool encodeObject(const store::Item_t& anObj, store::Item_t& aResult, JSONEncodeForRoundtripIteratorState* aState) const;
  bool encodeArray(const store::Item_t& anArray, store::Item_t& aResult, JSONEncodeForRoundtripIteratorState* aState) const;
  bool encodeAtomic(const store::Item_t& aValue, store::Item_t& aResult, JSONEncodeForRoundtripIteratorState* aState) const;
  bool encodeNode(const store::Item_t& aNode, store::Item_t& aResult, JSONEncodeForRoundtripIteratorState* aState) const;
  bool encodeItem(const store::Item_t& anItem, store::Item_t& aResult, JSONEncodeForRoundtripIteratorState* aState) const;
  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 * Author: 
 */
class JSONParseIteratorState : public PlanIteratorState
{
public:
  bool theAllowMultiple; //
  store::Item_t theInput; //
  std::istream* theInputStream; //
  bool theGotOne; //
  json::loader* loader_; //

  JSONParseIteratorState();

  ~JSONParseIteratorState();

  void init(PlanState&);
  void reset(PlanState&);
};

class JSONParseIterator : public NaryBaseIterator<JSONParseIterator, JSONParseIteratorState>
{ 
protected:
  QueryLoc theRelativeLocation; //
public:
  SERIALIZABLE_CLASS(JSONParseIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONParseIterator,
    NaryBaseIterator<JSONParseIterator, JSONParseIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

  JSONParseIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children,
    QueryLoc aRelativeLocation)
    : 
    NaryBaseIterator<JSONParseIterator, JSONParseIteratorState>(sctx, loc, children),
    theRelativeLocation(aRelativeLocation)
  {}

  virtual ~JSONParseIterator();

public:
  bool processBooleanOption(const store::Item_t& options, char const* option_name, bool* option_value) const;
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
  store::Iterator_t theNames; //

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

  void serialize( ::zorba::serialization::Archiver& ar);

  JSONObjectNamesIterator(
    static_context* sctx,
    const QueryLoc& loc,
    PlanIter_t& child)
    : 
    UnaryBaseIterator<JSONObjectNamesIterator, JSONObjectNamesIteratorState>(sctx, loc, child)
  {}

  virtual ~JSONObjectNamesIterator();

public:
  bool count(store::Item_t& result, PlanState& planState) const;
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

  void serialize( ::zorba::serialization::Archiver& ar);

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
class JSONObjectProjectIterator : public BinaryBaseIterator<JSONObjectProjectIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONObjectProjectIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONObjectProjectIterator,
    BinaryBaseIterator<JSONObjectProjectIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

  JSONObjectProjectIterator(
    static_context* sctx,
    const QueryLoc& loc,
    PlanIter_t& child1, PlanIter_t& child2)
    : 
    BinaryBaseIterator<JSONObjectProjectIterator, PlanIteratorState>(sctx, loc, child1, child2)
  {}

  virtual ~JSONObjectProjectIterator();

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

  void serialize( ::zorba::serialization::Archiver& ar);

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

  void serialize( ::zorba::serialization::Archiver& ar);

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

  void serialize( ::zorba::serialization::Archiver& ar);

  JSONArrayMembersIterator(
    static_context* sctx,
    const QueryLoc& loc,
    PlanIter_t& child)
    : 
    UnaryBaseIterator<JSONArrayMembersIterator, JSONArrayMembersIteratorState>(sctx, loc, child)
  {}

  virtual ~JSONArrayMembersIterator();

public:
  bool count(store::Item_t& result, PlanState& planState) const;
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

  void serialize( ::zorba::serialization::Archiver& ar);

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
 * jn:json-doc
 * Author: Zorba Team
 */
class JSONDocIteratorState : public PlanIteratorState
{
public:
  std::auto_ptr<internal::Resource> theResource; //
  std::istream* theStream; //
  bool theGotOne; //
  json::loader* loader_; //

  JSONDocIteratorState();

  ~JSONDocIteratorState();

  void init(PlanState&);
  void reset(PlanState&);
};

class JSONDocIterator : public NaryBaseIterator<JSONDocIterator, JSONDocIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONDocIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONDocIterator,
    NaryBaseIterator<JSONDocIterator, JSONDocIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

  JSONDocIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<JSONDocIterator, JSONDocIteratorState>(sctx, loc, children)
  {}

  virtual ~JSONDocIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 * Author: 
 */
class JSONItemAccessorIteratorState : public PlanIteratorState
{
public:
  store::Iterator_t theIterator; //

  JSONItemAccessorIteratorState();

  ~JSONItemAccessorIteratorState();

  void init(PlanState&);
  void reset(PlanState&);
};

class JSONItemAccessorIterator : public NaryBaseIterator<JSONItemAccessorIterator, JSONItemAccessorIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONItemAccessorIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONItemAccessorIterator,
    NaryBaseIterator<JSONItemAccessorIterator, JSONItemAccessorIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

  JSONItemAccessorIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<JSONItemAccessorIterator, JSONItemAccessorIteratorState>(sctx, loc, children)
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
class JSONNullIterator : public NoaryBaseIterator<JSONNullIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONNullIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONNullIterator,
    NoaryBaseIterator<JSONNullIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

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
 * Author: 
 */
class JSONIsNullIterator : public UnaryBaseIterator<JSONIsNullIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONIsNullIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONIsNullIterator,
    UnaryBaseIterator<JSONIsNullIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

  JSONIsNullIterator(
    static_context* sctx,
    const QueryLoc& loc,
    PlanIter_t& child)
    : 
    UnaryBaseIterator<JSONIsNullIterator, PlanIteratorState>(sctx, loc, child)
  {}

  virtual ~JSONIsNullIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 *      internal function
 *  
 * Author: Zorba Team
 */
class JSONObjectInsertIterator : public NaryBaseIterator<JSONObjectInsertIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONObjectInsertIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONObjectInsertIterator,
    NaryBaseIterator<JSONObjectInsertIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

  JSONObjectInsertIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<JSONObjectInsertIterator, PlanIteratorState>(sctx, loc, children)
  {}

  virtual ~JSONObjectInsertIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 *      internal function 
 *    
 * Author: Zorba Team
 */
class JSONArrayInsertIterator : public NaryBaseIterator<JSONArrayInsertIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONArrayInsertIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONArrayInsertIterator,
    NaryBaseIterator<JSONArrayInsertIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

  JSONArrayInsertIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<JSONArrayInsertIterator, PlanIteratorState>(sctx, loc, children)
  {}

  virtual ~JSONArrayInsertIterator();

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

  void serialize( ::zorba::serialization::Archiver& ar);

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
 *      internal function
 *    
 * Author: Zorba Team
 */
class JSONReplaceValueIterator : public NaryBaseIterator<JSONReplaceValueIterator, PlanIteratorState>
{ 
protected:
  bool theCopyInput; //
public:
  SERIALIZABLE_CLASS(JSONReplaceValueIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONReplaceValueIterator,
    NaryBaseIterator<JSONReplaceValueIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

  JSONReplaceValueIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children,
    bool copyInput)
    ;

  virtual ~JSONReplaceValueIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 *      
 *    
 * Author: Zorba Team
 */
class JSONRenameIterator : public NaryBaseIterator<JSONRenameIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONRenameIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONRenameIterator,
    NaryBaseIterator<JSONRenameIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

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
 *      internal function 
 *    
 * Author: Zorba Team
 */
class JSONArrayAppendIterator : public NaryBaseIterator<JSONArrayAppendIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONArrayAppendIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONArrayAppendIterator,
    NaryBaseIterator<JSONArrayAppendIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

  JSONArrayAppendIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<JSONArrayAppendIterator, PlanIteratorState>(sctx, loc, children)
  {}

  virtual ~JSONArrayAppendIterator();

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};

#endif

#ifdef ZORBA_WITH_JSON
/**
 * 
 *      
 *    
 * Author: Zorba Team
 */
class JSONBoxIterator : public UnaryBaseIterator<JSONBoxIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSONBoxIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSONBoxIterator,
    UnaryBaseIterator<JSONBoxIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

  JSONBoxIterator(
    static_context* sctx,
    const QueryLoc& loc,
    PlanIter_t& child)
    : 
    UnaryBaseIterator<JSONBoxIterator, PlanIteratorState>(sctx, loc, child)
  {}

  virtual ~JSONBoxIterator();

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
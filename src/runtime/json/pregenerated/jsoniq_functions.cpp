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

#include "stdafx.h"
#include "zorbatypes/rchandle.h"
#include "zorbatypes/zstring.h"
#include "runtime/visitors/planiter_visitor.h"
#include "runtime/json/jsoniq_functions.h"
#include "system/globalenv.h"



namespace zorba {

#ifdef ZORBA_WITH_JSON
// <JSONParseIterator>
const char* JSONParseIterator::class_name_str = "JSONParseIterator";
JSONParseIterator::class_factory<JSONParseIterator>
JSONParseIterator::g_class_factory;

const serialization::ClassVersion 
JSONParseIterator::class_versions[] ={{ 1, 0x000905, false}};

const int JSONParseIterator::class_versions_count =
sizeof(JSONParseIterator::class_versions)/sizeof(struct serialization::ClassVersion);

void JSONParseIterator::accept(PlanIterVisitor& v) const {
  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

JSONParseIterator::~JSONParseIterator() {}

// </JSONParseIterator>

#endif
#ifdef ZORBA_WITH_JSON
// <JSONObjectNamesIterator>
const char* JSONObjectNamesIterator::class_name_str = "JSONObjectNamesIterator";
JSONObjectNamesIterator::class_factory<JSONObjectNamesIterator>
JSONObjectNamesIterator::g_class_factory;

const serialization::ClassVersion 
JSONObjectNamesIterator::class_versions[] ={{ 1, 0x000905, false}};

const int JSONObjectNamesIterator::class_versions_count =
sizeof(JSONObjectNamesIterator::class_versions)/sizeof(struct serialization::ClassVersion);

void JSONObjectNamesIterator::accept(PlanIterVisitor& v) const {
  v.beginVisit(*this);

  theChild->accept(v);

  v.endVisit(*this);
}

JSONObjectNamesIterator::~JSONObjectNamesIterator() {}

JSONObjectNamesIteratorState::JSONObjectNamesIteratorState() {}

JSONObjectNamesIteratorState::~JSONObjectNamesIteratorState() {}


void JSONObjectNamesIteratorState::init(PlanState& planState) {
  PlanIteratorState::init(planState);
}

void JSONObjectNamesIteratorState::reset(PlanState& planState) {
  PlanIteratorState::reset(planState);
}
// </JSONObjectNamesIterator>

#endif
#ifdef ZORBA_WITH_JSON
// <JSONObjectValuesIterator>
const char* JSONObjectValuesIterator::class_name_str = "JSONObjectValuesIterator";
JSONObjectValuesIterator::class_factory<JSONObjectValuesIterator>
JSONObjectValuesIterator::g_class_factory;

const serialization::ClassVersion 
JSONObjectValuesIterator::class_versions[] ={{ 1, 0x000905, false}};

const int JSONObjectValuesIterator::class_versions_count =
sizeof(JSONObjectValuesIterator::class_versions)/sizeof(struct serialization::ClassVersion);

void JSONObjectValuesIterator::accept(PlanIterVisitor& v) const {
  v.beginVisit(*this);

  theChild->accept(v);

  v.endVisit(*this);
}

JSONObjectValuesIterator::~JSONObjectValuesIterator() {}

JSONObjectValuesIteratorState::JSONObjectValuesIteratorState() {}

JSONObjectValuesIteratorState::~JSONObjectValuesIteratorState() {}


void JSONObjectValuesIteratorState::init(PlanState& planState) {
  PlanIteratorState::init(planState);
}

void JSONObjectValuesIteratorState::reset(PlanState& planState) {
  PlanIteratorState::reset(planState);
}
// </JSONObjectValuesIterator>

#endif
#ifdef ZORBA_WITH_JSON
// <JSONObjectValueIterator>
const char* JSONObjectValueIterator::class_name_str = "JSONObjectValueIterator";
JSONObjectValueIterator::class_factory<JSONObjectValueIterator>
JSONObjectValueIterator::g_class_factory;

const serialization::ClassVersion 
JSONObjectValueIterator::class_versions[] ={{ 1, 0x000905, false}};

const int JSONObjectValueIterator::class_versions_count =
sizeof(JSONObjectValueIterator::class_versions)/sizeof(struct serialization::ClassVersion);

void JSONObjectValueIterator::accept(PlanIterVisitor& v) const {
  v.beginVisit(*this);

  theChild0->accept(v);
theChild1->accept(v);

  v.endVisit(*this);
}

JSONObjectValueIterator::~JSONObjectValueIterator() {}

// </JSONObjectValueIterator>

#endif
#ifdef ZORBA_WITH_JSON
// <JSONArraySizeIterator>
const char* JSONArraySizeIterator::class_name_str = "JSONArraySizeIterator";
JSONArraySizeIterator::class_factory<JSONArraySizeIterator>
JSONArraySizeIterator::g_class_factory;

const serialization::ClassVersion 
JSONArraySizeIterator::class_versions[] ={{ 1, 0x000905, false}};

const int JSONArraySizeIterator::class_versions_count =
sizeof(JSONArraySizeIterator::class_versions)/sizeof(struct serialization::ClassVersion);

void JSONArraySizeIterator::accept(PlanIterVisitor& v) const {
  v.beginVisit(*this);

  theChild->accept(v);

  v.endVisit(*this);
}

JSONArraySizeIterator::~JSONArraySizeIterator() {}

// </JSONArraySizeIterator>

#endif
#ifdef ZORBA_WITH_JSON
// <JSONArrayMemberIterator>
const char* JSONArrayMemberIterator::class_name_str = "JSONArrayMemberIterator";
JSONArrayMemberIterator::class_factory<JSONArrayMemberIterator>
JSONArrayMemberIterator::g_class_factory;

const serialization::ClassVersion 
JSONArrayMemberIterator::class_versions[] ={{ 1, 0x000905, false}};

const int JSONArrayMemberIterator::class_versions_count =
sizeof(JSONArrayMemberIterator::class_versions)/sizeof(struct serialization::ClassVersion);

void JSONArrayMemberIterator::accept(PlanIterVisitor& v) const {
  v.beginVisit(*this);

  theChild0->accept(v);
theChild1->accept(v);

  v.endVisit(*this);
}

JSONArrayMemberIterator::~JSONArrayMemberIterator() {}

// </JSONArrayMemberIterator>

#endif
#ifdef ZORBA_WITH_JSON
// <JSONArrayMembersIterator>
const char* JSONArrayMembersIterator::class_name_str = "JSONArrayMembersIterator";
JSONArrayMembersIterator::class_factory<JSONArrayMembersIterator>
JSONArrayMembersIterator::g_class_factory;

const serialization::ClassVersion 
JSONArrayMembersIterator::class_versions[] ={{ 1, 0x000905, false}};

const int JSONArrayMembersIterator::class_versions_count =
sizeof(JSONArrayMembersIterator::class_versions)/sizeof(struct serialization::ClassVersion);

void JSONArrayMembersIterator::accept(PlanIterVisitor& v) const {
  v.beginVisit(*this);

  theChild->accept(v);

  v.endVisit(*this);
}

JSONArrayMembersIterator::~JSONArrayMembersIterator() {}

JSONArrayMembersIteratorState::JSONArrayMembersIteratorState() {}

JSONArrayMembersIteratorState::~JSONArrayMembersIteratorState() {}


void JSONArrayMembersIteratorState::init(PlanState& planState) {
  PlanIteratorState::init(planState);
}

void JSONArrayMembersIteratorState::reset(PlanState& planState) {
  PlanIteratorState::reset(planState);
}
// </JSONArrayMembersIterator>

#endif
#ifdef ZORBA_WITH_JSON
// <JSONArrayFlattenIterator>
const char* JSONArrayFlattenIterator::class_name_str = "JSONArrayFlattenIterator";
JSONArrayFlattenIterator::class_factory<JSONArrayFlattenIterator>
JSONArrayFlattenIterator::g_class_factory;

const serialization::ClassVersion 
JSONArrayFlattenIterator::class_versions[] ={{ 1, 0x000905, false}};

const int JSONArrayFlattenIterator::class_versions_count =
sizeof(JSONArrayFlattenIterator::class_versions)/sizeof(struct serialization::ClassVersion);

void JSONArrayFlattenIterator::accept(PlanIterVisitor& v) const {
  v.beginVisit(*this);

  theChild->accept(v);

  v.endVisit(*this);
}

JSONArrayFlattenIterator::~JSONArrayFlattenIterator() {}

JSONArrayFlattenIteratorState::JSONArrayFlattenIteratorState() {}

JSONArrayFlattenIteratorState::~JSONArrayFlattenIteratorState() {}


void JSONArrayFlattenIteratorState::init(PlanState& planState) {
  PlanIteratorState::init(planState);
}
// </JSONArrayFlattenIterator>

#endif
#ifdef ZORBA_WITH_JSON
// <JSONItemAccessorIterator>
const char* JSONItemAccessorIterator::class_name_str = "JSONItemAccessorIterator";
JSONItemAccessorIterator::class_factory<JSONItemAccessorIterator>
JSONItemAccessorIterator::g_class_factory;

const serialization::ClassVersion 
JSONItemAccessorIterator::class_versions[] ={{ 1, 0x000905, false}};

const int JSONItemAccessorIterator::class_versions_count =
sizeof(JSONItemAccessorIterator::class_versions)/sizeof(struct serialization::ClassVersion);

void JSONItemAccessorIterator::accept(PlanIterVisitor& v) const {
  v.beginVisit(*this);

  theChild0->accept(v);
theChild1->accept(v);

  v.endVisit(*this);
}

JSONItemAccessorIterator::~JSONItemAccessorIterator() {}

// </JSONItemAccessorIterator>

#endif
#ifdef ZORBA_WITH_JSON
// <JSONItemEmptyAccessorIterator>
const char* JSONItemEmptyAccessorIterator::class_name_str = "JSONItemEmptyAccessorIterator";
JSONItemEmptyAccessorIterator::class_factory<JSONItemEmptyAccessorIterator>
JSONItemEmptyAccessorIterator::g_class_factory;

const serialization::ClassVersion 
JSONItemEmptyAccessorIterator::class_versions[] ={{ 1, 0x000905, false}};

const int JSONItemEmptyAccessorIterator::class_versions_count =
sizeof(JSONItemEmptyAccessorIterator::class_versions)/sizeof(struct serialization::ClassVersion);

void JSONItemEmptyAccessorIterator::accept(PlanIterVisitor& v) const {
  v.beginVisit(*this);

  theChild->accept(v);

  v.endVisit(*this);
}

JSONItemEmptyAccessorIterator::~JSONItemEmptyAccessorIterator() {}

JSONItemEmptyAccessorIteratorState::JSONItemEmptyAccessorIteratorState() {}

JSONItemEmptyAccessorIteratorState::~JSONItemEmptyAccessorIteratorState() {}


void JSONItemEmptyAccessorIteratorState::init(PlanState& planState) {
  PlanIteratorState::init(planState);
}

void JSONItemEmptyAccessorIteratorState::reset(PlanState& planState) {
  PlanIteratorState::reset(planState);
}
// </JSONItemEmptyAccessorIterator>

#endif
#ifdef ZORBA_WITH_JSON
// <JSONNullIterator>
const char* JSONNullIterator::class_name_str = "JSONNullIterator";
JSONNullIterator::class_factory<JSONNullIterator>
JSONNullIterator::g_class_factory;

const serialization::ClassVersion 
JSONNullIterator::class_versions[] ={{ 1, 0x000905, false}};

const int JSONNullIterator::class_versions_count =
sizeof(JSONNullIterator::class_versions)/sizeof(struct serialization::ClassVersion);

void JSONNullIterator::accept(PlanIterVisitor& v) const {
  v.beginVisit(*this);

  

  v.endVisit(*this);
}

JSONNullIterator::~JSONNullIterator() {}

// </JSONNullIterator>

#endif
#ifdef ZORBA_WITH_JSON
// <JSONInsertAsFirstIterator>
const char* JSONInsertAsFirstIterator::class_name_str = "JSONInsertAsFirstIterator";
JSONInsertAsFirstIterator::class_factory<JSONInsertAsFirstIterator>
JSONInsertAsFirstIterator::g_class_factory;

const serialization::ClassVersion 
JSONInsertAsFirstIterator::class_versions[] ={{ 1, 0x000905, false}};

const int JSONInsertAsFirstIterator::class_versions_count =
sizeof(JSONInsertAsFirstIterator::class_versions)/sizeof(struct serialization::ClassVersion);

void JSONInsertAsFirstIterator::accept(PlanIterVisitor& v) const {
  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

JSONInsertAsFirstIterator::~JSONInsertAsFirstIterator() {}

// </JSONInsertAsFirstIterator>

#endif
#ifdef ZORBA_WITH_JSON
// <JSONInsertAfterIterator>
const char* JSONInsertAfterIterator::class_name_str = "JSONInsertAfterIterator";
JSONInsertAfterIterator::class_factory<JSONInsertAfterIterator>
JSONInsertAfterIterator::g_class_factory;

const serialization::ClassVersion 
JSONInsertAfterIterator::class_versions[] ={{ 1, 0x000905, false}};

const int JSONInsertAfterIterator::class_versions_count =
sizeof(JSONInsertAfterIterator::class_versions)/sizeof(struct serialization::ClassVersion);

void JSONInsertAfterIterator::accept(PlanIterVisitor& v) const {
  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

JSONInsertAfterIterator::~JSONInsertAfterIterator() {}

// </JSONInsertAfterIterator>

#endif
#ifdef ZORBA_WITH_JSON
// <JSONInsertBeforeIterator>
const char* JSONInsertBeforeIterator::class_name_str = "JSONInsertBeforeIterator";
JSONInsertBeforeIterator::class_factory<JSONInsertBeforeIterator>
JSONInsertBeforeIterator::g_class_factory;

const serialization::ClassVersion 
JSONInsertBeforeIterator::class_versions[] ={{ 1, 0x000905, false}};

const int JSONInsertBeforeIterator::class_versions_count =
sizeof(JSONInsertBeforeIterator::class_versions)/sizeof(struct serialization::ClassVersion);

void JSONInsertBeforeIterator::accept(PlanIterVisitor& v) const {
  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

JSONInsertBeforeIterator::~JSONInsertBeforeIterator() {}

// </JSONInsertBeforeIterator>

#endif
#ifdef ZORBA_WITH_JSON
// <JSONInsertAsLastIterator>
const char* JSONInsertAsLastIterator::class_name_str = "JSONInsertAsLastIterator";
JSONInsertAsLastIterator::class_factory<JSONInsertAsLastIterator>
JSONInsertAsLastIterator::g_class_factory;

const serialization::ClassVersion 
JSONInsertAsLastIterator::class_versions[] ={{ 1, 0x000905, false}};

const int JSONInsertAsLastIterator::class_versions_count =
sizeof(JSONInsertAsLastIterator::class_versions)/sizeof(struct serialization::ClassVersion);

void JSONInsertAsLastIterator::accept(PlanIterVisitor& v) const {
  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

JSONInsertAsLastIterator::~JSONInsertAsLastIterator() {}

// </JSONInsertAsLastIterator>

#endif
#ifdef ZORBA_WITH_JSON
// <JSONDeleteIterator>
const char* JSONDeleteIterator::class_name_str = "JSONDeleteIterator";
JSONDeleteIterator::class_factory<JSONDeleteIterator>
JSONDeleteIterator::g_class_factory;

const serialization::ClassVersion 
JSONDeleteIterator::class_versions[] ={{ 1, 0x000905, false}};

const int JSONDeleteIterator::class_versions_count =
sizeof(JSONDeleteIterator::class_versions)/sizeof(struct serialization::ClassVersion);

void JSONDeleteIterator::accept(PlanIterVisitor& v) const {
  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

JSONDeleteIterator::~JSONDeleteIterator() {}

// </JSONDeleteIterator>

#endif
#ifdef ZORBA_WITH_JSON
// <JSONRenameIterator>
const char* JSONRenameIterator::class_name_str = "JSONRenameIterator";
JSONRenameIterator::class_factory<JSONRenameIterator>
JSONRenameIterator::g_class_factory;

const serialization::ClassVersion 
JSONRenameIterator::class_versions[] ={{ 1, 0x000905, false}};

const int JSONRenameIterator::class_versions_count =
sizeof(JSONRenameIterator::class_versions)/sizeof(struct serialization::ClassVersion);

void JSONRenameIterator::accept(PlanIterVisitor& v) const {
  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

JSONRenameIterator::~JSONRenameIterator() {}

// </JSONRenameIterator>

#endif
#ifdef ZORBA_WITH_JSON
// <JSONReplaceValueIterator>
const char* JSONReplaceValueIterator::class_name_str = "JSONReplaceValueIterator";
JSONReplaceValueIterator::class_factory<JSONReplaceValueIterator>
JSONReplaceValueIterator::g_class_factory;

const serialization::ClassVersion 
JSONReplaceValueIterator::class_versions[] ={{ 1, 0x000905, false}};

const int JSONReplaceValueIterator::class_versions_count =
sizeof(JSONReplaceValueIterator::class_versions)/sizeof(struct serialization::ClassVersion);

void JSONReplaceValueIterator::accept(PlanIterVisitor& v) const {
  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

JSONReplaceValueIterator::~JSONReplaceValueIterator() {}

// </JSONReplaceValueIterator>

#endif

}



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

#include "dict_impl.h"

namespace zorba {
namespace err {
namespace dict {

///////////////////////////////////////////////////////////////////////////////

extern entry const dict_en[] = {

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // !!!!! THIS MUST BE ASCII SORTED BY KEY !!!!!
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  { "FOAR0001", "division by zero" },
  { "FOAR0002", "numeric operation overflow/underflow${: 1}" },
  { "FOCA0001", "\"$1\": value too large for decimal" },
  { "FOCA0002", "\"$1\": invalid lexical value${: 2}" },
  { "FOCA0003", "\"$1\": value too large for integer" },
  { "FOCA0005", "NaN supplied as float/double value" },
  { "FOCA0006", "\"$1\": string to be cast to decimal has too many digits of precision" },
  { "FOCH0001", "\"$1\": invalid code-point for XML 1.0" },
  { "FOCH0002", "\"$1\": unsuported collation${: 2}" },
  { "FOCH0003", "\"$1\": unsupported normalization form" },
  { "FOCH0004", "\"$1\": collation does not support collation units" },
  { "FODC0001", "no context document for $1() function" },
  { "FODC0002", "\"$1\": error retrieving resource${: 2}" },
  { "FODC0003", "function stability not defined" },
  { "FODC0004", "\"$1\": invalid argument to fn:collection()${: 2}" },
  { "FODC0005", "\"$1\": invalid argument to fn:doc() or fn:doc-available()" },
  { "FODC0006", "invalid content passed to fn:parse(): $1" },
  { "FODC0007", "\"$1\": base URI passed to fn:parse() is not a valid absolute URI" },
  { "FODF1280", "\"$1\": invalid decimal format name for fn:format-number()" },
  { "FODF1310", "\"$1\": invalid fn:format-number() picture string" },
  { "FODT0001", "overflow/underflow in date/time operation" },
  { "FODT0002", "overflow/underflow in duration operation" },
  { "FODT0003", "\"$1\": invalid timezone value" },
  { "FOER0000", "unidentifier error" },
  { "FOFI0001", "\"$1\": not castable to xs:language" },
  { "FOFI0002", "invalid argument in $1" },
  { "FONS0004", "\"$1\": no namespace found for prefix" },
  { "FONS0005", "base-URI not defined in the static context" },
  { "FORG0001", "${\"1\": }invalid value for cast/constructor${: 2}" },
  { "FORG0002", "\"$1\": invalid argument to fn:resolve-uri()${: 2}" },
  { "FORG0003", "fn:zero-or-one() called with a sequnce containing more than one item" },
  { "FORG0004", "fn:one-or-more() called with a sequence containing no items" },
  { "FORG0005", "fn:exactly-one() called with a sequence containing zero or more than one item" },
  { "FORG0006", "invalid argument type${: 1}" },
  { "FORG0008", "\"$1\" & \"$2\": two arguments to fn:dateTime() have inconsistent timezones" },
  { "FORG0009", "error resolving a relative URI against a base URI in fn:resolve-uri()${: 1}" },
  { "FORX0001", "'$1': invalid regular expression flag" },
  { "FORX0002", "\"$1\": invalid regular expression${: 2}" },
  { "FORX0003", "\"$1\": regular expression matches zero-length string" },
  { "FORX0004", "\"$1\": invalid replacement string${: 2}" },
  { "FOTY0012", "\"$1\": element node of type $2 does not have a typed value" },
  { "FOTY0013", "argument to fn:data() is function item" },
  { "FOTY0014", "argument to fn:string() is a function item" },
  { "FOTY0015", "argument to fn:deep-equal() contains a function item" },
  { "FOUP0001", "first operand of fn:put() is not a node of a supported kind" },
  { "FOUP0002", "second operand of fn:put() is not a valid lexical representation of the xs:anyURI type" },

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // !!!!! THIS MUST BE ASCII SORTED BY KEY !!!!!
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef ZORBA_NO_FULL_TEXT
  { "FTDY0016", "\"$1\": invalid weight: absolute value must be in [0,1000]" },
  { "FTDY0017", "mild-not contains StringExclude" },
  { "FTDY0020", "${\"1\": }invalid wildcard syntax${: 2}" },
  { "FTST0008", "\"$1\": unknown stop-word list" },
  { "FTST0009", "\"$1\": unsupported language" },
  { "FTST0018", "\"$1\": unknown thesaurus" },
  { "FTST0019", "\"$1\": match option specified more than once" },
#endif /* ZORBA_NO_FULL_TEXT */

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // !!!!! THIS MUST BE ASCII SORTED BY KEY !!!!!
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  { "SENR0001", "\"$1\": can not serialize $2" },
  { "SEPM0004", "doctype-system parameter, or standalone parameter with a value other than \"omit\", specified" },
  { "SEPM0009", "omit-xml-declaration parameter is \"yes\" and $1" },
  { "SEPM0010", "the output method is \"xml\", the value of the undeclare-prefixes parameter is \"yes\", and the value of the version parameter is \"1.0\"" },
  { "SEPM0016", "\"$1\": value for parameter \"$2\" invalid${; $3}" },
  { "SERE0003", "serializer can't satisfy the rules for either a well-formed XML document entity or a well-formed XML external general parsed entity" },
  { "SERE0005", "invalid NCName character" },
  { "SERE0006", "\"$1\": invalid character for XML version $2" },
  { "SERE0008", "\"$1\": can not encode character as character reference here" },
  { "SERE0012", "the value of the normalization-form parameter is fully-normalized and any relevant construct of the result begins with a combining character" },
  { "SERE0014", "\"#$1\": character not allowed for HTML output method" },
  { "SERE0015", "can not use '>' within processing instruction for HTML output method" },
  { "SESU0007", "\"$1\": unsupported encoding" },
  { "SESU0011", "\"$1\": unsupported normalization form" },
  { "SESU0013", "\"$1\": unsupported $2 version; supported versions are: $3" },

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // !!!!! THIS MUST BE ASCII SORTED BY KEY !!!!!
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  { "XPDY0002", "\"$1\": undefined value" },
  { "XPDY0050", "invalid treat expression type" },
  { "XPST0001", "\"$1\": undefined value" },
  { "XPST0003", "invalid expression${: 1}" },
  { "XPST0005", "static type must not be empty-sequence()" },
  { "XPST0008", "\"$1\": undefined name" },
  { "XPST0010", "\"$1\": unsupported axis" },
  { "XPST0017", "function call does not match signature" },
  { "XPST0051", "\"$1\": not defined as atomic type${: 2}" },
  { "XPST0080", "\"$1\": invalid type for \"cast\" or \"castable\" exression${: 2}" },
  { "XPST0081", "\"$1\": can not expand namespace prefix to URI" },
  { "XPST0083", "\"$1\": not a string literal" },
  { "XPTY0004", "\"$1\": invalid type${: 2}" },
  { "XPTY0018", "path expression last step must not have nodes and atomic values" },
  { "XPTY0019", "path expression non-last step must not be an atomic value" },
  { "XPTY0020", "axis step context item is not a node" },
  { "XQDY0025", "\"$1\": duplicate attribute name" },
  { "XQDY0026", "computed processing instrucion must not contain \"?>\"" },
  { "XQDY0027", "\"$1\": unexpected validity property" },
  { "XQDY0041", "\"$1\": can not cast to xs:NCName" },
  { "XQDY0044", "\"$1\": invalid attibute node-name" },
  { "XQDY0061", "invalid validate expression operand" },
  { "XQDY0064", "\"XML\": invalid name expression" },
  { "XQDY0072", "comment must not contain \"--\" or end with \"-\"" },
  { "XQDY0074", "\"$1\": can not convert to expanded QName" },
  { "XQDY0084", "validated element does not have a top-level element declaration in the in-scope element declarations, if validation mode is strict" },
  { "XQDY0091", "\"xml:id\" encountered" },
  { "XQDY0092", "\"$1\": must be either \"preserve\" or \"default\"" },
  { "XQDY0096", "\"$1\": invalid node-name" },
  { "XQST0009", "schema import not supported" },
  { "XQST0012", "invalid schema definitions" },
  { "XQST0013", "invalid pragma content" },
  { "XQST0016", "invalid pragma content" },
  { "XQST0022", "namespace declaration attribute is not a URI literal" },
  { "XQST0031", "\"$1\": unsupported version" },
  { "XQST0032", "multiple base URI declarations" },
  { "XQST0033", "\"$1\": namespace prefix already bound to \"$2\"" },
  { "XQST0034", "\"$1\": duplicate function declaration" },
  { "XQST0035", "\"$1\": name previosly imported" },
  { "XQST0036", "incomplete in-scope schema definitions" },
  { "XQST0038", "multiple default collation declarations" },
  { "XQST0039", "\"$1\": duplicate parameter name" },
  { "XQST0040", "\"$1\": non-distinct expanded attribute QName" },
  { "XQST0045", "\"$1\": invalid function namespace" },
  { "XQST0046", "\"$1\": invalid URI literal${: 2}" },
  { "XQST0047", "\"$1\": duplicate target namespace" },
  { "XQST0048", "\"$1\": not in library namespace" },
  { "XQST0049", "\"$1\": duplicate variable declaration" },
  { "XQST0054", "\"$1\": variable must not depend on itself" },
  { "XQST0055", "multiple copy-namespaces declarations" },
  { "XQST0057", "empty target namespace" },
  { "XQST0058", "\"$1\": duplicate target namespace" },
  { "XQST0059", "\"$1\": target namespace not found" },
  { "XQST0060", "\"$1\": function name has a null namespace URI" },
  { "XQST0065", "multiple ordering mode declaraions" },
  { "XQST0066", "multiple element/type/function namespace declarations" },
  { "XQST0067", "multiple construction declarations" },
  { "XQST0068", "multiple boundary-space declarations" },
  { "XQST0069", "multiple empty order declarations" },
  { "XQST0070", "can not reuse \"xml\" or \"xmlns\" prefixes" },
  { "XQST0071", "\"$1\": duplicate namespace declaration attribute" },
  { "XQST0075", "\"validate\" expression not supported" },
  { "XQST0076", "unknown collation" },
  { "XQST0079", "unknown pragma or empty expression" },
  { "XQST0085", "namespace URI is empty" },
  { "XQST0087", "\"$1\": invalid encoding" },
  { "XQST0088", "empty target namespace literal" },
  { "XQST0089", "\"$1\": duplicate variable name" },
  { "XQST0090", "\"$1\": invalid character reference" },
  { "XQST0093", "\"$1\": module must not depend on itself" },
  { "XQST0097", "the decimal format declaration specifies a value that is not valid for a property" },
  { "XQST0098", "the properties representing characters used in a picture string do not each have distinct values" },
  { "XQST0106", "\"$1\": multiple function annotations with this name" },
  { "XQST0111", "the query contains two decimal formats with the same name, or two default decimal formats" },
  { "XQTY0024", "element constructor content sequence must not have an attribute node following a non-attribute node" },
  { "XQTY0030", "validate argument must be exactly one document or element node" },
  { "XQTY0086", "typed value of copied element or attribute node is namespace-sensitive when construction mode is preserve and copy-namespaces mode is no-preserve" },
  { "XTDE1310", "\"$1\": picture string does not satisfy format-number function rules" },
  { "XTDE1340", "\"$1\": invalid picture string" },
  { "XTDE1350", "\"$1\": component specifier not available" },

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // !!!!! THIS MUST BE ASCII SORTED BY KEY !!!!!
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  { "XUDY0009", "TODO" },
  { "XUDY0014", "TODO" },
  { "XUDY0015", "TODO" },
  { "XUDY0016", "TODO" },
  { "XUDY0017", "TODO" },
  { "XUDY0018", "TODO" },
  { "XUDY0019", "TODO" },
  { "XUDY0020", "TODO" },
  { "XUDY0021", "TODO" },
  { "XUDY0023", "TODO" },
  { "XUDY0024", "TODO" },
  { "XUDY0025", "TODO" },
  { "XUDY0027", "TODO" },
  { "XUDY0029", "TODO" },
  { "XUDY0030", "TODO" },
  { "XUDY0031", "TODO" },
  { "XUST0001", "updating expression illegal here" },
  { "XUST0002", "simple expression illegal here" },
  { "XUST0003", "multiple revalidation declarations" },
  { "XUST0026", "TODO" },
  { "XUST0028", "TODO" },
  { "XUTY0004", "attribute node follows non-attribute node" },
  { "XUTY0005", "target expression not a single element or document node" },
  { "XUTY0006", "target expression not a single element, text, comment, or processing instruction node" },
  { "XUTY0007", "target expression does not return a sequence of zero or more nodes" },
  { "XUTY0008", "target expression not a single element, attribute, text, comment, or processing instruction node" },
  { "XUTY0010", "TODO" },
  { "XUTY0011", "TODO" },
  { "XUTY0012", "TODO" },
  { "XUTY0013", "TODO" },
  { "XUTY0022", "TODO" },

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // !!!!! THIS MUST BE ASCII SORTED BY KEY !!!!!
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  { "ZAPI0002", "XQuery compilation failed${: 1}" },
  { "ZAPI0003", "XQuery not compiled" },
  { "ZAPI0004", "XQuery already compiled" },
  { "ZAPI0005", "XQuery already executing" },
  { "ZAPI0006", "XQuery already closed" },
  { "ZAPI0007", "cannot serialize pul" },
  { "ZAPI0008", "can not execute a non-updating XQuery" },
  { "ZAPI0009", "XQuery not compiled in debug mode" },
  { "ZAPI0014", "\"$1\": invalid argument${: 2}" },
  { "ZAPI0015", "\"$1\": createModule() function not found${: 2}" },
  { "ZAPI0019", "\"$1\": external module already registered" },
  { "ZAPI0020", "\"$1\": document already exists in store" },
  { "ZAPI0021", "\"$1\": item to load is not a node" },
  { "ZAPI0027", "cannot update dynamic context with iterators" },
  { "ZAPI0028", "\"$1\": invalid node URI" },
  { "ZAPI0039", "XQuery has iterator already" },
  { "ZAPI0040", "iterator is not open" },
  { "ZAPI0041", "iterator is already open" },
  { "ZAPI0042", "iterator is closed" },
  { "ZAPI0051", "REST error payload" },
  { "ZAPI0070", "\"$1\": invalid serialization method for SAX" },

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // !!!!! THIS MUST BE ASCII SORTED BY KEY !!!!!
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  { "ZCSE0001", "\"$1\": nonexistent input field" },
  { "ZCSE0002", "\"$1\": incompatible input field" },
  { "ZCSE0003", "\"$1\": unrecognized class field" },
  { "ZCSE0004", "\"$1\": unresolved field reference" },
  { "ZCSE0005", "\"$1\": class version is too new" },
  { "ZCSE0006", "\"$1\": class version is too old" },
  { "ZCSE0007", "input archive used for out serialization" },
  { "ZCSE0008", "output archive used for in serialization" },
  { "ZCSE0009", "class not serializable" },
  { "ZCSE0010", "\"$1\": item type not serializable" },
  { "ZCSE0011", "input archive not zorba archive" },
  { "ZCSE0012", "\"$1\": incompatible archive version" },
  { "ZCSE0013", "unable to load query" },
  { "ZCSE0014", "infinite circular dependencies" },
  { "ZCSE0015", "incompatible between 32/64 bits or little/big-endian" },

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // !!!!! THIS MUST BE ASCII SORTED BY KEY !!!!!
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  { "ZDDY0001", "\"$1\": collection not declared" },
  { "ZDDY0002", "\"$1\": collection already exists" },
  { "ZDDY0003", "\"$1\": collection does not exist" },
  { "ZDDY0004", "\"$1\": can not update constant collection" },
  { "ZDDY0005", "\"$1\": illegal insert into append-only collection" },
  { "ZDDY0006", "\"$1\": illegal insert into queue collection" },
  { "ZDDY0007", "\"$1\": illegal delete from append-only collection" },
  { "ZDDY0008", "\"$1\": illegal delete from queue collection" },
  { "ZDDY0009", "\"$1\": not all nodes to delete are at the beginning of this queue collection" },
  { "ZDDY0010", "\"$1\": illegal update of read-only nodes" },
  { "ZDDY0011", "\"$1\": collection does not contain node" },
  { "ZDDY0012", "\"$1\": illegal insert into unordered collection" },
  { "ZDDY0013", "\"$1\": can not delete collection because indexes reference it" },
  { "ZDDY0014", "\"$1\": can not delete collection because integrity constraits reference it" },
  { "ZDDY0015", "\"$1\": can not delete collection because there are references to its nodes" },
  { "ZDDY0016", "\"$1\": multiple calls to create-collection function in same snapshot" },
  { "ZDDY0020", "\"$1\": index domain expression yields nodes that are not in collection" },
  { "ZDDY0021", "\"$1\": undeclared index" },
  { "ZDDY0022", "\"$1\": index exists already" },
  { "ZDDY0023", "\"$1\": index does not exist" },
  { "ZDDY0024", "\"$1\": index uniqueness violation" },
  { "ZDDY0025", "\"$1\": invalid number of arguments in probe" },
  { "ZDDY0026", "\"$1\": index range probe not allowed" },
  { "ZDDY0027", "\"$1\": index multiple creates" },
  { "ZDDY0028", "\"$1\": index domain has duplicate nodes" },
  { "ZDDY0029", "\"$1\": index general probe not allowed" },
  { "ZDDY0031", "\"$1\": integrity constraint is not declared" },
  { "ZDDY0032", "\"$1\": integrity constraint is not activated" },
  { "ZDDY0033", "\"$1\": integrity constraint not met" },
  { "ZDST0001", "\"$1\": collection already declared" },
  { "ZDST0002", "\"$1\": collection already imported" },
  { "ZDST0003", "\"$1\": collection defl in main module" },
  { "ZDST0004", "collection multiple property values" },
  { "ZDST0005", "collection properties conflict" },
  { "ZDST0006", "collection invalid property value" },
  { "ZDST0007", "collection defl in foreign module" },
  { "ZDST0021", "index already declared" },
  { "ZDST0022", "index already imported" },
  { "ZDST0023", "index defl in main module" },
  { "ZDST0024", "index multiple property values" },
  { "ZDST0025", "index properties conflict" },
  { "ZDST0026", "index invalid property value" },
  { "ZDST0027", "index bad key type" },
  { "ZDST0028", "index not deterministic" },
  { "ZDST0029", "index invalid data source" },
  { "ZDST0030", "index non const data source" },
  { "ZDST0031", "index has free vars" },
  { "ZDST0032", "index references ctx item" },
  { "ZDST0033", "index non simple expr" },
  { "ZDST0034", "index cannot do automatic maintenance" },
  { "ZDST0035", "index general multikey" },
  { "ZDST0036", "index defl in foreign module" },
  { "ZDST0041", "integrity constraint is already declared" },
  { "ZDST0042", "multi-valued integrity constraint key" },
  { "ZDST0043", "non-atomic integrity constraint key" },
  { "ZDST0044", "integrity constraint defl in main module" },
  { "ZDST0045", "integrity constraint has free vars" },
  { "ZDST0046", "integrity constraint has invalid data source${: 1}" },
  { "ZDST0047", "integrity constraint not deterministic" },
  { "ZDST0048", "integrity constraint defl in foreign module" },
  { "ZDTY0001", "collection invalid node type" },
  { "ZDTY0010", "\"$1\": index domain expression yields a non-node item" },
  { "ZDTY0011", "result of some key expression of index $1 does not match its declared type" },
  { "ZDTY0012", "\"$1\": general range index key item has a type for which no ordering relationship exists" },

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // !!!!! THIS MUST BE ASCII SORTED BY KEY !!!!!
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  { "ZOSE0001", "\"$1\": file not found${: 2}" },
  { "ZOSE0002", "\"$1\": not plain file" },
  { "ZOSE0003", "stream read failure" },
  { "ZOSE0004", "I/O error${: 1}" },

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // !!!!! THIS MUST BE ASCII SORTED BY KEY !!!!!
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  { "ZSTR0001", "\"$1\": index already exists" },
  { "ZSTR0002", "\"$1\": index does not exist" },
  { "ZSTR0003", "\"$1\": partial key insertion into index \"$2\"" },
  { "ZSTR0004", "partial key deletion from index $1" },
  { "ZSTR0005", "partial key probe into index $1" },
  { "ZSTR0006", "\"$1\": invalid box probe condition for index \"$2\"" },
  { "ZSTR0007", "index unsupported probe condition" },
  { "ZSTR0008", "\"$1\": collection already exists" },
  { "ZSTR0009", "\"$1\": collection not found" },
  { "ZSTR0010", "can not insert node into colletion \"$1\" because it already belongs to collection \"$2\"" },
  { "ZSTR0011", "non-root node can not be inserted into collection \"$1\"" },
  { "ZSTR0012", "non-node item used with collection \"$1\"" },
  { "ZSTR0015", "integrity constraint already exists" },
  { "ZSTR0016", "integrity constraint does not exist" },
  { "ZSTR0020", "loader I/O error${: 1}" },
  { "ZSTR0021", "loader parsing error${: 1}" },
  { "ZSTR0030", "NodeID error${: 1}" },
  { "ZSTR0040", "type error${: 1}" },
  { "ZSTR0041", "NaN comparison" },
  { "ZSTR0045", "duplicate node found in sequence" },
  { "ZSTR0050", "\"$1\": function not implemented for item type $2" },
  { "ZSTR0055", "the given streamable string has already been consumed" },

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // !!!!! THIS MUST BE ASCII SORTED BY KEY !!!!!
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  { "ZXQD0000", "\"$1\": prefix not declared" },
  { "ZXQD0001", "document not valid" },
  { "ZXQP0000", "no error" },
  { "ZXQP0001", "dynamic runtime error${: 1}" },
  { "ZXQP0002", "dynamic iterator overrun" },
  { "ZXQP0003", "illegal node child" },
  { "ZXQP0004", "\"$1\": target namespace not found" },
  { "ZXQP0005", "\"$1\": not supported" },
  { "ZXQP0006", "\"$1\": assertion failed" },
  { "ZXQP0007", "hash error: KeyLen exceeds MaxKeyLen" },
  { "ZXQP0008", "vector out of range" },
  { "ZXQP0009", "read lock failed" },
  { "ZXQP0010", "write lock failed" },
  { "ZXQP0011", "pop from empty list" },
  { "ZXQP0012", "file error in function" },
  { "ZXQP0013", "FxCharHeap I/O error" },
  { "ZXQP0015", "not yet implemented: $1" },
  { "ZXQP0016", "\"$1\": reserved module target namespace" },
  { "ZXQP0017", "file access disabled" },
  { "ZXQP0019", "internal error${: 1}" },
  { "ZXQP0020", "\"$1\": invalid URI${: 2}" },
  { "ZXQP0021", "user error" },
  { "ZXQP0022", "get results as DOM failed" },
  { "ZXQP0023", "get results as SAX failed" },
  { "ZXQP0024", "XML does not match schema${: \"1\"}${ 2}" },
  { "ZXQP0025", "could not create item" },
  { "ZXQP0026", "can not initialize store" },
  { "ZXQP0026", "could not create thread" },
  { "ZXQP0027", "error from MS DOM engine" },
  { "ZXQP0028", "\"$1\": external function not bound" },
  { "ZXQP0029", "module import not allowed" },
  { "ZXQP0030", "deadlock" },
  { "ZXQP0031", "malformed XQueryX input" },
  { "ZXQP0032", "error transforming XQueryX to XQuery${: 1}" },
  { "ZXQP0034", "\"$1\": illegal UTF-8 byte" },
  { "ZXQP0035", "\"$1\": illegal UTF-16 byte" },
  { "ZXQP0036", "BreakIterator creation failed" },

#ifndef ZORBA_NO_FULL_TEXT
  { "ZXQP8401", "\"$1\": wrong WordNet file version; should be \"$2\"" },
  { "ZXQP8402", "thesaurus data error${: 1}" },
#endif /* ZORBA_NO_FULL_TEXT */

  /////////////////////////////////////////////////////////////////////////////

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // !!!!! THIS MUST BE ASCII SORTED BY KEY !!!!!
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  // Note: parameter numbers for sub-messages start with at LEAST $2.

  { "~AllMatchesHasExcludes", "AllMatches contains StringExclude" },
  { "~AlreadySpecified", "already specified" },
  { "~AttributeNode", "attribute node" },
  { "~BackRef0Illegal", "\"\\0\": illegal backreference" },
  { "~BackRefIllegalInCharClass", "backreference illegal in character class" },
  { "~BadAnyURI", "invalid xs:anyURI" },
  { "~BadCharAfter", "'$3': illegal character after '$4'" },
  { "~BadCharInBraces", "'$2': illegal character within { }" },
  { "~BadDecDigit", "'$3': invalid decimal digit" },
  { "~BadFileURIAuthority", "\"$2\": invalid authority for \"file\" scheme" },
  { "~BadHexDigit", "${'3': }invalid hexedecimal digit" },
  { "~BadItem", "invalid item" },
  { "~BadIterator", "invalid iterator" },
  { "~BadLibraryModule", "invalid library module" },
  { "~BadMathTypes", "arithmetic operation not defined with type $3" },
  { "~BadPath", "invalid path" },
  { "~BadTokenInBraces", "\"$3\": illegal token within { }" },
  { "~BadURIScheme", "\"$3\": unknown URI scheme" },
  { "~BadUnicodeChar", "\"$2\": invalid character code-point" },
  { "~BadWordNetPartOfSpeech", "\"$2\": invalid part-of-speech" },
  { "~BadWordNetPtr", "\"$2\": invalid pointer type" },
  { "~Base64BadChar", "invalid Base64 character" },
  { "~Base64Equals", "in Base64, '=' must be at the end and followed by one of [AEIMQUYcgkosw048]" },
  { "~Base64EqualsEquals", "in Base64, \"==\" must be at the end and followed by one of [AQgw]" },
  { "~Base64Multiple4", "Base64 data must be a multiple of 4 characters" },
  { "~CastFromToFailed", "$3 to $4 cast failed" },
  { "~CharExpected", "'$3' expected" },
  { "~ClosingBraceWithoutOpen", "'}' encountered without '{' first" },
  { "~CountClause11", "count clause only available in XQuery 1.1 or later" },
  { "~DefaultCollation", "default collation" },
  { "~DivisionNoINF", "division can not have +-INF dividend" },
  { "~DivisionNoNaN", "division can not involve NaN" },
  { "~EBVNotDef", "effective boolean value not defined for \"$2\"" },
  { "~EmptyPath", "empty path" },
  { "~Eval11", "eval only available in XQuery 1.1 or later" },
  { "~ExternFnDeterministic", "only external functions may be declared deterministic" },
  { "~ExternFnNondeterministic", "only external functions may be declared nondeterministic" },
  { "~FileNotFoundOrReadable", "file not found or readable" },
  { "~FullTextNotEnabled", "full-text was not enabled in this build" },
  { "~GoodValuesAreUTF8", "valid values are: UTF-8, UTF-16" },
  { "~GoodValuesAreXMLEtc", "valid values are: xml, html, xhtml, text, binary" },
  { "~GoodValuesAreYesNo", "valid values are: yes, no" },
  { "~GoodValuesAreYesNoOmit", "valid values are: yes, no, omit" },
  { "~HexBinaryMustBeEven", "HexBinary value must contain an even number of characters" },
  { "~IncompleteKeyInIndexBuild", "incomplete key during index build" },
  { "~ModuleDeclNotInMain", "module declaration must not be in main module" },
  { "~ModuleNotFound", "module not found" },
  { "~MustBeAbsoluteURI", "must be absolute" },
  { "~MustBeNCName", "must be an xs:NCName" },
  { "~NoCastTo", "can not cast to $3${: 4}" },
  { "~NoDriveSpecification", "missing drive specification" },
  { "~NoEmptySeqAsBaseURI", "can't treat empty sequence as base URI" },
  { "~NoResolveRelativeURI", "could not resolve relative URI" },
  { "~NoSourceURI", "no URI" },
  { "~NoTypeInCtx", "undefined type in current context" },
  { "~NoURIAuthority", "no authority" },
  { "~NoURIScheme", "no URI scheme" },
  { "~NonClosedBackRef", "'$$3': non-closed backreference" },
  { "~NonFileThesaurusURI", "non-file thesaurus URI" },
  { "~NonLocalhostAuthority", "non-localhost authority" },
  { "~NonexistantBackRef", "'$$3': non-existant backreference" },
  { "~NotAllowedForTypeName", "not allowed for typeName (use xsd:untyped instead)" },
  { "~NotAmongInScopeSchemaTypes", "not among in-scope schema types" },
  { "~NotDefInStaticCtx", "not defined in dynamic context" },
  { "~NotInStaticCtx", "not found in static context" },
  { "~NotSpecified", "not specified" },
  { "~OSFailedError", "error $1: $2" },
  { "~OSWhatFailedError", "$1 failed (error $2): $3" },
  { "~OuterForClause11", "outer-for clause only available in XQuery 1.1 or later" },
  { "~SEPM0009_Not10", "the version parameter has a value other than \"1.0\" and the doctype-system parameter is specified" },
  { "~SEPM0009_NotOmit", "the standalone attribute has a value other than \"omit\"" },
  { "~SeqFnBody", "only a function declared as sequential can have a body that is a sequential expression" },
  { "~StartEndTagMismatch", "start tag \"$2\" does not match end tag \"$3\"" },
  { "~SwitchExpr11", "switch expressions only available in XQuery 1.1 or later" },
  { "~TrailingChar", "trailing '$3'" },
  { "~TryCatchExpr11", "try/catch expressions only available in XQuery 1.1 or later" },
  { "~TypeIsNotSubtype", "item type is not a subtype of \"$3\"" },
  { "~U_REGEX_BAD_ESCAPE_SEQUENCE", "unrecognized backslash escape sequence" },
  { "~U_REGEX_BAD_INTERVAL", "error in {min,max} interval" },
  { "~U_REGEX_INTERNAL_ERROR", "an internal ICU error (bug) was detected" },
  { "~U_REGEX_INVALID_BACK_REF", "backreference to a non-existent capture group" },
  { "~U_REGEX_INVALID_FLAG", "invalid value for match mode flags" },
  { "~U_REGEX_INVALID_RANGE", "in a character range [x-y], x is greater than y" },
  { "~U_REGEX_INVALID_STATE", "RegexMatcher in invalid state for requested operation" },
  { "~U_REGEX_LOOK_BEHIND_LIMIT", "look-behind pattern matches must have a bounded maximum length" },
  { "~U_REGEX_MAX_LT_MIN", "in {min,max}, max is less than min" },
  { "~U_REGEX_MISMATCHED_PAREN", "incorrectly nested parentheses" },
  { "~U_REGEX_MISSING_CLOSE_BRACKET", "missing closing bracket on a bracket expression" },
  { "~U_REGEX_NUMBER_TOO_BIG", "decimal number is too large" },
  { "~U_REGEX_OCTAL_TOO_BIG", "octal character constants must be <= 0377" },
  { "~U_REGEX_PROPERTY_SYNTAX", "incorrect Unicode property" },
  { "~U_REGEX_RULE_SYNTAX", "syntax error" },
  { "~U_REGEX_SET_CONTAINS_STRING", "can not have UnicodeSets containing strings" },
  { "~U_REGEX_STACK_OVERFLOW", "backtrack stack overflow" },
  { "~U_REGEX_STOPPED_BY_CALLER", "matching operation aborted by user callback fn" },
  { "~U_REGEX_TIME_OUT", "maximum allowed match time exceeded" },
  { "~U_REGEX_UNIMPLEMENTED", "use of regular expression feature that is not yet implemented" },
  { "~UnbalancedChar", "missing '$3'" },
  { "~UnexpectedElement", "unexpected element" },
  { "~WindowClause11", "window clause only available in XQuery 1.1 or later" },
  { "~WrongWordNetEndianness", "wrong endianness" },
  { "~Zorba API error", "Zorba API error" },
  { "~Zorba data-definition error", "Zorba data-definition error" },
  { "~Zorba error", "Zorba error" },
  { "~Zorba serialization error", "Zorba serialization error" },
  { "~Zorba store error", "Zorba store error" },
  { "~dynamic error", "dynamic error" },
  { "~error", "error" },
  { "~format_integer_bad_picture_format", "format-integer: bad $picture format: $2" },
  { "~format_integer_duplicated_optional_format_modifier", "format-integer: duplicated optional format modifier $2" },
  { "~format_integer_optional_format_modifier_not_closed", "format-integer: bad optional format modifier, cannot find closing ')' " },
  { "~format_integer_picture_empty", "format-integer: $picture parameter should not be empty" },
  { "~format_integer_unknown_optional_format_modifier_character", "format-integer: unknown optional format modifier character $2" },
  { "~format_integer_value_1_10", "format-integer: $value should be between 1 and 10 for this formatting picture" },
  { "~format_integer_value_1_20", "format-integer: $value should be between 1 and 20 for this formatting picture" },
  { "~format_integer_value_gt_3000", "format-integer: $value should be less than 3000 for Roman representation" },
  { "~operating system error", "operating system error" },
  { "~serialization error", "serialization error" },
  { "~static error", "static error" },
  { "~type error", "type error" },
  { "~user-defined error", "user-defined error" },

};
DEF_DICT_END(en);

///////////////////////////////////////////////////////////////////////////////

} // namespace dict
} // namespace err
} // namespace zorba
/* vim:set et sw=2 ts=2: */

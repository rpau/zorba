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
#include "common/common.h"
#include "system/globalenv.h"
#include "common/shared_types.h"
#include <zorbatypes/xerces_xmlcharray.h>
#include "store/api/item_factory.h"
#include "store/api/pul.h"
#include "store/api/copymode.h"

#include "types/casting.h"
#include "types/delegating_typemanager.h"
#include "types/schema/schema.h"
#include "types/schema/SchemaValidator.h"
#include "types/schema/StrX.h"
#include "types/typeimpl.h"
#include "types/typeops.h"

#include "context/static_context.h"
#include "context/collation_cache.h"
#include "context/namespace_context.h"
#include "compiler/parser/query_loc.h"

#include "zorbaerrors/error_messages.h"
#include "zorbaerrors/errors.h"

//using namespace std;

namespace zorba
{

#ifndef ZORBA_NO_XMLSCHEMA
    
void validateAfterUpdate(zorba::store::Item* item, zorba::store::Item_t& pul,
    static_context* staticContext, const QueryLoc& loc);

void processElement( store::Item_t& pul, static_context* staticContext, 
    DelegatingTypeManager* delegatingTypeManager, SchemaValidator& schemaValidator, 
    store::Item_t element);
    
void validateAttributes( SchemaValidator& schemaValidator, store::Iterator_t attributes);
    
void processAttributes( store::Item_t& pul, namespace_context& nsCtx, 
    DelegatingTypeManager* delegatingTypeManager, SchemaValidator& schemaValidator, 
    store::Item* parent, store::Iterator_t attributes);
        
void processChildren( store::Item_t& pul, static_context* staticContext, 
    namespace_context& nsCtx, DelegatingTypeManager* delegatingTypeManager, 
    SchemaValidator& schemaValidator, store::Iterator_t children,
    std::vector<store::Item_t>& typedValues);
    
void processNamespaces ( SchemaValidator& schemaValidator, const store::Item *item);

void processTextValue (store::Item_t& pul, DelegatingTypeManager* delegatingTypeManager, 
    namespace_context &nsCtx, store::Item_t typeQName, xqpStringStore_t& textValue, 
    store::Item_t& originalChild, std::vector<store::Item_t> &resultList);

store::Item_t findAttributeItem(const store::Item *parent, store::Item_t &attQName);    

bool typeHasValue(xqtref_t t);
bool typeHasTypedValue(xqtref_t t);
bool typeHasEmptyValue(xqtref_t t);

#endif //ZORBA_NO_XMLSCHEMA
    


/**
 *   Given a vector of root nodes, this method validates all of them and 
 *   fills out pul with a list of changes that will be applied later, if
 *   the validation succeds. This should be called after an update.
 */
void validateAfterUpdate(
    const std::set<zorba::store::Item*>& nodes,
    zorba::store::Item_t& pul,
    static_context* staticContext, 
    const QueryLoc& loc)
{
//#if 0
#ifndef ZORBA_NO_XMLSCHEMA
    std::set<zorba::store::Item*>::const_iterator it = nodes.begin();
    std::set<zorba::store::Item*>::const_iterator end = nodes.end();
    for (; it != end; it++)
    {
        validateAfterUpdate(*it, pul, staticContext, loc);
    }
#endif //ZORBA_NO_XMLSCHEMA
//#endif
}

#ifndef ZORBA_NO_XMLSCHEMA
void validateAfterUpdate(
    store::Item* item,
    zorba::store::Item_t& pul,
    static_context* staticContext, 
    const QueryLoc& loc)
{
    ZORBA_ASSERT(item->isNode());
        
    TypeManager* typeManager = staticContext->get_typemanager();
    
    DelegatingTypeManager* delegatingTypeManager = 
        static_cast<DelegatingTypeManager*>(typeManager);
        
    bool isLax = true; //staticContext->isLax();
        
    Schema* schema = delegatingTypeManager->getSchema();
    if ( !schema )
    {
        // no schema available no change to pul
        return;
    }
        
    SchemaValidator schemaValidator = SchemaValidator(delegatingTypeManager, 
                                                        schema->getGrammarPool(),
                                                        isLax,
                                                        loc);
        
    switch ( item->getNodeKind() )
    {
    case store::StoreConsts::documentNode:
    {
        //cout << "Validate after update document" << "\n"; cout.flush();
    
        schemaValidator.startDoc();
    
        store::NsBindings bindings;
        namespace_context nsCtx = namespace_context(staticContext, bindings);
            
        std::vector<store::Item_t> typedValues;
        processChildren(pul,
                        staticContext,
                        nsCtx,
                        delegatingTypeManager,
                        schemaValidator, 
                        item->getChildren(),
                        typedValues);
    
        schemaValidator.endDoc();
    
        //cout << "End Validate after update doc" << "\n"; cout.flush();
        return;
    }
    case store::StoreConsts::elementNode: 
    {
        //cout << "Validate  after update element" << "\n"; cout.flush();
    
        schemaValidator.startDoc();
    
        processElement(pul,
                    staticContext,
                    delegatingTypeManager,
                    schemaValidator,
                    item);
    
        schemaValidator.endDoc();
            
        //cout << "End Validate  after update elem" << "\n"; cout.flush();
        return;
    }
    default:
        ZORBA_ERROR_LOC_DESC( XQDY0061, loc, 
                "Argument in validate expression not a document or element node.");
        return;
    }
}


void processElement(
    store::Item_t& pul,
    static_context* staticContext, 
    DelegatingTypeManager* delegatingTypeManager,
    SchemaValidator& schemaValidator, 
    store::Item_t element)
{
    ZORBA_ASSERT(element->isNode());
    ZORBA_ASSERT(element->getNodeKind() == store::StoreConsts::elementNode);
    
    store::Item_t nodeName = element->getNodeName();
    xqpStringStore_t baseUri = element->getBaseURI();
    
    //cout << " vup    - processElement: " << nodeName->getLocalName()->c_str()
    //    << " @ " << nodeName->getNamespace()->c_str() << "\n"; cout.flush();
            
    schemaValidator.startElem(nodeName);
    
    // namespace declarations must go first
    processNamespaces( schemaValidator, element);
        
    // since the type of an element is determined only after the validator
    // receives all of it's attributes, and an attribute node needs it's
    // parent when created we need to go through the attributes twice: once
    // for validation and once for creation
    validateAttributes(schemaValidator, element->getAttributes());
        
    store::Item_t typeQName = schemaValidator.getTypeQName();
    
    //cout << " vup      - elemType old: " 
    //    << element->getType()->getLocalName()->c_str() << " @ "
    //    << element->getType()->getNamespace()->c_str() << "\n"; cout.flush();
    //cout << " vup      - elemType new: " << typeQName->getLocalName()->c_str()
    //    << " @ " << typeQName->getNamespace()->c_str() << "\n"; cout.flush();
    
    bool isNewType = false;
    TypeIdentifier_t newTypeIdent;
    xqtref_t newType;
    bool tHasValue;
    bool tHasTypedValue;
    bool tHasEmptyValue;
    store::PUL* p;
    store::Item_t elm;
    
    if ( !typeQName->equals(element->getType()) )
    {
        isNewType = true;
        newTypeIdent = TypeIdentifier::createNamedType(typeQName->getNamespace(),
                                                    typeQName->getLocalName() );
        
        newType = delegatingTypeManager->create_type(*newTypeIdent);
        
        tHasValue      = typeHasValue(newType);
        tHasTypedValue = typeHasTypedValue(newType);
        tHasEmptyValue = typeHasEmptyValue(newType);
        
        p = static_cast<store::PUL *>(pul.getp());
        elm = element;
    }
    
    store::NsBindings bindings;
    element->getNamespaceBindings(bindings);
    namespace_context nsCtx = namespace_context(staticContext, bindings);
            
    processAttributes(pul, nsCtx, delegatingTypeManager, schemaValidator, element, element->getAttributes());
        
    std::vector<store::Item_t> typedValues;
    processChildren(pul, staticContext, nsCtx, delegatingTypeManager, schemaValidator, 
                    element->getChildren(), typedValues);
    
    if ( isNewType )
    {    
        //cout << " vup        - addSetElementType: " << elm->getNodeName()->getLocalName()->str() << "   " << newTypeIdent->getLocalName() << " @ " << newTypeIdent->getUri() << "\n"; cout.flush();
        //cout << " vup             - " << ( tHasTypedValue ? "hasTypedValue" : "" ) << " values.size: " << typedValues.size() << (typedValues.size()>0 ? " [0]=" + typedValues[0]->getStringValue()->str() : "" ) << ( tHasValue ? " hasValue" : "" ) << ( tHasEmptyValue ? " hasEmptyValue" : "" ) << "\n"; cout.flush();
            
        p->addSetElementType(elm,
                            typeQName,
                            (std::vector<store::Item_t>&)typedValues,
                            tHasValue, 
                            tHasEmptyValue,
                            tHasTypedValue,
                            element->isId(),
                            element->isIdRefs());
    }    

    schemaValidator.endElem(nodeName);
}


void validateAttributes( SchemaValidator& schemaValidator, store::Iterator_t attributes)
{
    store::Item_t attribute;
    
    while ( attributes->next(attribute) )
    {
        ZORBA_ASSERT(attribute->isNode());
        ZORBA_ASSERT(attribute->getNodeKind() == store::StoreConsts::attributeNode);

        //cout << " vup    - attr: " << attribute->getNodeName()->getLocalName()->c_str() << "\n"; cout.flush();
                    
        store::Item_t attName = attribute->getNodeName();
        schemaValidator.attr(attName, attribute->getStringValue());
    }
}


void processAttributes( store::Item_t& pul, namespace_context& nsCtx, 
    DelegatingTypeManager* delegatingTypeManager, SchemaValidator& schemaValidator, 
    store::Item* parent, store::Iterator_t attributes)
{
    std::list<AttributeValidationInfo*>* attList = schemaValidator.getAttributeList();
    std::list<AttributeValidationInfo*>::iterator curAtt;
    std::vector<store::Item_t> defaultAtts;    
        
    for( curAtt = attList->begin() ; curAtt != attList->end(); ++curAtt )
    {
        AttributeValidationInfo* att = *curAtt;
        //cout << " vup        - processATT2: " << att->_localName << " T: " << att->_typeName << "\n";
            
        store::Item_t attQName;
        GENV_ITEMFACTORY->createQName( attQName, att->_uri, att->_prefix, att->_localName);
        
        store::Item_t attrib = findAttributeItem(parent, attQName);
        
        std::string typePrefix;
        if ( std::strcmp(Schema::XSD_NAMESPACE, att->_typeURI->c_str() )==0 ) // hack around typeManager bug for comparing QNames
            typePrefix = "xs";
        else
            typePrefix = "";
        
        store::Item_t typeQName;
        GENV_ITEMFACTORY->createQName(typeQName, att->_typeURI, new xqpStringStore(typePrefix), att->_typeName);
     
        
        std::vector<store::Item_t> typedValues;        
        processTextValue(pul, delegatingTypeManager, nsCtx, typeQName, att->_value, attrib, typedValues);
        
        if ( attrib==NULL )
        {
            // this is an attibute filled in by the validator
            store::Item_t defaultAttNode;
            if ( typedValues.size()==1 ) // hack around serialization bug
                GENV_ITEMFACTORY->createAttributeNode( defaultAttNode, parent, -1, attQName, 
                    typeQName, typedValues[0], false, false );
            else            
                GENV_ITEMFACTORY->createAttributeNode( defaultAttNode, parent, -1, attQName, 
                    typeQName, typedValues, false, false );
            
            defaultAtts.push_back(defaultAttNode);
        } 
        else if ( !typeQName->equals(attrib->getType()) )
        {
            store::PUL *p = static_cast<store::PUL *>(pul.getp());
            store::Item_t atr = store::Item_t(attrib);
            if ( typedValues.size()==1 )        // optimize when only one item is available 
                p->addSetAttributeType( atr, typeQName, (store::Item_t&)(typedValues[0]), attrib->isId(), attrib->isIdRefs() );
            else            
                p->addSetAttributeType( atr, typeQName, typedValues, attrib->isId(), attrib->isIdRefs() );
        }
    }
    
    if ( defaultAtts.size()>0 )
    {
        store::PUL *p = static_cast<store::PUL *>(pul.getp());
        store::CopyMode lCopyMode;
        bool typePreserve = true; //(sctx->construction_mode() == StaticContextConsts::cons_preserve ? true : false);
        bool nsPreserve = true; //(sctx->preserve_mode() == StaticContextConsts::preserve_ns ? true : false);
        bool nsInherit = true; //(sctx->inherit_mode() == StaticContextConsts::inherit_ns ? true : false);
        lCopyMode.set(true, typePreserve, nsPreserve, nsInherit);
        
        store::Item_t parentElem = store::Item_t(parent);
        p->addInsertAttributes(parentElem, defaultAtts, lCopyMode);
    }
}


void processChildren( 
    store::Item_t& pul,
    static_context* staticContext,
    namespace_context& nsCtx,
    DelegatingTypeManager* delegatingTypeManager, 
    SchemaValidator& schemaValidator,
    store::Iterator_t children,
    std::vector<store::Item_t>& typedValues)
{
    store::Item_t child;

    store::Item_t typeName;
    
    while ( children->next(child) )
    {
        if ( child->isNode() )
        {
            //cout << " vup  - processChildren: " << child->getType()->getLocalName()->c_str() << "\n"; cout.flush();
            
            switch ( child->getNodeKind() )
            { 
            case store::StoreConsts::elementNode:                                     
                processElement( pul, staticContext, delegatingTypeManager, schemaValidator, child);
                break;
                
            case store::StoreConsts::attributeNode:
                ZORBA_ASSERT(false);
                break;
            
            case store::StoreConsts::documentNode:
                ZORBA_ASSERT(false);                    
                break;
            
            case store::StoreConsts::textNode:
                {
                    //cout << " vup        - pC text: '" << child->getStringValue()->normalizeSpace()->str() << "'\n"; cout.flush();
                    xqpStringStore_t childStringValue = child->getStringValue();
                    schemaValidator.text(childStringValue);
    
                    store::Item_t typeQName = schemaValidator.getTypeQName();
                    
                    processTextValue(pul,
                                    delegatingTypeManager,
                                    nsCtx,
                                    typeQName,
                                    childStringValue,
                                    child,
                                    typedValues );                        
                }
                break;
            
            case store::StoreConsts::piNode:
                //cout << " vup        - pi: " << child->getStringValue() << "\n"; cout.flush();
                // do nothing
                break;
            
            case store::StoreConsts::commentNode:
                //cout << " vup        - comment: " << child->getStringValue() << "\n"; cout.flush();
                // do nothing
                break;
            
            case store::StoreConsts::anyNode:
                //cout << " vup        - any: " << child->getStringValue() << "\n"; cout.flush();
                ZORBA_ASSERT(false);                    
                break;
                                
            default:
                ZORBA_ASSERT(false);
            }
        }
    }
}

void processNamespaces ( SchemaValidator& schemaValidator, const store::Item *item)
{
    store::NsBindings bindings;
    item->getNamespaceBindings(bindings, store::StoreConsts::ONLY_LOCAL_NAMESPACES);

    for (unsigned long i = 0; i < bindings.size(); i++)
    {
        schemaValidator.ns( bindings[i].first.getStore(), bindings[i].second.getStore() );
    }
}

void processTextValue (store::Item_t& pul, DelegatingTypeManager* delegatingTypeManager, 
    namespace_context &nsCtx, store::Item_t typeQName, xqpStringStore_t& textValue, 
    store::Item_t& originalChild, std::vector<store::Item_t> &resultList)
{
    xqtref_t type = delegatingTypeManager->create_named_atomic_type(typeQName, TypeConstants::QUANT_ONE);
    //cout << " vup        - processTextValue: " << typeQName->getPrefix()->str() << ":" << typeQName->getLocalName()->str() << "@" << typeQName->getNamespace()->str() ; cout.flush();
    //cout << "           type: " << ( type==NULL ? "NULL" : type->toString()) << "\n"; cout.flush();                    
            
    store::Item_t result;                    
    if (type!=NULL)
    {
        if ( type->content_kind()==XQType::ELEMENT_ONLY_CONTENT_KIND || 
             type->content_kind()==XQType::MIXED_CONTENT_KIND )
            return;
            
        if ( type->type_kind() == XQType::USER_DEFINED_KIND )
        {
            const UserDefinedXQType udXQType = static_cast<const UserDefinedXQType&>(*type);
            if ( udXQType.isList() || udXQType.isUnion() )
            {
                xqp_string str(textValue);
                delegatingTypeManager->getSchema()->
                    parseUserSimpleTypes(str, type, resultList);
                
                return;
            }
            else if ( udXQType.isComplex() )
            {   // text in mixed content, 
                //  - if invalid there will be a validation exception thrown
                //  - if xmlspace or mixed content it's fine to have the same node               
                //resultList.push_back(originalChild);                
                return;
            }
            // else isAtomic
        }

        bool isResult = GenericCast::instance()->castToAtomic(result, textValue, type.getp(), &nsCtx);
        if ( isResult )
            resultList.push_back(result);
    }
    else
    {
        if ( GENV_ITEMFACTORY->createUntypedAtomic( result, textValue) )
            resultList.push_back(result);
    }
}

store::Item_t findAttributeItem(const store::Item *parent, store::Item_t &attQName)
{
    store::Iterator_t attributes = parent->getAttributes();
    
    store::Item_t attribute;
    
    while ( attributes->next(attribute) )
    {
        ZORBA_ASSERT(attribute->isNode());
        ZORBA_ASSERT(attribute->getNodeKind() == store::StoreConsts::attributeNode);
                  
        store::Item_t currentAttName = attribute->getNodeName();
        
        if ( attQName->getLocalName()->
                compare(currentAttName->getLocalName())==0 && 
             attQName->getNamespace()->
                compare(currentAttName->getNamespace())==0 )
        {
            return attribute.getp();
        }
    }
    ZORBA_ASSERT(false);
    return NULL;
}

/**
  - haveValue : True if the element has a typed value. 
  The only case when an element node N does not have a typed value is when the type of N 
  is a complex type with element-only content. So, this flag is a function of the element's
  type only; not of the actual content of an element instance.
 */
bool typeHasValue(xqtref_t t)
{
  return (t->content_kind()==XQType::MIXED_CONTENT_KIND ||
          t->content_kind()==XQType::SIMPLE_CONTENT_KIND);
}

/**
  - haveTypedValue : True if the element has a non-empty typed value and the type of that 
  value is something other than untypedAtomic. This can happen only if the type of the 
  element node is a simple type or a complex type with simple content (i.e., the element 
  has no sub-elements). Again this flag is a function of the element's type only; not of 
  the actual content of an element instance.
 */
bool typeHasTypedValue(xqtref_t t)
{
  return t->content_kind()==XQType::SIMPLE_CONTENT_KIND &&
         !( TypeOps::is_equal(*t, *GENV_TYPESYSTEM.UNTYPED_TYPE) ||
            TypeOps::is_equal(*t, *GENV_TYPESYSTEM.ANY_TYPE) ||
            TypeOps::is_equal(*t, *GENV_TYPESYSTEM.UNTYPED_ATOMIC_TYPE_ONE) );
}

/**
  - haveEmptyValue : True if the typed value of the element is the empty sequence. 
  This can happen only if "the element has a complex type with empty content" 
  (quote from the spec). This flag also is a function of the element's type only.
 */
bool typeHasEmptyValue(xqtref_t t)
{
  return t->content_kind()==XQType::EMPTY_CONTENT_KIND;
}

#endif //ZORBA_NO_XMLSCHEMA

}// namespace zorba

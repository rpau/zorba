
#include <stack>

#include "system/globalenv.h"
#include "errors/error_manager.h"
#include "util/Assert.h"

#include "store/api/copymode.h"
#include "store/naive/store_defs.h"
#include "store/naive/simple_store.h"
#include "store/naive/node_updates.h"
#include "store/naive/node_items.h"
#include "store/naive/atomic_items.h"
#include "store/naive/basic_item_factory.h"
#include "zorbatypes/datetime.h"
#include "zorbatypes/duration.h"


namespace zorba { namespace store {


/*******************************************************************************

********************************************************************************/
void XmlNode::removeType(TypeUndoList& undoList)
{
  if (getNodeKind() == StoreConsts::elementNode)
  {
    ElementNode* n = reinterpret_cast<ElementNode*>(this);

    if (! n->theTypeName->equals(GET_STORE().theUntypedType, NULL))
    {
      NodeTypeInfo tinfo(n->theTypeName, n->isId(), n->isIdRefs());

      undoList.push_back(std::pair<XmlNode*, NodeTypeInfo>(n, tinfo));

      n->resetIsId();
      n->resetIsIdRefs();

      n->theTypeName = GET_STORE().theAnyType;

      if (n->theParent && n->theParent->getNodeKind() == StoreConsts::elementNode)
        n->theParent->removeType(undoList);
    }
  }
  else if (getNodeKind() == StoreConsts::attributeNode)
  {
    AttributeNode* n = reinterpret_cast<AttributeNode*>(this);

    NodeTypeInfo tinfo(n->theTypeName, n->isId(), n->isIdRefs());

    undoList.push_back(std::pair<XmlNode*, NodeTypeInfo>(n, tinfo));

    n->theTypeName = GET_STORE().theUntypedAtomicType;

    n->resetIsId();
    n->resetIsIdRefs();

    if (n->theParent != NULL)
      n->theParent->removeType(undoList);
  }
  else
  {
    ZORBA_FATAL(0, "");
  }
}


/*******************************************************************************

********************************************************************************/
void XmlNode::setToUntyped()
{
  if (getNodeKind() == StoreConsts::elementNode)
  {
    ElementNode* n = reinterpret_cast<ElementNode*>(this);

    n->theTypeName = GET_STORE().theUntypedType;

    n->resetIsId();
    n->resetIsIdRefs();

    ulong numAttrs = n->numAttributes();
    for (ulong i = 0; i < numAttrs; i++)
    {
      n->getAttr(i)->setToUntyped();
    }

    ulong numChildren = n->numChildren();
    for (ulong i = 0; i < numChildren; i++)
    {
      XmlNode* child = n->getChild(i);
      if (child->getNodeKind() == StoreConsts::elementNode)
        child->setToUntyped();
    }
  }
  else if (getNodeKind() == StoreConsts::attributeNode)
  {
    AttributeNode* n = reinterpret_cast<AttributeNode*>(this);

    n->theTypeName = GET_STORE().theUntypedAtomicType;

    n->resetIsId();
    n->resetIsIdRefs();
  }
  else
  {
    ZORBA_FATAL(0, "");
  }
}


/*******************************************************************************

********************************************************************************/
void XmlNode::revalidate()
{
}


/*******************************************************************************

********************************************************************************/
void XmlNode::insertChildren(
    std::vector<Item_t>& newChildren,
    ulong                pos,
    bool                 copy,
    const CopyMode&      copymode)
{
  ulong numNewChildren = newChildren.size();
  for (ulong i = 0; i < numNewChildren; i++)
  {
    XmlNode* child = BASE_NODE(newChildren[i]);

    if (copy)
    {
      child->copy(this, this, pos + i, copymode);
    }
    else
    {
      ZORBA_FATAL(child->isConstructed(), "");

      child->switchTree(getTree(), this, pos + i, true);

      children().insert(child, pos + i, false);
    }
  }
}


/*******************************************************************************

********************************************************************************/
void XmlNode::insertChildrenFirst(
    std::vector<Item_t>& newChildren,
    bool                 copy,
    const CopyMode&      copymode)
{
  ulong numNewChildren = newChildren.size();
  for (long i = numNewChildren - 1; i >= 0; i--)
  {
    XmlNode* child = BASE_NODE(newChildren[i]);

    if (copy)
    {
      child->copy(this, this, 0, copymode);
    }
    else
    {
      ZORBA_FATAL(child->isConstructed(), "");

      child->switchTree(getTree(), this, 0, true);

      this->children().insert(child, 0, false);
    }
  }
}


/*******************************************************************************

********************************************************************************/
void XmlNode::insertChildrenLast(
    std::vector<Item_t>& newChildren,
    bool                 copy,
    const CopyMode&      copymode)
{
  insertChildren(newChildren, numChildren(), copy, copymode);
}


/*******************************************************************************

********************************************************************************/
void XmlNode::insertSiblingsBefore(
    std::vector<Item_t>& siblings,
    bool                 copy,
    const CopyMode&      copymode)
{
  ZORBA_FATAL(theParent, "");

  ElementNode* parent = reinterpret_cast<ElementNode*>(theParent);

  ulong pos = parent->children().find(this);

  if (pos == 0)
    parent->insertChildrenFirst(siblings, copy, copymode);
  else
    parent->insertChildren(siblings, pos, copy, copymode);
}


/*******************************************************************************

********************************************************************************/
void XmlNode::insertSiblingsAfter(
    std::vector<Item_t>& siblings,
    bool                 copy,
    const CopyMode&      copymode)
{
  ZORBA_FATAL(theParent, "");

  ElementNode* parent = reinterpret_cast<ElementNode*>(theParent);

  ulong pos = parent->children().find(this);
  pos++;

  parent->insertChildren(siblings, pos, copy, copymode);
}


/*******************************************************************************

********************************************************************************/
void XmlNode::replaceChild(
    std::vector<Item_t>& newChildren,
    ulong                pos,
    bool                 copy,
    const CopyMode&      copymode)
{
  removeChild(pos);

  ulong numNewChildren = newChildren.size();

  for (ulong i = 0; i < numNewChildren; i++)
  {
    XmlNode* child = BASE_NODE(newChildren[i]);

    if (copy)
    {
      child->copy(this, this, pos + i, copymode);
    }
    else
    {
      ZORBA_FATAL(child->isConstructed(), "");

      child->switchTree(getTree(), this, pos + i, true);

      children().insert(child, pos + i, false);
    }
  }
}


/*******************************************************************************

********************************************************************************/
void ElementNode::insertAttributes(
    std::vector<Item_t>& attrs,
    bool                 copy,
    const CopyMode&      copymode)
{
  ulong numAttrs = numAttributes();
  ulong numNewAttrs = attrs.size();

  for (ulong i = 0; i < numNewAttrs; i++)
  {
    AttributeNode* attr = reinterpret_cast<AttributeNode*>(attrs[i].getp());

    checkQName(reinterpret_cast<QNameItemImpl*>(attr->theName.getp()));
    checkUniqueAttr(attr->theName);

    if (copy)
    {
      attr->copy(this, this, numAttrs, copymode);
    }
    else
    {
      ZORBA_FATAL(attr->isConstructed(), "");

      attr->switchTree(getTree(), this, numAttrs + i, true);

      attributes().push_back(attr, false);
    }

    addBindingForQName(attr->getNodeName());
  }
}


/*******************************************************************************

********************************************************************************/
void ElementNode::replaceAttribute(
    std::vector<Item_t>& newAttrs,
    ulong                pos,
    bool                 copy,
    const CopyMode&      copymode)
{
  removeAttr(pos);

  ulong numNewAttrs = newAttrs.size();

  for (ulong i = 0; i < numNewAttrs; i++)
  {
    AttributeNode* attr = reinterpret_cast<AttributeNode*>(newAttrs[i].getp());

    checkQName(reinterpret_cast<QNameItemImpl*>(attr->theName.getp()));
    checkUniqueAttr(attr->theName);

    if (copy)
    {
      attr->copy(this, this, pos + i, copymode);
    }
    else
    {
      ZORBA_FATAL(attr->isConstructed(), "");

      attr->switchTree(getTree(), this, pos + i, true);

      attributes().insert(attr, pos + i, false);
    }

    addBindingForQName(attr->getNodeName());
  }
}


/*******************************************************************************
  Disconnect all the current children of "this" and make the given text node
  the only child of "this". Return a vector of pointers to the disconnected
  children.
********************************************************************************/
void ElementNode::replaceContent(
    XmlNode*          newTextChild,
    ConstrNodeVector& oldChildren)
{
  ulong numChildren = this->numChildren();
  for (ulong i = 0; i < numChildren; i++)
  {
    XmlNode* child = getChild(i);
    if (child->theParent == this)
      child->theParent = NULL;
  }

  children().copy(oldChildren);
  children().clear();

  newTextChild->theParent = this;
  newTextChild->setTree(getTree());

  newTextChild->theOrdPath = theOrdPath;
  newTextChild->theOrdPath.appendComp(1);

  children().push_back(newTextChild, false);
}


/*******************************************************************************
  Check if the ns binding implied by the given qname conflicts with the current
  ns bindings of "this" node.
********************************************************************************/
void ElementNode::checkQName(QNameItemImpl* newName)
{
  xqpStringStore* ns = findBinding(newName->getPrefixP());

  if (ns != NULL && ns->byteEqual(*newName->getNamespaceP()))
  {
    ZORBA_ERROR_DESC(ZorbaError::XUDY0024,
                     "The implied namespace binding of " << newName->show()
                     << " conflicts with namespace binding ["
                     << newName->getPrefixP() << ", " 
                     << newName->getNamespaceP() << "]");
  }
}


/*******************************************************************************

********************************************************************************/
void AttributeNode::replaceValue(
    xqpStringStore_t& newValue,
    xqpStringStore_t& oldValue)
{
  xqpStringStore_t tmp = theTypedValue->getStringValue();
  oldValue.transfer( tmp );
  theTypedValue = new UntypedAtomicItemImpl(newValue);
}


void TextNode::replaceValue(
    xqpStringStore_t& newValue,
    xqpStringStore_t& oldValue)
{
  oldValue.transfer(theContent);
  theContent = newValue;
}


void PiNode::replaceValue(
    xqpStringStore_t& newValue,
    xqpStringStore_t& oldValue)
{
  oldValue.transfer(theContent);
  theContent = newValue;
}


void CommentNode::replaceValue(
    xqpStringStore_t& newValue,
    xqpStringStore_t& oldValue)
{
  oldValue.transfer(theContent);
  theContent = newValue;
}


/*******************************************************************************

********************************************************************************/
void ElementNode::rename(Item_t& newName, Item_t& oldName)
{
  QNameItemImpl* qn = reinterpret_cast<QNameItemImpl*>(newName.getp());

  checkQName(qn);

  oldName.transfer(theName);
  theName.transfer(newName);

  addLocalBinding(qn->getPrefixP(), qn->getNamespaceP());
}


void AttributeNode::rename(Item_t& newName, Item_t& oldName)
{
  if (theParent)
  {
    ElementNode* parent = reinterpret_cast<ElementNode*>(theParent);

    QNameItemImpl* qn = reinterpret_cast<QNameItemImpl*>(newName.getp());
    parent->checkQName(qn);
    parent->addLocalBinding(qn->getPrefixP(), qn->getNamespaceP());
  }

  oldName.transfer(theName);
  theName.transfer(newName);
}


void PiNode::rename(xqpStringStore_t& newName, xqpStringStore_t& oldName)
{
  oldName.transfer(theTarget);
  theTarget.transfer(newName);
}

}
}

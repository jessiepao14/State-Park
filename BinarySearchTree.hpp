//Team 9
//BST template Class

#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include "BinaryTree.hpp"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode, int compare(ItemType *, ItemType *));

    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, ItemType *target, bool & success, int compare(ItemType *, ItemType *));

    // delete target node from tree, called by internal remove node
    BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType *successor);

    // search for target node
    BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, ItemType *target, int compare(ItemType *, ItemType *)) const;

    //private function for inOrderSameKey
    bool _inOrderSameKey(ItemType *target, void visit(ItemType *), int compare(ItemType *, ItemType *), BinaryNode<ItemType>*) const;

public:
    // insert a node at the correct location
    bool insert(ItemType *newEntry, int compare(ItemType *, ItemType*));
    // remove a node if found
    bool remove(ItemType *anEntry, int compare(ItemType *, ItemType *));
    // find a target node
    bool getEntry(ItemType *target, ItemType &returnedItem, int compare(ItemType *, ItemType *)) const;
    //visit nodes only with the same key, in order traversal
    bool inOrderSameKey(ItemType *, void visit(ItemType *), int compare(ItemType *, ItemType *)) const;

};


///////////////////////// public function definitions ///////////////////////////
//Inserting items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::insert(ItemType *newEntry, int compare(ItemType *, ItemType *))
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    this->rootPtr = _insert(this->rootPtr, newNodePtr, compare);
    this->count++;
    return true;
}

//Removing items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(ItemType *target, int compare(ItemType *, ItemType *))
{
    bool isSuccessful = false;
    this->rootPtr = _remove(this->rootPtr, target, isSuccessful, compare);
    this->count--;
    return isSuccessful;
}

//Finding entries within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(ItemType *anEntry, ItemType &returnedItem, int compare(ItemType *, ItemType *)) const
{
    BinaryNode<ItemType> *ptr = findNode(this->rootPtr, anEntry, compare);
    if (!ptr)
        return false;
    returnedItem = *ptr->getItem();
    return true;
}

//visit nodes with the same key, in order traversal
//used when there are multiple entries with information in common
template <class ItemType>
bool BinarySearchTree<ItemType>::inOrderSameKey(ItemType *target, void visit(ItemType *), int compare(ItemType *, ItemType *)) const
{
    if (_inOrderSameKey(target, visit, compare, this->rootPtr))
        return true;
    return false;
}



//////////////////////////// private functions ////////////////////////////////////////////

//Implementation of the insert operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
    BinaryNode<ItemType>* newNodePtr, int compare(ItemType *, ItemType *))
{
    if (nodePtr == 0)
    {
        nodePtr = newNodePtr;
        return nodePtr;
    }
    ItemType *newNodeItem =  newNodePtr->getItem();
    ItemType *nodeItem = nodePtr->getItem();
    if (compare(newNodeItem, nodeItem) == -1)//(newNodePtr->getItem() < nodePtr->getItem())
    {
        if (nodePtr->getLeftPtr() == 0)
            nodePtr->setLeftPtr(newNodePtr);
        else
            _insert(nodePtr->getLeftPtr(), newNodePtr, compare);
    }
    else //if compare == 0 or compare == 1, insert or set to the right
    {
        if (nodePtr->getRightPtr() == 0)
            nodePtr->setRightPtr(newNodePtr);
        else
            _insert(nodePtr->getRightPtr(), newNodePtr, compare);
    }

    return nodePtr;
}

//Implementation for the search operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
    ItemType *target, int compare(ItemType *, ItemType *)) const
{
    ItemType *nodeItem = nodePtr->getItem();
    ItemType *targetItem = target;
    if (compare(nodeItem, targetItem) == 0)//(nodePtr->getItem() == target)
        return nodePtr;
    if (nodePtr == 0)
        return NULL;
    else if (compare(nodeItem, targetItem) == 1)//(nodePtr->getItem() > target)
    {
        if (nodePtr->getLeftPtr() == 0)
            return NULL;
        return findNode(nodePtr->getLeftPtr(), target, compare);
    }
    else //if (compare(nodeItem, targetItem) == -1)//(nodePtr->getItem() < target)
    {
        if (nodePtr->getRightPtr() == 0)
            return NULL;
        return findNode(nodePtr->getRightPtr(), target, compare);
    }
}


////////////////////////////////////////////////////////////////////////
// The follwoing functions will be needed for the team project
//Implementation of the remove operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
    ItemType *target,
    bool & success, int compare(ItemType *, ItemType *))

{
    if (nodePtr == 0)
    {
        success = false;
        return 0;
    }
    ItemType *nodePtrItem = nodePtr->getItem();
    ItemType *targetItem = target;
    if (compare(nodePtrItem, targetItem) == 1)//(nodePtr->getItem() > target)
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success, compare));
    else if (compare(nodePtrItem, targetItem) == -1)//(nodePtr->getItem() < target)
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success, compare));
    else //node matches target
    {
        target = nodePtr->getItem();
        nodePtr = deleteNode(nodePtr);
        //target = nodePtr->getItem();
        success = true;
    }
    return nodePtr;
}

//Implementation of the delete operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr->isLeaf())
    {
        delete nodePtr;
        nodePtr = 0;
        return nodePtr;
    }
    else if (nodePtr->getLeftPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else if (nodePtr->getRightPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else
    {
        ItemType *newNodeValue = new StatePark();
        nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
        nodePtr->setItem(newNodeValue);
        return nodePtr;
    }
}

//Implementation to remove the left leaf
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
    ItemType *successor)
{
    if (nodePtr->getLeftPtr() == 0)
    {
        successor = nodePtr->getItem();
        return deleteNode(nodePtr);
    }
    else
    {
        nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
        return nodePtr;
    }
}

//implementation of searching for parks
//in the same city
template <class ItemType>
bool BinarySearchTree<ItemType>::_inOrderSameKey(ItemType *target, void visit(ItemType *), int compare(ItemType *, ItemType *),
    BinaryNode<ItemType> *nodePtr) const
{
    static bool found = false;
    ItemType *targetItem = target;
    if (nodePtr != 0)
    {
        _inOrderSameKey(target, visit, compare, nodePtr->getLeftPtr());
        ItemType *item = nodePtr->getItem();
        if (compare(item, targetItem) == 0)
        {
            visit(item);
            found = true;
        }
        _inOrderSameKey(target, visit, compare, nodePtr->getRightPtr());
    }
    return found;
}



#endif /* BinarySearchTree_hpp */

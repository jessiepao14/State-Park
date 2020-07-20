//Team 9
//Binary Tree Template Class

#ifndef BinaryTree_hpp
#define BinaryTree_hpp

#include "BinaryNode.hpp"
#include "Queue.hpp"


template<class ItemType>
class BinaryTree
{
protected:
    BinaryNode<ItemType>* rootPtr;        // ptr to root node
    int count;                            // number of nodes in tree

public:
    // "admin" functions
    BinaryTree(void) { rootPtr = 0; count = 0; }
    BinaryTree(const BinaryTree<ItemType> & tree) { }
    virtual ~BinaryTree() { }

    // common functions for all binary trees
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
    void clear() { destroyTree(rootPtr); rootPtr = 0; count = 0; }
    void preOrder(void visit(ItemType *)) const { _preorder(visit, rootPtr); }
    void inOrder(void visit(ItemType *)) const { _inorder(visit, rootPtr); }
    void postOrder(void visit(ItemType *)) const { _postorder(visit, rootPtr); }
    void breadthFirst(void visit(ItemType *));
    void printTree(void visit(ItemType *)) { _printTree(visit, 1, rootPtr); }
    
    
    // abstract functions to be implemented by derived class
    virtual bool insert(ItemType *newData, int compare(ItemType *, ItemType *)) = 0;
    virtual bool remove(ItemType *data, int compare(ItemType *, ItemType *)) = 0;
    virtual bool getEntry(ItemType *anEntry, ItemType &returnedItem, int compare(ItemType *, ItemType *)) const = 0;

private:
    // delete all nodes from the tree
    void destroyTree(BinaryNode<ItemType>* nodePtr);

    // internal traverse
    void _preorder(void visit(ItemType *), BinaryNode<ItemType>* nodePtr) const;
    void _inorder(void visit(ItemType *), BinaryNode<ItemType>* nodePtr) const;
    void _postorder(void visit(ItemType *), BinaryNode<ItemType>* nodePtr) const;
    void _printTree(void visit(ItemType *), int level, BinaryNode<ItemType> *nodePtr) const;
};

//Destroy the entire tree
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr->isLeaf())
        delete nodePtr;
    else if (nodePtr == 0)
        return;
    else
    {
        destroyTree(nodePtr->leftPtr);
        destroyTree(nodePtr->rightPtr);
        delete nodePtr;
    }
}

//Preorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType *), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        ItemType *item = nodePtr->getItem();
        visit(item);
        _preorder(visit, nodePtr->getLeftPtr());
        _preorder(visit, nodePtr->getRightPtr());
    }
}

//Inorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType *), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        _inorder(visit, nodePtr->getLeftPtr());
        ItemType* item = nodePtr->getItem();
        visit(item);
        _inorder(visit, nodePtr->getRightPtr());
    }
}

//Postorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType *), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        _postorder(visit, nodePtr->getLeftPtr());
        _postorder(visit, nodePtr->getRightPtr());
        ItemType item = nodePtr->getItem();
        visit(item);
    }
}

//print tree as indented list
template<class ItemType>
void BinaryTree<ItemType>::_printTree(void visit(ItemType *), int level, BinaryNode<ItemType> *nodePtr) const
{
    string indent = "     ";
    for (int i = 0; i < level - 1; i++)
    {
        cout << indent;
    }
    cout << "Level " << level << ". ";
    ItemType *item = nodePtr->getItem();
    visit(item);
    cout << endl;

    if (nodePtr->getRightPtr() != 0)
        _printTree(visit, level + 1, nodePtr->getRightPtr());
    if (nodePtr->getLeftPtr() != 0)
        _printTree(visit, level + 1, nodePtr->getLeftPtr());
}


//breadth first traversal
template <class ItemType>
void BinaryTree<ItemType>::breadthFirst(void visit(ItemType *))
{
    Queue<BinaryNode<ItemType> *> q;
    BinaryNode<ItemType> *temp = this->rootPtr;
    q.enqueue(temp);
    while (!q.isEmpty())
    {
        q.dequeue(temp);
        ItemType item = temp->getItem();
        visit(item);
        if (temp->getLeftPtr() != 0)
            q.enqueue(temp->getLeftPtr());
        if (temp->getRightPtr() != 0)
            q.enqueue(temp->getRightPtr());

    }
}

#endif /* BinaryTree_hpp */

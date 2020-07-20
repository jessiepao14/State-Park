//Team 9
//Binary Node Template Class

#ifndef BinaryNode_hpp
#define BinaryNode_hpp

#include "StatePark.hpp"
template<class ItemType>
class BinaryNode
{
private:
    ItemType              *item;         // Data portion
    BinaryNode<ItemType>* leftPtr;        // Pointer to left child
    BinaryNode<ItemType>* rightPtr;        // Pointer to right child

public:
    // constructors
    BinaryNode(ItemType * anItem) { item = anItem; leftPtr = 0; rightPtr = 0; }
    BinaryNode(ItemType *anItem,
        BinaryNode<ItemType>* left,
        BinaryNode<ItemType>* right) {
        item = anItem; leftPtr = left; rightPtr = right;
    }
    // setters
    void setItem(ItemType* anItem) { item = anItem; }
    void setLeftPtr(BinaryNode<ItemType>* left) { leftPtr = left; }
    void setRightPtr(BinaryNode<ItemType>* right) { rightPtr = right; }
    // getters
    ItemType* getItem() const { return item; }
    BinaryNode<ItemType>* getLeftPtr() const { return leftPtr; }
    BinaryNode<ItemType>* getRightPtr() const { return rightPtr; }




    bool isLeaf() const { return (leftPtr == 0 && rightPtr == 0); }

};

#endif /* BinaryNode_hpp */

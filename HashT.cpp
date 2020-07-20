// Team 9
// Hash Call Class

#include "HashT.hpp"
#include "LinkedList.hpp"
#include "ListNode.hpp"
#include <iostream>
using namespace std;

// Constructor
HashCell::HashCell()
{
    count = 0;
    //head = new ListNode;
    //head->setForw(head);
    //head->setBack(head);

}

//Destructor
HashCell::~HashCell()
{

}

//Overloaded Constructor
HashCell::HashCell(StatePark p, int c)
{
    park = p;
    count = c;
    //head = h;

}

// insertHash receives an instance of
// the StatePark class and inserts it
// into the linkedList and updates the count
void HashCell::insertHash(StatePark dataIn)
{
    list.insertNodeHash(dataIn);
    count++;

}

// printHashCell receives the HashCell
// class and calls the printHashList function
// to print the Hash Cell
void HashCell::printHashCell(HashCell dataIn)
{
    dataIn.list.printHashList(dataIn.list.printNodeHash);
}

// seach receives the HashCell class and StatePark class
// and the string of the park name. Calls the searchList function
// to look for the park in the hash
void HashCell :: Search(HashCell dataIn, StatePark &returnedItem,string n)
{
    dataIn.list.searchList(returnedItem,n);
}

// Delete receives the HashCell class and a string
// of the park name to delete. Calls the deleteNodeHash
// function to delete the park
void HashCell :: Delete(HashCell dataIn, string n)
{
    dataIn.list.deleteNodeHash(n);
}

// getFirstList receives a HashCell and StatePark class
// and gets the item of the list
void HashCell :: getFirstList(HashCell dataIn, StatePark & returnedItem)
{
    ListNode* temp = dataIn.list.getHead();
    returnedItem = temp->getPark();
    //call delete node
    dataIn.list.deleteNode(returnedItem);


}

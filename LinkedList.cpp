//Team 9
//LinkedList class

#include <iomanip>
#include <iostream>
#include "LinkedList.hpp"
#include "HashFunc.hpp"
#include <string>
using namespace std;

//**************************************************
// Constructor
// This function allocates and initializes a sentinel node
//      A sentinel (or dummy) node is an extra node added before the first data record.
//      This convention simplifies and accelerates some list-manipulation algorithms,
//      by making sure that all links can be safely dereferenced and that every list
//      (even one that contains no data elements) always has a "first" node.
//**************************************************
LinkedList::LinkedList()
{
    head = new ListNode;
    head->setForw(head);
    head->setBack(head);
    count = 0;
}

//**************************************************
// printHeader prints the header to a list
// of nodes. It is designed to be a callback
// function to be used by the traveral functions
//**************************************************
void LinkedList::printHeader()
{
    cout << "===== =============== ==== ===== ==============================================" << endl;
    cout << " Zip  City            Year Acres Park Name                                     " << endl;
    cout << "===== =============== ==== ===== ==============================================" << endl;

}

//**************************************************
// printNode receives a pointer to a const ListNode
// and prints the contents of a node of a linked
// list. It is designed to be a callback function
// to be called by the traveral functions.
//**************************************************
void LinkedList::printNode(const ListNode* pCur)
{
    cout << left << setw(5) << pCur->getPark().getZip() << " "
        << setw(15) << pCur->getPark().getCity() << " "
        << setw(4) << pCur->getPark().getYear() << " " << right
        << setw(5) << pCur->getPark().getAcres() << " " << left
        << setw(15) << pCur->getPark().getName() << endl;
}

//**************************************************
// printNodeHash receives a pointer to a const ListNode
// and prints Park name. It is designed to be a
// callback function to be called by the traveral functions.
//**************************************************
void LinkedList::printNodeHash(const ListNode* pCur)
{
    cout  << "---->" << pCur->getPark().getName();
}

//**************************************************
// printHashList receives a print function
// and uses the function to print the hash
//**************************************************
void LinkedList::printHashList(void printN(const ListNode* pCur)) const
{
    ListNode *pCur;
    pCur = head->getForw();
    while(pCur != head)
    {
        printNodeHash(pCur);
        pCur = pCur->getForw();
    }

}


//**************************************************
// printFooter prints the footer to a list
// of nodes. It is designed to be a callback
// function to be used by the traveral functions
//**************************************************
void LinkedList::printFooter()
{
    cout << "===== =============== ==== ===== ==============================================" << endl;
}


//**************************************************
// traverseForward receives function pointers to the
// printHeader, printNode, and printFooter functions.
// By calling the print functions, traverseForward
// displays the contents of the linked list in
// forward order from head.
//**************************************************
void LinkedList::traverseForward(void printN(const ListNode* pCur),
    void printH(), void printF()) const
{
    ListNode *pCur;
    pCur = head->getForw();
    printH();    // call to printHeader()
    while(pCur != head)
    {
        printN(pCur);    // call to printNode()
        pCur = pCur->getForw();
    }
    printF();    // call to printFooter()
}

//**************************************************
// traverseBackward receives function pointers to the
// printHeader, printNode, and printFooter functions.
// By calling the print functions, traverseBackward
// displays the contents of the linked list, in
// reverse order from back.
//**************************************************
void LinkedList::traverseBackward(void printN(const ListNode* pCur),
    void printH(), void printF()) const
{
    ListNode *pCur;
    pCur = head->getBack();
    printH();
    while (pCur != head)
    {
        printN(pCur);
        pCur = pCur->getBack();
    }
    printF();
}

////**************************************************
//// The searchList function looks for a target city
//// in the sorted linked list: if found, it returns true
//// and copies the data in that node to the output parameter
////**************************************************
bool LinkedList::searchList(StatePark& dataOut, string n)
{
    bool found = false;
    ListNode *pCur = head->getForw();


    while(pCur != head && found == false)
    {


        if(pCur != head && pCur->getPark().getName() == n )
        {
            dataOut = pCur->getPark();
            found = true;
        }
        pCur = pCur->getForw();

    }
    return found;
}

//**************************************************
// The insertNode function inserts a new node in a
// sorted linked list
//**************************************************
void LinkedList::insertNode(StatePark dataIn)
{
    ListNode *newNode;
    ListNode *pPre;
    ListNode *pCur;
    newNode = new ListNode;
    newNode->setPark(dataIn);

    pPre = head;
    pCur = head->getForw();
    while(pCur != head )
    {
        pPre = pCur;
        pCur = pCur->getForw();
    }
    newNode->setForw(pPre->getForw());    // pNew->forw
    newNode->setBack(pPre);                // pNew->back
    pPre->getForw()->setBack(newNode);    // pPre->forw->back
    pPre->setForw(newNode);                // pPre->forw

    count++;
}

//**************************************************
// insertNodeHash receives an instance of the
// StatPark class and inserts it into the hash
// and updates the counter
//**************************************************
void LinkedList::insertNodeHash(StatePark dataIn)
{

    ListNode *newNode;
    ListNode *pPre;
    ListNode *pCur;
    newNode = new ListNode;
    newNode->setPark(dataIn);

    pPre = head;
    pCur = head->getForw();


    while(pCur != head)
    {
        pPre = pCur;
        pCur = pCur->getForw();
    }
    newNode->setForw(pPre->getForw());    // pNew->forw
    newNode->setBack(pPre);                // pNew->back
    pPre->getForw()->setBack(newNode);    // pPre->forw->back
    pPre->setForw(newNode);                // pPre->forw

    count++;
}

//**************************************************
// The deleteNode function searches for a node
// in a sorted linked list; if found, the node is
// deleted from the list and from memory.
//**************************************************
bool LinkedList::deleteNode(StatePark targetPark)
{
    ListNode *pCur;
    bool deleted = false;

    pCur = head->getForw();
    while(pCur != head && pCur->getPark() < targetPark)
    {
        pCur = pCur->getForw();
    }

    if(pCur != head && pCur->getPark() == targetPark)
    {
        pCur->getBack()->setForw(pCur->getForw());
        pCur->getForw()->setBack(pCur->getBack());
        delete pCur;
        deleted = true;
        count--;
    }
    return deleted;
}

//**************************************************
// deleteNodeHash receives a sting of the park name
// and searches for that park in the hash
// if it is found then that park is removed
//**************************************************
bool LinkedList::deleteNodeHash(string targetPark)
{
    ListNode *pCur;
    bool deleted = false;

    pCur = head->getForw();
    while(pCur != head && pCur->getPark().getName() < targetPark)
    {
        pCur = pCur->getForw();
    }

    if(pCur != head && pCur->getPark().getName() == targetPark)
    {
        pCur->getBack()->setForw(pCur->getForw());
        pCur->getForw()->setBack(pCur->getBack());
        delete pCur;
        deleted = true;
        count--;
    }
    return deleted;
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************
LinkedList::~LinkedList()
{
    /*
    ListNode *pCur;
    ListNode *pForw;

    pCur = head->getForw();
    while(pCur != head)
    {
        pForw = pCur->getForw();
        cout << "DEBUG - Destructor: Now deleting " << pCur->getPark().getName() << endl;
        delete pCur;
        pCur = pForw;
    }
    cout << "DEBUG - Destructor: Now deleting the sentinel node: " << head->getPark().getYear() << endl;
    delete head;*/
}

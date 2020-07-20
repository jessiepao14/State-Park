//Team 9
//Linked List Class

#ifndef LinkedList_hpp
#define LinkedList_hpp

#include "ListNode.hpp"

class LinkedList{
private:
    ListNode node;
    ListNode *head;
    int count;

public:
    LinkedList();   // Constructor
    ~LinkedList();  // Destructor

    // Linked list operations
    int getCount() const {return count;}
    void insertNode(StatePark);


    bool deleteNode(StatePark);
    static void printHeader();
    static void printNode(const ListNode*);


    static void printFooter();
    void traverseForward(void printN(const ListNode* pCur),
    void printH(), void printF()) const;
    void traverseBackward(void printN(const ListNode* pCur),
        void printH(), void printF()) const;
    bool searchList(StatePark&, string n);
    bool isEmpty() const { if (!count) return true; else return false; }

    //functions for hash
     void printHashList(void printN(const ListNode* pCur)) const;
     static void printNodeHash(const ListNode*);
     void insertNodeHash(StatePark);
     ListNode* getHead() {return head->getForw();}
     bool deleteNodeHash(string);

};

#endif /* LinkedList_hpp */

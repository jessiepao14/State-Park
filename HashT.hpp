// Team 9
// HashCell class

#ifndef HashT_hpp
#define HashT_hpp

#include "StatePark.hpp"
#include "ListNode.hpp"
#include "LinkedList.hpp"
#include<iostream>

class HashCell
{
private:
    StatePark park;
    int count;
    LinkedList list;
public:
    HashCell();
    HashCell(StatePark,int);
    ~HashCell();

    //Setters
    void setPark(StatePark p) { park = p; count++;}
    //void setHead (ListNode*h) {head = h;}
    void setCount (int c) {count = c;}

    //Getters
    StatePark getPark() const {return park;}
    //ListNode* getHead() const {return head;}
    int getCount () {return count;}

    bool isEmpty(){return count ==0;};

    void insertHash(StatePark);

    void printHashCell(HashCell);

    void Search(HashCell,StatePark &,string);
    void Delete(HashCell,string);
    void getFirstList(HashCell, StatePark&);





};
#endif /* HashT_hpp */

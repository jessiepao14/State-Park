//Team 9
//ListNode Class

#ifndef ListNode_hpp
#define ListNode_hpp

#include "StatePark.hpp"

class ListNode
{
private:
    StatePark park;
    ListNode *forw, *back;

public:
    // Default Constructor
    ListNode() { forw = NULL; back = NULL; }

    // Setters
    void setPark(StatePark p) { park = p; }
    void setForw(ListNode *f) { forw = f; }
    void setBack(ListNode *b) { back = b; }
    // Getters
    StatePark getPark() const { return park; }
    ListNode* getForw() const { return forw; }
    ListNode* getBack() const { return back; }
};
#endif /* ListNode_hpp */

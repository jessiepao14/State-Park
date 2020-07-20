// Team 9
// HashFunc Class

#ifndef HashFunc_hpp
#define HashFunc_hpp

#include "HashT.hpp"

class HashFunc
{
    public:
        HashFunc();
        ~HashFunc();
        void buildHash(StatePark);
        void printArray();
        double getLoadFactor();
        int getNumOfCollisions();
        int getSizeOfArray() { return sizeOfArray; }
        bool SearchHash(string, StatePark &);
        void DeleteHashCell(string);


    private:
        HashCell *hashArray;
        int numOfCollisions;
        double loadFactor;
        int sizeOfArray;

        //private functions
        void _insertHash(ListNode*);
        int _hashName(string);
        void reHash();
        bool isPrime(int n);
        int nextPrime(int N);

};
#endif /* HashFunc_hpp */

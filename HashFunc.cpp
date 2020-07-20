// Team 9
// HashFunc class

#include "HashFunc.hpp"
#include "HashT.hpp"
#include "ListNode.hpp"
#include<string.h>
#include "iostream"
using namespace std;

//constructor
HashFunc::HashFunc()
{
    sizeOfArray = 15;
    hashArray = new HashCell[sizeOfArray];
    numOfCollisions = 0;
    loadFactor = 0;

}

//destructor
HashFunc::~HashFunc()
{
    cout << "\nDeleting Hash." << endl;
    delete [] hashArray;

}


/************************************************
Function -> buildHash
input: a StatePark Object
output: none
Purpose: Builds the hash table by calling the hashName
function and places the StatePark object in the respected
index of the array. Will call searchHash and determine
if item already exist in the hash table.
Will call reHash function if the load factor exceeds 75%
*************************************************/
void HashFunc :: buildHash(StatePark dataIn)
{
    getLoadFactor();
    if (loadFactor > 75)
    {
        //cout << "Load Factor is greater than 75%. Need to Rehash.\n\nOld Hash Table\n";
        //cout << "-----------------------------\n";
        //printArray();
        reHash();
        //cout << "\nDONE REHASHING\n";
    }

    int module = _hashName(dataIn.getName());
    StatePark returnItem;
    if (SearchHash(dataIn.getName(),returnItem) == false)
    {
        if (hashArray[module].isEmpty())
        {
            hashArray[module].setPark(dataIn);
        }
        else
        {
            hashArray[module].insertHash(dataIn);
        }
    }
}

/************************************************
Function -> hashName
input: string
output: int
Purpose: Converts the string name in to a char array
and takes the sum of all the letters in the string.
Will return the remainder of division of the size of
the array and the sum.
*************************************************/
int HashFunc:: _hashName(string n)
{

    int nameSize = n.length() + 1;
    char *chrAry = new char[nameSize];
    strcpy(chrAry,n.c_str());
    int sum = 0;
    int modul = 0;
    for (int i = 0; i < nameSize; i++)
    {
        sum+= chrAry[i];
    }
    modul = sum % sizeOfArray;
    delete [] chrAry;
    return modul;

    //Alternate hash function
    /*
    int nameSize = n.length() + 1;
    char *chrAry = new char[nameSize];
    strcpy(chrAry,n.c_str());
    int sum = 0;
    int modul = 0;
    for (int i = 0; i < nameSize; i++)
    {
        sum+= chrAry[i];
    }
    sum = sum*sum/2;
    //cout << "Sum of " << n << " " << sum << endl;
    modul = sum % sizeOfArray;
    delete [] chrAry;
    return modul;*/
}

/************************************************
Function -> Print Array
input: none
output: none
Purpose: Prints the Hash Table by index
*************************************************/
void HashFunc::printArray()
{
    for (int i = 0; i < sizeOfArray; i++)
    {
        cout << i << ")" << hashArray[i].getPark().getName();
        if (hashArray[i].getCount() > 1)
        {
            hashArray[i].printHashCell(hashArray[i]);
        }
        cout << endl;
    }
    cout << "\nLoad Factor: "  << getLoadFactor() << "%" << endl;
    cout << "Number of Collisions: " << getNumOfCollisions() << endl;
    cout << "Size of Array: " << getSizeOfArray() << endl;
}

/************************************************
Function -> getLoadFactor
input: none
output: double
Purpose: will calculate the load factor of the
hash table and return it
*************************************************/
double HashFunc :: getLoadFactor()
{
    double FilledCells = sizeOfArray;
    for (int i = 0; i < sizeOfArray; i++)
    {
        if (hashArray[i].isEmpty())
        {
            FilledCells-=1;
        }
    }
    loadFactor = (FilledCells / sizeOfArray)*100;
    return loadFactor;

}

/************************************************
Function -> getNumOfCollisions
input: none
output: int
Purpose: calculates the number of collisions by calling
the getCount function
*************************************************/
int HashFunc :: getNumOfCollisions()
{
    for (int i = 0; i < sizeOfArray; i++)
    {
        int sum = hashArray[i].getCount();
        if (sum > 1)
        {
            numOfCollisions += (sum-1);
        }
    }
    return numOfCollisions;
}

/************************************************
Function -> Search Hash
input: string, address of a StatePark object
output: bool
Purpose: Searches the hash table for the string input
and will return true or false. Returned item will
address of the deleted StatePark object if true
*************************************************/
bool HashFunc:: SearchHash(string n,StatePark & returnedItem)
{
    bool status = false;
    int mod = _hashName(n);


    if(hashArray[mod].getPark().getName() == n)
    {
        status = true;
        returnedItem = hashArray[mod].getPark();
    }

    else
    {
        hashArray[mod].Search(hashArray[mod],returnedItem,n);
        if (returnedItem.getName() == n)
        {
            status = true;
        }
    }
    return status;
}

/************************************************
Function -> Delete Hash Cell
input: string
output: none
Purpose: Deletes a StatePark Object in the hash
table. Will call Search Hash function to see if
item exist and will delete if found
*************************************************/
void HashFunc :: DeleteHashCell(string n)
{
    StatePark returnedItem;
    bool status = SearchHash(n,returnedItem);
    int mod = _hashName(n);

    if (status == true)
    {

        if (returnedItem.getName() == hashArray[mod].getPark().getName() && hashArray[mod].getCount() == 1)
        {
            StatePark temp;
            hashArray[mod].setPark(temp);


        }
        else if (returnedItem.getName() == hashArray[mod].getPark().getName() && hashArray[mod].getCount() > 1)
        {
            StatePark newHead;
            hashArray[mod].getFirstList(hashArray[mod], newHead);
            hashArray[mod].setPark(newHead);
        }
        else
        {
            hashArray[mod].Delete(hashArray[mod],n);
        }
        //if the inserted string is the hashCell state park
            //get the hashCell state park and replace it with the first item in the list and update the list

        //else traverse the list of the hashCell and update the list
    }

    else
    {
        cout << "Item not found.\n\n";
    }
}
/************************************************
Function -> reHash
input: none
output: none
Purpose: Will resize the size of the hash table by
multiplying by two and finding next prime number
(entered manually) and will put current objects into
temp array and deletes old array. Creates a new array
and calls buildHash function to insert into new hash table.
Then deletes temporary array
*************************************************/
void HashFunc :: reHash(){
    int tempsize = nextPrime(2*sizeOfArray);
    HashCell *temp = new HashCell[tempsize];
    for (int i = 0 ; i < sizeOfArray; i++)
    {
        temp[i] = hashArray[i];
    }
    sizeOfArray = tempsize;
    tempsize = tempsize/2;
    delete [] hashArray;
    hashArray = new HashCell[sizeOfArray];
    loadFactor = 0;
    numOfCollisions = 0;
    for (int i = 0; i < tempsize; i++)
    {
        buildHash(temp[i].getPark());
    }
    for (int i = 0; i < tempsize; i++)
    {
        if (!temp[i].isEmpty())
        {
            for (int j = 0; j <= temp[i].getCount();j++)
            {
                StatePark item;
                temp[i].getFirstList(temp[i],item);
                buildHash(item);
            }
        }
    }
    delete[] temp;
}


// The isPrime function returns true if n
// is prime and otherwise false
bool HashFunc::isPrime(int n)
{
    bool flag = true;
    for (int i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
        {
            flag = false;
        }
    }
    return flag;
}

// The nextPrime function returns the smallest
// prime number greater than n
int HashFunc::nextPrime(int n)
{

    // Base case
    if (n <= 1)
        return 2;

    int testNum = n;
    bool found = false;

    // Increment n until isPrime
    // returns true
    while (!found)
    {
        testNum++;

        if (isPrime(testNum))
            found = true;
    }

    return testNum;
}

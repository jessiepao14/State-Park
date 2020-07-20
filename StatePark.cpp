// Team 9
// Implementation file for the StatePark class

#include <iostream>
#include "StatePark.hpp"
#include <iomanip>
#include <string>
using namespace std;

//**************************************************
// Constructor
//**************************************************
StatePark::StatePark()
{
    parkName = "";
    zip = -1;
    city = "";
    year = -1;
    acres = -1;
}

//**************************************************
// Overloaded Constructor
//**************************************************
StatePark::StatePark(string n, int z, string c, int y, int a)
{
    parkName = n;
    zip = z;
    city = c;
    year = y;
    acres = a;
}

//***********************************************************
// Overloaded == operator to compare City class objects
// according to the value of their member variable, name
//***********************************************************
bool StatePark::operator == (const StatePark &right)
{
    bool status;
    if (parkName == right.parkName)
        status = true;
    else
        status = false;
    return status;
}

//***********************************************************
// Overloaded < operator to compare City class objects
// according to the value of their member variable, name
//***********************************************************
bool StatePark::operator < (const StatePark &right)
{
    bool status;
    if (parkName < right.parkName)
        status = true;
    else
        status = false;
    return status;
}

//***********************************************************
// Overloaded > operator to compare City class objects
// according to the value of their member variable, name
//***********************************************************
bool StatePark::operator > (const StatePark &right)
{
    bool status;
    if (parkName > right.parkName)
        status = true;
    else
        status = false;
    return status;
}

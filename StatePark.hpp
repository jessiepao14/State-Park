//specification file for State Park class
//Written by Team 9

#ifndef StatePark_hpp
#define StatePark_hpp

#include <string>
#include <stdio.h>

using std::string;

class StatePark
{
private:
    string parkName;
    int zip;
    string city;
    int year;
    int acres;


public:
    StatePark();
    StatePark(string n, int z, string c, int y, int a);
    //~StatePark();

    //setters
    void setName(string n) { parkName = n; }
    void setZip(int z) { zip = z; }
    void setCity(string c) { city = c; }
    void setYear(int y) { year = y; }
    void setAcres(int a) { acres = a; }
    //Getters
    string getName() { return parkName; }
    int getZip() { return zip; }
    string getCity() { return city; }
    int getYear() { return year; }
    int getAcres() { return acres; }

    //void displayPark();

    //Overloaded functions
    bool operator<(const StatePark &p); // { return (parkName < p.parkName); }
    bool operator>(const StatePark &p); // { return (parkName > p.parkName); }
    bool operator==(const StatePark &p); // { return (parkName == p.parkName); }

};



#endif /* StatePark_hpp */

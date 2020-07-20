/**
 Team 9
This is the driver for the State Park Database
**/

#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.hpp"
#include "StatePark.hpp"
#include "BinarySearchTree.hpp"
#include "HashT.hpp"
#include "HashFunc.hpp"
#include "Stack.hpp"


using namespace std;


// FUNCTION PROTOTYPES
void menu();

void buildList(string filename, BinarySearchTree<StatePark> &, BinarySearchTree<StatePark> &, HashFunc&);
void searchManager(BinarySearchTree<StatePark> &, BinarySearchTree<StatePark> &);
void insertManager(BinarySearchTree<StatePark> &, BinarySearchTree<StatePark> &, HashFunc &);
void deleteManager(BinarySearchTree<StatePark> &, BinarySearchTree<StatePark> &, HashFunc &, Stack<StatePark> &);
void undoDeleteManager(BinarySearchTree<StatePark> &, BinarySearchTree<StatePark> &, HashFunc &, Stack<StatePark> &);

void displayTree(BinarySearchTree<StatePark> &, BinarySearchTree<StatePark> &);
void displayList(BinarySearchTree<StatePark> &, BinarySearchTree<StatePark> &, HashFunc &);

int compareParkName(StatePark *, StatePark *);
int compareCityName(StatePark *, StatePark *);//used in search
int compareCityNameAndPark(StatePark *left, StatePark *right);//used in insert and delete

void displayParkNames(BinarySearchTree<StatePark> &);
void printName(StatePark *);

void printHeader();
void printInfo(StatePark *);

void writeParkNames(BinarySearchTree<StatePark> *parkNameTree);
void writeName(StatePark *park);

string checkString(string);

const string FILENAME_OUT = "outputReport.txt";
ofstream outputFile;

int main()
{
    string INPUT_FILE = "ParkList.txt";
    char choice = 'Z';
    string empty;
    
    StatePark park;
    LinkedList list;
    HashFunc hash;
    BinarySearchTree<StatePark> parkTree;
    BinarySearchTree<StatePark> cityTree;
    Stack<StatePark> undoStack;

    buildList(INPUT_FILE, parkTree, cityTree, hash);

    //list.traverseForward(list.printNode, list.printHeader, list.printFooter);
    
    menu();
    
    while(choice != 'E')
    {
        cout << "Enter an option (H- for help): \n";
        cin >> choice;
        getline(cin, empty);
        choice = toupper(choice);
        if(choice == 'S')
        {
            searchManager(parkTree, cityTree);
        }
        else if(choice == 'A')
        {
            insertManager(parkTree , cityTree, hash);
        }
        else if(choice == 'D')
        {
            deleteManager(parkTree, cityTree, hash, undoStack);
        }
        else if(choice == 'U')
        {
            undoDeleteManager(parkTree, cityTree, hash, undoStack);
        }
        else if(choice == 'B')
        {
            cout << "Load Factor is : " << hash.getLoadFactor() <<endl;
            cout << "Number of Collisions: " << hash.getNumOfCollisions() <<endl;
        }
        else if(choice == 'T')
        {
            displayTree(parkTree, cityTree);
        }
        else if(choice == 'L')
        {
            displayList(parkTree, cityTree, hash);
        }
        else if(choice == 'H')
        {
            menu();
        }
    }
    outputFile.open(FILENAME_OUT.c_str()); // open the output file
    outputFile << "===== =============== ==== ===== ==============================================" << endl;
    outputFile << " Zip  City            Year Acres Park Name                                     " << endl;
    outputFile << "===== =============== ==== ===== ==============================================" << endl;
    writeParkNames(&parkTree);
    outputFile.close();  // close the output file
    return 0;
}

// This function prints the menu to the screen
void menu()
{
    cout << "\n===== Main Menu ======\n" << endl;
    cout << "S – Search" << endl;
    cout << "A – Add a new Park" << endl;
    cout << "D – Delete a Park" << endl;
    cout << "U - Undo Delete" << endl;
    cout << "B - Hash Table Statistics" << endl;
    cout << "T - Print a tree" << endl;
    cout << "L - Print a list" << endl;
    cout << "E – Exit" << endl;
}

/*****************************************************************************
 This function reads data about parks from a given file and inserts them
 into a sorted linked list.
 *****************************************************************************/
void buildList(string filename, BinarySearchTree<StatePark> &parkTree, BinarySearchTree<StatePark> &cityTree, HashFunc& a)
{
    ifstream inFile;
    string city, name;
    int year, acres, zip;

    inFile.open(filename);

    if (!inFile) {
        cout << "Error opening the input file: \"" << filename << "\"" << endl;
        exit(EXIT_FAILURE);
    }

    while (inFile >> year >> acres)
    {
        StatePark *park = new StatePark();
        inFile.ignore(); // skip the space in front of the city name
        getline(inFile, city, ';');
        inFile >> zip;
        inFile.ignore(); // skip the space in front of the park name
        getline(inFile, name);
        park->setYear(year);
        park->setAcres(acres);
        park->setCity(city);
        park->setZip(zip);
        park->setName(name);
        parkTree.insert(park, compareParkName);
        cityTree.insert(park, compareCityName);
        a.buildHash(*park);
    }

    inFile.close();
}

/*****************************************************************************
This function gets park name from the user and searches for it in the tree
 then prints the information about the park to the screen
*****************************************************************************/
void searchManager(BinarySearchTree<StatePark> &parkNameTree, BinarySearchTree<StatePark> &cityNameTree)
{
    string input;
    cout << "Enter 'p' to search by park name" << endl;
    cout << "Enter 'c' to search by city" << endl;
    cin >> input;
    if (input == "p")
    {
        cout << "Enter park name to search: ";
        cin.ignore();
        getline(cin, input);
        input = checkString(input);//check if input is valid
        
        cout << "input is: " << input <<endl;
        
        StatePark *targetPark = new StatePark();
        StatePark entry;
        
        targetPark->setName(input);
        if (parkNameTree.getEntry(targetPark, entry, compareParkName))
        {
            cout << "'" << entry.getName() << "' has been found." << endl;
            printHeader();    //display more info of park
            printInfo(&entry);
        }
        else
            cout << "'"<< input << "' has not been found" << endl;

    }
    if (input == "c")
    {
        do
        {
            cout << "Enter city to search: ";
            cin.ignore();
            getline(cin, input);
            input = checkString(input);//check if input is valid
        }
        while(input == "false");
        
        StatePark *targetCity = new StatePark();
        targetCity->setCity(input);
        if (cityNameTree.inOrderSameKey(targetCity, printName, compareCityName))
            cout << "Park Names in the city '" << targetCity->getCity() << "'" << endl;
        else
            cout << "No parks found in '" << targetCity->getCity() << "'" << endl;

    }
    
}

/*****************************************************************************
This function gets park name from the user and deletes that park from
the tree. If park is not found then error message is printed
*****************************************************************************/
void deleteManager(BinarySearchTree<StatePark> &parkNameTree, BinarySearchTree<StatePark> &cityNameTree, HashFunc &a, Stack<StatePark> &undoStack)
{
    StatePark entry;
    string input;
    do
    {
        cout << "Enter the Park you want to delete: " << endl;
        getline(cin, input);
        input = checkString(input); //input valid?
    }
    while(input == "false");
    
    StatePark *targetPark = new StatePark();
    targetPark->setName(input);
    if (parkNameTree.getEntry(targetPark, entry, compareParkName))
    {
        undoStack.push(entry);
        parkNameTree.remove(targetPark, compareParkName);
        cityNameTree.remove(targetPark, compareCityNameAndPark);
        a.DeleteHashCell(input);
        cout << input << " has been deleted." << endl;
    }
    else
        cout << input << " was not found." << endl;
    
}

/*****************************************************************************
This function undos the delete using a stack
*****************************************************************************/
void undoDeleteManager(BinarySearchTree<StatePark> &parkTree, BinarySearchTree<StatePark> &cityTree, HashFunc &a, Stack<StatePark> &undoStack)
{
    StatePark *returnPark = new StatePark();
    if(undoStack.pop(*returnPark))
    {
        parkTree.insert(returnPark, compareParkName);
        cityTree.insert(returnPark, compareCityNameAndPark);
        a.buildHash(*returnPark);
        cout << returnPark->getName() << " has been reinserted." << endl << endl;
    }
    else
    {
        cout << "Nothing has been deleted" <<endl;
    }
}

/*****************************************************************************
This function gets input from the user and inserts the park
*****************************************************************************/
void insertManager(BinarySearchTree<StatePark> &parkTree, BinarySearchTree<StatePark> &cityTree, HashFunc &a)
{
    string city, name;
    int year, acres, zip;
    do
    {
        //cin.ignore();
        cout << "City: ";
        getline(cin, city);
        city = checkString(city);
        cout << city <<endl;
    }
    while (city == "false");
    
    do
    {
        cout << "Park Name: ";
        getline(cin, name);
        name = checkString(name);
        cout << name << endl;
    }
    while (name == "false");
    
    cout << "Year: ";
    cin >> year;
    cout << year << endl;
    while(year < 1850 || year > 2020)
    {
        cout << "Year has to be between 1850 and 2019" << endl;
        cout << "Year: ";
        cin >> year;
        cout << year <<endl;;
    }
    cout << "Acres: ";
    cin >> acres;
    cout << acres << endl;
    while(acres < 0)
    {
        cout << "Acres has to be a positive intager" << endl;
        cout << "Acres: ";
        cin >> acres;
        cout << acres << endl;
    }
    cout << "Zip: ";
    cin >> zip;
    cout << zip << endl;
    while(zip < 90000)
    {
        cout << "Zip code has to be greater than 90000" <<endl;
        cout << "Zip: ";
        cin >> zip;
        cout << zip << endl;
    }
    
    StatePark *newPark = new StatePark(name, zip, city, year, acres);
    parkTree.insert(newPark, compareParkName);
    cityTree.insert(newPark, compareCityNameAndPark);
    a.buildHash(*newPark);
    cout << newPark->getName() << " has been inserted." << endl << endl;
}

void displayTree(BinarySearchTree<StatePark> &parkTree, BinarySearchTree<StatePark> &cityTree)
{
    char sort = 'Z';
    cout << "Sort Tree by: \nP - Park\nC - City" << endl;
    cin >> sort;
    sort = toupper(sort);
    if(sort == 'P')
    {
        parkTree.printTree(printName);
    }
    if(sort == 'C')
    {
        cityTree.printTree(printName);
    }
}

void displayList(BinarySearchTree<StatePark> &parkTree, BinarySearchTree<StatePark> &cityTree, HashFunc & a)
{
    char sort = 'Z';
    cout << "Sort Tree by: \nP - Park\nC - City\nU-Unsorted" << endl;
    cin >> sort;
    sort = toupper(sort);
    if(sort == 'P')
    {
        printHeader();
        parkTree.inOrder(printInfo);
    }
    else if(sort == 'C')
    {
        printHeader();
        cityTree.inOrder(printInfo);
    }
    else if(sort == 'U')
    {
        a.printArray();
    }
}

int compareParkName(StatePark *left, StatePark *right)
{
    if (left->getName() > right->getName())
        return 1;
    else if (left->getName() == right->getName())
        return 0;
    else
        return -1;
}

int compareCityNameAndPark(StatePark *left, StatePark *right)
{
    if (left->getCity() > right->getCity())
        return 1;
    else if (left->getCity() < right->getCity())
        return -1;
    //if city is the same, compare park names
    else
        return compareParkName(left, right);
}

int compareCityName(StatePark *left, StatePark *right)
{
    if (left->getCity() > right->getCity())
        return 1;
    else if (left->getCity() < right->getCity())
        return -1;
    else
        return 0;
}

void displayParkNames(BinarySearchTree<StatePark> *parkNameTree)
{
    parkNameTree->inOrder(printName);
}

void printName(StatePark* park)
{
    cout << park->getName() <<" "<< park->getCity()<< endl;
}

string checkString(string input)
{
    bool space = false;
    for(int i = 0; i < input.size(); i++)
    {
        if(isalpha(input[i]) || input[i] == ' ')
        {
            if (i == 0 || space == true )
            {
                input[i] = toupper(input[i]);
                space = false;
            }
            else if (input[i] == ' ')
                space = true;
            else
                input[i] = tolower(input[i]);
        }
        else
            return "false";
    }
    return input;
}


void printHeader()
{
    cout << "===== =============== ==== ===== ==============================================" << endl;
    cout << " Zip  City            Year Acres Park Name                                     " << endl;
    cout << "===== =============== ==== ===== ==============================================" << endl;

}

void printInfo(StatePark *park)
{
    cout << left << setw(5) << park->getZip() << " "
                 << setw(15) << park->getCity() << " "
                 << setw(4) << park->getYear() << " " << right
                 << setw(5) << park->getAcres() << " " << left
                 << setw(15) << park->getName() << endl;
}

void writeParkNames(BinarySearchTree<StatePark> *parkNameTree)
{
    parkNameTree->preOrder(writeName);
}

// WRITE FUNC
void writeName(StatePark *park)
{
    outputFile << left << setw(5) << park->getZip() << " "
        << setw(15) << park->getCity() << " "
        << setw(4) << park->getYear() << " " << right
        << setw(5) << park->getAcres() << " " << left
        << setw(15) << park->getName() << endl;
}

/***********
 TEST OUTPUT

 ===== Main Menu ======

 S – Search
 A – Add a new Park
 D – Delete a Park
 U - Undo Delete
 B - Hash Table Statistics
 T - Print a tree
 L - Print a list
 E – Exit
 Enter an option (H- for help):
 l
 Sort Tree by:
 P - Park
 C - City
 U-Unsorted
 p
 ===== =============== ==== ===== ==============================================
  Zip  City            Year Acres Park Name
 ===== =============== ==== ===== ==============================================
 94060 Pescadero       1985  4209 Ano Nuevo State Park
 94060 Pescadero       1958    44 Bean Hollow State Beach
 94514 Byron           1974   609 Bethany Reservoir State Recreation Area
 94019 Half Moon Bay   1979  1325 Burleigh H. Murray Ranch
 94060 Pescadero       1956  4728 Butano State Park
 95376 Tracy           1979  5075 Carnegie State Vehicular Recreation Area
 95033 Los Gatos       1968  5242 Castle Rock State Park
 94561 Oakley          1959  3523 Franks Tract State Recreation Area
 94019 Half Moon Bay   1966     3 Gray Whale Cove State Beach
 94019 Half Moon Bay   1956   181 Half Moon Bay State Beach
 95037 Morgan Hill     1959 89164 Henry W. Coe State Park
 94550 Livermore       1967  3732 Lake Del Valle State Recreation Area
 94513 Brentwood       2012  3659 Marsh Creek State Historic Park
 95136 San Jose        2003   137 Martial Cottle Park State Recreation Area
 94720 Berkeley        1985   442 McLaughlin Eastshore State Park State Seashore
 94037 Montara         1959   780 Montara State Beach
 94598 Walnut Creek    1931 20124 Mount Diablo State Park
 94044 Pacifica        1979    21 Pacifica State Beach
 94060 Pescadero       1958   700 Pescadero State Beach
 94060 Pescadero       1981    76 Pigeon Point Light Station State Historic Park
 94074 San Gregorio    1960   421 Pomponio State Beach
 94020 La Honda        1945  2608 Portola Redwoods State Park
 94501 Alameda         1961   132 Robert W. Crown Memorial State Beach
 94005 Brisbane        1980   298 San Bruno Mountain State Park
 94074 San Gregorio    1958   414 San Gregorio State Beach
 94015 Daly City       1955    58 Thornton State Beach
 Enter an option (H- for help):
 l
 Sort Tree by:
 P - Park
 C - City
 U-Unsorted
 c
 ===== =============== ==== ===== ==============================================
  Zip  City            Year Acres Park Name
 ===== =============== ==== ===== ==============================================
 94501 Alameda         1961   132 Robert W. Crown Memorial State Beach
 94720 Berkeley        1985   442 McLaughlin Eastshore State Park State Seashore
 94513 Brentwood       2012  3659 Marsh Creek State Historic Park
 94005 Brisbane        1980   298 San Bruno Mountain State Park
 94514 Byron           1974   609 Bethany Reservoir State Recreation Area
 94015 Daly City       1955    58 Thornton State Beach
 94019 Half Moon Bay   1979  1325 Burleigh H. Murray Ranch
 94019 Half Moon Bay   1966     3 Gray Whale Cove State Beach
 94019 Half Moon Bay   1956   181 Half Moon Bay State Beach
 94020 La Honda        1945  2608 Portola Redwoods State Park
 94550 Livermore       1967  3732 Lake Del Valle State Recreation Area
 95033 Los Gatos       1968  5242 Castle Rock State Park
 94037 Montara         1959   780 Montara State Beach
 95037 Morgan Hill     1959 89164 Henry W. Coe State Park
 94561 Oakley          1959  3523 Franks Tract State Recreation Area
 94044 Pacifica        1979    21 Pacifica State Beach
 94060 Pescadero       1985  4209 Ano Nuevo State Park
 94060 Pescadero       1958    44 Bean Hollow State Beach
 94060 Pescadero       1956  4728 Butano State Park
 94060 Pescadero       1958   700 Pescadero State Beach
 94060 Pescadero       1981    76 Pigeon Point Light Station State Historic Park
 94074 San Gregorio    1960   421 Pomponio State Beach
 94074 San Gregorio    1958   414 San Gregorio State Beach
 95136 San Jose        2003   137 Martial Cottle Park State Recreation Area
 95376 Tracy           1979  5075 Carnegie State Vehicular Recreation Area
 94598 Walnut Creek    1931 20124 Mount Diablo State Park
 Enter an option (H- for help):
 l
 Sort Tree by:
 P - Park
 C - City
 U-Unsorted
 u
 0)
 1)Carnegie State Vehicular Recreation Area
 2)Bean Hollow State Beach---->Pomponio State Beach
 3)
 4)Martial Cottle Park State Recreation Area
 5)Pigeon Point Light Station State Historic Park
 6)
 7)
 8)McLaughlin Eastshore State Park State Seashore
 9)Pescadero State Beach
 10)Bethany Reservoir State Recreation Area---->Portola Redwoods State Park---->Half Moon Bay State Beach
 11)Butano State Park
 12)
 13)Thornton State Beach
 14)Robert W. Crown Memorial State Beach
 15)Franks Tract State Recreation Area
 16)Henry W. Coe State Park
 17)Mount Diablo State Park
 18)Gray Whale Cove State Beach
 19)
 20)Lake Del Valle State Recreation Area---->Ano Nuevo State Park
 21)Marsh Creek State Historic Park
 22)
 23)
 24)San Bruno Mountain State Park
 25)Burleigh H. Murray Ranch
 26)San Gregorio State Beach---->Castle Rock State Park
 27)
 28)
 29)
 30)Montara State Beach---->Pacifica State Beach

 Load Factor: 64.5161%
 Number of Collisions: 6
 Size of Array: 31
 Enter an option (H- for help):
 s
 Enter 'p' to search by park name
 Enter 'c' to search by city
 p
 Enter park name to search: Thornton State Beach
 input is: Thornton State Beach
 'Thornton State Beach' has been found.
 ===== =============== ==== ===== ==============================================
  Zip  City            Year Acres Park Name
 ===== =============== ==== ===== ==============================================
 94015 Daly City       1955    58 Thornton State Beach
 Enter an option (H- for help):
 s
 Enter 'p' to search by park name
 Enter 'c' to search by city
 c
 Enter city to search: Pescadero
 Ano Nuevo State Park Pescadero
 Bean Hollow State Beach Pescadero
 Butano State Park Pescadero
 Pescadero State Beach Pescadero
 Pigeon Point Light Station State Historic Park Pescadero
 Park Names in the city 'Pescadero'
 Enter an option (H- for help):
 h

 ===== Main Menu ======

 S – Search
 A – Add a new Park
 D – Delete a Park
 U - Undo Delete
 B - Hash Table Statistics
 T - Print a tree
 L - Print a list
 E – Exit
 Enter an option (H- for help):
 d
 Enter the Park you want to delete:
 Pacifica State Beach
 Pacifica State Beach has been deleted.
 Enter an option (H- for help):
 l
 Sort Tree by:
 P - Park
 C - City
 U-Unsorted
 p
 ===== =============== ==== ===== ==============================================
  Zip  City            Year Acres Park Name
 ===== =============== ==== ===== ==============================================
 94060 Pescadero       1985  4209 Ano Nuevo State Park
 94060 Pescadero       1958    44 Bean Hollow State Beach
 94514 Byron           1974   609 Bethany Reservoir State Recreation Area
 94019 Half Moon Bay   1979  1325 Burleigh H. Murray Ranch
 94060 Pescadero       1956  4728 Butano State Park
 95376 Tracy           1979  5075 Carnegie State Vehicular Recreation Area
 95033 Los Gatos       1968  5242 Castle Rock State Park
 94561 Oakley          1959  3523 Franks Tract State Recreation Area
 94019 Half Moon Bay   1966     3 Gray Whale Cove State Beach
 94019 Half Moon Bay   1956   181 Half Moon Bay State Beach
 95037 Morgan Hill     1959 89164 Henry W. Coe State Park
 94550 Livermore       1967  3732 Lake Del Valle State Recreation Area
 94513 Brentwood       2012  3659 Marsh Creek State Historic Park
 95136 San Jose        2003   137 Martial Cottle Park State Recreation Area
 94720 Berkeley        1985   442 McLaughlin Eastshore State Park State Seashore
 94037 Montara         1959   780 Montara State Beach
 94598 Walnut Creek    1931 20124 Mount Diablo State Park
 94060 Pescadero       1958   700 Pescadero State Beach
 94060 Pescadero       1981    76 Pigeon Point Light Station State Historic Park
 94074 San Gregorio    1960   421 Pomponio State Beach
 94020 La Honda        1945  2608 Portola Redwoods State Park
 94501 Alameda         1961   132 Robert W. Crown Memorial State Beach
 94005 Brisbane        1980   298 San Bruno Mountain State Park
 94074 San Gregorio    1958   414 San Gregorio State Beach
 94015 Daly City       1955    58 Thornton State Beach
 Enter an option (H- for help):
 u
 Pacifica State Beach has been reinserted.

 Enter an option (H- for help):
 l
 Sort Tree by:
 P - Park
 C - City
 U-Unsorted
 p
 ===== =============== ==== ===== ==============================================
  Zip  City            Year Acres Park Name
 ===== =============== ==== ===== ==============================================
 94060 Pescadero       1985  4209 Ano Nuevo State Park
 94060 Pescadero       1958    44 Bean Hollow State Beach
 94514 Byron           1974   609 Bethany Reservoir State Recreation Area
 94019 Half Moon Bay   1979  1325 Burleigh H. Murray Ranch
 94060 Pescadero       1956  4728 Butano State Park
 95376 Tracy           1979  5075 Carnegie State Vehicular Recreation Area
 95033 Los Gatos       1968  5242 Castle Rock State Park
 94561 Oakley          1959  3523 Franks Tract State Recreation Area
 94019 Half Moon Bay   1966     3 Gray Whale Cove State Beach
 94019 Half Moon Bay   1956   181 Half Moon Bay State Beach
 95037 Morgan Hill     1959 89164 Henry W. Coe State Park
 94550 Livermore       1967  3732 Lake Del Valle State Recreation Area
 94513 Brentwood       2012  3659 Marsh Creek State Historic Park
 95136 San Jose        2003   137 Martial Cottle Park State Recreation Area
 94720 Berkeley        1985   442 McLaughlin Eastshore State Park State Seashore
 94037 Montara         1959   780 Montara State Beach
 94598 Walnut Creek    1931 20124 Mount Diablo State Park
 94044 Pacifica        1979    21 Pacifica State Beach
 94060 Pescadero       1958   700 Pescadero State Beach
 94060 Pescadero       1981    76 Pigeon Point Light Station State Historic Park
 94074 San Gregorio    1960   421 Pomponio State Beach
 94020 La Honda        1945  2608 Portola Redwoods State Park
 94501 Alameda         1961   132 Robert W. Crown Memorial State Beach
 94005 Brisbane        1980   298 San Bruno Mountain State Park
 94074 San Gregorio    1958   414 San Gregorio State Beach
 94015 Daly City       1955    58 Thornton State Beach
 Enter an option (H- for help):
 t
 Sort Tree by:
 P - Park
 C - City
 p
 Level 1. Bethany Reservoir State Recreation Area Byron

      Level 2. Lake Del Valle State Recreation Area Livermore

           Level 3. Robert W. Crown Memorial State Beach Alameda

                Level 4. San Bruno Mountain State Park Brisbane

                     Level 5. San Gregorio State Beach San Gregorio

                          Level 6. Thornton State Beach Daly City

                Level 4. McLaughlin Eastshore State Park State Seashore Berkeley

                     Level 5. Mount Diablo State Park Walnut Creek

                          Level 6. Pescadero State Beach Pescadero

                               Level 7. Pigeon Point Light Station State Historic Park Pescadero

                                    Level 8. Pomponio State Beach San Gregorio

                                         Level 9. Portola Redwoods State Park La Honda

                               Level 7. Pacifica State Beach Pacifica

                          Level 6. Montara State Beach Montara

                     Level 5. Marsh Creek State Historic Park Brentwood

                          Level 6. Martial Cottle Park State Recreation Area San Jose

           Level 3. Carnegie State Vehicular Recreation Area Tracy

                Level 4. Franks Tract State Recreation Area Oakley

                     Level 5. Gray Whale Cove State Beach Half Moon Bay

                          Level 6. Half Moon Bay State Beach Half Moon Bay

                               Level 7. Henry W. Coe State Park Morgan Hill

                     Level 5. Castle Rock State Park Los Gatos

                Level 4. Burleigh H. Murray Ranch Half Moon Bay

                     Level 5. Butano State Park Pescadero

      Level 2. Ano Nuevo State Park Pescadero

           Level 3. Bean Hollow State Beach Pescadero

 Enter an option (H- for help):
 t
 Sort Tree by:
 P - Park
 C - City
 c
 Level 1. Bethany Reservoir State Recreation Area Byron

      Level 2. Lake Del Valle State Recreation Area Livermore

           Level 3. Carnegie State Vehicular Recreation Area Tracy

                Level 4. Mount Diablo State Park Walnut Creek

                Level 4. Franks Tract State Recreation Area Oakley

                     Level 5. Ano Nuevo State Park Pescadero

                          Level 6. Bean Hollow State Beach Pescadero

                               Level 7. Butano State Park Pescadero

                                    Level 8. Pescadero State Beach Pescadero

                                         Level 9. Pigeon Point Light Station State Historic Park Pescadero

                                              Level 10. Pomponio State Beach San Gregorio

                                                   Level 11. San Gregorio State Beach San Gregorio

                                                        Level 12. Martial Cottle Park State Recreation Area San Jose

                          Level 6. Pacifica State Beach Pacifica

                               Level 7. Pacifica State Beach Pacifica

                     Level 5. Montara State Beach Montara

                          Level 6. Henry W. Coe State Park Morgan Hill

                          Level 6. Castle Rock State Park Los Gatos

           Level 3. Burleigh H. Murray Ranch Half Moon Bay

                Level 4. Gray Whale Cove State Beach Half Moon Bay

                     Level 5. Half Moon Bay State Beach Half Moon Bay

                          Level 6. Portola Redwoods State Park La Honda

                Level 4. Thornton State Beach Daly City

      Level 2. Robert W. Crown Memorial State Beach Alameda

           Level 3. McLaughlin Eastshore State Park State Seashore Berkeley

                Level 4. Marsh Creek State Historic Park Brentwood

                     Level 5. San Bruno Mountain State Park Brisbane

 Enter an option (H- for help):
 b
 Load Factor is : 64.5161
 Number of Collisions: 13
 Enter an option (H- for help):
 a
 City: cupertino
 Cupertino
 Park Name: de anza park
 De Anza Park
 Year: 1923
 1923
 Acres: 1234
 1234
 Zip: 95014
 95014
 De Anza Park has been inserted.

 Enter an option (H- for help):
 l
 Sort Tree by:
 P - Park
 C - City
 U-Unsorted
 p
 ===== =============== ==== ===== ==============================================
  Zip  City            Year Acres Park Name
 ===== =============== ==== ===== ==============================================
 94060 Pescadero       1985  4209 Ano Nuevo State Park
 94060 Pescadero       1958    44 Bean Hollow State Beach
 94514 Byron           1974   609 Bethany Reservoir State Recreation Area
 94019 Half Moon Bay   1979  1325 Burleigh H. Murray Ranch
 94060 Pescadero       1956  4728 Butano State Park
 95376 Tracy           1979  5075 Carnegie State Vehicular Recreation Area
 95033 Los Gatos       1968  5242 Castle Rock State Park
 95014 Cupertino       1923  1234 De Anza Park
 94561 Oakley          1959  3523 Franks Tract State Recreation Area
 94019 Half Moon Bay   1966     3 Gray Whale Cove State Beach
 94019 Half Moon Bay   1956   181 Half Moon Bay State Beach
 95037 Morgan Hill     1959 89164 Henry W. Coe State Park
 94550 Livermore       1967  3732 Lake Del Valle State Recreation Area
 94513 Brentwood       2012  3659 Marsh Creek State Historic Park
 95136 San Jose        2003   137 Martial Cottle Park State Recreation Area
 94720 Berkeley        1985   442 McLaughlin Eastshore State Park State Seashore
 94037 Montara         1959   780 Montara State Beach
 94598 Walnut Creek    1931 20124 Mount Diablo State Park
 94044 Pacifica        1979    21 Pacifica State Beach
 94060 Pescadero       1958   700 Pescadero State Beach
 94060 Pescadero       1981    76 Pigeon Point Light Station State Historic Park
 94074 San Gregorio    1960   421 Pomponio State Beach
 94020 La Honda        1945  2608 Portola Redwoods State Park
 94501 Alameda         1961   132 Robert W. Crown Memorial State Beach
 94005 Brisbane        1980   298 San Bruno Mountain State Park
 94074 San Gregorio    1958   414 San Gregorio State Beach
 94015 Daly City       1955    58 Thornton State Beach
 Enter an option (H- for help):
 e

 Deleting Hash.
 Program ended with exit code: 0
 */

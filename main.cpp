// ********************************************************* 
// Program: YOUR_FILENAME.cpp 
// Course: CCP6114 Programming Fundamentals
// Lecture Class: 
// Tutorial Class: 
// Trimester: 2430
// Member_1: ID | NAME | EMAIL | PHONE
// Member_2: ID | NAME | EMAIL | PHONE
// Member_3: ID | NAME | EMAIL | PHONE
// Member_4: ID | NAME | EMAIL | PHONE
// *********************************************************
// Task Distribution
// Member_1: 
// Member_2: 
// Member_3: 
// Member_4:
// *********************************************************

#include <iostream>
#include <fstream> // header file for file access

using namespace std;

int main() {

ifstream dataIn;  // inputs from a file
ofstream dataOut; // outputs to a file
string filename , line;


cout << "Hello world"  << endl ;

cout << "Enter the filename: " <<endl ;
cin >> filename ;

dataIn.open(filename) ;

if (dataIn) {
    cout << "opened" ;
    // timer to display output after a bit 
    while (getline(dataIn,line) ) {
        cout << line ;
        dataOut.open(line) ;
    }
    dataIn.close() ;

}
else {
    cout << "Failed to open the file" ;

}
// dataOut.open(filename) ;


return 0;
}

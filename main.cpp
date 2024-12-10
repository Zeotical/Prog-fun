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
#include <string>

using namespace std;

int main() {

ifstream dataIn;  // inputs from a file
ofstream dataOut; // outputs to a file
string filename , line , fileOut, first;
int pos1, pos2 ;


cout << "Hello world"  << endl ;

cout << "Enter the filename: " <<endl ;
cin >> filename ;

dataIn.open(filename) ;

if (dataIn) {
    cout << "opened" << endl<<endl;
    // add timer to display output after a bit 
    // dataOut.open("placeholderrr.txt") ;
    while (getline(dataIn,line) ) {
        
        if (!line.find("CREATE")) {
            int pos1= line.find(";") ;

            int pos2 = line.find(" ");

            string sub = line.substr(pos2,pos1-pos2) ;
    
            dataOut.open(sub); 
            dataOut << "CREATE" << sub<<";" << endl ;
            cout << "CREATE" << sub<<";" << endl ;

            while (getline(dataIn,line) ) {
            cout << line << endl;

            dataOut<< line << endl;    
            } }

 
            
         

    }
    dataIn.close() ;

}
else {
    cout << "Failed to open the file" ;

}
// dataOut.open(filename) ;


return 0;
}

// ********************************************************* 
// Program: YOUR_FILENAME.cpp 
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC6L
// Tutorial Class: T12L
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
    while (getline(dataIn,line) ) { // Reads each line from the input file (dataIn) into the string 'line'
        
        if (!line.find("CREATE")) {    //True if "CREATE" is at the start of the line."!" negates 0 (index pos of CREATE) to true.
            int pos1= line.find(";") ; //Finds index of first ';'in the string

            int pos2 = line.find(" ");  //Finds index of the first empty space (' ') in the string

            string dbName = line.substr(pos2,pos1-pos2) ; //Extracts the substring starting at pos2 with length (pos1-pos2)
    
            dataOut.open(dbName); //Opens the file using the extracted filename stored in 'sub'
            dataOut << "CREATE" << dbName<<";" << endl ; //Writes "CREATE <filename> ;" to the file
            cout << "CREATE" << dbName <<";" << endl ; // "  " to the terminal

            while (getline(dataIn,line) ) {
            cout << line << endl; //Writes each line to the terminal 

            dataOut<< line << endl; // " " to the outputfile  
                

            if (!line.find("CREATE TABLE") || !line.find("TABLES;")) {    //True if "CREATE" is at the start of the line."!" negates 0 (index pos of CREATE) to true
                if (!line.find("CREATE TABLE")){
                int pos1= line.find("(") ; //Finds index of first ';'in the string

                int pos2 = line.find("BLE");  //Finds index of the first empty space (' ') in the string

                string tableName = line.substr(pos1-pos2,pos2) ;
                cout << tableName ;
                dataOut << tableName ; }
                else if (!line.find("TABLES;")) {
                cout << tableName ;
                dataOut << tableName ;
                }   } 

             }}

 
            
         

    }
    dataIn.close() ;

}
else {
    cout << "Failed to open the file" ;

}

return 0;
}


// #include <iostream>
// using namespace std;
// int main() {
//    string line ="CREATE Table customer(" ;
//      if (!line.find("CREATE Table")) {    //True if "CREATE" is at the start of the line."!" negates 0 (index pos of CREATE) to true
//             int pos1= line.find("(") ; //Finds index of first ';'in the string

//             int pos2 = line.find("ble");  //Finds index of the first empty space (' ') in the string

//             string tableName = line.substr(pos1-pos2,pos2) ;
//             cout << sub ; }
//         if (!line.find("TABLES")) {
//             cout << sub ;
//             dataOut << sub ;
//         }    
        

//     return 0;
// }
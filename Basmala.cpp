// ********************************************************* 
// Program: YOUR_FILENAME.cpp 
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC6L
// Tutorial Class: T12L
// Trimester: 2430
// Member_1: 243UC247PF | BASMALA MOHAMMED ALI ELIMAM | BASMALA.MOHAMED.ALI@student.mmu.edu.my | +966 50 849 3218
// Member_2: 243UC246PD | ATODAN RIZKY PARIJOGO| ATODAN.RIZKY.PARIJOGO@student.mmu.edu.my | +62 811-8851-054
// Member_3: 243UC247KC | NUR IRFAN BIN MD SHAHRUL NIZAM | NUR.IRFAN.MD@student.mmu.edu.my | +60 17-230 6376
// Member_4: 243UC245K6 | KOK CHUEN HOU |  KOK.CHUEN.HOU@student.mmu.edu.my | +60 11-1984 8099
// *********************************************************
// Task Distribution
// Member_1: CREATE AND VIEW DB
// Member_2: CREATE AND VIEW TABLE NAME AND COLUMNS
// Member_3: INSERT ROWS TO TABLE
// Member_4: VIEW TABLE IN CSV
// *********************************************************

#include <iostream>
#include <fstream> // header file for file access
#include <string>
#include <vector> 
#include <filesystem> // library to output filepath

using namespace std;

int main() {

ifstream dataIn;  // inputs from a file
ofstream dataOut; // outputs to a file

// FUNCTIONS PROTOTYPES
void createDb (string, ofstream&);
void markKeywords (string&, string ,ofstream&);
void displayFilepath (string, string, ofstream&);


// VARIABLES + VECTORS
string filename , line, dbName ;
int pos1, pos2 ;
string tableName ;
vector <string> columns; 
vector <string> rows ;
vector <vector<string>> twoDrows;
string symbol("> ") ;

cout << "Light Mariadb Interpreter"  << endl ;

cout << "Enter the filename: " <<endl ;
cin >> filename ;

dataIn.open(filename) ;

if (dataIn) { //outer if
    // add timer to display output after a bit 
    while (getline(dataIn,line) ) { // Reads each line from the input file (dataIn) into the string 'line' //while loop
        //DATABASE OPERATIONS
        createDb(line,dataOut) ;
        while (getline(dataIn,line) ) { // inner while
        // INSERTING THIS > AT THE BEGIINING 
        markKeywords(line,symbol,dataOut);
        
        cout << line << endl; //Writes each line to the terminal 
        dataOut<< line << endl;  // " " to the outputfile  
        //FILE PATH
        displayFilepath(line,filename,dataOut);
            
        //TABLE OPERATIONS
            if (!line.find("> CREATE TABLE") || !line.find("> TABLES;") )  {    //True if "CREATE" is at the start of the line."!" negates 0 (index pos of CREATE) to true
               
                if (!line.find("> CREATE TABLE") ) {
                int pos1= line.find("TABLE") + 6 ; 

                int pos2 = line.find("("); 

                tableName = line.substr(pos1,pos2-pos1) ; 
                }
                else if (!line.find("> TABLES;")) {
                cout << tableName << endl ;
                dataOut << tableName  << endl; 
            }                                   }
            
            else if (line.find("INT")!= std::string::npos && line.find("INSERT")== std::string::npos && columns.size() <= 9 )   {
                    int pos = line.find("INT") - 1 ;
                    string integer = line.substr(0,pos); // FOR some reason gives insert too
                    columns.push_back(integer);
            } 


            else if (line.find("TEXT")!= std::string::npos && columns.size() <=9 ) {
                    int pos = line.find("TEXT") - 1;
                    string text = line.substr(0,pos);
                    columns.push_back(text);
                    
            } 

            //ROW STUFF 
            else if (line.find("VALUES")!= std::string::npos){ // outer inner if
            rows.clear() ; //clears the vector not wanted 
            int pos1= line.find(" (") + 2 ; 
            int pos2 = line.find(";");
            
            string all_values = line.substr(pos1,pos2-pos1) ; // takes out 4,'name4','city4','state4','country4','phone4','email4'
        //cout << all_values;
            if(all_values.find(",")) { //inner if
            int pos1= 0 ;
            int pos2 = all_values.find(",");

            string sep_values = all_values.substr(pos1,pos2) ;
            //cout << sep_values << endl ;     // prints the number
            rows.push_back(sep_values) ;
            int pos ;
            pos = all_values.find(",") ;
            all_values.erase(0, pos+1) ; //removes the number if i remember right

            while (!all_values.find("'"))  {
                
            if( all_values.find("',") != std::string::npos) {
            pos1= all_values.find("'") +1 ;
            pos2 = all_values.find("',")-1;

            sep_values = all_values.substr(pos1,pos2) ;
            //cout << sep_values << endl ; //all values between the number and the last value
            rows.push_back(sep_values);
            pos = all_values.find("',") ;
            all_values.erase(0, pos + 2) ;    
            }  
       
            else {
            pos1= all_values.find("'") +1;
            pos2 = all_values.find_last_of("'");
            sep_values = all_values.substr(pos1,pos2-pos1) ;
            //cout << sep_values << endl ; //the last value
            rows.push_back(sep_values);
            twoDrows.push_back(rows) ; /// variable an then from there add ++ 
            all_values.clear();} // clears the sub so the loop stops
            
            } // while loop
            } // inner if
        } // outer iinner if

        //CSV 
        else if (line.find("SELECT * FROM")!= std::string::npos){
        //COLUMNS CSV  
        for(int col = 0 ; col < columns.size() ; col ++){
            if (col==columns.size()-1) {
                cout << columns[col]  ;
                dataOut << columns[col] ;
            }
            else {
               cout << columns[col] << "," ; 
               dataOut << columns[col] << "," ; 
            } 
        }

        cout << endl; 
        dataOut << endl;   

        //ROWS CSV
        for (int x=0 ; x< twoDrows.size(); x++){ //lol size is four so four rows yay
          for (int i=0 ; i<rows.size(); i++) { //twoDrows[x].back().size() figure out this row thing 
            if (i==rows.size() - 1) {
               cout << twoDrows[x][i] ;
        //cout <<   twoDrows[x].back().size() ;     
               dataOut << twoDrows[x][i] ;
            }
            else {
            cout << twoDrows[x][i] <<"," ;
            dataOut<< twoDrows[x][i] <<","; 
            }
          } 
            cout << endl;
            dataOut << endl ;
        }
        cout << endl ; // add space after final row is displayed                                  
  
        } 
        }   

 
            
         

    }
    dataIn.close() ;


}
else {
    cout << "Failed to open the file" << endl ;

}
//CSV file code ez
// dataOut.close() ;
// dataOut.open("hi.csv") ;
// for (int x=0 ; x< twoDrows.size(); x++){ //lol size is four so four rows yay
//           for (int i=0 ; i<= twoDrows[x].back().size(); i++) {
//             if (i==twoDrows[x].back().size()) {
//                cout << twoDrows[x][i] ;
//         cout <<   twoDrows[x].back().size() ;     
//                dataOut << twoDrows[x][i] ;
//             }
//             else {
//             cout << twoDrows[x][i] <<"," ;
//             dataOut<< twoDrows[x][i] <<","; 
//             }
//           } 
//             cout << endl;
//             dataOut << endl ;
//         }

return 0;
}

//FUNCTIONS

void createDb(string line, ofstream &dataOut) {
 if (!line.find("CREATE")) {    //True if "CREATE" is at the start of the line."!" negates 0 (index pos of CREATE) to true.
            int pos1= line.find(";") ; //Finds index of first ';'in the string // inner if

            int pos2 = line.find(" ");  //Finds index of the first empty space (' ') in the string

            string dbName = line.substr(pos2,pos1-pos2) ; //Extracts the substring starting at pos2 with length (pos1-pos2)
            dataOut.open(dbName); //Opens the file using the extracted filename stored in 'dbName'
            dataOut << "> CREATE" << dbName<<";" << endl ; //Writes "CREATE <filename> ;" to the file
            cout << "> CREATE" << dbName <<";" << endl ; // "  " to the terminal
            
             }

}

void markKeywords(string &line, string symbol ,ofstream &dataOut){
    if (!line.find("DATABASES")|| !line.find("CREATE TABLE") || 
            !line.find("TABLES;") || !line.find("INSERT INTO") || 
            !line.find("SELECT * FROM") || !line.find("SELECT COUNT(*)") || 
            !line.find("DELETE FROM") || !line.find("UPDATE") ) {
                line.insert(0,symbol) ; }

}

void displayFilepath(string line,string filename, ofstream &dataOut){
    if (!line.find("> DATABASES")){
            string filepath = std::filesystem::absolute(filename);
            cout << filepath ;
            dataOut << filepath ; 
            }

}
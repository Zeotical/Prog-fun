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
string filename , line ;
int pos1, pos2 ;


cout << "Hello world"  << endl ;

cout << "Enter the filename: " <<endl ;
cin >> filename ;

dataIn.open(filename) ;

if (dataIn) { //outer if
    cout << "opened" << endl<<endl;
    // add timer to display output after a bit 
    while (getline(dataIn,line) ) { // Reads each line from the input file (dataIn) into the string 'line' //while loop
        
        if (!line.find("CREATE")) {    //True if "CREATE" is at the start of the line."!" negates 0 (index pos of CREATE) to true.
            int pos1= line.find(";") ; //Finds index of first ';'in the string // inner if

            int pos2 = line.find(" ");  //Finds index of the first empty space (' ') in the string

            string dbName = line.substr(pos2,pos1-pos2) ; //Extracts the substring starting at pos2 with length (pos1-pos2)
            dataOut.open(dbName); //Opens the file using the extracted filename stored in 'dbName'
            dataOut << "> CREATE" << dbName<<";" << endl ; //Writes "CREATE <filename> ;" to the file
            cout << "> CREATE" << dbName <<";" << endl ; // "  " to the terminal
            
             }


            string tableName ;
            string result ;
            vector <string> hat ;
            vector <string> bus ;
            vector <string> textType; 
            vector <int> numType ;

        while (getline(dataIn,line) ) { // inner while
            cout << line << endl; //Writes each line to the terminal 
            dataOut<< line << endl; // " " to the outputfile  

            if (!line.find("DATABASES")){
            string filepath = std::filesystem::absolute(filename);
            cout << filepath ;
            dataOut << filepath ; 
            }

            else if (!line.find("CREATE TABLE") || !line.find("TABLES;") )  {    //True if "CREATE" is at the start of the line."!" negates 0 (index pos of CREATE) to true
                if (!line.find("CREATE TABLE") ) {
                int pos1= line.find("TABLE") + 6 ; 

                int pos2 = line.find("("); 

                tableName = line.substr(pos1,pos2-pos1) ; 
                }
                else if (!line.find("TABLES;")) {
                cout << tableName << endl ;
                dataOut << tableName  << endl; 
            }                                   }
            
                
            else if (line.find("INT")!= std::string::npos)   {
                 int pos = line.find("INT") ;
                 string integer = line.substr(0,pos);
                 hat.push_back(integer);

                 cout << result ; 
            } 


            else if (line.find("TEXT")!= std::string::npos) {
                int pos = line.find("TEXT") ;
                string text = line.substr(0,pos);
                textType.push_back(text);
                cout << result ;
            }

           // else if (!line.find(tableName)   ) { // outer inner else if
            else  if (line.find("VALUES") != std::string::npos){ 
                cout <<  endl ;
                int pos1= line.find(" (") + 2 ; 
                int pos2 = line.find(");");
                string valuess = line.substr(pos1,pos2-pos1) ;
                //numType.push_back(2);
                textType.push_back(valuess) ; 
               } //}
      
 
            else if (line.find("SELECT * FROM")!= std::string::npos){
                for (string cars:textType) {
                    while (cars.find("'")!= std::string::npos) {
                        int pos = cars.find("'") ;
                        cars.erase(pos, 1);
                        if (cars.find("'")==std::string::npos){ 
   
                        cout << cars << endl;
                        dataOut << cars << endl ; }
                    }        
                }        
            }           
                                
            
        }   

 
            
         

    }
    dataIn.close() ;


}
else {
    cout << "Failed to open the file" << endl ;

}


return 0;
}


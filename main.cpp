// ******************************************************************************************************************
// Program: main.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC6L
// Tutorial Class: T12L
// Trimester: 2430
// Member_1: 243UC247PF | BASMALA MOHAMMED ALI ELIMAM | BASMALA.MOHAMED.ALI@student.mmu.edu.my | +966 50 849 3218
// Member_2: 243UC246PD | ATODAN RIZKY PARIJOGO| ATODAN.RIZKY.PARIJOGO@student.mmu.edu.my | +62 811-8851-054
// Member_3: 243UC247KC | NUR IRFAN BIN MD SHAHRUL NIZAM | NUR.IRFAN.MD@student.mmu.edu.my | +60 17-230 6376
// Member_4: 243UC245K6 | KOK CHUEN HOU |  KOK.CHUEN.HOU@student.mmu.edu.my | +60 11-1984 8099
// ******************************************************************************************************************

// Task Distribution
// Member_1: Milestone 1 tasks, marking the keywords, filepath
// Member_2: Update table rows and view table,sample 3
// Member_3: Delete table rows and view table
// Member_4: Count and output number of rows in the table , Loop for user input, Naming csv output file
// ******************************************************************************************************************

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
void markCommands (string&, string ,ofstream&);
void displayFilepath (string, string, ofstream&);
void createTable (string,string&,ofstream&);
void extractColumns (string, vector<string>&, ofstream&);
void extractRows (string, vector<string> & ,vector<vector<string>>&, ofstream&);
void displayCols (string, vector<string> & , ofstream&);
void displayRows (string, vector<string> & ,vector<vector<string>>&, ofstream&);
void displayTable (string,vector<string> &,vector<string> & ,vector<vector<string>>&,ofstream&) ;
void rowCounter(string,vector<vector<string>>&, ofstream&);
void deleteRows(string,vector<vector<string>>&, ofstream&);
void updateRows(vector<vector<string>>& , vector<string> &,  string&, string&, int);




// VARIABLES + VECTORS
string filename , line, dbName , output_name;
int pos1, pos2 ;
string tableName ;
vector <string> columns;
vector <string> rows ;
vector <vector<string>> twoDrows;
string symbol("> ") ;
char menu, output_choice;

do{
    twoDrows.clear();
    rows.clear();
    columns.clear();
    cout << "Light Mariadb Interpreter"  << endl ;

    cout << "Enter the filename: " <<endl ;
    cin >> filename ;

    dataIn.open(filename) ;

if (dataIn) { //outer if
    while (getline(dataIn,line) ) { // Reads each line from the input file (dataIn) into the string 'line' //while loop
        //DATABASE OPERATIONS
        if (!line.find("CREATE")) {    //True if "CREATE" is at the start of the line."!" negat es 0 (index pos of CREATE) to true.
        createDb(line,dataOut) ;
        }
        // INSERTING THIS > AT THE BEGINNING OF EACH COMMAND
         markCommands(line,symbol,dataOut);
        cout << line << endl; //Writes the CREATE command to the terminal
        dataOut<< line << endl;  //Writes the CREATE command to the output file
        while(getline(dataIn,line) ) {
        // INSERTING THIS > AT THE BEGINNING OF EACH COMMAND
         markCommands(line,symbol,dataOut);

        cout << line << endl; //Writes each line to the terminal
        dataOut<< line << endl;  //Writes each line to the output file

        //FILE PATH
        if (!line.find("> DATABASES")){
         displayFilepath(line,filename,dataOut);
         }

        //TABLE OPERATIONS
        else if (!line.find("> CREATE TABLE") || !line.find("> TABLES;") )  {  //True if "CREATE" is at the start of the line."!" negates 0 (index pos of CREATE) to true
         createTable(line,tableName,dataOut);
        }

        //Extracting Columns
        else if (line.find("INT")!= string::npos || line.find("TEXT")!= string::npos && columns.size() <= 9 )   {

         extractColumns(line,columns,dataOut); }

        //Exatracting ROWS
        else if (line.find("VALUES")!= string::npos){
         extractRows(line,rows,twoDrows,dataOut);
        }

        //Display Table
        else if (line.find("SELECT * FROM")!= string::npos){
         displayTable(line,columns,rows,twoDrows,dataOut);
         }

        // DELETE ROWS
        else if (line.find("DELETE FROM") != string::npos && line.find("WHERE") != string::npos){
         deleteRows(line,twoDrows,dataOut);

        }

        //Update Row
        else if (line.find("UPDATE") != string::npos) {
            int pos = line.find("SET")+ 4;
             int pos2 = line.find("=");
             string columnValue = line.substr(pos,pos2-pos);

             int pos3 = line.find("=") + 2 ;
             int pos4 = line.find_last_of("'")  ;
             string newValue = line.substr(pos3, pos4-pos3);

             int pos5 = line.find_last_of("=")+ 1;
             int pos6 = line.find(";") ;
             string row = line.substr(pos5,pos6);
             int rowToUpdate = stoi(row) ;

    
                    updateRows(twoDrows, columns, columnValue, newValue, rowToUpdate);
                }

                

        // ROW COUNTER
        else if (line.find("SELECT COUNT(*)")!= string::npos){
         rowCounter(line,twoDrows,dataOut);
         }
  
        

    }// inner while loop
    }//outer while loop
    dataIn.close() ;
    //CSV output file
    dataOut.close() ;
    do
    {
        cout << "Do you want to output this file as a csv file?" << endl;
        cout << "If yes, please input \"Y\" or \"N\" for no." << endl;
        cin >> output_choice;
        output_choice = toupper(output_choice);


    if (output_choice == 'Y')
    {
         cout << "Enter a name for the csv file." << endl;
            cin >> output_name;
            dataOut.open(output_name+".csv") ;
            displayTable(line,columns,rows,twoDrows,dataOut) ;
            output_choice= 'N';
    } }  while (output_choice != 'Y' && output_choice != 'N');



}
else {
    cout << "Failed to open the file" << endl ;
}

    do
    {
        cout << endl << "Continue? [Y/N]" << endl;
        cin >> menu; // can jus capitalize this
        if (menu=='Y' || menu=='y'){
            twoDrows.clear(); //clears rows from previous input file
            dataOut.close(); //closes previous input file
        }
        menu = toupper(menu);
    } while (menu != 'Y' && menu != 'N');

} while (menu != 'N');

    return 0;
}

//FUNCTIONS

void createDb(string line, ofstream &dataOut) {

    int pos1= line.find(";") ; //Finds index of first ';'in the string // inner if

    int pos2 = line.find(" ");  //Finds index of the first empty space (' ') in the string

    string dbName = line.substr(pos2,pos1-pos2) ; //Extracts the substring starting at pos2 with length (pos1-pos2)
    dataOut.open(dbName); //Opens the file using the extracted filename stored in 'dbName'
    }

void markCommands(string &line, string symbol ,ofstream &dataOut){
    if (!line.find("CREATE")||!line.find("DATABASES")|| !line.find("CREATE TABLE") ||
            !line.find("TABLES;") || !line.find("INSERT INTO") ||
            !line.find("SELECT * FROM") || !line.find("SELECT COUNT(*)") ||
            !line.find("DELETE FROM") || !line.find("UPDATE") ) {

            line.insert(0,symbol) ;
            }

}

void displayFilepath(string line,string filename, ofstream &dataOut){
    string filepath = filesystem::absolute(filename);
    cout << filepath ;
    dataOut << filepath ;
    }

void createTable(string line, string &tableName ,ofstream &dataOut){
    if (!line.find("> CREATE TABLE") ) {
    int pos1= line.find("TABLE") + 6 ;
    int pos2 = line.find("(");

    tableName = line.substr(pos1,pos2-pos1) ;
    }
    else if (!line.find("> TABLES;")) {
    cout << tableName << endl ;
    dataOut << tableName  << endl;
    }
}

void extractColumns(string line,vector <string> &columns,ofstream &dataOut){
    if (line.find("INT")!= string::npos && line.find("INSERT INTO")== string::npos && columns.size() <= 9 )   { //line find INT from INSERT INTO so to avoide that I search for lines that don't contain it.
                    int pos = line.find("INT") - 1 ;
                    string integer = line.substr(0,pos);
                    columns.push_back(integer);
            }
    else if (line.find("TEXT")!= string::npos && columns.size() <=9 ) {
                    int pos = line.find("TEXT") - 1;
                    string text = line.substr(0,pos);
                    columns.push_back(text);

            }
}

void extractRows(string line, vector<string> &rows, vector<vector<string>> &twoDrows, ofstream &dataOut){
    rows.clear() ; //clears the vector
    int pos1= line.find(" (") + 2 ;
    int pos2 = line.find(";");

    string all_values = line.substr(pos1,pos2-pos1) ; // takes out the values eg: 4,'name4','city4','state4','country4','phone4','email4'
        //cout << all_values;
    if(all_values.find(",")) { //inner if
        int pos1= 0 ;
        int pos2 = all_values.find(",");

            string sep_values = all_values.substr(pos1,pos2) ;
            rows.push_back(sep_values) ; //pushes the number into the rows vector
            int pos ;
            pos = all_values.find(",") ;
            all_values.erase(0, pos+1) ; //removes the number from the rest of the values

            while (!all_values.find("'"))  {

            if( all_values.find("',") != string::npos) { //Takes out all the values between the number and the last value
            pos1= all_values.find("'") +1 ;
            pos2 = all_values.find("',")-1;

            sep_values = all_values.substr(pos1,pos2) ;
            rows.push_back(sep_values);
            pos = all_values.find("',") ;
            all_values.erase(0, pos + 2) ;
            }

            else { //Takes out the last value
            pos1= all_values.find("'") +1;
            pos2 = all_values.find_last_of("'");
            sep_values = all_values.substr(pos1,pos2-pos1) ;
            rows.push_back(sep_values);
            twoDrows.push_back(rows) ;
            all_values.clear();} // clears the sub so the loop stops

            } // while loop
            } // inner if
} //func closing brace

void displayCols(string line, vector<string> &columns, ofstream &dataOut){
 //COLUMNS display
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
}

void displayRows(string line, vector<string> &rows, vector<vector<string>> &twoDrows, ofstream &dataOut){
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
            dataOut << endl ; //space b/w each rows
        }
        cout << endl ; // add space after final row is displayed maybe remove this?
        dataOut << endl ;
}

void displayTable(string line,  vector<string> &columns, vector<string> &rows, vector<vector<string>> &twoDrows, ofstream &dataOut){

    displayCols(line,columns,dataOut);
    cout << endl; //space b/w columns and rows
    dataOut << endl;
    displayRows(line,rows,twoDrows,dataOut);
    }


void rowCounter (string line, vector<vector<string>> &twoDrows, ofstream &dataOut){

    cout << twoDrows.size() << endl;
    dataOut  << twoDrows.size() << endl;
    }

void deleteRows(string line,vector<vector<string>> &twoDrows, ofstream &dataOut ){
    int wherePos = line.find("WHERE");
    string condition = line.substr(wherePos); // From "WHERE customer_id=X;"
    int equalsPos = condition.find("=");
    string targetID = condition.substr(equalsPos + 1); // Get the "X" value (e.g., "4;")
    targetID = targetID.substr(0, targetID.find(";")); // Remove trailing ";"

    // Convert targetID to integer
    int targetRow = stoi(targetID);

    // Delete the specific row in twoDrows based on targetID
    for (int i = 0; i < twoDrows.size(); i++)
    {
        if (stoi(twoDrows[i][0]) == targetRow) // Compare with customer_id (first column)
        {
            twoDrows.erase(twoDrows.begin() + i); // Remove the row
            break;                                // Exit after deleting the row
        }
    }
}

void updateRows(vector<vector<string>>& twoDrows, vector<string> &columns,string &columnValue, string& newValue, int rowToUpdate) {
    // Find column index based on column value
    int columnIndex = -1;
    for (int i = 0; i < columns.size(); ++i) {
        if (columns[i] == columnValue) {
            columnIndex = i;
            break;
        }
    }

    if (columnIndex == -1) {
        cout << "Column not found!" << endl;
        return;
    }

    // Update the row corresponding to the ID
    for (auto& row : twoDrows) {
        if (stoi(row[0]) == rowToUpdate) { // Assuming the first column is ID
             for (int col = 0; col < columns.size(); ++col) {
                if (columns[col] == columnValue) { 
                    row[col] = newValue;
                }}
            break; }
        else if (stoi(row[0]) != rowToUpdate){
            cout << "No such ID found"<<endl;
        }    
         
        
    }
}
// #include <iostream>
// #include <fstream> // header file for file access
// #include <string>
// #include <vector> 

// using namespace std;

// int main() {

// vector <string> car ={"1,'name1','city1','state1','country1','phone1','email1'"}  ;
// string line = "INSERT INTO customer(customer_id,customer_name,customer_city,customer_state,customer_country,customer_phone,customer_email) VALUES (4,'name4','city4','state4','country','phone4','email4');"  ;

// if (!line.find("INSERT INTO")) { // outer if
//     if (line.find("VALUES")){ // outer inner if
        
//         int pos1= line.find(" (") + 2 ; 
//         int pos2 = line.find(");");
        
//         string sub = line.substr(pos1,pos2-pos1) ;
//         cout << sub<< endl ;
     
//         if(sub.find(",")) { //inner if
//          int pos1= 0 ;
//          int pos2 = sub.find(",");

//          string bus = sub.substr(pos1,pos2) ;
//          cout << bus << endl ;     
//         int pos ;
//         pos = sub.find(",") ;
//         sub.erase(0, pos+1) ;
//         while (!sub.find("'"))  {
            
//        // cout << sub<< endl ;
//         if( sub.find("',") != std::string::npos) {
//          pos1= sub.find("'") +1 ;
//          pos2 = sub.find("',")-1;

//          bus = sub.substr(pos1,pos2) ;
//          cout << bus << endl ;
//          pos = sub.find("',") ;
//          sub.erase(0, pos + 2) ;    
//         }  
       
//         else {
//           pos1= sub.find("'") +1;
//           pos2 = sub.find_last_of("'");
//           bus = sub.substr(pos1,pos2-pos1) ;
//           cout << bus << endl ;
//           sub.clear();}
          
//         } // while loop
//         } // inner if
//     } // outer iinner if
// }  //outer if

// return 0; } 

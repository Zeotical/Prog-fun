#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    ifstream dataIn;  // File input stream
    ofstream dataOut; // File output stream

    string filename, line, dbName;
    string tableName;
    vector<string> columns;
    vector<string> rows;
    vector<vector<string>> twoDrows;
    string sil("> ");

    cout << "Light Mariadb Interpreter" << endl;
    cout << "Enter the filename: ";
    cin >> filename;

    // Improved file handling with filename display for debugging
    cout << "Attempting to open file: " << filename << endl;
    dataIn.open(filename);
    if (!dataIn) {
        cout << "Failed to open the file: " << filename << endl;
        return 1;
    }

    while (getline(dataIn, line)) {
        if (!line.find("CREATE")) {
            int pos1 = line.find(";");
            int pos2 = line.find(" ");
            dbName = line.substr(pos2, pos1 - pos2);
            dataOut.open(dbName);
            dataOut << "> CREATE " << dbName << ";" << endl;
            cout << "> CREATE " << dbName << ";" << endl;
        }

        if (!line.find("DATABASES") || !line.find("CREATE TABLE") || !line.find("TABLES;") || !line.find("INSERT INTO") || !line.find("SELECT * FROM")) {
            line.insert(0, sil);
            cout << line << endl;
            dataOut << line << endl;
        } else {
            cout << line << endl;
            dataOut << line << endl;
        }

        if (line.find("VALUES") != string::npos) {
            // Improved row parsing using stringstream
            rows.clear();
            int pos1 = line.find(" (") + 2;
            int pos2 = line.find(";");
            string all_values = line.substr(pos1, pos2 - pos1);
            stringstream ss(all_values);
            string sep_values;

            while (getline(ss, sep_values, ',')) {
                // Assuming a helper function trim() removes whitespace or quotes if needed
                rows.push_back(sep_values);  // Replace with trim(sep_values) if necessary
            }
            twoDrows.push_back(rows);
        }

        if (line.find("SELECT * FROM") != string::npos) {
            // Improved CSV output formatting using range-based for loops
            for (const auto& col : columns) {
                cout << col << (col == columns.back() ? "" : ",");
            }
            cout << endl;
            dataOut << endl;

            for (const auto& row : twoDrows) {
                for (size_t i = 0; i < row.size(); ++i) {
                    cout << row[i] << (i == row.size() - 1 ? "" : ",");
                }
                cout << endl;
                dataOut << endl;
            }
        }
    }

    dataIn.close();
    dataOut.close();

    return 0;
}

#include "properties.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>


using namespace std;

//Generic Class for grabbing the properties stored in properties.txt
Properties::Properties()
{
    fillProperties();
}

vector<string> Properties::splitString(const string & text, char sep)
{
        string field;
        vector<string> fields;

        stringstream inputStr(text);

        while (getline(inputStr, field, sep)) {
            fields.push_back(field);
        }

        return fields;
}


void Properties::fillProperties(){
    string line;
    ifstream input("../properties.txt", ios::in);
    vector<string> fields;


    if (!input.is_open()) {
        cout << "File not found. Will Exit..." << endl;
        exit(1);
    }
    else {
        while (getline(input, line)) {
            fields = splitString(line, '=');
            if (fields.size() > 0) {
                this->properties[fields[0]] = fields[1];
            }
        }
        input.close();
    }
}

#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>


User::User()
{
}

User::User(const string & username, const string & password)
{
	this->password = Password(password);
	this->username = username;
}


User::~User()
{
}

void User::setUsername(const string & username)
{
	this->username = username;
}

void User::setPassword(const string & password)
{
	this->password = Password(password);
}

bool User::verifyLogin()
{
	string line;
    ifstream input("../properties.txt", ios::in);
	vector<string> fields;

	map<string, string> map;


	if (!input.is_open()) {
		cout << "File not found. Will Exit..." << endl;
		exit(1);
	}
	else {
		while (getline(input, line)) {
			fields = splitString(line, '=');
			if (fields.size() > 0) {
				map[fields[0]] = fields[1];
			}
		}
		input.close();
	}

    cout << "The hash of the entered password: " << this->password.getHashedPassword() << endl;
	if (map["password"] != this->password.getHashedPassword()) {
		return false;
	}
	
	if (map["username"] != this->username) {
		return false;
	}

	return true;


}

vector<string> User::splitString(const string & text, char sep)
{
		string field;
		vector<string> fields;

		stringstream inputStr(text);

		while (getline(inputStr, field, sep)) {
			fields.push_back(field);
		}

		return fields;
}

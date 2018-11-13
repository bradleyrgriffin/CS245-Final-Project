#ifndef USER
#define USER

#include <string>
#include <iostream>
#include <vector>
#include "Password.h"
using namespace std;


class User
{
public:
	User();
	User(const string & username, const string & password);

	~User();

	void setUsername(const string & username);
	void setPassword(const string & password);

	bool verifyLogin();

	
private:
	string username;
	Password password;


};

#endif

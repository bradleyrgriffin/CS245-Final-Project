#ifndef PASSWORD
#define PASSWORD

#include <string>
#include <unordered_map>

using namespace std;

class Password
{
public:
	Password();
	Password(const string & unEncodedPassword);
	~Password();

	void encodePassword(const string &unEncodedPassword);
	string getHashedPassword();

private:
	int hashedString;
};

#endif

#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <string>
#include <map>
#include <vector>

using namespace std;

class Properties
{
public:
    Properties();

    map<string, string> getProperties(){ return this->properties; }


private:
    map<string, string> properties;
    void fillProperties();
    vector<string> splitString(const string & text, char sep);
};

#endif // PROPERTIES_H

#ifndef GROUP_H
#define GROUP_H

#include <string>

using namespace std;

class Group
{
public:
    Group();
    Group(const string& gName, const int& gId){
        this->groupId = gId;
        this->groupName = gName;
    }

    int getGroupId(){return this->groupId; }
    string getGroupName(){return this->groupName; }

private:
    string groupName;
    int groupId;
};

#endif // GROUP_H

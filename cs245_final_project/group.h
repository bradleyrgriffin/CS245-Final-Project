#ifndef GROUP_H
#define GROUP_H
#include <string>

class Group
{
public:
    Group();
    Group(const std::string& cName, const int& cId);

    std::string getGroupName(){return this->groupName; }
    int getGroupId(){return this->groupId; }


private:
    std::string groupName;
    int groupId;
};

#endif // GROUP_H

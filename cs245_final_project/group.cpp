#include "group.h"
#include <map>
#include "databaseconnection.h"

Group::Group()
{

}

Group::Group(const std::string& gName, const int& gId){
    if(gId > 0){
        this->groupId = gId;
    }

    if(gName != ""){
        this->groupName = gName;
    }
}

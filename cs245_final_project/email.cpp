#include "email.h"

Email::Email()
{

}

Email::Email(const std::string& eName, const int& eId, const int& catId){
    if(eName != ""){
        this->emailName = eName;
    }

    if(eId > 0){
        this->emailId = eId;
    }

    this->categoryId = catId;
}

#include "email.h"

Email::Email()
{

}

Email::Email(const std::string& eName, const int& eId){
    if(eName != ""){
        this->emailName = eName;
    }

    if(eId > 0){
        this->emailId = eId;
    }
}

#include "phone.h"

Phone::Phone()
{

}


Phone::Phone(const std::string& pNumber, const int& pId, const int& catId){
    if(pNumber != ""){
        this->phoneNumber = pNumber;
    }

    if(pId > 0){
        this->phoneNumberId = pId;
    }

    this->categoryId = catId;
}

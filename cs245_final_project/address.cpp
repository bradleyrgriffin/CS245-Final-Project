#include "address.h"

Address::Address()
{

}


Address::Address(const std::string& c, const std::string& s, const std::string& a, const std::string& z, const int& aId, const int& catId){
    if(c != ""){
        this->city = c;
    }

    if(s != ""){
        this->state = s;
    }

    if(a != ""){
        this->address = a;
    }

    if(z != ""){
        this->zipcode = z;
    }

    if(aId > 0){
        this->addressId =aId;
    }

    if(catId > 0){
        this->categoryId = catId;
    }

}

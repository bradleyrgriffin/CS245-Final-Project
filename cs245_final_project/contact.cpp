#include "contact.h"

Contact::Contact()
{

}

Contact::Contact(const std::string& fName, const std::string& lName, const int& cId, const int& pId){
    this->firstName = fName;
    this->lastName = lName;
    this->contactId = cId;
    this->photoId = pId;
}

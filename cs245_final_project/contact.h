#ifndef CONTACT_H
#define CONTACT_H



//Objects
#include "address.h"
#include "phone.h"
#include "group.h"
#include "email.h"


#include <vector>
#include <string>

class Contact
{
public:
    Contact();

    //Builds out initial object
    Contact(const std::string& fName, const std::string& lName, const int& cId, const int& pId);

    //Getters

    //Need to add code to get a contact's other data.

private:
    std::vector<Address> addresses;
    std::vector<Phone> phones;
    std::vector<Group> groups;
    std::vector<Email> emails;

    std::string firstName;
    std::string lastName;
    int contactId;
    int photoId;

};

#endif // CONTACT_H

#ifndef CONTACT_H
#define CONTACT_H



//Objects
#include "address.h"
#include "phone.h"
#include "email.h"
#include "photo.h"

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
    //should have code to get addresses, phones, emails, and a function to get the group ids (ideally, we'll have a separate vector for all the groups.)

private:
    std::vector<Address> addresses;
    std::vector<Phone> phones;
    std::vector<Email> emails;
    std::vector<int> groups; //Groups by ID

    std::string firstName;
    std::string lastName;
    int contactId;
    int photoId;

};

#endif // CONTACT_H

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
    int getContactId(){return this->contactId; }
    std::string getFirstName(){return this->firstName; }
    std::string getLastName(){ return this->lastName; }

    std::vector<Address>& getAddresses(){ return this->addresses; }
    std::vector<Phone>& getPhoneNumbers(){ return this->phones; }
    std::vector<Email>& getEmails(){ return this->emails; }

    //Need to add code to get a contact's other data.
    //should have code to get addresses, phones, emails, and a function to get the group ids (ideally, we'll have a separate vector for all the groups.)

    void setContactEmail(Email email){
        this->emails.push_back(email);
    }

    void setContactPhone(Phone phone){
        this->phones.push_back(phone);
    }

    void setContactAddress(Address address){
        this->addresses.push_back(address);
    }
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

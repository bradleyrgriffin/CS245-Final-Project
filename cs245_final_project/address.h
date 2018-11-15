#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

class Address
{
public:
    Address();

    Address(const std::string& c, const std::string& s, const std::string& a, const std::string& z, const int& aId);

    std::string getCity(){return this->city;}
    std::string getState(){return this->state; }
    std::string getAddress(){return this->address; }
    std::string getZipcode(){return this->zipcode; }

    int getAddressId(){return this->addressId; }

private:
    std::string city;
    std::string state;
    std::string address;
    std::string zipcode;
    int addressId;
};

#endif // ADDRESS_H

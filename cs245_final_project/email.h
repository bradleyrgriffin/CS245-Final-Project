#ifndef EMAIL_H
#define EMAIL_H

#include <string>

class Email
{
public:
    Email();

    Email(const std::string& emailName, const int& emailId);

    int getEmailId(){return this->emailId; }
    std::string getEmailName(){ return this->emailName; }
private:
    std::string emailName;
    int emailId;
};

#endif // EMAIL_H

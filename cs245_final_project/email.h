#ifndef EMAIL_H
#define EMAIL_H

#include <string>

class Email
{
public:
    Email();

    Email(const std::string& emailName, const int& emailId, const int& catId);

    int getEmailId(){return this->emailId; }
    std::string getEmailName(){ return this->emailName; }
    int getCategoryId(){ return this->categoryId; }
    std::string displayName;
private:
    std::string emailName;
    int emailId;
    int categoryId;
};

#endif // EMAIL_H

#include "Password.h"
#include <QCryptographicHash>
#include <QString>

Password::Password()
{
}

Password::Password(const string & unEncodedPassword)
{
	encodePassword(unEncodedPassword);
}


Password::~Password()
{
}

void Password::encodePassword(const string & unEncodedPassword)
{

    this->hashedString = QString(QCryptographicHash::hash((unEncodedPassword.c_str()),
                                                          QCryptographicHash::Sha3_224).toHex()).toStdString();


}

string Password::getHashedPassword()
{
    return hashedString;
}

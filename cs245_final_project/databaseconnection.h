#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <string>
#include <QtSql/QSqlDatabase>
#include <map>
#include <contact.h>

using namespace std;

class DatabaseConnection
{
public:
    DatabaseConnection();
    ~DatabaseConnection();
    bool executeQuery(const string& sql, map<int,string> params, const string& objectToMap);

    vector<Contact>& getContacts(){return this->contacts; }
    Contact& getContactById(const int& cId);


private:
    string connectionString;
    void fillConnectionDetails();
    QSqlDatabase db;
    QString getQueryStringByName(const string & queryName);

    vector<string> data;
    vector<Contact> contacts;
};

#endif // DATABASECONNECTION_H

#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <string>
#include <QtSql/QSqlDatabase>
#include <map>
#include <contact.h>
#include <address.h>
#include <category.h>
#include <email.h>
#include <group.h>
#include <phone.h>
#include <photo.h>


using namespace std;

class DatabaseConnection
{
public:
    DatabaseConnection();
    ~DatabaseConnection();
    bool executeQuery(const string& sql, map<int,string> params, const string& objectToMap);

    vector<Contact>& getContacts(){ return this->contacts; }
    vector<Category>& getCategories(){ return this->categories; }
    vector<Group>& getGroups(){ return this->groups; }

    void populateContactData();

private:
    string connectionString;
    void fillConnectionDetails();
    QSqlDatabase db;
    QString getQueryStringByName(const string & queryName);

    //catch all, to try and save some data
    vector<string> data;

    //Mapped Vector Objects
    vector<Contact> contacts;
    vector<Group> groups;
    vector<Category> categories;
        
};

#endif // DATABASECONNECTION_H

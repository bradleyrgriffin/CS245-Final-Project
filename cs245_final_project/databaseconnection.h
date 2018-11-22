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
    bool executeQuery(const string& sql, map<int,string>& params, const string& objectToMap);

    vector<Contact>& getContacts(){ return this->contacts; }
    vector<Category>& getCategories(){ return this->categories; }
    vector<Group>& getGroups(){ return this->groups; }
    vector<Photo>& getPhotos(){ return this->photos; }

    bool deleteContact(int& id);

    //Add Contact
    void addContact(map<int, string>& data);
    void addCategory(map<int, string>& data);
    void addGroup(map<int, string>& data);


    //Gets for Groups, Categories, Photos
    Group& getGroupById(int& id);
    Category& getCategoryById(int& id);
    Photo& getPhotoById(int& id);


    void populateContactData();

    void refreshData(const string& dataToRefresh);



private:
    string connectionString;
    void fillConnectionDetails();
    QSqlDatabase db;
    bool ok;
    QString getQueryStringByName(const string & queryName);

    //catch all, to try and save some data
    vector<string> data;

    //Mapped Vector Objects
    vector<Contact> contacts;
    vector<Group> groups;
    vector<Category> categories;
    vector<Photo> photos;
};

#endif // DATABASECONNECTION_H

#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <string>
#include <QtSql/QSqlDatabase>
#include <map>
#include "category.h"
#include "group.h"

using namespace std;

class DatabaseConnection
{
public:
    DatabaseConnection();
    ~DatabaseConnection();
    bool executeQuery(const string& sql, map<int,string> params, const string& objectToMap);

    vector<Category> getCategories(){return this->categories; }
    vector<Group> getGroups(){return this->groups; }

private:
    string connectionString;
    void fillConnectionDetails();
    QSqlDatabase db;
    QString getQueryStringByName(const string & queryName);

    vector<string> data;

    vector<Category> categories;
    vector<Group> groups;
};

#endif // DATABASECONNECTION_H

#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <string>
#include <QtSql/QSqlDatabase>
#include <map>

using namespace std;

class DatabaseConnection
{
public:
    DatabaseConnection();
    ~DatabaseConnection();
    bool executeQuery(const string& sql, map<int,string> params, const string& objectToMap);

private:
    string connectionString;
    void fillConnectionDetails();
    QSqlDatabase db;
    QString getQueryStringByName(const string & queryName);

    vector<string> data;
};

#endif // DATABASECONNECTION_H

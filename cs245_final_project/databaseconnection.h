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
    bool executeQuery(const string& sql, map<int,string> params);


private:
    string connectionString;
    void fillConnectionDetails();
    QSqlDatabase db;
};

#endif // DATABASECONNECTION_H

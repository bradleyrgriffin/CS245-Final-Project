#include "databaseconnection.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include "Properties.h"
#include <string>
#include <QSqlQuery>
#include <QString>

using namespace std;

DatabaseConnection::DatabaseConnection()
{
    fillConnectionDetails();

}

void DatabaseConnection::fillConnectionDetails(){
    db = QSqlDatabase::addDatabase("QODBC");

    Properties props = Properties();
    auto properties = props.getProperties();

    db.setDatabaseName(QString::fromStdString(properties["connection"]));
}

bool DatabaseConnection::executeQuery(const string& sql, map<int, string> params){
    // open the connection
    bool ok = db.open();

        // if we connect successfully...
        if(ok)
        {
            // build the SQL string
            QString s = QString::fromStdString(sql);
//            QString s;
//            s = "UPDATE customer ";
//            s += "SET email = ?, city = ?, state = ? ";
//            s += "WHERE lastName = ?";

            // prepare the query
            QSqlQuery query;
            query.setForwardOnly(true);
            query.prepare(s);

            //query.bindValue(0,QString::fromStdString("hey"));
            // bind your values to the prepared statement
            for(auto i : params){
                //query.bindValue(0, "QString::fromStdString(i.second)");
            }

            // execute the UPDATE
            if(query.exec())
            {
                return true;
            }

        } else {
            return false;
        }
        return false;
}

DatabaseConnection::~DatabaseConnection(){
    this->db.close();
}

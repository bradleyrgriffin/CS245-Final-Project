#include "databaseconnection.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include "properties.h"
#include <string>
#include <QSqlQuery>
#include <QString>
#include <QVariant>

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

QString DatabaseConnection::getQueryStringByName(const string& queryName){
    string SELECT_ALL_CONTACTS = "SELECT * FROM CONTACT";
    string INSERT_GROUP = "INSERT INTO GROUPS(GROUP_NAME) VALUES(?)";

    if(queryName == "SELECT_ALL_CONTACTS"){
        return QString::fromStdString(SELECT_ALL_CONTACTS);
    }else if(queryName == "INSERT_GROUP"){
        return QString::fromStdString(INSERT_GROUP);
    }else{
        return QString::fromStdString("N");
    }
}


//This Executes a query, binding the parameters.
bool DatabaseConnection::executeQuery(const string& queryName, map<int, string> params, const string& objectToMap){
    // open the connection
    bool ok = db.open();

        // if we connect successfully...
        if(ok)
        {

            //Grabs the SQL Query from the query function.
            QString s = getQueryStringByName(queryName);

            // prepare the query
            QSqlQuery query;
            query.setForwardOnly(true);
            query.prepare(s);

            // Bind the parameters, starting from 0, make sure you only pass in as many parameters as there are in the SQL string.
            for(auto i : params){
               query.bindValue(i.first, QString::fromStdString(i.second));
            }

            // execute the query
            if(query.exec())
            {

                //Result Set
                while (query.next())
                {
                    //Assign to The Object Needed...
                    if(objectToMap == "contact"){
                        //Create new Contact Object and assign values:
                        //E.G.
                        /*
                         * The value result set starts at 1, not 0:
                         *
                         * QString value1 = query.value(1).toString();
                         * QString value2 = query.value(2).toString();
                         *
                         * Or, to convert to normal C++ string:
                         *
                         * string value1 = QString::fromStdString(query.value(1).toString());
                        */

                        //push the object to the list of objects located in the header file.
                        //Should have get functions from the list of objects.




                    }else{
                        try{
                            data.push_back(query.value(1).toString().toStdString());
                            data.push_back(query.value(2).toString().toStdString());
                            data.push_back(query.value(3).toString().toStdString());
                            data.push_back(query.value(4).toString().toStdString());
                            data.push_back(query.value(5).toString().toStdString());
                        }catch(exception& e){
                            cout << "Error When Retrieving Result Set: " << e.what() << endl;
                        }
                    }
                }

                db.close();
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

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
#include "address.h"
#include "phone.h"
#include "contact.h"

using namespace std;

DatabaseConnection::DatabaseConnection()
{
    fillConnectionDetails();

}

void DatabaseConnection::fillConnectionDetails(){
    this->db = QSqlDatabase::addDatabase("QODBC");

    Properties props = Properties();
    auto properties = props.getProperties();

    QString driver = QString::fromStdString(properties["DRIVER"]);
    QString server = QString::fromStdString(properties["Server"]);
    QString database = QString::fromStdString(properties["Database"]);
    QString username = QString::fromStdString(properties["Uid"]);
    QString pass = QString::fromStdString(properties["Pwd"]);
    QString port = QString::fromStdString(properties["Port"]);
    QString encrypt = QString::fromStdString(properties["encrypt"]);
    QString trustServerCertificate = QString::fromStdString(properties["trustServerCertificate"]);
    QString hostName = QString::fromStdString(properties["hostNameInCertificate"]);
    QString timeout = QString::fromStdString(properties["loginTimeout"]);

    QString connectionString = "DRIVER=" + driver;
    connectionString += "Server=" + server;
    connectionString += "Database=" + database;
    connectionString += "Uid=" + username;
    connectionString += "Port=" + port;
    connectionString += "Pwd=" + pass;
    connectionString += "encrypt=" + encrypt;
    connectionString += "trustEncyptionCertificate=" + trustServerCertificate;
    connectionString += "hostNameInCertificate=" + hostName;
    connectionString += "loginTimeout=" + timeout;

    this->db.setDatabaseName(connectionString);
}

QString DatabaseConnection::getQueryStringByName(const string& queryName){


    //Insert
    string INSERT_GROUP = "INSERT INTO GROUPS(GROUP_NAME) VALUES(?)";
    string INSERT_CATEGORY = "INSERT INTO CATEGORY(CATEGORY_NAME) VALUES (?)";
    string INSERT_CONTACT = "INSERT INTO CONTACT(FIRST_NAME, LAST_NAME, PHOTO_LIBRARY_ID) VALUES (?, ?, ?)";

    //Select
    string GET_CATEGORY_BY_ID = "SELECT DISTINCT TOP(1) CATEGORY_ID, CATEGORY_NAME FROM CATEGORY WHERE CATEGORY_ID = ?";
    string GET_CATEGORY_BY_NAME = "SELECT DISTINCT TOP(1) CATEGORY_ID, CATEGORY_NAME FROM CATEGORY WHERE CATEGORY_NAME = ?";
    string GET_GROUP_BY_ID = "SELECT DISTINCT TOP(1) GROUP_ID, GROUP_NAME FROM GROUPS WHERE GROUP_ID = ?";
    string GET_GROUP_BY_NAME = "SELECT DISTINCT TOP(1) GROUP_ID, GROUP_NAME FROM GROUPS WHERE GROUP_NAME = ?";
    string SELECT_ALL_CONTACTS = "SELECT * FROM CONTACT";

    //Update


    //Delete

    if(queryName == "SELECT_ALL_CONTACTS"){
        return QString::fromStdString(SELECT_ALL_CONTACTS);
    }else if(queryName == "INSERT_GROUP"){
        return QString::fromStdString(INSERT_GROUP);
    }else if(queryName == "INSERT_CATEGORY"){
        return QString::fromStdString(INSERT_CATEGORY);
    }else if(queryName == "INSERT_CONTACT"){
        return QString::fromStdString(INSERT_CONTACT);
    }else if(queryName == "GET_CATEGORY_BY_ID"){
        return QString::fromStdString(GET_CATEGORY_BY_ID);
    }else if(queryName == "GET_CATEGORY_BY_NAME"){
       return QString::fromStdString(GET_CATEGORY_BY_NAME);
    }else if(queryName == "GET_GROUP_BY_ID"){
       return QString::fromStdString(GET_GROUP_BY_ID);
    }else if(queryName == "GET_GROUP_BY_NAME"){
       return QString::fromStdString(GET_GROUP_BY_NAME);
    }else{
        return QString::fromStdString("N");
    }
}


//This Executes a query, binding the parameters.
bool DatabaseConnection::executeQuery(const string& queryName, map<int, string> params, const string& objectToMap){
    // open the connection
    bool ok = this->db.open();

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




                    }else if(objectToMap == "insert"){
                             cout << "Just an insert" << endl;
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
            cout << "failed ok" << endl;
            return false;
        }
        return false;
}

DatabaseConnection::~DatabaseConnection(){
    this->db.close();
}

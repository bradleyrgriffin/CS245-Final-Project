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
    string GET_CATEGORIES = "SELECT CATEGORY_NAME, CATEGORY_ID FROM CATEGORY";
    string GET_GROUPS = "SELECT GROUP_NAME, GROUP_ID FROM GROUPS";
    string GET_CONTACTS = "SELECT FIRST_NAME, LAST_NAME, CONTACT_ID, PHOTO_LIBRARY_ID FROM CONTACT";
    string GET_PHONE_NUMBERS_BY_CONTACT_ID = "SELECT PHONE_NUMBER, CONTACT_X_PHONE_X_CATEGORY_ID, CATEGORY_ID FROM CONTACT_X_PHONE_X_CATEGORY WHERE CONTACT_ID = ?";
    string GET_EMAIL_BY_CONTACT_ID = "SELECT EMAIL_ADDRESS, CONTACT_X_EMAIL_X_CATEGORY_ID, CATEGORY_ID FROM CONTACT_X_EMAIL_X_CATEGORY WHERE CONTACT_ID = ?";
    string GET_ADDRESS_BY_CONTACT_ID = "SELECT CITY, STATE, STREET_ADDRESS, ZIP_CODE, CONTACT_X_ADDRESS_X_CATEGORY_ID, CATEGORY_ID FROM CONTACT_X_ADDRESS_X_CATEGORY WHERE CONTACT_ID = ?";

    //Update


    //Delete

    if(queryName == "GET_CONTACTS"){
        return QString::fromStdString(GET_CONTACTS);
    }else if(queryName == "INSERT_GROUP"){
        return QString::fromStdString(INSERT_GROUP);
    }else if(queryName == "INSERT_CATEGORY"){
        return QString::fromStdString(INSERT_CATEGORY);
    }else if(queryName == "INSERT_CONTACT"){
        return QString::fromStdString(INSERT_CONTACT);
    }else if(queryName == "GET_CATEGORIES"){
        return QString::fromStdString(GET_CATEGORIES);
    }else if(queryName == "GET_PHONE_NUMBERS_BY_CONTACT_ID"){
        return QString::fromStdString(GET_PHONE_NUMBERS_BY_CONTACT_ID);
    }else if(queryName == "GET_GROUPS"){
       return QString::fromStdString(GET_GROUPS);
    }else if(queryName == "GET_EMAIL_BY_CONTACT_ID"){
        return QString::fromStdString(GET_EMAIL_BY_CONTACT_ID);
    }else if(queryName == "GET_ADDRESS_BY_CONTACT_ID"){
        return QString::fromStdString(GET_ADDRESS_BY_CONTACT_ID);
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

                        Contact newContact = Contact(
                                    query.value(0).toString().toStdString(),
                                    query.value(1).toString().toStdString(),
                                    stoi(query.value(2).toString().toStdString()),
                                    stoi(query.value(3).toString().toStdString()));

                        this->contacts.push_back(newContact);


                    }else if(objectToMap == "insert"){
                             cout << "Just an insert" << endl;
                    }else if(objectToMap == "category"){
                        Category newCategory = Category(query.value(0).toString().toStdString(),
                                                        stoi(query.value(1).toString().toStdString()));
                        this->categories.push_back(newCategory);

                    }else if(objectToMap == "group"){
                        Group newGroup = Group(query.value(0).toString().toStdString(),
                                               stoi(query.value(1).toString().toStdString()));

                        this->groups.push_back(newGroup);

                    }else if(objectToMap == "email"){
                        Email newEmail = Email(query.value(0).toString().toStdString(),
                                               stoi(query.value(1).toString().toStdString()),
                                               stoi(query.value(2).toString().toStdString()));

                        //Attach to the Contact (should be ID of params[0])
                        for(auto& i : contacts){
                            if(i.getContactId() == stoi(params[0])){
                                i.setContactEmail(newEmail);
                                break;
                            }
                        }
                    }else if(objectToMap == "phone"){
                        Phone newPhone = Phone(query.value(0).toString().toStdString(),
                                               stoi(query.value(1).toString().toStdString()),
                                               stoi(query.value(2).toString().toStdString()));

                        //Attach to the Contact (should be ID of params[0])
                        for(auto& i : contacts){
                            if(i.getContactId() == stoi(params[0])){
                                i.setContactPhone(newPhone);
                                break;
                            }
                        }
                    }else if(objectToMap == "address"){
                        string st = query.value(0).toString().toStdString();
                        Address newAddress = Address(query.value(0).toString().toStdString(),
                                               query.value(1).toString().toStdString(),
                                               query.value(2).toString().toStdString(),
                                               query.value(3).toString().toStdString(),
                                               stoi(query.value(4).toString().toStdString()),
                                               stoi(query.value(5).toString().toStdString()));

                        //Attach to the Contact (should be ID of params[0])
                        for(auto& i : contacts){
                            if(i.getContactId() == stoi(params[0])){
                                i.setContactAddress(newAddress);
                                break;
                            }
                        }
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

                this->db.close();
                return true;
            }

        } else {
            cout << "failed ok" << endl;
            this->db.close();
            return false;
        }
        this->db.close();
        return false;
}

void DatabaseConnection::populateContactData(){

    map<int, string> paramMap;

    for(auto i : this->contacts){
        paramMap[0] = to_string(i.getContactId());


        executeQuery("GET_EMAIL_BY_CONTACT_ID", paramMap, "email");
        executeQuery("GET_PHONE_NUMBERS_BY_CONTACT_ID", paramMap, "phone");
        executeQuery("GET_ADDRESS_BY_CONTACT_ID", paramMap, "address");
    }

}

DatabaseConnection::~DatabaseConnection(){
    this->db.close();
}

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

    string INSERT_CONTACT_GROUP = "INSERT INTO GROUP_X_CONTACT(CONTACT_ID, GROUP_ID) VALUES(?, ?)";
    string INSERT_CONTACT_EMAIL = "INSERT INTO CONTACT_X_EMAIL_X_CATEGORY(CONTACT_ID, EMAIL_ADDRESS, CATEGORY_ID) VALUES (?, ?, ?)";
    string INSERT_CONTACT_PHONE = "INSERT INTO CONTACT_X_PHONE_X_CATEGORY(PHONE_NUMBER, CONTACT_ID, CATEGORY_ID) VALUES (?, ?, ?)";
    string INSERT_CONTACT_ADDRESS = "INSERT INTO CONTACT_X_ADDRESS_X_CATEGORY(STREET_ADDRESS, CITY, STATE, ZIP_CODE, CONTACT_ID, CATEGORY_ID) VALUES(?, ?, ?, ?, ?, ?)";

    //Select All
    string GET_PHOTOS = "SELECT PHOTO_LIBRARY_ID, PHOTO_PATH FROM PHOTO_LIBRARY";
    string GET_CATEGORIES = "SELECT CATEGORY_NAME, CATEGORY_ID FROM CATEGORY";
    string GET_GROUPS = "SELECT GROUP_NAME, GROUP_ID FROM GROUPS";
    string GET_CONTACTS = "SELECT FIRST_NAME, LAST_NAME, CONTACT_ID, PHOTO_LIBRARY_ID FROM CONTACT";
    string GET_PHONE_NUMBERS_BY_CONTACT_ID = "SELECT PHONE_NUMBER, CONTACT_X_PHONE_X_CATEGORY_ID, CATEGORY_ID FROM CONTACT_X_PHONE_X_CATEGORY WHERE CONTACT_ID = ?";
    string GET_EMAIL_BY_CONTACT_ID = "SELECT EMAIL_ADDRESS, CONTACT_X_EMAIL_X_CATEGORY_ID, CATEGORY_ID FROM CONTACT_X_EMAIL_X_CATEGORY WHERE CONTACT_ID = ?";
    string GET_ADDRESS_BY_CONTACT_ID = "SELECT CITY, STATE, STREET_ADDRESS, ZIP_CODE, CONTACT_X_ADDRESS_X_CATEGORY_ID, CATEGORY_ID FROM CONTACT_X_ADDRESS_X_CATEGORY WHERE CONTACT_ID = ?";
    string GET_GROUPS_BY_CONTACT_ID = "SELECT GROUP_ID FROM GROUP_X_CONTACT WHERE CONTACT_ID = ?";

    //Select Unique
    string GET_CONTACT_EMAIL_ID_BY_EMAIL = "SELECT TOP(1) EMAIL_ADDRESS, CONTACT_X_EMAIL_X_CATEGORY_ID, CATEGORY_ID FROM CONTACT_X_EMAIL_X_CATEGORY WHERE CONTACT_ID = ? AND EMAIL_ADDRESS = ? AND CATEGORY_ID = ? ORDER BY CONTACT_X_EMAIL_X_CATEGORY_ID DESC";
    string GET_CONTACT_PHONE_ID_BY_PHONE = "SELECT TOP(1) PHONE_NUMBER, CONTACT_X_PHONE_X_CATEGORY_ID, CATEGORY_ID FROM CONTACT_X_PHONE_X_CATEGORY WHERE CONTACT_ID = ? AND PHONE_NUMBER = ? AND CATEGORY_ID = ? ORDER BY CONTACT_X_PHONE_X_CATEGORY_ID DESC";
    string GET_CONTACT_ADDRESS_ID_BY_ADDRESS = "SELECT TOP(1) CITY, STATE, STREET_ADDRESS, ZIP_CODE, CONTACT_X_ADDRESS_X_CATEGORY_ID, CATEGORY_ID FROM CONTACT_X_ADDRESS_X_CATEGORY WHERE CONTACT_ID = ? AND STREET_ADDRESS = ? AND CITY = ? AND STATE = ? AND CATEGORY_ID = ? ORDER BY CONTACT_X_ADDRESS_X_CATEGORY_ID DESC";
    string GET_GROUP_BY_ID = "SELECT TOP(1) GROUP_ID FROM GROUP_X_CONTACT WHERE CONTACT_ID = ? AND GROUP_ID = ? ORDER BY GROUP_ID DESC";
    string GET_CONTACT_ID_BY_FIRST_LAST_NAME = "SELECT TOP(1) FIRST_NAME, LAST_NAME, CONTACT_ID, PHOTO_LIBRARY_ID FROM CONTACT WHERE FIRST_NAME = ? AND LAST_NAME = ? ORDER BY CONTACT_ID DESC";

    string GET_GROUP_BY_NAME = "SELECT TOP(1) GROUP_NAME, GROUP_ID FROM GROUPS WHERE GROUP_NAME = ? ORDER BY GROUP_ID DESC";
    string GET_CATEGORY_BY_NAME = "SELECT TOP(1) CATEGORY_NAME, CATEGORY_ID FROM CATEGORY WHERE CATEGORY_NAME = ? ORDER BY CATEGORY_ID DESC";
    //Update
    string UPDATE_CONTACT = "UPDATE CONTACT SET FIRST_NAME = ?, LAST_NAME  = ? WHERE CONTACT_ID = ?";

    //Delete

    //Call these in the below order to delete a contact from the database...or you'll have foreign key constraints.
        string DELETE_ALL_CONTACT_EMAILS = "DELETE FROM CONTACT_X_EMAIL_X_CATEGORY WHERE CONTACT_ID = ?"; //1
        string DELETE_ALL_CONTACT_PHONE = "DELETE FROM CONTACT_X_PHONE_X_CATEGORY WHERE CONTACT_ID = ?"; //2
        string DELETE_ALL_CONTACT_ADDRESS = "DELETE FROM CONTACT_X_ADDRESS_X_CATEGORY WHERE CONTACT_ID = ?"; //3
        string DELETE_ALL_CONTACT_GROUPS = "DELETE FROM GROUP_X_CONTACT WHERE CONTACT_ID = ?";
        string DELETE_CONTACT = "DELETE FROM CONTACT WHERE CONTACT_ID = ?"; //5

    //Remove Individual records
    string DELETE_SINGLE_EMAIL = "DELETE FROM CONTACT_X_EMAIL_X_CATEGORY WHERE CONTACT_X_EMAIL_X_CATEGORY_ID = ?";
    string DELETE_SINGLE_PHONE = "DELETE FROM CONTACT_X_PHONE_X_CATEGORY WHERE CONTACT_X_PHONE_X_CATEGORY_ID = ?";
    string DELETE_SINGLE_ADDRESS = "DELETE FROM CONTACT_X_ADDRESS_X_CATEGORY WHERE CONTACT_X_ADDRESS_X_CATEGORY_ID = ?";

    if(queryName == "GET_CONTACTS"){
        return QString::fromStdString(GET_CONTACTS);
    }else if(queryName == "GET_CATEGORY_BY_NAME"){
        return QString::fromStdString(GET_CATEGORY_BY_NAME);
    }else if(queryName == "GET_GROUP_BY_NAME"){
        return QString::fromStdString(GET_GROUP_BY_NAME);
    }else if(queryName == "GET_GROUPS_BY_CONTACT_ID"){
        return QString::fromStdString(GET_GROUPS_BY_CONTACT_ID);
    }else if(queryName == "INSERT_CONTACT_GROUP"){
        return QString::fromStdString(INSERT_CONTACT_GROUP);
    }else if(queryName == "GET_PHOTOS"){
        return QString::fromStdString(GET_PHOTOS);
    }else if(queryName == "GET_CONTACT_ADDRESS_ID_BY_ADDRESS"){
        return QString::fromStdString(GET_CONTACT_ADDRESS_ID_BY_ADDRESS);
    }else if(queryName == "GET_CONTACT_EMAIL_ID_BY_EMAIL"){
        return QString::fromStdString(GET_CONTACT_EMAIL_ID_BY_EMAIL);
    }else if(queryName == "GET_CONTACT_PHONE_ID_BY_PHONE"){
        return QString::fromStdString(GET_CONTACT_PHONE_ID_BY_PHONE);
    }else if(queryName == "DELETE_ALL_CONTACT_GROUPS"){
        return QString::fromStdString(DELETE_ALL_CONTACT_GROUPS);
    }else if(queryName == "GET_GROUP_BY_ID"){
        return QString::fromStdString(GET_GROUP_BY_ID);
    }else if(queryName == "GET_CONTACT_ID_BY_FIRST_LAST_NAME"){
        return QString::fromStdString(GET_CONTACT_ID_BY_FIRST_LAST_NAME);
    }else if(queryName == "INSERT_CONTACT_ADDRESS"){
        return QString::fromStdString(INSERT_CONTACT_ADDRESS);
    }else if(queryName == "INSERT_CONTACT_PHONE"){
            return QString::fromStdString(INSERT_CONTACT_PHONE);
    }else if(queryName == "INSERT_CONTACT_EMAIL"){
        return QString::fromStdString(INSERT_CONTACT_EMAIL);
    }else if(queryName == "UPDATE_CONTACT"){
        return QString::fromStdString(UPDATE_CONTACT);
    }else if(queryName == "DELETE_CONTACT"){
        return QString::fromStdString(DELETE_CONTACT);
    }else if(queryName == "DELETE_ALL_CONTACT_EMAILS"){
        return QString::fromStdString(DELETE_ALL_CONTACT_EMAILS);
    }else if(queryName == "DELETE_ALL_CONTACT_PHONE"){
        return QString::fromStdString(DELETE_ALL_CONTACT_PHONE);
    }else if(queryName == "DELETE_ALL_CONTACT_ADDRESS"){
        return QString::fromStdString(DELETE_ALL_CONTACT_ADDRESS);
    }else if(queryName == "DELETE_SINGLE_EMAIL"){
        return QString::fromStdString(DELETE_SINGLE_EMAIL);
    }else if(queryName == "DELETE_SINGLE_PHONE"){
        return QString::fromStdString(DELETE_SINGLE_PHONE);
    }else if(queryName == "DELETE_SINGLE_ADDRESS"){
        return QString::fromStdString(DELETE_SINGLE_ADDRESS);
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
bool DatabaseConnection::executeQuery(const string& queryName, map<int, string>& params, const string& objectToMap){
    // open the connection

    if(!(this->db.isOpen())){
        cout << "Opening DB Connection" <<endl;
         this->ok = this->db.open();
    }else if(!ok){
        cout << "Bad DB connection, reopening" << endl;
        this->db.close();
        this->ok = this->db.open();
    }

        // if we connect successfully...
        if(ok)
        {

            //Grabs the SQL Query from the query function.
            QString s = getQueryStringByName(queryName);

            //Escape if we could not find the query
            if(s == "N"){
                cout << "Query not found" << endl;
                return false;
            }


            // prepare the query
            QSqlQuery query;
            query.setForwardOnly(true);
            query.prepare(s);

            // Bind the parameters, starting from 0, make sure you only pass in as many parameters as there are in the SQL string.
            for(auto i : params){
               query.bindValue(i.first, QString::fromStdString(i.second));
            }




            try{
            // execute the query
            if(query.exec())
            {
                if(objectToMap == "delete"){
                    cout << "Deleting Object" << endl;
                }else if(objectToMap == "insert"){
                    cout << "Inserting Object" << endl;
                }else if(objectToMap == "update"){
                    cout << "Updating Object" << endl;
                }

                //Result Set
                while (query.next())
                {
                try{
                    //Assign to The Object Needed...
                    if(objectToMap == "contact"){

                        Contact newContact = Contact(
                                    query.value(0).toString().toStdString(),
                                    query.value(1).toString().toStdString(),
                                    stoi(query.value(2).toString().toStdString()),
                                    stoi(query.value(3).toString().toStdString()));

                        this->contacts.push_back(newContact);
                        cout << "Getting Contacts" << endl;

                    }else if(objectToMap == "category"){

                        Category newCategory = Category(query.value(0).toString().toStdString(),
                                                        stoi(query.value(1).toString().toStdString()));
                        this->categories.push_back(newCategory);
                        cout << "Getting Categories" << endl;

                    }else if(objectToMap == "photo"){
                        Photo newPhoto = Photo(query.value(1).toString().toStdString(),
                                               stoi(query.value(0).toString().toStdString()));
                        this->photos.push_back(newPhoto);
                        cout << "Getting Photos" << endl;

                    }else if(objectToMap == "group"){

                        Group newGroup = Group(query.value(0).toString().toStdString(),
                                               stoi(query.value(1).toString().toStdString()));

                        this->groups.push_back(newGroup);
                        cout << "Getting Groups" << endl;

                    }else if(objectToMap == "contactGroups"){
                        //Attach to the Contact (should be ID of params[0])
                        for(auto& i : contacts){
                            if(i.getContactId() == stoi(params[0])){
                                i.setGroup(stoi(query.value(0).toString().toStdString()));
                                break;
                            }
                        }
                        cout <<"Getting Contact Groups" << endl;

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

                        cout << "Getting Emails" << endl;
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

                        cout << "Getting Phone Numbers" << endl;
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

                        cout << "Getting Addresses" << endl;
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
                    }catch(exception& e){
                        cout << "Failed the mapping " << e.what() << endl;
                    }
                }
                    return true;
            }

        } catch(exception& e){
            cout << "Failed To Execute Query, closing DB: " << e.what() << endl;
            this->db.close();
            return false;
        }
        }
        cout << "Closing DB, Probably bad connection." <<endl;
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
        executeQuery("GET_GROUPS_BY_CONTACT_ID", paramMap, "contactGroups");
    }

}

//This isn't used, but will refresh all the data from the database.
void DatabaseConnection::refreshData(const string& data){
    map<int, string> paramMap;
    if(data == "contacts"){
        this->contacts.clear();
        executeQuery("GET_CONTACTS", paramMap, "contact");
        populateContactData();
    }else if(data == "categories"){
        this->categories.clear();
        executeQuery("GET_CATEGORIES", paramMap, "category");
    }else if(data == "groups"){
        this->groups.clear();
        executeQuery("GET_GROUPS", paramMap, "groups");
    }

    populateContactData();

}

bool DatabaseConnection::deleteContact(int& id){

    for(std::vector<Contact>::iterator it = this->contacts.begin(); it != this->contacts.end(); ++it) {
        if((*it).getContactId() == id){
            this->contacts.erase(it);
            return true;
        }
    }

    return false;
}

void DatabaseConnection::addContact(map<int, string>& data){
    map<int, string> paramMap;
    paramMap[0] = data[0];
    paramMap[1] = data[1];
    executeQuery("GET_CONTACT_ID_BY_FIRST_LAST_NAME", paramMap, "contact");
}

void DatabaseConnection::addCategory(map<int, string>& data){
    map<int, string> paramMap;
    paramMap[0] = data[0];
    executeQuery("GET_CATEGORY_BY_NAME", paramMap, "category");
}

void DatabaseConnection::addGroup(map<int, string>& data){
    map<int, string> paramMap;
    paramMap[0] = data[0];
    executeQuery("GET_GROUP_BY_NAME", paramMap, "group");
}

Group& DatabaseConnection::getGroupById(int& id){
    for(auto& i : this->groups){
        if(i.getGroupId() == id){
            return i;
        }
    }
}

Category& DatabaseConnection::getCategoryById(int& id){
    for(auto& i : this->categories){
        if(i.getCategoryId() == id){
            return i;
        }
    }
}

Photo& DatabaseConnection::getPhotoById(int& id){
    for(auto& i : this->photos){
        if(i.getPhotoId() == id){
            return i;
        }
    }
}

DatabaseConnection::~DatabaseConnection(){
    this->db.close();
}

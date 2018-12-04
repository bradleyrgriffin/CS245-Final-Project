#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databaseconnection.h"
#include <QInputDialog>
#include <QLineEdit>
#include <iostream>
#include <QDir>
#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QtDebug>
#include "User.h"
#include <contact.h>
#include <string>
#include <map>
#include "commonutils.h"
#include <QTableWidgetItem>
#include <QModelIndex>
#include <QSortFilterProxyModel>
using namespace std;

/*------------------------LOGIN WINDOW-------------------------*/
bool loginAuthentication(MainWindow * thisPtr){
    QDialog dialog(thisPtr);
    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);
    // Add some text above the fields
    form.addRow(new QLabel("Enter Your Credentials:"));
    // Add the lineEdits with their respective labels
    QList<QLineEdit *> fields;
    QLineEdit *lineEdit = new QLineEdit(&dialog);
    QString label = QString("User:").arg(1);
    form.addRow(label, lineEdit);
    fields << lineEdit;
    lineEdit = new QLineEdit(&dialog);
    lineEdit->setEchoMode(QLineEdit::Password);
    label = QString("Password:").arg(2);
    form.addRow(label, lineEdit);
    fields << lineEdit;
    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    string username;
    string password;
    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        username = fields[0]->text().toStdString();
        password = fields[1]->text().toStdString();}
    User user = User(username, password);
    cout << (user.verifyLogin() ? "Successful Login":"Failed Login") << endl;
    return (user.verifyLogin() ? false : true);
}
/*-------------------DATA MANAGEMENT--------------------*/
void MainWindow::loadData(){
    map<int, string> paramMap;
    this->data.executeQuery("GET_CONTACTS", paramMap, "contact");
    this->data.executeQuery("GET_GROUPS", paramMap, "group");
    this->data.executeQuery("GET_CATEGORIES", paramMap, "category");
    this->data.executeQuery("GET_PHOTOS", paramMap, "photo");
}

/*-------------------MAIN PROGRAM-------------------*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Initial Login Prompt, code is above.
    //It uses a QtDialog box and get the username/password and compares the password
    //hashes to confirm login, exits if incorrect login.
    try{
        int i = 0;
        while(loginAuthentication(this)){
            if(i == 2){
                exit(1);
            }
            i++;
        }
    }catch (exception& e){
        cout << "Error Logging In " << e.what() << endl;
        exit(1);
    }
    //This gets all the data from the database, and maps it to C++ objects.
    //All the data we need is stored in this->data property.
    try {
        loadData();
    } catch (exception& e) {
         cout << "Error loading data " << e.what() << endl;
    }
    try{
        this->data.populateContactData();
    } catch (exception& e) {
         cout << "Error populating contact data " << e.what() << endl;
    }

    if(this->data.getContacts().size() == 0 || this->data.getCategories().size() == 0 || this->data.getGroups().size() == 0 || this->data.getPhotos().size() == 0){
        cout << "Failed to Load all the data, probably due to a network issue, timeout requests, or server speed. Will exit program, please reboot and try again" << endl;
        exit(1);
    }

    //Loads User Interface
    try {

        ui->setupUi(this);

        // Set Up Table View
        model = new ContactTableModel(this);
        model->updateContacts(this->data.getContacts());
        ui->searchContactTable->setModel(model);
        ui->searchContactTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        ui->searchContactTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->searchContactTable->resizeColumnsToContents();

        //Set Up Phone ListView
        //Temporary data
        vector<Phone> tempPhoneList = vector<Phone>();
        phoneListModel = new PhoneNumberListView(tempPhoneList);
        ui->phoneList->setModel(phoneListModel);

        //Set Up Address ListView
        //Temporary data
        vector<Address> tempAddressList = vector<Address>();
        addressListModel = new AddresListView(tempAddressList);
        ui->addressList->setModel(addressListModel);

        //Set Up Email ListView
        //Temporary data
        vector<Email> tempEmailList = vector<Email>();
        emailListModel = new EmailListView(tempEmailList);
        ui->emailList->setModel(emailListModel);

        //Set Up Email ListView
        //Temporary data
        vector<Group> tempGroupList = vector<Group>();
        groupListModel = new GroupListView(tempGroupList);
        ui->groupList->setModel(groupListModel);


    } catch (exception& e) {
        cout << "Failed to Create GUI Or Model, exiting..." << e.what() << endl;
        exit(1);
    }



}


//--------------------------------Menu Exit-----------------------------//
void MainWindow::on_actionExit_triggered()
{
    exit(1);
}
/*------------------------------BUTTONS----------------------------------*/
void MainWindow::on_addContactButton_clicked()
{

    vector<string> addcontactinformation;
    addcontactinformation.push_back("First Name");
    addcontactinformation.push_back("Last Name");
    addcontactinformation.push_back("Photo");


    map<string, string> returnMap;

    CommonUtils utils = CommonUtils();
    returnMap = utils.dialogPrompt(this, addcontactinformation);
    utils.toggleContactIdButtons(this);

    if(utils.validateFields(returnMap, this)){
        map<int, string> paramMap;
        int increment = 0;
        for(auto i : returnMap){
            cout << i.first << " is: " << i.second << endl;
            paramMap[increment] = i.second;
            increment++;
        }

        this->data.executeQuery("INSERT_CONTACT", paramMap, "insert");
        this->data.addContact(paramMap);


        this->model->addContact(this->data.getContacts()[(this->data.getContacts().size() - 1)]);
        this->ui->contactId->setText("");
    }
    utils.toggleContactIdButtons(this);


}
void MainWindow::on_addCategoryButton_clicked()
{
    vector<string> addcategoryinformation;
    addcategoryinformation.push_back("Category Name");

    map<string, string> returnMap;

    CommonUtils utils = CommonUtils();
    returnMap = utils.dialogPrompt(this, addcategoryinformation);
    utils.toggleContactIdButtons(this);

    if(utils.validateFields(returnMap, this) && utils.checkDuplicateNames(this, returnMap["Category Name"],"category")){
        map<int, string> paramMap;
        for(auto i : returnMap){
            cout << i.first << " is: " << i.second << endl;
            paramMap[0] = i.second;
        }

        this->data.executeQuery("INSERT_CATEGORY", paramMap, "insert");
        this->data.addCategory(paramMap);
    }

}
void MainWindow::on_addGroupButton_clicked()
{
    vector<string> addgroupinformation;
    addgroupinformation.push_back("Group Name");

    map<string, string> returnMap;

    CommonUtils utils = CommonUtils();
    returnMap = utils.dialogPrompt(this, addgroupinformation);
    utils.toggleContactIdButtons(this);

    if(utils.validateFields(returnMap, this) && utils.checkDuplicateNames(this, returnMap["Group Name"],"groups")){
        map<int, string> paramMap;

        for(auto i : returnMap){
            cout << i.first << " is: " << i.second << endl;
            paramMap[0] = i.second;
        }
        this->data.executeQuery("INSERT_GROUP", paramMap, "insert");
        this->data.addGroup(paramMap);
    }
}
void MainWindow::on_searchButton_clicked()
{
    this->model->resetTable();
    this->model->customSearch(this->ui->searchBar->text().toStdString());

    CommonUtils utils;
    utils.toggleContactIdButtons(this);
}
MainWindow::~MainWindow()
{
    delete model;
    delete ui;

}

void MainWindow::on_deleteContactButton_clicked()
{

    int contactId = stoi(ui->contactId->text().toStdString());
    map<int, string> paramMap;
    paramMap[0] = to_string(contactId);

    CommonUtils utils = CommonUtils();



    this->data.executeQuery("DELETE_ALL_CONTACT_EMAILS", paramMap, "delete");
    this->data.executeQuery("DELETE_ALL_CONTACT_PHONE", paramMap, "delete");
    this->data.executeQuery("DELETE_ALL_CONTACT_ADDRESS", paramMap, "delete");
    this->data.executeQuery("DELETE_ALL_CONTACT_GROUPS", paramMap, "delete");
    this->data.executeQuery("DELETE_CONTACT", paramMap, "delete");
    this->data.deleteContact(contactId);
    this->model->deleteContact(contactId);
    this->ui->contactId->setText("");
    utils.toggleContactIdButtons(this);


}

void MainWindow::on_updateContactButton_clicked()
{

    int contactId = stoi(ui->contactId->text().toStdString());
    string fName = ui->firstName->text().toStdString();
    string lName = ui->lastName->text().toStdString();
    map<string, string> checkMap;
    checkMap["first"] = fName;
    checkMap["last"] = lName;

    CommonUtils utils;
    utils.toggleContactIdButtons(this);

    if(utils.validateFields(checkMap, this)){

        map<int, string> paramMap;
        paramMap[0] = fName;
        paramMap[1] = lName;
        paramMap[2] = to_string(contactId);

        this->data.executeQuery("UPDATE_CONTACT", paramMap, "update");

        for(auto& i : this->data.getContacts()){
            if(i.getContactId() == contactId){
                i.setFName(fName);
                i.setLName(lName);
                utils.toggleContactIdButtons(this);
                this->model->updateContact(i);
                break;
            }
        }
    }
    utils.toggleContactIdButtons(this);

}

void MainWindow::on_addAddressButton_clicked()
{
    int contactId = stoi(ui->contactId->text().toStdString());
    vector<string> addContactAddress;
    addContactAddress.push_back("Street");
    addContactAddress.push_back("City");
    addContactAddress.push_back("State");
    addContactAddress.push_back("ZIP");
    addContactAddress.push_back("Category");

    map<string, string> returnMap;

    CommonUtils utils = CommonUtils();
    returnMap = utils.dialogPrompt(this, addContactAddress);
    utils.toggleContactIdButtons(this);

    if(utils.validateFields(returnMap, this)){
        map<int, string> paramMap;
        paramMap[0] = returnMap["Street"];
        paramMap[1] = returnMap["City"];
        paramMap[2] = returnMap["State"];
        paramMap[3] = returnMap["ZIP"];
        paramMap[4] = to_string(contactId);
        paramMap[5] = utils.substringStr(returnMap["Category"]);

        this->data.executeQuery("INSERT_CONTACT_ADDRESS", paramMap, "insert");

        paramMap.clear(); //Empty Out previous Values

        paramMap[0] = to_string(contactId); //Contact Id
        paramMap[1] = returnMap["Street"];
        paramMap[2] = returnMap["City"];
        paramMap[3] = returnMap["State"];
        paramMap[4] = utils.substringStr(returnMap["Category"]);
        this->data.executeQuery("GET_CONTACT_ADDRESS_ID_BY_ADDRESS", paramMap, "address");
    }
    utils.toggleContactIdButtons(this);
}

void MainWindow::on_deleteAddressButton_clicked()
{
    int contactId = stoi(ui->contactId->text().toStdString());
    CommonUtils utils;
    map<int, string> paramMap;
    paramMap[0] = to_string(contactId);
    this->data.executeQuery("DELETE_ALL_CONTACT_ADDRESS", paramMap, "delete");
    for(auto& i : this->data.getContacts()){
        if(i.getContactId() == contactId){
            i.clearAddresses();
            break;
        }
    }
    utils.toggleContactIdButtons(this);
}

void MainWindow::on_deletePhoneButton_clicked()
{
    int contactId = stoi(ui->contactId->text().toStdString());

    CommonUtils utils;

    map<int, string> paramMap;
    paramMap[0] = to_string(contactId);
    this->data.executeQuery("DELETE_ALL_CONTACT_PHONE", paramMap, "delete");
    for(auto& i : this->data.getContacts()){
        if(i.getContactId() == contactId){
            i.clearPhones();
            break;
        }
    }
    utils.toggleContactIdButtons(this);
}

void MainWindow::on_deleteEmailButton_clicked()
{
    int contactId = stoi(ui->contactId->text().toStdString());

    CommonUtils utils;
    map<int, string> paramMap;
    paramMap[0] = to_string(contactId);
    this->data.executeQuery("DELETE_ALL_CONTACT_EMAILS", paramMap, "delete");
    for(auto& i : this->data.getContacts()){
        if(i.getContactId() == contactId){
            i.clearEmails();
            utils.toggleContactIdButtons(this);
            break;
        }
    }
    utils.toggleContactIdButtons(this);
}

void MainWindow::on_deleteGroupButton_clicked()
{
    int contactId = stoi(ui->contactId->text().toStdString());

    CommonUtils utils;
    map<int, string> paramMap;
    paramMap[0] = to_string(contactId);
    this->data.executeQuery("DELETE_ALL_CONTACT_GROUPS", paramMap, "delete");
    for(auto& i : this->data.getContacts()){
        if(i.getContactId() == contactId){
            i.clearGroups();
            utils.toggleContactIdButtons(this);
            break;
        }
    }
    utils.toggleContactIdButtons(this);
}

void MainWindow::on_addPhoneButton_clicked()
{
    int contactId = stoi(ui->contactId->text().toStdString());
    vector<string> addContactAddress;
    addContactAddress.push_back("Phone");
    addContactAddress.push_back("Category");

    map<string, string> returnMap;

    CommonUtils utils = CommonUtils();
    returnMap = utils.dialogPrompt(this, addContactAddress);
    utils.toggleContactIdButtons(this);

    if(utils.validateFields(returnMap, this)){
        map<int, string> paramMap;
        paramMap[0] = returnMap["Phone"];
        paramMap[1] = to_string(contactId);
        paramMap[2] = utils.substringStr(returnMap["Category"]);

        this->data.executeQuery("INSERT_CONTACT_PHONE", paramMap, "insert");
        paramMap[0] = paramMap[1];
        paramMap[1] = returnMap["Phone"];
        this->data.executeQuery("GET_CONTACT_PHONE_ID_BY_PHONE", paramMap, "phone");
    }
    utils.toggleContactIdButtons(this);
}

void MainWindow::on_addEmailButton_clicked()
{
    int contactId = stoi(ui->contactId->text().toStdString());
    vector<string> addContactAddress;
    addContactAddress.push_back("Email");
    addContactAddress.push_back("Category");

    map<string, string> returnMap;

    CommonUtils utils = CommonUtils();
    returnMap = utils.dialogPrompt(this, addContactAddress);
    utils.toggleContactIdButtons(this);

    if(utils.validateFields(returnMap, this)){
        map<int, string> paramMap;
        paramMap[0] = to_string(contactId);
        paramMap[1] = returnMap["Email"];
        paramMap[2] = utils.substringStr(returnMap["Category"]);

        this->data.executeQuery("INSERT_CONTACT_EMAIL", paramMap, "insert");
        this->data.executeQuery("GET_CONTACT_EMAIL_ID_BY_EMAIL", paramMap, "email");
    }
    utils.toggleContactIdButtons(this);
}

void MainWindow::on_addGroupButton_2_clicked()
{
    int contactId = stoi(ui->contactId->text().toStdString());
    vector<string> addContactAddress;
    addContactAddress.push_back("Group");

    map<string, string> returnMap;

    CommonUtils utils = CommonUtils();
    returnMap = utils.dialogPrompt(this, addContactAddress);
    utils.toggleContactIdButtons(this);

    if(utils.validateFields(returnMap, this)){
        map<int, string> paramMap;
        paramMap[0] = to_string(contactId); //Contact Id
        paramMap[1] = utils.substringStr(returnMap["Group"]); //Group Id

        this->data.executeQuery("INSERT_CONTACT_GROUP", paramMap, "insert");
        this->data.executeQuery("GET_GROUP_BY_ID", paramMap, "contactGroups");
    }
    utils.toggleContactIdButtons(this);
}

void MainWindow::on_searchContactTable_pressed(const QModelIndex &index)
{
    int id = this->model->getContactIdByIndex(index);
    this->ui->contactId->setText(QString::fromStdString((to_string(id) == "-1" ? "" : to_string(id))));

    CommonUtils utils = CommonUtils();
    utils.toggleContactIdButtons(this);

}

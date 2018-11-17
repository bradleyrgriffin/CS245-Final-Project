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
#include <string>
#include <map>
#include "commonutils.h"
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
    label = QString("Password:").arg(2);
    form.addRow(label, lineEdit);
    fields << lineEdit;
    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    string username;
    string password;
    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        username = fields[0]->text().toStdString();
        password = fields[1]->text().toStdString();
    }
    User user = User(username, password);
            cout << (user.verifyLogin() ? "Successful Login":"Failed Login") << endl;
            if(!user.verifyLogin()){
                return true;
            }else{
                return false;
            }
}
/*-------------------DATA MANAGEMENT--------------------*/
void MainWindow::loadData(){
    map<int, string> paramMap;
    this->data.executeQuery("GET_CONTACTS", paramMap, "contact");
    //this->data.executeQuery("GET_GROUPS", paramMap, "contact");
    //this->data.executeQuery("GET_CATEGORIES", paramMap, "contact");
}
string MainWindow::GetCategoryNameById(int& id){
    for(auto i : this->data.getCategories()){
        if(i.getCategoryId() == id){
            return i.getCategoryName();
        }
    }
    return "N/A";
}
string MainWindow::GetGroupNameById(int& id){
    for(auto i : this->data.getGroups()){
        if(i.getGroupId() == id){
            return i.getGroupName();
        }
    }
    return "N/A";
}

/*-------------------MAIN PROGRAM-------------------*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Initial Login Prompt, code is above.
    //It uses a QtDialog box and get the username/password and compares the password
    //hashes to confirm login, exits if incorrect login.
    while(loginAuthentication(this));

    //This gets all the data from the database, and maps it to C++ objects.
    //All the data we need is stored in this->data property.
    loadData();

    //Loads User Interface
    ui->setupUi(this);

    //Lazy loading
    this->data.populateContactData();

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
    addcontactinformation.push_back("Photo ID");


    map<string, string> returnMap;

    CommonUtils utils = CommonUtils();
    returnMap = utils.dialogPrompt(this, addcontactinformation);

    map<int, string> paramMap;
    int increment = 0;
    for(auto i : returnMap){
        cout << i.first << " is: " << i.second << endl;
        paramMap[increment] = i.second;
        increment++;
    }
    this->data.executeQuery("INSERT_CONTACT", paramMap, "insert");
}
void MainWindow::on_addCategoryButton_clicked()
{
    vector<string> addcategoryinformation;
    addcategoryinformation.push_back("Category Name");

    map<string, string> returnMap;

    CommonUtils utils = CommonUtils();
    returnMap = utils.dialogPrompt(this, addcategoryinformation);

    map<int, string> paramMap;
    for(auto i : returnMap){
        cout << i.first << " is: " << i.second << endl;
        paramMap[0] = i.second;
    }

    this->data.executeQuery("INSERT_CATEGORY", paramMap, "insert");

}
void MainWindow::on_addGroupButton_clicked()
{
    vector<string> addgroupinformation;
    addgroupinformation.push_back("Group Name");

    map<string, string> returnMap;

    CommonUtils utils = CommonUtils();
    returnMap = utils.dialogPrompt(this, addgroupinformation);

    map<int, string> paramMap;

    for(auto i : returnMap){
        cout << i.first << " is: " << i.second << endl;
        paramMap[0] = i.second;
    }
    this->data.executeQuery("INSERT_GROUP", paramMap, "insert");
}
void MainWindow::on_searchButton_clicked()
{
    //This should strip the search term of special characters,and execute a query to Select from the view that joins
    //all the data together, concatenating email, first name, last name, and address, and stripping special characters,
    //And also uppercasing everything.

    for( auto i : this->data.getContacts()){
        cout << "ID/Name: " << i.getContactId() << "/" << i.getFirstName() << " " << i.getLastName() << endl;// <<
                //"Primary Email: " << i.getEmails()[0].getEmailName() << endl <<
               // "Primary Phone: " << i.getPhoneNumbers()[0].getPhoneNumber() << endl <<
               // "Primary Street Address: " << i.getAddresses()[0].getAddress() << endl;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

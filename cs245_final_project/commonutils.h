#ifndef COMMONUTILS_H
#define COMMONUTILS_H

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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include "contact.h"

class CommonUtils
{
public:
    CommonUtils();

    map<string, string> dialogPrompt(MainWindow * thisPtr,vector<string> fieldNames);

    bool validateFields(map<string, string>& data, MainWindow* thing);

    //Just pass in a the button to disable/enable
    void disableBtn(QPushButton* btn);
    void enableBtn(QPushButton* btn);


    string substringStr(const string& s);

    //Disable/Enable buttons related to ContactID Field
    //Pass in the window so we can alter the buttons
    void toggleContactIdButtons(MainWindow * thing);

    //Loads User Data to the Update Panel
    void displayData(MainWindow* thing);

    //Displays the User's profile picture
    void displayProfilePicture(MainWindow* thing, const string& path);

    //Check dublicate category/group names
    bool checkDuplicateNames(MainWindow* thing, const string& nme, const string& type);

private:


};

#endif // COMMONUTILS_H

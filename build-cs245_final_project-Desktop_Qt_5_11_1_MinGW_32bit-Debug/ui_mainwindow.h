/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QWidget *centralWidget;
    QPushButton *addCategoryButton;
    QPushButton *addContactButton;
    QPushButton *addGroupButton;
    QTableView *searchContactTable;
    QLineEdit *searchBar;
    QPushButton *searchButton;
    QLabel *firstNameLabel;
    QLabel *lastNameLabel;
    QLabel *contactIdLabel;
    QLineEdit *firstName;
    QLineEdit *lastName;
    QLineEdit *contactId;
    QListView *addressList;
    QLabel *addressLabel;
    QListView *phoneList;
    QLabel *phoneLabel;
    QListView *emailList;
    QLabel *emailLabel;
    QListView *groupList;
    QLabel *groupLabel;
    QPushButton *updateContactButton;
    QPushButton *deleteContactButton;
    QPushButton *addAddressButton;
    QPushButton *addPhoneButton;
    QPushButton *addEmailButton;
    QPushButton *addGroupButton_2;
    QPushButton *deleteAddressButton;
    QPushButton *deletePhoneButton;
    QPushButton *deleteEmailButton;
    QPushButton *deleteGroupButton;
    QMenuBar *menuBar;
    QMenu *menuSearch_Contacts;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1100, 688);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        addCategoryButton = new QPushButton(centralWidget);
        addCategoryButton->setObjectName(QStringLiteral("addCategoryButton"));
        addCategoryButton->setGeometry(QRect(280, 560, 93, 28));
        addContactButton = new QPushButton(centralWidget);
        addContactButton->setObjectName(QStringLiteral("addContactButton"));
        addContactButton->setGeometry(QRect(10, 560, 93, 28));
        addGroupButton = new QPushButton(centralWidget);
        addGroupButton->setObjectName(QStringLiteral("addGroupButton"));
        addGroupButton->setGeometry(QRect(570, 560, 93, 28));
        searchContactTable = new QTableView(centralWidget);
        searchContactTable->setObjectName(QStringLiteral("searchContactTable"));
        searchContactTable->setGeometry(QRect(10, 80, 661, 461));
        searchBar = new QLineEdit(centralWidget);
        searchBar->setObjectName(QStringLiteral("searchBar"));
        searchBar->setGeometry(QRect(20, 20, 431, 22));
        searchButton = new QPushButton(centralWidget);
        searchButton->setObjectName(QStringLiteral("searchButton"));
        searchButton->setGeometry(QRect(560, 20, 93, 28));
        firstNameLabel = new QLabel(centralWidget);
        firstNameLabel->setObjectName(QStringLiteral("firstNameLabel"));
        firstNameLabel->setGeometry(QRect(720, 10, 71, 16));
        lastNameLabel = new QLabel(centralWidget);
        lastNameLabel->setObjectName(QStringLiteral("lastNameLabel"));
        lastNameLabel->setGeometry(QRect(720, 40, 71, 16));
        contactIdLabel = new QLabel(centralWidget);
        contactIdLabel->setObjectName(QStringLiteral("contactIdLabel"));
        contactIdLabel->setGeometry(QRect(930, 10, 21, 16));
        firstName = new QLineEdit(centralWidget);
        firstName->setObjectName(QStringLiteral("firstName"));
        firstName->setEnabled(true);
        firstName->setGeometry(QRect(810, 10, 113, 22));
        lastName = new QLineEdit(centralWidget);
        lastName->setObjectName(QStringLiteral("lastName"));
        lastName->setEnabled(true);
        lastName->setGeometry(QRect(810, 40, 113, 22));
        contactId = new QLineEdit(centralWidget);
        contactId->setObjectName(QStringLiteral("contactId"));
        contactId->setGeometry(QRect(950, 10, 113, 22));
        contactId->setReadOnly(true);
        addressList = new QListView(centralWidget);
        addressList->setObjectName(QStringLiteral("addressList"));
        addressList->setEnabled(false);
        addressList->setGeometry(QRect(810, 70, 256, 91));
        addressList->setProperty("isWrapping", QVariant(false));
        addressLabel = new QLabel(centralWidget);
        addressLabel->setObjectName(QStringLiteral("addressLabel"));
        addressLabel->setGeometry(QRect(720, 70, 81, 16));
        phoneList = new QListView(centralWidget);
        phoneList->setObjectName(QStringLiteral("phoneList"));
        phoneList->setEnabled(false);
        phoneList->setGeometry(QRect(810, 180, 256, 101));
        phoneLabel = new QLabel(centralWidget);
        phoneLabel->setObjectName(QStringLiteral("phoneLabel"));
        phoneLabel->setGeometry(QRect(720, 180, 55, 16));
        emailList = new QListView(centralWidget);
        emailList->setObjectName(QStringLiteral("emailList"));
        emailList->setEnabled(false);
        emailList->setGeometry(QRect(810, 300, 256, 111));
        emailLabel = new QLabel(centralWidget);
        emailLabel->setObjectName(QStringLiteral("emailLabel"));
        emailLabel->setGeometry(QRect(720, 300, 55, 16));
        groupList = new QListView(centralWidget);
        groupList->setObjectName(QStringLiteral("groupList"));
        groupList->setEnabled(false);
        groupList->setGeometry(QRect(810, 430, 256, 111));
        groupLabel = new QLabel(centralWidget);
        groupLabel->setObjectName(QStringLiteral("groupLabel"));
        groupLabel->setGeometry(QRect(720, 440, 55, 16));
        updateContactButton = new QPushButton(centralWidget);
        updateContactButton->setObjectName(QStringLiteral("updateContactButton"));
        updateContactButton->setEnabled(false);
        updateContactButton->setGeometry(QRect(860, 550, 161, 28));
        deleteContactButton = new QPushButton(centralWidget);
        deleteContactButton->setObjectName(QStringLiteral("deleteContactButton"));
        deleteContactButton->setEnabled(false);
        deleteContactButton->setGeometry(QRect(890, 580, 111, 28));
        addAddressButton = new QPushButton(centralWidget);
        addAddressButton->setObjectName(QStringLiteral("addAddressButton"));
        addAddressButton->setEnabled(false);
        addAddressButton->setGeometry(QRect(720, 90, 61, 21));
        addPhoneButton = new QPushButton(centralWidget);
        addPhoneButton->setObjectName(QStringLiteral("addPhoneButton"));
        addPhoneButton->setEnabled(false);
        addPhoneButton->setGeometry(QRect(720, 200, 61, 21));
        addEmailButton = new QPushButton(centralWidget);
        addEmailButton->setObjectName(QStringLiteral("addEmailButton"));
        addEmailButton->setEnabled(false);
        addEmailButton->setGeometry(QRect(720, 320, 61, 21));
        addGroupButton_2 = new QPushButton(centralWidget);
        addGroupButton_2->setObjectName(QStringLiteral("addGroupButton_2"));
        addGroupButton_2->setEnabled(false);
        addGroupButton_2->setGeometry(QRect(720, 460, 61, 21));
        deleteAddressButton = new QPushButton(centralWidget);
        deleteAddressButton->setObjectName(QStringLiteral("deleteAddressButton"));
        deleteAddressButton->setEnabled(false);
        deleteAddressButton->setGeometry(QRect(720, 120, 61, 21));
        deletePhoneButton = new QPushButton(centralWidget);
        deletePhoneButton->setObjectName(QStringLiteral("deletePhoneButton"));
        deletePhoneButton->setEnabled(false);
        deletePhoneButton->setGeometry(QRect(720, 230, 61, 21));
        deleteEmailButton = new QPushButton(centralWidget);
        deleteEmailButton->setObjectName(QStringLiteral("deleteEmailButton"));
        deleteEmailButton->setEnabled(false);
        deleteEmailButton->setGeometry(QRect(720, 350, 61, 21));
        deleteGroupButton = new QPushButton(centralWidget);
        deleteGroupButton->setObjectName(QStringLiteral("deleteGroupButton"));
        deleteGroupButton->setEnabled(false);
        deleteGroupButton->setGeometry(QRect(720, 490, 61, 21));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1100, 26));
        menuSearch_Contacts = new QMenu(menuBar);
        menuSearch_Contacts->setObjectName(QStringLiteral("menuSearch_Contacts"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuSearch_Contacts->menuAction());
        menuSearch_Contacts->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
#ifndef QT_NO_SHORTCUT
        actionExit->setShortcut(QApplication::translate("MainWindow", "Esc", nullptr));
#endif // QT_NO_SHORTCUT
        addCategoryButton->setText(QApplication::translate("MainWindow", "Add Category", nullptr));
        addContactButton->setText(QApplication::translate("MainWindow", "Add Contact", nullptr));
        addGroupButton->setText(QApplication::translate("MainWindow", "Add Group", nullptr));
#ifndef QT_NO_TOOLTIP
        searchBar->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        searchBar->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        searchBar->setText(QApplication::translate("MainWindow", "Enter a Contact ID Here to Load data over there ->...", nullptr));
        searchButton->setText(QApplication::translate("MainWindow", "Search", nullptr));
        firstNameLabel->setText(QApplication::translate("MainWindow", "First Name:", nullptr));
        lastNameLabel->setText(QApplication::translate("MainWindow", "Last Name:", nullptr));
        contactIdLabel->setText(QApplication::translate("MainWindow", "ID:", nullptr));
        addressLabel->setText(QApplication::translate("MainWindow", "Addresses:", nullptr));
        phoneLabel->setText(QApplication::translate("MainWindow", "Phones:", nullptr));
        emailLabel->setText(QApplication::translate("MainWindow", "Emails:", nullptr));
        groupLabel->setText(QApplication::translate("MainWindow", "Groups:", nullptr));
        updateContactButton->setText(QApplication::translate("MainWindow", "Update First/Last Name", nullptr));
        deleteContactButton->setText(QApplication::translate("MainWindow", "Delete Contact", nullptr));
        addAddressButton->setText(QApplication::translate("MainWindow", "Add", nullptr));
        addPhoneButton->setText(QApplication::translate("MainWindow", "Add", nullptr));
        addEmailButton->setText(QApplication::translate("MainWindow", "Add", nullptr));
        addGroupButton_2->setText(QApplication::translate("MainWindow", "Add", nullptr));
        deleteAddressButton->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        deletePhoneButton->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        deleteEmailButton->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        deleteGroupButton->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        menuSearch_Contacts->setTitle(QApplication::translate("MainWindow", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

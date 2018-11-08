#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QLineEdit>
#include <iostream>
#include <QDir>
#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QtDebug>
#include "User.h"

using namespace std;

//void loginAuthentication(const string & username, const string & password){

//        User user = User(username, password);
//        cout << (user.verifyLogin() ? "Successful Login":"Failed Login") << endl;
//        if(!user.verifyLogin()){
//            exit(1);
//        }
//}

void loginAuthentication(MainWindow * thisPtr){
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
                exit(1);
            }

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    loginAuthentication(this);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

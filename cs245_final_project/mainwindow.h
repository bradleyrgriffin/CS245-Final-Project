#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <databaseconnection.h>
#include <string>
#include "contacttablemodel.h"
#include "phonenumberlistview.h"
#include "phone.h"
#include "addreslistview.h"
#include "emaillistview.h"
#include "grouplistview.h"
#include <QListView>
#include <QComboBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadData();

public slots:
    void on_actionExit_triggered();

    void on_addContactButton_clicked();

    void on_addCategoryButton_clicked();

    void on_addGroupButton_clicked();

    void on_searchButton_clicked();


    void on_deleteContactButton_clicked();

    void on_updateContactButton_clicked();

    void on_addAddressButton_clicked();

    void on_deleteAddressButton_clicked();

    void on_deletePhoneButton_clicked();

    void on_deleteEmailButton_clicked();

    void on_deleteGroupButton_clicked();

    void on_addPhoneButton_clicked();

    void on_addEmailButton_clicked();

    void on_addGroupButton_2_clicked();

public:
    Ui::MainWindow *ui;
    ContactTableModel *model;
    DatabaseConnection data = DatabaseConnection();

    PhoneNumberListView* phoneListModel;
    AddresListView* addressListModel;
    EmailListView* emailListModel;
    GroupListView* groupListModel;

//    QListView* groupView;
//    QListView* categoryView;
//    QListView* photoView;

//    QComboBox* groupCombo;
//    QComboBox* categoryCombo;
//    QComboBox* photoCombo;

private slots:
    void on_searchContactTable_pressed(const QModelIndex &index);
};

#endif // MAINWINDOW_H

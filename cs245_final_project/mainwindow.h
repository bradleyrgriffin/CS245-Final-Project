#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <databaseconnection.h>
#include <string>

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
    std::string GetCategoryNameById(int& id);
    std::string GetGroupNameById(int& id);

private slots:
    void on_actionExit_triggered();

    void on_addContactButton_clicked();

    void on_addCategoryButton_clicked();

    void on_addGroupButton_clicked();

    void on_searchButton_clicked();


    void on_deleteContactButton_clicked();

private:
    Ui::MainWindow *ui;
    DatabaseConnection data = DatabaseConnection();
};

#endif // MAINWINDOW_H

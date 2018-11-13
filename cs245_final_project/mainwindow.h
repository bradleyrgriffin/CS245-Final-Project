#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_addContactButton_clicked();

    void on_addCategoryButton_clicked();

    void on_addGroupButton_clicked();

    void on_searchButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

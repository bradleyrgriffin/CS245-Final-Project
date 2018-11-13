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
#include <QtWidgets/QLineEdit>
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
    QMenuBar *menuBar;
    QMenu *menuSearch_Contacts;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(708, 501);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        addCategoryButton = new QPushButton(centralWidget);
        addCategoryButton->setObjectName(QStringLiteral("addCategoryButton"));
        addCategoryButton->setGeometry(QRect(420, 390, 93, 28));
        addContactButton = new QPushButton(centralWidget);
        addContactButton->setObjectName(QStringLiteral("addContactButton"));
        addContactButton->setGeometry(QRect(310, 390, 93, 28));
        addGroupButton = new QPushButton(centralWidget);
        addGroupButton->setObjectName(QStringLiteral("addGroupButton"));
        addGroupButton->setGeometry(QRect(530, 390, 93, 28));
        searchContactTable = new QTableView(centralWidget);
        searchContactTable->setObjectName(QStringLiteral("searchContactTable"));
        searchContactTable->setGeometry(QRect(20, 10, 661, 291));
        searchBar = new QLineEdit(centralWidget);
        searchBar->setObjectName(QStringLiteral("searchBar"));
        searchBar->setGeometry(QRect(20, 320, 431, 22));
        searchButton = new QPushButton(centralWidget);
        searchButton->setObjectName(QStringLiteral("searchButton"));
        searchButton->setGeometry(QRect(530, 320, 93, 28));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 708, 26));
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
        searchBar->setText(QApplication::translate("MainWindow", "Enter Your Search text Here...", nullptr));
        searchButton->setText(QApplication::translate("MainWindow", "Search", nullptr));
        menuSearch_Contacts->setTitle(QApplication::translate("MainWindow", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

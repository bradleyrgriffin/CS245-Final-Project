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

class CommonUtils
{
public:
    CommonUtils();

    map<string, string> dialogPrompt(MainWindow * thisPtr,vector<string> fieldNames);

private:


};

#endif // COMMONUTILS_H

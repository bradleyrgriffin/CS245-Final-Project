#-------------------------------------------------
#
# Project created by QtCreator 2018-10-16T09:33:24
#
#-------------------------------------------------

QT       += core gui widgets sql

TARGET = cs245_final_project
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Password.cpp \
    User.cpp \
    properties.cpp \
    databaseconnection.cpp \
    commonutils.cpp \
    contact.cpp \
    email.cpp \
    address.cpp \
    phone.cpp \
    photo.cpp \
    group.cpp \
    category.cpp \
    contacttablemodel.cpp \
    phonenumberlistview.cpp

HEADERS += \
        mainwindow.h \
    Password.h \
    User.h \
    searchcontact.h \
    properties.h \
    databaseconnection.h \
    commonutils.h \
    contact.h \
    email.h \
    address.h \
    phone.h \
    photo.h \
    group.h \
    category.h \
    contacttablemodel.h \
    phonenumberlistview.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    properties.txt \
    photos/photo1.jpg

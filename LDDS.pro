#-------------------------------------------------
#
# Project created by QtCreator 2018-04-14T14:03:15
#
#-------------------------------------------------

QT       += \
            widgets \
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LDDS
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += \
            QT_DEPRECATED_WARNINGS \
           "VERSION=\"\\\"0.1.1\\\"\"" \
           "BDD_VERSION=\"\\\"0.1.1\\\"\""

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        view.cpp \
        dbhandler.cpp \
        dbmanager.cpp \
        tools.cpp \
        mainPage.cpp \
        familyPage.cpp \
        retaillerPage.cpp \
        typeArticlesPage.cpp \
        paymentMethodPage.cpp \
        baseUnitPage.cpp \
        customerPage.cpp \
    articlePage.cpp \
    parameterPage.cpp


HEADERS += \
        view.hpp \
        tools.hpp \
        dbmanager.hpp \
        dbhandler.hpp \
        mainPage.hpp \
        familyPage.hpp \
        retaillerPage.hpp \
        typeArticlesPage.hpp \
        paymentMethodPage.hpp \
        baseUnitPage.hpp \
        customerPage.hpp \
    articlePage.hpp \
    parameterPage.hpp


FORMS +=

CONFIG += mobility
MOBILITY = 

RESOURCES +=


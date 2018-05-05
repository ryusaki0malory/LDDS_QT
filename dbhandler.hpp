#ifndef DBHANDLER_HPP
#define DBHANDLER_HPP

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QString>
#include <QMap>
#include <QStandardItemModel>
#include <QDebug>
#include "dbmanager.hpp"

class DbHandler: public DbManager
{

public:
    DbHandler();
    ~DbHandler();
    QString getPathLogo();
    //family
    bool addFamily(const QString &family);
    void getFamily(QStandardItemModel *modele);
    bool updateFamily(const int &ID, const QString &family);
    bool deleteFamily(const int &ID);

    //retailler
    bool addRetailler(const QString &name, const QString &comment);
    void getRetailler(QStandardItemModel *modele);
    bool updateRetailler(const int &ID, const QString &name, const QString &comment);
    bool deleteRetailler(const int &ID);

    //TypeArticle
    bool addTypeArticle(const QString &name, const double &qte, const int &baseUnit);
    void getTypeArticle(QStandardItemModel *modele);
    bool updateTypeArticle(const int &ID, const QString &name, const double &qte, const int &baseUnit);
    bool deleteTypeArticle(const int &ID);

    //Base unit
    bool addBaseUnit(const QString &name, const double &mult);
    void getBaseUnit(QStandardItemModel *modele);
    void getBaseUnit(QMap <QString, QString> &lst);
    bool updateBaseUnit(const int &ID, const QString &name, const double &mult);
    bool deleteBaseUnit(const int &ID);
private :

};

#endif // DBHANDLER_HPP

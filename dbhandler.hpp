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
#include <QBitArray>
#include "dbmanager.hpp"

class DbHandler: public DbManager
{

public:
    DbHandler();
    ~DbHandler();
    //family
    bool addFamily(const QString &family);
    void getFamily(QStandardItemModel *modele);
    void getFamily(QMap <QString, QString> &lst);
    bool updateFamily(const int &ID, const QString &family);
    bool deleteFamily(const int &ID);

    //retailler
    bool addRetailler(const QString &name, const QString &comment);
    void getRetailler(QStandardItemModel *modele);
    void getRetailler(QMap <QString, QString> &lst);
    bool updateRetailler(const int &ID, const QString &name, const QString &comment);
    bool deleteRetailler(const int &ID);

    //TypeArticle
    bool addTypeArticle(const QString &name, const double &qte, const int &baseUnit);
    void getTypeArticle(QStandardItemModel *modele);
    void getTypeArticle(QMap <QString, QString> &lst);
    bool updateTypeArticle(const int &ID, const QString &name, const double &qte, const int &baseUnit);
    bool deleteTypeArticle(const int &ID);

    //Base unit
    bool addBaseUnit(const QString &name, const double &mult);
    void getBaseUnit(QStandardItemModel *modele);
    void getBaseUnit(QMap <QString, QString> &lst);
    bool updateBaseUnit(const int &ID, const QString &name, const double &mult);
    bool deleteBaseUnit(const int &ID);

    //Base unit
    bool addPaymentMethod(const QString &name);
    void getPaymentMethod(QStandardItemModel *modele);
    bool updatePaymentMethod(const int &ID, const QString &name);
    bool deletePaymentMethod(const int &ID);

    //Article
    bool addArticle(const QString &name, const double &price, const double &qte, const int &family, const int &retailer, const int &type, const QString &comment, const QByteArray &image);
    void getArticle(QStandardItemModel *modele);
    QByteArray getImageArticle(const int &ID_article);
    bool updateArticle(const int &ID, const QString &name, const double &price, const double &qte, const int &family, const int &retailer, const int &type, const QString &comment, const QByteArray &image);
    bool deleteArticle(const int &ID);

    //parameter
    QString const parameterExist(void) const;
    bool addParameter(const QByteArray &image);
    bool updateParameter(const QString &ID_parameter, const QByteArray &image);
    QByteArray const getImageParameter(void) const;

    //Customer
    bool addCustomer(const QString &LastName, const QString &FirstName, const int &IDAccount, const QString &address, const QString &postalCode, const QString &city, const QString &comment, const QString &Phone, const QString &Mail);
    void getCustomer(QStandardItemModel *modele);
    bool updateCustomer(const int &ID, const QString &LastName, const QString &FirstName, const int &IDAccount, const QString &address, const QString &postalCode, const QString &city, const QString &comment, const QString &Phone, const QString &Mail);
    bool deleteCustomer(const int &ID);

private :

};

#endif // DBHANDLER_HPP

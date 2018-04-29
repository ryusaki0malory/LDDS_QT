#ifndef DBMANAGER_HPP
#define DBMANAGER_HPP

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QString>
#include <QStandardItemModel>
#include <QDebug>

class DbManager
{

private:
    QSqlDatabase db;
    void onCreate();

    const QString DATABASE_NAME = "LDDS.db";
    //Table family article
    const QString TABLE_FAMILY = "familyArticles";
    const QString KEY_ID_FAMILY = "IDFamily";
    const QString KEY_NAME_FAMILY = "NameFamily";

public:
    DbManager();
    ~DbManager();
    //family
    bool addFamily(const QString &family);
    void getFamily(QStandardItemModel *modele);
    bool updateFamily(const int &ID, const QString &family);
    bool deleteFamily(const int &ID);

};

#endif // DBMANAGER_HPP

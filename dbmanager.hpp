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
    bool addFamily(const QString &family);
    void getFamily(QStandardItemModel *modele);

};

#endif // DBMANAGER_HPP

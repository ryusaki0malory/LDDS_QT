#include "dbmanager.hpp"

DbManager::DbManager()
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName(DATABASE_NAME);

    if (!this->db.open())
    {
        qWarning() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
        this->onCreate();
    }
}

DbManager::~DbManager()
{
    if (this->db.open())
    {
        this->db.close();
    }
}

void DbManager::onCreate()
{


    //Table family article
    QString CREATE_TABLE_FAMILY = "CREATE TABLE IF NOT EXISTS " + TABLE_FAMILY + " ( " +
                    KEY_ID_FAMILY + " INTEGER PRIMARY KEY AUTOINCREMENT," +
                    KEY_NAME_FAMILY + " TEXT);";
    QSqlQuery queryCreateFamily;
    queryCreateFamily.prepare(CREATE_TABLE_FAMILY);
    if(!queryCreateFamily.exec())
    {
        qWarning() << "familyTable error :" << queryCreateFamily.lastError();
    }

}

void DbManager::getFamily(QStandardItemModel *modele)
{
    QSqlQuery query;
    QString SELECT_FAMILY = "SELECT " + KEY_ID_FAMILY + ","+ KEY_NAME_FAMILY + " FROM " + TABLE_FAMILY;

    if(query.exec(SELECT_FAMILY))
    {
        while (query.next())
        {
            QString ID = query.value(KEY_ID_FAMILY).toString();
            QString NAME = query.value(KEY_NAME_FAMILY).toString();
            modele->setItem(modele->rowCount(),0, new QStandardItem(ID));
            modele->setItem(modele->rowCount() -1 ,1, new QStandardItem(NAME));
        }
    }
    else
    {
        qWarning() << "getFamily error :" << query.lastError();
    }
}

bool DbManager::addFamily(const QString &family)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("INSERT INTO " + TABLE_FAMILY + " (" + KEY_NAME_FAMILY + ") VALUES (:" + KEY_NAME_FAMILY + ")");
    query.bindValue(":"+ KEY_NAME_FAMILY, family);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "addFamily error :" << query.lastError();
    }

       return (success);
}

bool DbManager::updateFamily(const int &ID, const QString &family)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("UPDATE " + TABLE_FAMILY + " SET " + KEY_NAME_FAMILY + " = :" + KEY_NAME_FAMILY + " WHERE " + KEY_ID_FAMILY + " = :" + KEY_ID_FAMILY );
    query.bindValue(":"+ KEY_NAME_FAMILY, family);
    query.bindValue(":"+ KEY_ID_FAMILY, ID);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "updateFamily error :" << query.lastError();
    }

       return (success);
}

bool DbManager::deleteFamily(const int &ID)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("DELETE FROM " + TABLE_FAMILY + " WHERE " + KEY_ID_FAMILY + " = :" + KEY_ID_FAMILY );
    query.bindValue(":"+ KEY_ID_FAMILY, ID);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "deleteFamily error :" << query.lastError();
    }

       return (success);
}


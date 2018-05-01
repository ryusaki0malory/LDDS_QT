#include "dbmanager.hpp"

DbManager::DbManager()
{
}

DbManager::~DbManager()
{
    if (this->db.open())
    {
        this->db.close();
    }
}

bool DbManager::init(const QString &path)
{
    if (path != "")
    {
        QFile file(path + "LDDS.ini");
        if(!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Init:" << file.errorString();
            return(false);
        }
        QTextStream in(&file);

        while(!in.atEnd()) {
            QString line = in.readLine();
            if (line[0] != "" && line[0] != "/" && line[0] != " ")
            {
                QStringList list = line.split("=");
                QString str1 = list.at(0);
                if (str1 == "SERVEUR") param.SERVEUR = list.at(1);
                if (str1 == "PORT") param.PORT = list.at(1);
                if (str1 == "BDD_PATH") param.BDD_PATH = list.at(1);
                if (str1 == "BDD_VER") param.BDD_VER = list.at(1);
                if (str1 == "BDD_LAST_UPDATE") param.BDD_LAST_UPDATE = list.at(1);
                if (str1 == "VER_APP") param.VER_APP = list.at(1);
                if (str1 == "LOGO_PATH") param.LOGO_PATH = list.at(1);
            }
        }

        file.close();
        this->connection();
        return (true);
    }
    return (false);
}

QString DbManager::getPathLogo()
{
    return (this->param.LOGO_PATH);
}

void DbManager::connection()
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName(param.BDD_PATH + DATABASE_NAME);

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

void DbManager::onCreate()
{
    //Table family article
    QString CREATE_TABLE_FAMILY = "CREATE TABLE IF NOT EXISTS " + TABLE_FAMILY + " ( " +
                    KEY_ID_FAMILY + " INTEGER PRIMARY KEY AUTOINCREMENT," +
                    KEY_NAME_FAMILY + " TEXT," +
                    KEY_D_MODIF_FAMILY + " TEXT);";
    QSqlQuery queryCreateFamily;
    queryCreateFamily.prepare(CREATE_TABLE_FAMILY);
    if(!queryCreateFamily.exec())
    {
        qWarning() << "familyTable error :" << queryCreateFamily.lastError();
    }

    //Table retailler
    QString CREATE_TABLE_RETAILLER = "CREATE TABLE IF NOT EXISTS " + TABLE_RETAILLER + " ( " +
                    KEY_ID_RETAILLER + " INTEGER PRIMARY KEY AUTOINCREMENT," +
                    KEY_NAME_RETAILLER + " TEXT," +
                    KEY_COMMENT_RETAILLER + " TEXT," +
                    KEY_D_MODIF_RETAILLER + " TEXT);";
    QSqlQuery queryCreateRetailler;
    queryCreateRetailler.prepare(CREATE_TABLE_RETAILLER);
    if(!queryCreateRetailler.exec())
    {
        qWarning() << "retaillerTable error :" << queryCreateRetailler.lastError();
    }

    //Table typeArticle
    QString CREATE_TABLE_TYPE_ARTICLE = "CREATE TABLE IF NOT EXISTS " + TABLE_TYPE + " ( " +
                    KEY_ID_TYPE + " INTEGER PRIMARY KEY AUTOINCREMENT," +
                    KEY_NAME_TYPE + " TEXT," +
                    KEY_QTE_TYPE + " NUMERIC," +
                    KEY_BASE_UNIT_TYPE + " INTEGER," +
                    KEY_D_MODIF_TYPE + " TEXT);";
    QSqlQuery queryCreateTypeArticle;
    queryCreateTypeArticle.prepare(CREATE_TABLE_TYPE_ARTICLE);
    if(!queryCreateTypeArticle.exec())
    {
        qWarning() << "typeArticleTable error :" << queryCreateTypeArticle.lastError();
    }
    //Table baseunit
    QString CREATE_TABLE_BASE_UNIT = "CREATE TABLE IF NOT EXISTS " + TABLE_BASE + " ( " +
                    KEY_ID_BASE + " INTEGER PRIMARY KEY AUTOINCREMENT," +
                    KEY_NAME_BASE + " TEXT," +
                    KEY_MULT_BASE + " NUMERIC," +
                    KEY_D_MODIF_BASE + " TEXT);";
    QSqlQuery queryCreateBaseUnit;
    queryCreateBaseUnit.prepare(CREATE_TABLE_BASE_UNIT);
    if(!queryCreateBaseUnit.exec())
    {
        qWarning() << "baseUnitTable error :" << queryCreateBaseUnit.lastError();
    }
}

//family
void DbManager::getFamily(QStandardItemModel *modele)
{
    QSqlQuery query;
    QString SELECT = "SELECT " + KEY_ID_FAMILY + ","+ KEY_NAME_FAMILY + " FROM " + TABLE_FAMILY;

    if(query.exec(SELECT))
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

    query.prepare("INSERT INTO " + TABLE_FAMILY + " (" + KEY_NAME_FAMILY + "," + KEY_D_MODIF_FAMILY + ") VALUES (:" + KEY_NAME_FAMILY + ",DATETIME('now'))");
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

    query.prepare("UPDATE " + TABLE_FAMILY + " SET " + KEY_NAME_FAMILY + " = :" + KEY_NAME_FAMILY + ", " + KEY_D_MODIF_FAMILY + " =  DATETIME('now') WHERE " + KEY_ID_FAMILY + " = :" + KEY_ID_FAMILY );
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

//retailler
void DbManager::getRetailler(QStandardItemModel *modele)
{
    QSqlQuery query;
    QString SELECT = "SELECT " + KEY_ID_RETAILLER + ","+ KEY_NAME_RETAILLER + ","+ KEY_COMMENT_RETAILLER+ " FROM " + TABLE_RETAILLER;

    if(query.exec(SELECT))
    {
        while (query.next())
        {
            QString ID = query.value(KEY_ID_RETAILLER).toString();
            QString NAME = query.value(KEY_NAME_RETAILLER).toString();
            QString COMMENT = query.value(KEY_COMMENT_RETAILLER).toString();
            modele->setItem(modele->rowCount(),0, new QStandardItem(ID));
            modele->setItem(modele->rowCount() -1 ,1, new QStandardItem(NAME));
            modele->setItem(modele->rowCount() -1 ,2, new QStandardItem(COMMENT));
        }
    }
    else
    {
        qWarning() << "getRetailler error :" << query.lastError();
    }
}
bool DbManager::addRetailler(const QString &name, const QString &comment)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("INSERT INTO " + TABLE_RETAILLER + " (" + KEY_NAME_RETAILLER + "," + KEY_COMMENT_RETAILLER + "," + KEY_D_MODIF_RETAILLER + ") VALUES (:" + KEY_NAME_RETAILLER + ",:" +KEY_COMMENT_RETAILLER + ", DATETIME('now'))");
    query.bindValue(":"+ KEY_NAME_RETAILLER, name);
    query.bindValue(":"+ KEY_COMMENT_RETAILLER, comment);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "addRetailler error :" << query.lastError();
    }
    return (success);
}
bool DbManager::updateRetailler(const int &ID, const QString &name, const QString &comment)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("UPDATE " + TABLE_RETAILLER + " SET " + KEY_NAME_RETAILLER + " = :" + KEY_NAME_RETAILLER + ", " + KEY_COMMENT_RETAILLER + " = :" + KEY_COMMENT_RETAILLER + ", " + KEY_D_MODIF_RETAILLER + " =  DATETIME('now') WHERE " + KEY_ID_RETAILLER + " = :" + KEY_ID_RETAILLER );
    query.bindValue(":"+ KEY_NAME_RETAILLER, name);
    query.bindValue(":"+ KEY_COMMENT_RETAILLER, comment);
    query.bindValue(":"+ KEY_ID_RETAILLER, ID);
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
bool DbManager::deleteRetailler(const int &ID)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("DELETE FROM " + TABLE_RETAILLER + " WHERE " + KEY_ID_RETAILLER + " = :" + KEY_ID_RETAILLER );
    query.bindValue(":"+ KEY_ID_RETAILLER, ID);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "deleteRetailler error :" << query.lastError();
    }
    return (success);
}

//type articles
void DbManager::getTypeArticle(QStandardItemModel *modele)
{
    QSqlQuery query;
    QString SELECT = "SELECT " + KEY_ID_TYPE + ","+ KEY_NAME_TYPE + ","+ KEY_QTE_TYPE+ "," + KEY_BASE_UNIT_TYPE + " FROM " + TABLE_TYPE;

    if(query.exec(SELECT))
    {
        while (query.next())
        {
            QString ID = query.value(KEY_ID_TYPE).toString();
            QString NAME = query.value(KEY_NAME_TYPE).toString();
            QString QTE = query.value(KEY_QTE_TYPE).toString();
            QString BASE_UNIT = query.value(KEY_BASE_UNIT_TYPE).toString();
            modele->setItem(modele->rowCount(),0, new QStandardItem(ID));
            modele->setItem(modele->rowCount() -1 ,1, new QStandardItem(NAME));
            modele->setItem(modele->rowCount() -1 ,2, new QStandardItem(QTE));
            modele->setItem(modele->rowCount() -1 ,3, new QStandardItem(BASE_UNIT));
        }
    }
    else
    {
        qWarning() << "getType error :" << query.lastError();
    }
}
bool DbManager::addTypeArticle(const QString &name, const double &qte, const int &baseUnit)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO " + TABLE_TYPE + " (" + KEY_NAME_TYPE + "," + KEY_QTE_TYPE + "," + KEY_BASE_UNIT_TYPE + "," + KEY_D_MODIF_TYPE + ") VALUES (:" + KEY_NAME_TYPE + ",:" +KEY_QTE_TYPE + ",:" + KEY_BASE_UNIT_TYPE + ", DATETIME('now'))");
    query.bindValue(":"+ KEY_NAME_TYPE, name);
    query.bindValue(":"+ KEY_QTE_TYPE, qte);
    query.bindValue(":"+ KEY_BASE_UNIT_TYPE, baseUnit);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "addTypeArticle error :" << query.lastError();
    }
    return (success);
}
bool DbManager::updateTypeArticle(const int &ID, const QString &name, const double &qte, const int &baseUnit)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("UPDATE " + TABLE_TYPE + " SET " + KEY_NAME_TYPE + " = :" + KEY_NAME_TYPE + ", " + KEY_QTE_TYPE + " = :" + KEY_QTE_TYPE + ", " + KEY_BASE_UNIT_TYPE + " = :" + KEY_BASE_UNIT_TYPE + ", "+ KEY_D_MODIF_TYPE + " =  DATETIME('now') WHERE " + KEY_ID_TYPE + " = :" + KEY_ID_TYPE );
    query.bindValue(":"+ KEY_NAME_TYPE, name);
    query.bindValue(":"+ KEY_QTE_TYPE, qte);
    query.bindValue(":"+ KEY_BASE_UNIT_TYPE, baseUnit);
    query.bindValue(":"+ KEY_ID_TYPE, ID);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "updateTypeArticle error :" << query.lastError();
    }

    return (success);
}
bool DbManager::deleteTypeArticle(const int &ID)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("DELETE FROM " + TABLE_TYPE + " WHERE " + KEY_ID_TYPE + " = :" + KEY_ID_TYPE );
    query.bindValue(":"+ KEY_ID_TYPE, ID);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "deleteTypeArticle error :" << query.lastError();
    }
    return (success);
}

//base unit
void DbManager::getBaseUnit(QStandardItemModel *modele)
{
    QSqlQuery query;
    QString SELECT = "SELECT " + KEY_ID_BASE + ","+ KEY_NAME_BASE + ","+ KEY_MULT_BASE + " FROM " + TABLE_BASE;

    if(query.exec(SELECT))
    {
        while (query.next())
        {
            QString ID = query.value(KEY_ID_BASE).toString();
            QString NAME = query.value(KEY_NAME_BASE).toString();
            QString MULT = query.value(KEY_MULT_BASE).toString();
            modele->setItem(modele->rowCount(),0, new QStandardItem(ID));
            modele->setItem(modele->rowCount() -1 ,1, new QStandardItem(NAME));
            modele->setItem(modele->rowCount() -1 ,2, new QStandardItem(MULT));
        }
    }
    else
    {
        qWarning() << "getBase error :" << query.lastError();
    }
}
bool DbManager::addBaseUnit(const QString &name, const double &mult)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO " + TABLE_BASE + " (" + KEY_NAME_BASE + "," + KEY_MULT_BASE + "," + KEY_D_MODIF_BASE + ") VALUES (:" + KEY_NAME_BASE + ",:" +KEY_MULT_BASE + ", DATETIME('now'))");
    query.bindValue(":"+ KEY_NAME_BASE, name);
    query.bindValue(":"+ KEY_MULT_BASE, mult);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "addBaseUnit error :" << query.lastError();
    }
    return (success);
}
bool DbManager::updateBaseUnit(const int &ID, const QString &name, const double &mult)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("UPDATE " + TABLE_BASE + " SET " + KEY_NAME_BASE + " = :" + KEY_NAME_BASE + ", " + KEY_MULT_BASE + " = :" + KEY_MULT_BASE + ", "+ KEY_D_MODIF_BASE + " =  DATETIME('now') WHERE " + KEY_D_MODIF_BASE + " = :" + KEY_D_MODIF_BASE );
    query.bindValue(":"+ KEY_NAME_BASE, name);
    query.bindValue(":"+ KEY_MULT_BASE, mult);
    query.bindValue(":"+ KEY_D_MODIF_BASE, ID);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "updateBaseUnit error :" << query.lastError();
    }

    return (success);
}
bool DbManager::deleteBaseUnit(const int &ID)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("DELETE FROM " + TABLE_BASE + " WHERE " + KEY_ID_BASE + " = :" + KEY_ID_BASE );
    query.bindValue(":"+ KEY_ID_BASE, ID);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "deleteBaseUnit error :" << query.lastError();
    }
    return (success);
}

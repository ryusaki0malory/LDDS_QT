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
    //Table paymentMethod
    QString CREATE_TABLE_PAYMENT_METHOD = "CREATE TABLE IF NOT EXISTS " + TABLE_PAYMENT + " ( " +
                    KEY_ID_PAYMENT + " INTEGER PRIMARY KEY AUTOINCREMENT," +
                    KEY_NAME_PAYMENT + " TEXT," +
                    KEY_D_MODIF_PAYMENT + " TEXT);";
    QSqlQuery queryCreatePaymentMethod;
    queryCreatePaymentMethod.prepare(CREATE_TABLE_PAYMENT_METHOD);
    if(!queryCreatePaymentMethod.exec())
    {
        qWarning() << "paymentMethodTable error :" << queryCreatePaymentMethod.lastError();
    }
    //Table cutomer
    QString CREATE_TABLE_CUSTOMER = "CREATE TABLE IF NOT EXISTS " + TABLE_CUSTOMER + " ( " +
                    KEY_ID_CUSTOMER + " INTEGER PRIMARY KEY AUTOINCREMENT," +
                    KEY_LAST_NAME_CUSTOMER + " TEXT," +
                    KEY_FIRST_NAME_CUSTOMER + " TEXT," +
                    KEY_ADDRESS_CUSTOMER + " TEXT," +
                    KEY_POSTAL_CODE_CUSTOMER + " VARCHAR(10)," +
                    KEY_CITY_CUSTOMER + " TEXT," +
                    KEY_COMMENT_CUSTOMER + " TEXT," +
                    KEY_ACCOUNT_ID_CUSTOMER + " INTEGER," +
                    KEY_PHONE_CUSTOMER + " VARCHAR(20)," +
                    KEY_MAIL_CUSTOMER + " TEXT," +
                    KEY_D_MODIF_PAYMENT + " TEXT);";
    QSqlQuery queryCreateCustomer;
    queryCreateCustomer.prepare(CREATE_TABLE_CUSTOMER);
    if(!queryCreateCustomer.exec())
    {
        qWarning() << "Customer error :" << queryCreateCustomer.lastError();
    }
}

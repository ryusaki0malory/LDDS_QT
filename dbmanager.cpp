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
        QFile file(path + "/LDDS.ini");
        if(!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Init:" << file.errorString();
            this->status = ERROR_INITIALISATION;
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
        this->status = RUNNING;
        this->connection();
        return (true);
    }
    this->status = ERROR_INITIALISATION;
    return (false);
}

void DbManager::connection()
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName(param.BDD_PATH + DATABASE_NAME);

    if (!this->db.open())
    {
        this->status = ERROR_INITIALISATION;
        qWarning() << "Error: connection with database fail";
    }
    else
    {
        this->status = RUNNING;
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
        this->status = ERROR_BDD;
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
        this->status = ERROR_BDD;
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
        this->status = ERROR_BDD;
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
        this->status = ERROR_BDD;
        qWarning() << "baseUnitTable error :" << queryCreateBaseUnit.lastError();
    }
    //Table Article
    QString CREATE_TABLE_ARTICLE = "CREATE TABLE IF NOT EXISTS " + TABLE_ARTICLE + " ( " +
                    KEY_ID_ARTICLE + " INTEGER PRIMARY KEY AUTOINCREMENT," +
                    KEY_NAME_ARTICLE + " TEXT," +
                    KEY_QTE_ARTICLE + " REAL," +
                    KEY_ID_FAMILY_ARTICLE + " INTEGER," +
                    KEY_PRICE_ARTICLE + " REAL," +
                    KEY_ID_RETAILLER_ARTICLE + " INTEGER," +
                    KEY_ID_TYPE_ARTICLE + " INTEGER," +
                    KEY_COMMENT_ARTICLE + " TEXT," +
                    KEY_IMAGE_ARTICLE + " BLOB," +
                    KEY_D_MODIF_ARTICLE + " TEXT);";
    QSqlQuery queryCreateArticle;
    queryCreateArticle.prepare(CREATE_TABLE_ARTICLE);
    if(!queryCreateArticle.exec())
    {
        this->status = ERROR_BDD;
        qWarning() << "Article error :" << queryCreateArticle.lastError();
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
        this->status = ERROR_BDD;
        qWarning() << "paymentMethodTable error :" << queryCreatePaymentMethod.lastError();
    }
    //Table cutomer
    QString CREATE_TABLE_CUSTOMER = "CREATE TABLE IF NOT EXISTS " + TABLE_CUSTOMER + " ( " +
                    KEY_ID_CUSTOMER + " INTEGER PRIMARY KEY AUTOINCREMENT," +
                    KEY_FIRST_NAME_CUSTOMER + " TEXT," +
                    KEY_LAST_NAME_CUSTOMER + " TEXT," +
                    KEY_COMMENT_CUSTOMER + " TEXT," +
                    KEY_ACCOUNT_ID_CUSTOMER + " INTEGER," +
                    KEY_MAIL_CUSTOMER + " TEXT," +
                    KEY_D_MODIF_PAYMENT + " TEXT);";
    QSqlQuery queryCreateCustomer;
    queryCreateCustomer.prepare(CREATE_TABLE_CUSTOMER);
    if(!queryCreateCustomer.exec())
    {
        this->status = ERROR_BDD;
        qWarning() << "Customer error :" << queryCreateCustomer.lastError();
    }
    //Table address
    QString CREATE_TABLE_ADDRESS = "CREATE TABLE IF NOT EXISTS " + TABLE_ADDRESS + " ( " +
                    KEY_ID_ADDRESS + " INTEGER PRIMARY KEY AUTOINCREMENT," +
                    KEY_ID_TYPE_ADDRESS + " INTEGER," +
                    KEY_BODY_ADDRESS + " TEXT," +
                    KEY_POSTAL_CODE_CUSTOMER + " VARCHAR(10)," +
                    KEY_CITY_CUSTOMER + " TEXT," +
                    KEY_D_MODIF_ADDRESS + " TEXT);";
    QSqlQuery queryCreateAddress;
    queryCreateAddress.prepare(CREATE_TABLE_ADDRESS);
    if(!queryCreateAddress.exec())
    {
        this->status = ERROR_BDD;
        qWarning() << "Address error :" << queryCreateAddress.lastError();
    }
    //Table link address
    QString CREATE_TABLE_LINK_ADDRESS = "CREATE TABLE IF NOT EXISTS " + TABLE_LINK_ADDRESS + " ( " +
                    KEY_ID_LINK_ADDRESS + " INTEGER PRIMARY KEY AUTOINCREMENT," +
                    KEY_ID_CUSTOMER_LINK_ADDRESS + " INTEGER," +
                    KEY_ID_ADDRESS_LINK_ADDRESS + " INTEGER," +
                    KEY_D_MODIF_LINK_ADDRESS + " TEXT);";
    QSqlQuery queryCreateLinkAddress;
    queryCreateLinkAddress.prepare(CREATE_TABLE_LINK_ADDRESS);
    if(!queryCreateLinkAddress.exec())
    {
        this->status = ERROR_BDD;
        qWarning() << "Link address error :" << queryCreateLinkAddress.lastError();
    }
    //Table type address
    QString CREATE_TABLE_TYPE_ADDRESS = "CREATE TABLE IF NOT EXISTS " + TABLE_TYPE_ADDRESS + " ( " +
                    KEY_ID_TYPE_ADDRESS + " INTEGER PRIMARY KEY AUTOINCREMENT," +
                    KEY_NAME_TYPE_ADDRESS + " TEXT," +
                    KEY_D_MODIF_TYPE_ADDRESS + " TEXT);";
    QSqlQuery queryCreateTypeAddress;
    queryCreateTypeAddress.prepare(CREATE_TABLE_TYPE_ADDRESS);
    if(!queryCreateTypeAddress.exec())
    {
        this->status = ERROR_BDD;
        qWarning() << "Type address error :" << queryCreateTypeAddress.lastError();
    }
    //Table Phone
    QString CREATE_TABLE_PHONE = "CREATE TABLE IF NOT EXISTS " + TABLE_PHONE + " ( " +
                    KEY_ID_PHONE + " INTEGER PRIMARY KEY AUTOINCREMENT," +
                    KEY_NAME_PHONE + " TEXT," +
                    KEY_NUMBER_PHONE + " VARCHAR(20)," +
                    KEY_ID_TYPE_PHONE_PHONE + " INTEGER," +
                    KEY_D_MODIF_PHONE + " TEXT);";
    QSqlQuery queryCreatePhone;
    queryCreatePhone.prepare(CREATE_TABLE_PHONE);
    if(!queryCreatePhone.exec())
    {
        this->status = ERROR_BDD;
        qWarning() << "Phone error :" << queryCreatePhone.lastError();
    }
    //Table Link Phone
    QString CREATE_TABLE_LINK_PHONE = "CREATE TABLE IF NOT EXISTS " + TABLE_LINK_PHONE + " ( " +
                    KEY_ID_LINK_PHONE + " INTEGER PRIMARY KEY AUTOINCREMENT," +
                    KEY_ID_CUSTOMER_LINK_PHONE + " INTEGER," +
                    KEY_ID_PHONE_LINK_PHONE + " INTEGER," +
                    KEY_D_LINK_PHONE + " TEXT);";
    QSqlQuery queryCreateLinkPhone;
    queryCreateLinkPhone.prepare(CREATE_TABLE_LINK_PHONE);
    if(!queryCreateLinkPhone.exec())
    {
        this->status = ERROR_BDD;
        qWarning() << "Link Phone error :" << queryCreateLinkPhone.lastError();
    }
    //Table Type Phone
    QString CREATE_TABLE_TYPE_PHONE = "CREATE TABLE IF NOT EXISTS " + TABLE_TYPE_PHONE + " ( " +
                    KEY_ID_TYPE_PHONE + " INTEGER PRIMARY KEY AUTOINCREMENT," +
                    KEY_NAME_TYPE_PHONE + " TEXT," +
                    KEY_D_MODIF_TYPE_PHONE + " TEXT);";
    QSqlQuery queryCreateTypePhone;
    queryCreateTypePhone.prepare(CREATE_TABLE_TYPE_PHONE);
    if(!queryCreateTypePhone.exec())
    {
        this->status = ERROR_BDD;
        qWarning() << "Type Phone error :" << queryCreateTypePhone.lastError();
    }
}

#ifndef DBMANAGER_HPP
#define DBMANAGER_HPP

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QTextStream>

//Please call init function befor using public method
class DbManager
{

public:
    DbManager();
    ~DbManager();

    bool init(const QString &path); //need the path to LDDS.ini

protected:

    typedef struct paramInit
    {
        QString SERVEUR;
        QString PORT;
        QString BDD_PATH;
        QString BDD_VER;
        QString BDD_LAST_UPDATE;
        QString VER_APP;
        QString LOGO_PATH;
    } paramInit_t;

    void onCreate();
    void connection();
    QSqlDatabase db;
    paramInit_t param;
    const QString DATABASE_NAME = "LDDS.db";
    //Table family article
    const QString TABLE_FAMILY = "family";
    const QString KEY_ID_FAMILY = "ID";
    const QString KEY_NAME_FAMILY = "Name";
    const QString KEY_D_MODIF_FAMILY = "Modif";

    //Table retailler article
    const QString TABLE_RETAILLER = "retailler";
    const QString KEY_ID_RETAILLER = "ID";
    const QString KEY_NAME_RETAILLER = "Name";
    const QString KEY_COMMENT_RETAILLER = "Comment";
    const QString KEY_D_MODIF_RETAILLER = "Modif";

    //Table type article
    const QString TABLE_TYPE = "typeArticle";
    const QString KEY_ID_TYPE = "ID";
    const QString KEY_NAME_TYPE = "Name";
    const QString KEY_QTE_TYPE = "qte";
    const QString KEY_BASE_UNIT_TYPE = "baseUnit";
    const QString KEY_D_MODIF_TYPE = "Modif";

    //Table base unit
    const QString TABLE_BASE = "baseUnit";
    const QString KEY_ID_BASE = "ID";
    const QString KEY_NAME_BASE = "Name";
    const QString KEY_MULT_BASE = "mult";
    const QString KEY_D_MODIF_BASE = "Modif";

    //Table base unit
    const QString TABLE_PAYMENT = "paymentMethod";
    const QString KEY_ID_PAYMENT = "ID";
    const QString KEY_NAME_PAYMENT = "Name";
    const QString KEY_D_MODIF_PAYMENT = "Modif";

    //Articles
    const QString TABLE_ARTICLE = "article";
    const QString KEY_ID_ARTICLE = "ID";
    const QString KEY_NAME_ARTICLE = "NameArticle";
    const QString KEY_QTE_ARTICLE = "QteArticle";
    const QString KEY_ID_FAMILY_ARTICLE = "IDFamily";
    const QString KEY_PRICE_ARTICLE = "Price";
    const QString KEY_ID_RETAILLER_ARTICLE = "IDRetailler";
    const QString KEY_ID_TYPE_ARTICLE = "IDTypeArticle";
    const QString KEY_COMMENT_ARTICLE = "CommentArticle";
    const QString KEY_IMAGE_ARTICLE = "ImageArticle";
    const QString KEY_D_MODIF_ARTICLE = "Modif";

    //Table customer
    const QString TABLE_CUSTOMER = "customer";
    const QString KEY_ID_CUSTOMER = "ID";
    const QString KEY_FIRST_NAME_CUSTOMER = "FirstName";
    const QString KEY_LAST_NAME_CUSTOMER = "LastName";
    const QString KEY_COMMENT_CUSTOMER = "Comment";
    const QString KEY_ACCOUNT_ID_CUSTOMER = "AccountId";
    const QString KEY_MAIL_CUSTOMER = "Mail";
    const QString KEY_D_MODIF_CUSTOMER = "Modif";

    //Table address
    const QString TABLE_ADDRESS = "address";
    const QString KEY_ID_ADDRESS = "ID";
    const QString KEY_ID_TYPE_ADDRESS_ADDRESS = "IDType";
    const QString KEY_BODY_ADDRESS = "Body";
    const QString KEY_POSTAL_CODE_CUSTOMER = "PostalCode";
    const QString KEY_CITY_CUSTOMER = "City";
    const QString KEY_D_MODIF_ADDRESS = "Modif";

    //Table link address
    const QString TABLE_LINK_ADDRESS = "linkAddress";
    const QString KEY_ID_LINK_ADDRESS = "IDLink";
    const QString KEY_ID_CUSTOMER_LINK_ADDRESS = "IDCustomer";
    const QString KEY_ID_ADDRESS_LINK_ADDRESS = "IDAddress";
    const QString KEY_D_MODIF_LINK_ADDRESS = "Modif";

    //TypeAddress
    const QString TABLE_TYPE_ADDRESS = "typeAddress";
    const QString KEY_ID_TYPE_ADDRESS = "IDType";
    const QString KEY_NAME_TYPE_ADDRESS = "NameType";
    const QString KEY_D_MODIF_TYPE_ADDRESS = "ModifType";

    //Table Phone
    const QString TABLE_PHONE = "phone";
    const QString KEY_ID_PHONE = "ID";
    const QString KEY_NAME_PHONE = "Name";
    const QString KEY_NUMBER_PHONE = "Number";
    const QString KEY_ID_TYPE_PHONE_PHONE = "IdType";
    const QString KEY_D_MODIF_PHONE = "Modif";

    //Table link phone
    const QString TABLE_LINK_PHONE = "linkPhone";
    const QString KEY_ID_LINK_PHONE = "IDLink";
    const QString KEY_ID_CUSTOMER_LINK_PHONE = "IDCustomerLink";
    const QString KEY_ID_PHONE_LINK_PHONE = "IDPhoneLink";
    const QString KEY_D_LINK_PHONE = "ModifLink";

    //TypePhone
    const QString TABLE_TYPE_PHONE = "typePhone";
    const QString KEY_ID_TYPE_PHONE = "IDType";
    const QString KEY_NAME_TYPE_PHONE = "NameType";
    const QString KEY_D_MODIF_TYPE_PHONE = "ModifType";

};

#endif // DBMANAGER_HPP

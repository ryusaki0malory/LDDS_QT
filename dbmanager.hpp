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
    const QString KEY_ID_FAMILY = "IDFamily";
    const QString KEY_NAME_FAMILY = "NameFamily";
    const QString KEY_D_MODIF_FAMILY = "ModifFamily";

    //Table retailler article
    const QString TABLE_RETAILLER = "retailler";
    const QString KEY_ID_RETAILLER = "IDRetailler";
    const QString KEY_NAME_RETAILLER = "NameRetailler";
    const QString KEY_COMMENT_RETAILLER = "CommentRetailler";
    const QString KEY_D_MODIF_RETAILLER = "ModifRetailler";

    //Table type article
    const QString TABLE_TYPE = "typeArticle";
    const QString KEY_ID_TYPE = "IDTypeArticle";
    const QString KEY_NAME_TYPE = "NameTypeArticle";
    const QString KEY_QTE_TYPE = "qteTypeArticle";
    const QString KEY_BASE_UNIT_TYPE = "baseUnitTypeArticle";
    const QString KEY_D_MODIF_TYPE = "ModifTypeArticles";

    //Table base unit
    const QString TABLE_BASE = "baseUnit";
    const QString KEY_ID_BASE = "IDBaseUnit";
    const QString KEY_NAME_BASE = "NameBaseUnit";
    const QString KEY_MULT_BASE = "multBaseUnit";
    const QString KEY_D_MODIF_BASE = "ModifBaseUnit";

};

#endif // DBMANAGER_HPP

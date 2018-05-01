#ifndef DBMANAGER_HPP
#define DBMANAGER_HPP

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QString>
#include <QStandardItemModel>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>

//Please call init function befor using public method
class DbManager
{

public:
    DbManager();
    ~DbManager();

    bool init(const QString &path); //need the path to LDDS.ini
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
    bool updateBaseUnit(const int &ID, const QString &name, const double &mult);
    bool deleteBaseUnit(const int &ID);

private:

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

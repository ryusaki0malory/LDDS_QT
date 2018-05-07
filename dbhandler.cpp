#include "dbhandler.hpp"

DbHandler::DbHandler() : DbManager()
{

}

DbHandler::~DbHandler()
{

}

QString DbHandler::getPathLogo()
{
    return (this->param.LOGO_PATH);
}

//family
void DbHandler::getFamily(QStandardItemModel *modele)
{
    QSqlQuery query;
    QString SELECT = "SELECT " +
                        KEY_ID_FAMILY + "," +
                        KEY_NAME_FAMILY +
                    " FROM " +
                        TABLE_FAMILY;

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
bool DbHandler::addFamily(const QString &family)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("INSERT INTO " +
                        TABLE_FAMILY +
                  " (" + KEY_NAME_FAMILY + "," +
                        KEY_D_MODIF_FAMILY +
                  ") VALUES (:" +
                        KEY_NAME_FAMILY +
                        ",DATETIME('now'))");
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
bool DbHandler::updateFamily(const int &ID,
                             const QString &family)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("UPDATE " +
                        TABLE_FAMILY +
                  " SET " +
                        KEY_NAME_FAMILY + " = :" + KEY_NAME_FAMILY +
                  ", " + KEY_D_MODIF_FAMILY + " =  DATETIME('now') " +
                  "WHERE " +
                        KEY_ID_FAMILY + " = :" + KEY_ID_FAMILY );
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
bool DbHandler::deleteFamily(const int &ID)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("DELETE FROM " +
                        TABLE_FAMILY +
                  " WHERE " +
                        KEY_ID_FAMILY + " = :" + KEY_ID_FAMILY );
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
void DbHandler::getRetailler(QStandardItemModel *modele)
{
    QSqlQuery query;
    QString SELECT = "SELECT " +
                            KEY_ID_RETAILLER + "," +
                            KEY_NAME_RETAILLER + "," +
                            KEY_COMMENT_RETAILLER +
                    " FROM " +
                            TABLE_RETAILLER;

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
bool DbHandler::addRetailler(const QString &name,
                             const QString &comment)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("INSERT INTO " +
                        TABLE_RETAILLER +
                  " (" + KEY_NAME_RETAILLER + "," +
                        KEY_COMMENT_RETAILLER + "," +
                        KEY_D_MODIF_RETAILLER +
                  ") VALUES (:" +
                        KEY_NAME_RETAILLER + ",:" +
                        KEY_COMMENT_RETAILLER +
                        ", DATETIME('now'))");
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
bool DbHandler::updateRetailler(const int &ID,
                                const QString &name,
                                const QString &comment)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("UPDATE " +
                        TABLE_RETAILLER +
                  " SET " +
                        KEY_NAME_RETAILLER + " = :" + KEY_NAME_RETAILLER + ", " +
                        KEY_COMMENT_RETAILLER + " = :" + KEY_COMMENT_RETAILLER + ", " +
                        KEY_D_MODIF_RETAILLER + " =  DATETIME('now') " +
                  "WHERE " + KEY_ID_RETAILLER + " = :" + KEY_ID_RETAILLER );
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
bool DbHandler::deleteRetailler(const int &ID)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("DELETE FROM " +
                        TABLE_RETAILLER +
                  " WHERE " + KEY_ID_RETAILLER + " = :" + KEY_ID_RETAILLER );
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
void DbHandler::getTypeArticle(QStandardItemModel *modele)
{
    QSqlQuery query;
    QString SELECT = "SELECT " +
                        KEY_ID_TYPE + "," +
                        KEY_NAME_TYPE + "," +
                        KEY_QTE_TYPE+ "," +
                        KEY_BASE_UNIT_TYPE +
                    " FROM " +
                        TABLE_TYPE;

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
            modele->setItem(modele->rowCount() -1 ,4, new QStandardItem(BASE_UNIT));
            //second query
            QSqlQuery queryBaseUnit;
            queryBaseUnit.prepare("SELECT " +
                                        KEY_NAME_BASE +
                                  " FROM " +
                                        TABLE_BASE +
                                  " WHERE " +
                                        KEY_ID_BASE + "=:" +KEY_ID_BASE);
            queryBaseUnit.bindValue(":" + KEY_ID_BASE, BASE_UNIT);
            if (queryBaseUnit.exec())
            {
                if (queryBaseUnit.next())
                {
                    QString BASE_UNIT_NAME = queryBaseUnit.value(KEY_NAME_BASE).toString();
                    modele->setItem(modele->rowCount() -1 ,3, new QStandardItem(BASE_UNIT_NAME));
                }
            }
            else
            {
                qWarning() << "BaseUnit In type articler error :" << queryBaseUnit.lastError();
            }
        }
    }
    else
    {
        qWarning() << "getType error :" << query.lastError();
    }
}
bool DbHandler::addTypeArticle(const QString &name,
                               const double &qte,
                               const int &baseUnit)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO " +
                            TABLE_TYPE +
                  " (" + KEY_NAME_TYPE + "," +
                        KEY_QTE_TYPE + "," +
                        KEY_BASE_UNIT_TYPE + "," +
                        KEY_D_MODIF_TYPE + ") " +
                  "VALUES (:" +
                        KEY_NAME_TYPE + ",:" +
                        KEY_QTE_TYPE + ",:" +
                        KEY_BASE_UNIT_TYPE + "," +
                        " DATETIME('now'))");
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
bool DbHandler::updateTypeArticle(const int &ID,
                                  const QString &name,
                                  const double &qte,
                                  const int &baseUnit)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("UPDATE " +
                        TABLE_TYPE +
                  " SET " +
                        KEY_NAME_TYPE + " = :" + KEY_NAME_TYPE + ", " +
                        KEY_QTE_TYPE + " = :" + KEY_QTE_TYPE + ", " +
                        KEY_BASE_UNIT_TYPE + " = :" + KEY_BASE_UNIT_TYPE + ", " +
                        KEY_D_MODIF_TYPE + " =  DATETIME('now') " +
                        "WHERE " +
                        KEY_ID_TYPE + " = :" + KEY_ID_TYPE );
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
bool DbHandler::deleteTypeArticle(const int &ID)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("DELETE FROM " +
                        TABLE_TYPE +
                  " WHERE " +
                        KEY_ID_TYPE + " = :" + KEY_ID_TYPE );
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
void DbHandler::getBaseUnit(QStandardItemModel *modele)
{
    QSqlQuery query;
    QString SELECT = "SELECT " +
                        KEY_ID_BASE + "," +
                        KEY_NAME_BASE + "," +
                        KEY_MULT_BASE +
                    " FROM " +
                        TABLE_BASE;

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
void DbHandler::getBaseUnit(QMap <QString, QString> &lst)
{
    QSqlQuery query;
    QString SELECT = "SELECT " +
                        KEY_ID_BASE + "," +
                        KEY_NAME_BASE +
                    " FROM " +
                        TABLE_BASE;

    if(query.exec(SELECT))
    {
        while (query.next())
        {
            lst[query.value(KEY_ID_BASE).toString()] = query.value(KEY_NAME_BASE).toString();
        }
    }
    else
    {
        qWarning() << "getBase error :" << query.lastError();
    }
}
bool DbHandler::addBaseUnit(const QString &name,
                            const double &mult)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO " +
                        TABLE_BASE +
                  " (" +
                        KEY_NAME_BASE + "," +
                        KEY_MULT_BASE + "," +
                        KEY_D_MODIF_BASE + ") " +
                  "VALUES (:" +
                        KEY_NAME_BASE + ",:" +
                        KEY_MULT_BASE + "," +
                        " DATETIME('now'))");
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
bool DbHandler::updateBaseUnit(const int &ID,
                               const QString &name,
                               const double &mult)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("UPDATE " +
                        TABLE_BASE +
                  " SET " +
                        KEY_NAME_BASE + " = :" + KEY_NAME_BASE + ", " +
                        KEY_MULT_BASE + " = :" + KEY_MULT_BASE + ", " +
                        KEY_D_MODIF_BASE + " =  DATETIME('now') " +
                  "WHERE " +
                        KEY_D_MODIF_BASE + " = :" + KEY_D_MODIF_BASE );
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
bool DbHandler::deleteBaseUnit(const int &ID)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("DELETE FROM " +
                        TABLE_BASE +
                  " WHERE " +
                        KEY_ID_BASE + " = :" + KEY_ID_BASE );
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

//payment method
void DbHandler::getPaymentMethod(QStandardItemModel *modele)
{
    QSqlQuery query;
    QString SELECT = "SELECT " +
                        KEY_ID_PAYMENT + "," +
                        KEY_NAME_PAYMENT +
                    " FROM " +
                        TABLE_PAYMENT;

    if(query.exec(SELECT))
    {
        while (query.next())
        {
            QString ID = query.value(KEY_ID_PAYMENT).toString();
            QString NAME = query.value(KEY_NAME_PAYMENT).toString();
            modele->setItem(modele->rowCount(),0, new QStandardItem(ID));
            modele->setItem(modele->rowCount() -1 ,1, new QStandardItem(NAME));
        }
    }
    else
    {
        qWarning() << "getPaymentMethod error :" << query.lastError();
    }
}
bool DbHandler::addPaymentMethod(const QString &name)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO " +
                        TABLE_PAYMENT +
                  " (" +
                        KEY_NAME_PAYMENT + "," +
                        KEY_D_MODIF_PAYMENT +
                  ") VALUES (:" +
                        KEY_NAME_PAYMENT + "," +
                        " DATETIME('now'))");
    query.bindValue(":"+ KEY_NAME_PAYMENT, name);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "addBPaymentMethod error :" << query.lastError();
    }
    return (success);
}
bool DbHandler::updatePaymentMethod(const int &ID,
                                    const QString &name)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("UPDATE " +
                        TABLE_PAYMENT +
                  " SET " +
                        KEY_NAME_PAYMENT + " = : " + KEY_NAME_PAYMENT + "," +
                        KEY_D_MODIF_PAYMENT + " =  DATETIME('now') " +
                  "WHERE " +
                        KEY_ID_PAYMENT + " = :" + KEY_ID_PAYMENT );
    query.bindValue(":"+ KEY_NAME_PAYMENT, name);
    query.bindValue(":"+ KEY_ID_PAYMENT, ID);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "updatePaymentMethod error :" << query.lastError();
    }

    return (success);
}
bool DbHandler::deletePaymentMethod(const int &ID)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("DELETE FROM " +
                        TABLE_PAYMENT +
                  " WHERE " +
                        KEY_ID_PAYMENT + " = :" + KEY_ID_PAYMENT );
    query.bindValue(":"+ KEY_ID_PAYMENT, ID);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "deletePaymentMethod error :" << query.lastError();
    }
    return (success);
}

//customer
void DbHandler::getCustomer(QStandardItemModel *modele)
{
    QSqlQuery query;
    QString SELECT = "SELECT " +
                        KEY_ID_CUSTOMER + "," +
                        KEY_FIRST_NAME_CUSTOMER + "," +
                        KEY_LAST_NAME_CUSTOMER + "," +
                        KEY_ADDRESS_CUSTOMER + "," +
                        KEY_POSTAL_CODE_CUSTOMER + "," +
                        KEY_CITY_CUSTOMER + "," +
                        KEY_COMMENT_CUSTOMER + "," +
                        KEY_ACCOUNT_ID_CUSTOMER + "," +
                        KEY_PHONE_CUSTOMER + "," +
                        KEY_MAIL_CUSTOMER +
                      " FROM " +
                        TABLE_CUSTOMER;

    if(query.exec(SELECT))
    {
        while (query.next())
        {
            QString ID = query.value(KEY_ID_CUSTOMER).toString();
            QString FIRST_NAME = query.value(KEY_FIRST_NAME_CUSTOMER).toString();
            QString LAST_NAME = query.value(KEY_LAST_NAME_CUSTOMER).toString();
            QString ADDRESS = query.value(KEY_ADDRESS_CUSTOMER).toString();
            QString POSTAL_CODE = query.value(KEY_POSTAL_CODE_CUSTOMER).toString();
            QString CITY = query.value(KEY_CITY_CUSTOMER).toString();
            QString COMMENT = query.value(KEY_COMMENT_CUSTOMER).toString();
            int ACCOUNT_ID = query.value(KEY_ACCOUNT_ID_CUSTOMER).toInt();
            QString PHONE = query.value(KEY_PHONE_CUSTOMER).toString();
            QString MAIL = query.value(KEY_MAIL_CUSTOMER).toString();
            modele->setItem(modele->rowCount(),0, new QStandardItem(ID));
            modele->setItem(modele->rowCount() -1 ,1, new QStandardItem(FIRST_NAME));
            modele->setItem(modele->rowCount() -1 ,2, new QStandardItem(LAST_NAME));
            modele->setItem(modele->rowCount() -1 ,3, new QStandardItem(ADDRESS));
            modele->setItem(modele->rowCount() -1 ,4, new QStandardItem(POSTAL_CODE));
            modele->setItem(modele->rowCount() -1 ,5, new QStandardItem(CITY));
            modele->setItem(modele->rowCount() -1 ,6, new QStandardItem(COMMENT));
            modele->setItem(modele->rowCount() -1 ,7, new QStandardItem(ACCOUNT_ID));
            modele->setItem(modele->rowCount() -1 ,8, new QStandardItem(PHONE));
            modele->setItem(modele->rowCount() -1 ,8, new QStandardItem(MAIL));
        }
    }
    else
    {
        qWarning() << "getPaymentMethod error :" << query.lastError();
    }
}
bool DbHandler::addCustomer(const QString &FirstName,
                            const QString &LastName,
                            const QString &Address,
                            const QString &CodePost,
                            const QString &City,
                            const QString &Comment,
                            const QString &Phone,
                            const QString &Mail,
                            const int &Account)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("INSERT INTO " +
                        TABLE_CUSTOMER +
                  " (" +
                        KEY_FIRST_NAME_CUSTOMER + "," +
//                        KEY_LAST_NAME_CUSTOMER + "," +
//                        KEY_ADDRESS_CUSTOMER + "," +
//                        KEY_POSTAL_CODE_CUSTOMER + "," +
//                        KEY_CITY_CUSTOMER + "," +
//                        KEY_COMMENT_CUSTOMER + "," +
//                        KEY_PHONE_CUSTOMER + "," +
//                        KEY_MAIL_CUSTOMER + "," +
//                        KEY_ACCOUNT_ID_CUSTOMER + "," +
                        KEY_D_MODIF_CUSTOMER +
                  ") VALUES (:" +
                        KEY_FIRST_NAME_CUSTOMER + "," +
//                        KEY_LAST_NAME_CUSTOMER + ",:" +
//                        KEY_ADDRESS_CUSTOMER + ",:" +
//                        KEY_POSTAL_CODE_CUSTOMER + ",:" +
//                        KEY_CITY_CUSTOMER + ",:" +
//                        KEY_COMMENT_CUSTOMER + ",:" +
//                        KEY_PHONE_CUSTOMER + ",:" +
//                        KEY_MAIL_CUSTOMER + ",:" +
//                        KEY_ACCOUNT_ID_CUSTOMER + "," +
                        " DATETIME('now'))");
    query.bindValue(":"+ KEY_FIRST_NAME_CUSTOMER, FirstName);
//    query.bindValue(":"+ KEY_LAST_NAME_CUSTOMER, LastName);
//    query.bindValue(":"+ KEY_ADDRESS_CUSTOMER, Address);
//    query.bindValue(":"+ KEY_POSTAL_CODE_CUSTOMER, CodePost);
//    query.bindValue(":"+ KEY_CITY_CUSTOMER, City);
//    query.bindValue(":"+ KEY_COMMENT_CUSTOMER, Comment);
//    query.bindValue(":"+ KEY_PHONE_CUSTOMER, Phone);
//    query.bindValue(":"+ KEY_MAIL_CUSTOMER, Mail);
//    query.bindValue(":"+ KEY_ACCOUNT_ID_CUSTOMER, Account);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "addCustomer error :" << query.lastError();
    }
    return (success);
}
bool DbHandler::updateCustomer(const int &ID,
                               const QString &FirstName,
                               const QString &LastName,
                               const QString &Address,
                               const QString &CodePost,
                               const QString &City,
                               const QString &Comment,
                               const QString &Phone,
                               const QString &Mail,
                               const int &Account)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("UPDATE " +
                        TABLE_CUSTOMER +
                  " SET " +
                        KEY_FIRST_NAME_CUSTOMER + " = :" + KEY_FIRST_NAME_CUSTOMER + "," +
                        KEY_LAST_NAME_CUSTOMER + " = :" + KEY_LAST_NAME_CUSTOMER + "," +
                        KEY_ADDRESS_CUSTOMER + " = :" + KEY_ADDRESS_CUSTOMER + "," +
                        KEY_POSTAL_CODE_CUSTOMER + " = :" + KEY_POSTAL_CODE_CUSTOMER + "," +
                        KEY_CITY_CUSTOMER + " = :" + KEY_CITY_CUSTOMER + "," +
                        KEY_COMMENT_CUSTOMER + " = :" + KEY_COMMENT_CUSTOMER + "," +
                        KEY_PHONE_CUSTOMER + " = :" + KEY_PHONE_CUSTOMER + "," +
                        KEY_MAIL_CUSTOMER + " = :" + KEY_MAIL_CUSTOMER + "," +
                        KEY_ACCOUNT_ID_CUSTOMER + " = :" + KEY_ACCOUNT_ID_CUSTOMER + "," +
                        KEY_D_MODIF_CUSTOMER + " =  DATETIME('now')" +
                  " WHERE " +
                        KEY_ID_CUSTOMER + " = :" + KEY_ID_CUSTOMER );
    query.bindValue(":"+ KEY_FIRST_NAME_CUSTOMER, FirstName);
    query.bindValue(":"+ KEY_LAST_NAME_CUSTOMER, LastName);
    query.bindValue(":"+ KEY_ADDRESS_CUSTOMER, Address);
    query.bindValue(":"+ KEY_POSTAL_CODE_CUSTOMER, CodePost);
    query.bindValue(":"+ KEY_CITY_CUSTOMER, City);
    query.bindValue(":"+ KEY_COMMENT_CUSTOMER, Comment);
    query.bindValue(":"+ KEY_PHONE_CUSTOMER, Phone);
    query.bindValue(":"+ KEY_MAIL_CUSTOMER, Mail);
    query.bindValue(":"+ KEY_ACCOUNT_ID_CUSTOMER, Account);
    query.bindValue(":"+ KEY_ID_CUSTOMER, ID);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "updateCustomer error :" << query.lastError();
    }

    return (success);
}
bool DbHandler::deleteCustomer(const int &ID)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("DELETE FROM " +
                        TABLE_CUSTOMER +
                  " WHERE " +
                        KEY_ID_CUSTOMER + " = :" + KEY_ID_CUSTOMER );
    query.bindValue(":"+ KEY_ID_CUSTOMER, ID);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "deleteCustomer error :" << query.lastError();
    }
    return (success);
}


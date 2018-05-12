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
void DbHandler::getFamily(QMap <QString, QString> &lst)
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
            lst[query.value(KEY_ID_FAMILY).toString()] = query.value(KEY_NAME_FAMILY).toString();
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
void DbHandler::getRetailler(QMap <QString, QString> &lst)
{
    QSqlQuery query;
    QString SELECT = "SELECT " +
                        KEY_ID_RETAILLER + "," +
                        KEY_NAME_RETAILLER +
                    " FROM " +
                        TABLE_RETAILLER;

    if(query.exec(SELECT))
    {
        while (query.next())
        {
            lst[query.value(KEY_ID_RETAILLER).toString()] = query.value(KEY_NAME_RETAILLER).toString();
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
void DbHandler::getTypeArticle(QMap <QString, QString> &lst)
{
    QSqlQuery query;
    QString SELECT = "SELECT " +
                        KEY_ID_TYPE + "," +
                        KEY_NAME_TYPE +
                    " FROM " +
                        TABLE_TYPE;

    if(query.exec(SELECT))
    {
        while (query.next())
        {
            lst[query.value(KEY_ID_TYPE).toString()] = query.value(KEY_NAME_TYPE).toString();
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
//article
void DbHandler::getArticle(QStandardItemModel *modele)
{
    QSqlQuery query;
    QString SELECT = "SELECT " +
                        KEY_ID_ARTICLE + "," +
                        KEY_NAME_ARTICLE + "," +
                        KEY_QTE_ARTICLE + "," +
                        KEY_ID_FAMILY_ARTICLE + "," +
                        KEY_PRICE_ARTICLE + "," +
                        KEY_ID_RETAILLER_ARTICLE + "," +
                        KEY_ID_TYPE_ARTICLE + "," +
                        KEY_COMMENT_ARTICLE + "," +
                        KEY_IMAGE_ARTICLE +
                    " FROM " +
                        TABLE_ARTICLE;

    if(query.exec(SELECT))
    {
        while (query.next())
        {
            QString ID = query.value(KEY_ID_ARTICLE).toString();
            QString NAME = query.value(KEY_NAME_ARTICLE).toString();
            QString QTE = query.value(KEY_QTE_ARTICLE).toString();
            QString IDFAMILY = query.value(KEY_ID_FAMILY_ARTICLE).toString();
            QString PRICE = query.value(KEY_PRICE_ARTICLE).toString();
            QString IDRETAILER = query.value(KEY_ID_RETAILLER_ARTICLE).toString();
            QString IDTYPE = query.value(KEY_ID_TYPE_ARTICLE).toString();
            QString COMMENT = query.value(KEY_COMMENT_ARTICLE).toString();
            QByteArray BIT_ARRAY_IMAGE = query.value(KEY_IMAGE_ARTICLE).toByteArray();
            modele->setItem(modele->rowCount(),0, new QStandardItem(ID));
            modele->setItem(modele->rowCount() -1 ,1, new QStandardItem(NAME));
            modele->setItem(modele->rowCount() -1 ,2, new QStandardItem(QTE));
            modele->setItem(modele->rowCount() -1 ,4, new QStandardItem(IDFAMILY));
            modele->setItem(modele->rowCount() -1 ,5, new QStandardItem(PRICE));
            modele->setItem(modele->rowCount() -1 ,7, new QStandardItem(IDRETAILER));
            modele->setItem(modele->rowCount() -1 ,9, new QStandardItem(IDTYPE));
            modele->setItem(modele->rowCount() -1 ,10, new QStandardItem(COMMENT));
            //Image
            QPixmap PIXMAP_IMAGE = QPixmap();
            PIXMAP_IMAGE.loadFromData( BIT_ARRAY_IMAGE);
            QImage IMAGE(1920,1080,QImage::Format_Indexed8);
            IMAGE = QImage::fromData(BIT_ARRAY_IMAGE,"PNG");
            QStandardItem *ITEM_IMAGE = new QStandardItem();
            ITEM_IMAGE->setData(QVariant(QPixmap::fromImage(IMAGE)), Qt::DecorationRole);
            modele->setItem(modele->rowCount() -1 ,11, ITEM_IMAGE);
            //query FAMILY
            QSqlQuery queryFamily;
            queryFamily.prepare("SELECT " +
                                        KEY_NAME_FAMILY +
                                  " FROM " +
                                        TABLE_FAMILY +
                                  " WHERE " +
                                        KEY_ID_FAMILY + "=:" +KEY_ID_FAMILY);
            queryFamily.bindValue(":" + KEY_ID_FAMILY, IDFAMILY);
            if (queryFamily.exec())
            {
                if (queryFamily.next())
                {
                    QString FAMILY_NAME = queryFamily.value(KEY_NAME_FAMILY).toString();
                    modele->setItem(modele->rowCount() -1 ,3, new QStandardItem(FAMILY_NAME));
                }
            }
            else
            {
                qWarning() << "Family in article error :" << queryFamily.lastError();
            }
            //query RETAILER
            QSqlQuery queryRetailer;
            queryRetailer.prepare("SELECT " +
                                        KEY_NAME_RETAILLER +
                                  " FROM " +
                                        TABLE_RETAILLER +
                                  " WHERE " +
                                        KEY_ID_RETAILLER + "=:" +KEY_ID_RETAILLER);
            queryRetailer.bindValue(":" + KEY_ID_RETAILLER, IDRETAILER);
            if (queryRetailer.exec())
            {
                if (queryRetailer.next())
                {
                    QString RETAILER_NAME = queryRetailer.value(KEY_NAME_FAMILY).toString();
                    modele->setItem(modele->rowCount() -1 ,6, new QStandardItem(RETAILER_NAME));
                }
            }
            else
            {
                qWarning() << "Retailer in article error :" << queryRetailer.lastError();
            }
            //query TYPE
            QSqlQuery queryType;
            queryType.prepare("SELECT " +
                                        KEY_NAME_TYPE +
                                  " FROM " +
                                        TABLE_TYPE +
                                  " WHERE " +
                                        KEY_ID_TYPE + "=:" +KEY_ID_TYPE);
            queryType.bindValue(":" + KEY_ID_TYPE, IDTYPE);
            if (queryType.exec())
            {
                if (queryType.next())
                {
                    QString TYPE_NAME = queryType.value(KEY_NAME_TYPE).toString();
                    modele->setItem(modele->rowCount() -1 ,8, new QStandardItem(TYPE_NAME));
                }
            }
            else
            {
                qWarning() << "Type in article error :" << queryType.lastError();
            }
        }
    }
    else
    {
        qWarning() << "Article error :" << query.lastError();
    }
}
bool DbHandler::addArticle(const QString &name,
                           const double &price,
                           const double &qte,
                           const int &family,
                           const int &retailer,
                           const int &type,
                           const QString &comment,
                           const QByteArray &image)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO " +
                        TABLE_ARTICLE +
                  " (" +
                        KEY_NAME_ARTICLE + "," +
                        KEY_QTE_ARTICLE + "," +
                        KEY_ID_FAMILY_ARTICLE + "," +
                        KEY_PRICE_ARTICLE + "," +
                        KEY_ID_RETAILLER_ARTICLE + "," +
                        KEY_ID_TYPE_ARTICLE + "," +
                        KEY_COMMENT_ARTICLE + "," +
                        KEY_IMAGE_ARTICLE + "," +
                        KEY_D_MODIF_ARTICLE +
                  ") VALUES (:" +
                        KEY_NAME_ARTICLE + ",:" +
                        KEY_QTE_ARTICLE + ",:" +
                        KEY_ID_FAMILY_ARTICLE + ",:" +
                        KEY_PRICE_ARTICLE + ",:" +
                        KEY_ID_RETAILLER_ARTICLE + ",:" +
                        KEY_ID_TYPE_ARTICLE + ",:" +
                        KEY_COMMENT_ARTICLE + ",:" +
                        KEY_IMAGE_ARTICLE + "," +
                        " DATETIME('now'))");
    query.bindValue(":"+ KEY_NAME_ARTICLE, name);
    query.bindValue(":"+ KEY_QTE_ARTICLE, qte);
    query.bindValue(":"+ KEY_ID_FAMILY_ARTICLE, family);
    query.bindValue(":"+ KEY_PRICE_ARTICLE, price);
    query.bindValue(":"+ KEY_ID_RETAILLER_ARTICLE, retailer);
    query.bindValue(":"+ KEY_ID_TYPE_ARTICLE, type);
    query.bindValue(":"+ KEY_COMMENT_ARTICLE, comment);
    query.bindValue(":"+ KEY_IMAGE_ARTICLE, image);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "addArticle error :" << query.lastError();
    }
    return (success);
}
//bool DbHandler::updateArticle(const int &ID,
//                                    const QString &name)
//{
//    bool success = false;
//    QSqlQuery query;

//    query.prepare("UPDATE " +
//                        TABLE_PAYMENT +
//                  " SET " +
//                        KEY_NAME_PAYMENT + " = : " + KEY_NAME_PAYMENT + "," +
//                        KEY_D_MODIF_PAYMENT + " =  DATETIME('now') " +
//                  "WHERE " +
//                        KEY_ID_PAYMENT + " = :" + KEY_ID_PAYMENT );
//    query.bindValue(":"+ KEY_NAME_PAYMENT, name);
//    query.bindValue(":"+ KEY_ID_PAYMENT, ID);
//    if(query.exec())
//    {
//        success = true;
//    }
//    else
//    {
//        qWarning() << "updatePaymentMethod error :" << query.lastError();
//    }

//    return (success);
//}
bool DbHandler::deleteArticle(const int &ID)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("DELETE FROM " +
                        TABLE_ARTICLE +
                  " WHERE " +
                        KEY_ID_ARTICLE + " = :" + KEY_ID_ARTICLE );
    query.bindValue(":"+ KEY_ID_ARTICLE, ID);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qWarning() << "deleteArticle error :" << query.lastError();
    }
    return (success);
}


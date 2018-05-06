#ifndef CUSTOMERPAGE_HPP
#define CUSTOMERPAGE_HPP

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableView>
#include <QFormLayout>
#include <QLineEdit>
#include <QHeaderView>
#include <QMessageBox>
#include "tools.hpp"
#include "dbhandler.hpp"

class CustomerPage : public QWidget
{
    Q_OBJECT
public:
    explicit CustomerPage(DbHandler &newDb, QWidget *parent = nullptr);
    ~CustomerPage();
    void setLayoutWindow();

    typedef enum status
    {
        SUCCESS
        ,FAIL
        ,INFORMATION

    } status_t;

    void setGroupBoxAttributes(QGroupBox* groupBox, const QString name);
    void setButtonAttributes(QPushButton* button, const QString toolTip);
    void setMessage(const status_t status, const QString message);
    void cleanItem();
    QGroupBox* getHead();
    QGroupBox* getList();
    QGroupBox* getBottom();
    DbHandler &db;

    //Head
    QPushButton *But_return;
    QPushButton *But_add;
    QPushButton *but_delete;

    //List
    QLabel *label;
    QLabel *LabMessage;
    QStandardItemModel *modele;
    QTableView *table;

    //bottom
    QLineEdit *Li_ID;
    QLineEdit *Li_first_name;
    QLineEdit *Li_last_name;
    QLineEdit *Li_address;
    QLineEdit *Li_postal_code;
    QLineEdit *Li_city;
    QLineEdit *Li_comment;
    QLineEdit *Li_phone;
    QLineEdit *Li_mail;
    QPushButton *But_valid;


signals:
    void loadPageParent(const Tools_LDDS::windowsName_t);

public slots:
    void emitLoadMAIN_PAGE();
    void addItem();
    void deleteItem();
    void validItem();
    void rowSelected(const QItemSelection&, const QItemSelection&);
};


#endif // CUSTOMERPAGE_HPP

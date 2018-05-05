#ifndef RETAILLERPAGE_HPP
#define RETAILLERPAGE_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableView>
#include <QFormLayout>
#include <QMessageBox>
#include <QHeaderView>
#include "tools.hpp"
#include "dbhandler.hpp"

class RetaillerPage : public QWidget
{
    Q_OBJECT

public:
    explicit RetaillerPage(DbHandler &newDb, QWidget *parent = nullptr);
    ~RetaillerPage();
    void setLayoutWindow();

private:
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
    QLineEdit *Li_name;
    QLineEdit *Li_ID;
    QTextEdit *Li_comment;
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

#endif // RETAILLERPAGE_HPP

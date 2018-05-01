#ifndef FAMILY_HPP
#define FAMILY_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QMessageBox>
#include "tools.hpp"
#include "dbmanager.hpp"

class FamilyPage : public QWidget
{
    Q_OBJECT

public:
    explicit FamilyPage(DbManager &newDb, QWidget *parent = nullptr);
    ~FamilyPage();
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
    DbManager &db;

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
    QPushButton *But_valid;


signals:
    void loadPageParent(const Tools_LDDS::windowsName_t);

public slots:
    void emitLoadMAIN_PAGE();
    void addFamily();
    void deleteFamily();
    void validFamily();
    void rowSelected(const QItemSelection&, const QItemSelection&);
};

#endif // FAMILY_HPP

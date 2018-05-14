#ifndef BASEUNITPAGE_HPP
#define BASEUNITPAGE_HPP

#include <QWidget>

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QHeaderView>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDoubleSpinBox>
#include <QStandardItemModel>
#include "tools.hpp"
#include "dbhandler.hpp"

class BaseUnitPage : public QWidget
{
    Q_OBJECT
public:
    explicit BaseUnitPage(DbHandler &newDb, QWidget *parent = nullptr);
    ~BaseUnitPage();
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
    QDoubleSpinBox *Li_mult;
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

#endif // BASEUNITPAGE_HPP

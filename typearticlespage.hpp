#ifndef TYPEARTICLESPAGE_HPP
#define TYPEARTICLESPAGE_HPP

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QTableView>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QHeaderView>
#include <QLineEdit>
#include "tools.hpp"
#include "dbmanager.hpp"

class TypeArticlesPage : public QWidget
{
    Q_OBJECT

public:
    explicit TypeArticlesPage(DbManager &newDb, QWidget *parent = nullptr);
    ~TypeArticlesPage();
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
    QDoubleSpinBox *Li_qte;
    QDoubleSpinBox *Li_baseUnit;
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

#endif // TYPEARTICLESPAGE_HPP

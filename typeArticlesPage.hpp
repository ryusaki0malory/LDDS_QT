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
#include <QComboBox>
#include <QMap>
#include "tools.hpp"
#include "dbhandler.hpp"

class TypeArticlesPage : public QWidget
{
    Q_OBJECT

public:
    explicit TypeArticlesPage(DbHandler &newDb, QWidget *parent = nullptr);
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
    void setLabelAttributes(QLabel* label);
    void setLineAttributes(QLineEdit *line);
    void setMessage(const status_t status, const QString message);
    void cleanItem();
    QGroupBox* getHead();
    QGroupBox* getList();
    QGroupBox* getBottom();
    void    loadQComboBox();
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
    QLabel *La_name;
    QLineEdit *Li_name;
    QLabel *La_ID;
    QLineEdit *Li_ID;
    QLabel *La_qte;
    QDoubleSpinBox *Li_qte;
    QLabel *La_baseUnit;
    QComboBox *Li_baseUnit;
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

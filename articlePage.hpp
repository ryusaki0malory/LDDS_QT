#ifndef ARTICLEPAGE_HPP
#define ARTICLEPAGE_HPP

#include <QWidget>
#include <QGroupBox>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDoubleSpinBox>
#include <QStandardItemModel>
#include "tools.hpp"
#include "dbhandler.hpp"

class ArticlePage : public QWidget
{
    Q_OBJECT
public:
    explicit ArticlePage(DbHandler &newDb, QWidget *parent = nullptr);
    ~ArticlePage();
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
    QLabel    *La_name;
    QLineEdit *Li_name;
    QLabel    *La_ID;
    QLineEdit *Li_ID;
    QLabel    *La_mult;
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

#endif // ARTICLEPAGE_HPP

#ifndef ARTICLEPAGE_HPP
#define ARTICLEPAGE_HPP

#include <QWidget>
#include <QGroupBox>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QFormLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QDoubleSpinBox>
#include <QComboBox>
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
    QLabel    *La_comment;
    QTextEdit *Li_comment;
    QLabel    *La_ID;
    QLineEdit *Li_ID;
    QLabel    *La_prix;
    QDoubleSpinBox *Li_prix;
    QLabel    *La_qte;
    QDoubleSpinBox *Li_qte;
    QLabel    *La_family;
    QComboBox *Li_family;
    QLabel    *La_retailer;
    QComboBox *Li_retailer;
    QLabel    *La_type;
    QComboBox *Li_type;
    QLabel    *La_image;
    QLabel    *Li_image;
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

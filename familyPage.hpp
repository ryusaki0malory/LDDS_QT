#ifndef FAMILY_HPP
#define FAMILY_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QFrame>
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
private:
    typedef enum status
    {
        SUCCESS
        ,FAIL
        ,INFORMATION

    } status_t;

    void setFrameAttributes(QFrame* frame, const QString name);
    void setButtonAttributes(QPushButton* button, const QString toolTip);
    void setMessage(const status_t status, const QString message);
    QFrame* getFrameHead();
    QFrame* getFrameList();
    QFrame* getFrameBottom();
    DbManager *db;

    //Head
    QPushButton *But_return;
    QPushButton *But_add;
    QPushButton *but_delete;

    //List
    QLabel *label;
    QLabel *LabMessage;
    QStandardItemModel *modeleFamily;
    QTableView *table;

    //bottom
    QLineEdit *Li_name;
    QLineEdit *Li_ID;
    QPushButton *But_valid;
    QPushButton *But_cancel;

public:
    explicit FamilyPage(QWidget *parent = nullptr);
    ~FamilyPage();
    void setLayoutWindow(QWidget *view);

signals:
    void loadPageParent(const Tools_LDDS::windowsName_t);

public slots:
    void emitLoadMAIN_PAGE();
    void addFamily();
    void deleteFamily();
    void validFamily();
    void cancelFamily();
    void rowSelected(const QItemSelection&, const QItemSelection&);
};

#endif // FAMILY_HPP

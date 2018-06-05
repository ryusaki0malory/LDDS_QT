#ifndef MAINPAGE_HPP
#define MAINPAGE_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include "tools.hpp"
#include "dbhandler.hpp"

class MainPage : public QWidget
{
     Q_OBJECT

public:
    explicit MainPage(DbHandler &newDb, QWidget *parent = nullptr);
    ~MainPage();
    void setLayoutWindow(); // init main layout

private:
    void setButtonAttributes(QPushButton* button, const QString toolTip);
    void setGroupBoxAttributes();
    void createFrameArtickes();
    void createFrameProducts();
    void createFrameCustomers();
    void createFrameSales();
    void createFrameGestion();
    void setLogo();

    QGroupBox *articleGroupBox;
    QGroupBox *productGroupBox;
    QGroupBox *customersGroupBox;
    QGroupBox *salesGroupBox;
    QGroupBox *gestionGroupBox;

    QLabel *_logo;
    DbHandler &db;

signals:
    void loadPageParent(const Tools_LDDS::windowsName_t);

public slots:
    void emitLoadRETAILLER_PAGE();
    void emitLoadFAMILY_PAGE();
    void emitLoadARTICLE_PAGE();
    void emitLoadBASE_PAGE();
    void emitLoadTYPE_ARTICLES_PAGE();
    void emitLoadPRODUCT_PAGE();
    void emitLoadPRODUCTION_PAGE();
    void emitLoadPAYMENT_PAGE();
    void emitLoadSALE_PAGE();
    void emitLoadBILL_PAGE();
    void emitLoadCUSTOMER_PAGE();
    void emitLoadPARAMETER_PAGE();
    void emitLoadSTOCK_PAGE();
    void emitLoadACCOUNT_PAGE();
};

#endif // MAINPAGE_HPP

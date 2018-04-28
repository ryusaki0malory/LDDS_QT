#ifndef MAINPAGE_HPP
#define MAINPAGE_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include "tools.hpp"

class MainPage : public QWidget
{
     Q_OBJECT
private:
    QLayout* getLayoutWindow(QWidget *view);
    void setButtonAttributes(QPushButton* button, const QString toolTip);
    void setFrameAttributes(QFrame* frame, const QString name);
    QFrame* getFrameArtickes();
    QFrame* getFrameProducts();
    QFrame* getFrameCustomers();
    QFrame* getFrameSales();
    QFrame* getFrameGestion();

    QLabel *_logo;

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();

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
    void defineLogo();
};

#endif // MAINPAGE_HPP

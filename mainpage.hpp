#ifndef MAINPAGE_HPP
#define MAINPAGE_HPP

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include "tools.hpp"

class MainPage : public QWidget
{
     Q_OBJECT
private:
    QLayout* getLayoutWindow(QWidget *view);
    QPushButton* setButtonAttributes(QPushButton* button, const QString toolTip);

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
    void emitLoadSELL_PAGE();
    void emitLoadBILL_PAGE();
    void emitLoadCLIENT_PAGE();
    void emitLoadPARAMETER_PAGE();
    void emitLoadSTOCK_PAGE();
    void emitLoadACCOUNT_PAGE();
};

#endif // MAINPAGE_HPP

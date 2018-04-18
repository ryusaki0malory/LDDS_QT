#include "mainPage.hpp"

MainPage::MainPage(QWidget *parent) : QWidget(parent)
{

    setLayout(getLayoutWindow(parent));
}

 MainPage::~MainPage()
 {

 }

 QPushButton*    MainPage::setButtonAttributes(QPushButton* button, const QString toolTip = "")
 {
    button->setToolTip(toolTip);
    button->setFont(QFont("Times", 18, QFont::Bold));

    return (button);
 }

 QLayout* MainPage::getLayoutWindow(QWidget *parent)
 {
     QGridLayout *gridLayout = new QGridLayout(parent);

     QPushButton *retaillers = new QPushButton("Retaillers");
     retaillers = setButtonAttributes(retaillers, "Gestion of retaillers");
     connect(retaillers, SIGNAL(clicked()), this, SLOT(emitLoadRETAILLER_PAGE()));
     gridLayout->addWidget(retaillers, 0, 0);

     QPushButton *family = new QPushButton("Family");
     family = setButtonAttributes(family,"Gestion of families");
     connect(family, SIGNAL(clicked()), this, SLOT(emitLoadFAMILY_PAGE()));
     gridLayout->addWidget(family, 0, 1);

     QPushButton *article = new QPushButton("Articles");
     article = setButtonAttributes(article,"Gestion of articles");
     connect(article, SIGNAL(clicked()), this, SLOT(emitLoadARTICLE_PAGE()));
     gridLayout->addWidget(article, 0, 2);

     QPushButton *baseProducts = new QPushButton("Bases of product");
     baseProducts = setButtonAttributes(baseProducts,"Gestion of bases unit");
     connect(baseProducts, SIGNAL(clicked()), this, SLOT(emitLoadBASE_PAGE()));
     gridLayout->addWidget(baseProducts, 1, 0);
     return(gridLayout);

     QPushButton *articlesType = new QPushButton("Types of article");
     articlesType = setButtonAttributes(articlesType,"Gestion of articles type");
     connect(articlesType, SIGNAL(clicked()), this, SLOT(emitLoadTYPE_ARTICLES_PAGE()));
     gridLayout->addWidget(articlesType, 1, 1);

     QPushButton *products = new QPushButton("Products");
     products = setButtonAttributes(products, "Gestion of Products");
     connect(products, SIGNAL(clicked()), this, SLOT(emitLoadPRODUCT_PAGE()));
     gridLayout->addWidget(products, 1, 2);

     QPushButton *production = new QPushButton("Production");
     production = setButtonAttributes(production,"Gestion of Products");
     connect(production, SIGNAL(clicked()), this, SLOT(emitLoadPRODUCTION_PAGE()));
     gridLayout->addWidget(production, 2, 0);

     gridLayout->setSizeConstraint(QLayout::SetFixedSize);
     return(gridLayout);
 }

 //SLOTS
 void MainPage::emitLoadRETAILLER_PAGE()
 {
    emit loadPageParent(Tools_LDDS::RETAILLER_PAGE);
 }
 void MainPage::emitLoadFAMILY_PAGE()
 {
    emit loadPageParent(Tools_LDDS::FAMILY_PAGE);
 }
 void MainPage::emitLoadARTICLE_PAGE()
 {
    emit loadPageParent(Tools_LDDS::ARTICLE_PAGE);
 }
 void MainPage::emitLoadBASE_PAGE()
 {
    emit loadPageParent(Tools_LDDS::BASE_PAGE);
 }
 void MainPage::emitLoadTYPE_ARTICLES_PAGE()
 {
    emit loadPageParent(Tools_LDDS::TYPE_ARTICLES_PAGE);
 }
 void MainPage::emitLoadPRODUCT_PAGE()
 {
    emit loadPageParent(Tools_LDDS::PRODUCT_PAGE);
 }
 void MainPage::emitLoadPRODUCTION_PAGE()
 {
    emit loadPageParent(Tools_LDDS::PRODUCTION_PAGE);
 }
 void MainPage::emitLoadPAYMENT_PAGE()
 {
    emit loadPageParent(Tools_LDDS::PAYMENT_PAGE);
 }
 void MainPage::emitLoadSELL_PAGE()
 {
    emit loadPageParent(Tools_LDDS::SELL_PAGE);
 }
 void MainPage::emitLoadBILL_PAGE()
 {
    emit loadPageParent(Tools_LDDS::BILL_PAGE);
 }
 void MainPage::emitLoadCLIENT_PAGE()
 {
    emit loadPageParent(Tools_LDDS::CLIENT_PAGE);
 }
 void MainPage::emitLoadPARAMETER_PAGE()
 {
    emit loadPageParent(Tools_LDDS::PARAMETER_PAGE);
 }
 void MainPage::emitLoadSTOCK_PAGE()
 {
    emit loadPageParent(Tools_LDDS::STOCK_PAGE);
 }
 void MainPage::emitLoadACCOUNT_PAGE()
 {
    emit loadPageParent(Tools_LDDS::ACCOUNT_PAGE);
 }

#include "mainPage.hpp"

MainPage::MainPage(QWidget *parent) : QWidget(parent)
{

    setLayout(getLayoutWindow(parent));
}

 MainPage::~MainPage()
 {

 }

 void   MainPage::setFrameAttributes(QFrame* frame, const QString name = "")
 {
     frame->setObjectName(name);
     frame->setStyleSheet("#"+name+" { border: 2px solid pink; }");
     frame->setFrameShape(QFrame::StyledPanel);

 }

 void    MainPage::setButtonAttributes(QPushButton* button, const QString toolTip = "")
 {
    button->setToolTip(toolTip);
    button->setFont(QFont("Times", 18, QFont::Bold));
 }


 QFrame* MainPage::getFrameProducts()
 {
     QFrame *frameProducts = new QFrame(this);
     this->setFrameAttributes(frameProducts, "Products");
     QGridLayout *LayoutProducts = new QGridLayout(frameProducts);

     QPushButton *products = new QPushButton("Products", frameProducts);
     this->setButtonAttributes(products, "Gestion of Products");
     connect(products, SIGNAL(clicked()), this, SLOT(emitLoadPRODUCT_PAGE()));
     LayoutProducts->addWidget(products, 0, 0);

     QPushButton *production = new QPushButton("Production", frameProducts);
     this->setButtonAttributes(production,"Gestion of Products");
     connect(production, SIGNAL(clicked()), this, SLOT(emitLoadPRODUCTION_PAGE()));
     LayoutProducts->addWidget(production, 0, 1);

     frameProducts->setLayout(LayoutProducts);
     return (frameProducts);
 }

 QFrame* MainPage::getFrameGestion()
 {
     QFrame *frameGestion = new QFrame(this);
     this->setFrameAttributes(frameGestion, "Gestion");
     QGridLayout *LayoutGestion = new QGridLayout(frameGestion);

     QPushButton *stocks = new QPushButton("Stocks", frameGestion);
     this->setButtonAttributes(stocks,"Gestion of stocks");
     connect(stocks, SIGNAL(clicked()), this, SLOT(emitLoadSTOCK_PAGE()));
     LayoutGestion->addWidget(stocks, 0, 0);

     QPushButton *account = new QPushButton("Account", frameGestion);
     this->setButtonAttributes(account,"Gestion of account");
     connect(account, SIGNAL(clicked()), this, SLOT(emitLoadSTOCK_PAGE()));
     LayoutGestion->addWidget(account, 0, 1);

     QPushButton *parameters = new QPushButton("Parameters", frameGestion);
     this->setButtonAttributes(parameters,"Gestion of parameters");
     connect(parameters, SIGNAL(clicked()), this, SLOT(emitLoadPARAMETER_PAGE()));
     LayoutGestion->addWidget(parameters, 0, 2);

     frameGestion->setLayout(LayoutGestion);
     return (frameGestion);
 }

 QFrame* MainPage::getFrameSales()
 {
     QFrame *frameSales = new QFrame(this);
     this->setFrameAttributes(frameSales, "Sales");
     QGridLayout *LayoutSales = new QGridLayout(frameSales);

     QPushButton *sales = new QPushButton("Sales", frameSales);
     this->setButtonAttributes(sales,"Gestion of sales");
     connect(sales, SIGNAL(clicked()), this, SLOT(emitLoadSALE_PAGE()));
     LayoutSales->addWidget(sales, 0, 0);

     QPushButton *bills = new QPushButton("Bills", frameSales);
     this->setButtonAttributes(bills,"Gestion of bills");
     connect(bills, SIGNAL(clicked()), this, SLOT(emitLoadBILL_PAGE()));
     LayoutSales->addWidget(bills, 0, 1);

     frameSales->setLayout(LayoutSales);
     return (frameSales);
 }

 QFrame* MainPage::getFrameCustomers()
 {
     QFrame *frameCustomers = new QFrame(this);
     this->setFrameAttributes(frameCustomers, "Customers");
     QGridLayout *LayoutCustomers = new QGridLayout(frameCustomers);

     QPushButton *customers = new QPushButton("Customers", frameCustomers);
     this->setButtonAttributes(customers,"Gestion of customers");
     connect(customers, SIGNAL(clicked()), this, SLOT(emitLoadCUSTOMER_PAGE()));
     LayoutCustomers->addWidget(customers, 0, 0);

     QPushButton *payment = new QPushButton("Payment method", frameCustomers);
     this->setButtonAttributes(payment,"Gestion of payment method");
     connect(payment, SIGNAL(clicked()), this, SLOT(emitLoadPAYMENT_PAGE()));
     LayoutCustomers->addWidget(payment, 0, 1);

     frameCustomers->setLayout(LayoutCustomers);
     return (frameCustomers);
 }

 QFrame* MainPage::getFrameArtickes()
 {
     QFrame *frameArticles = new QFrame(this);
     this->setFrameAttributes(frameArticles, "Articles");
     QGridLayout *LayoutArticles = new QGridLayout(frameArticles);

     //buttons
     QPushButton *retaillers = new QPushButton("Retaillers", frameArticles);
     this->setButtonAttributes(retaillers, "Gestion of retaillers");
     connect(retaillers, SIGNAL(clicked()), this, SLOT(emitLoadRETAILLER_PAGE()));
     LayoutArticles->addWidget(retaillers, 0, 0);

     QPushButton *family = new QPushButton("Family", frameArticles);
     this->setButtonAttributes(family,"Gestion of families");
     connect(family, SIGNAL(clicked()), this, SLOT(emitLoadFAMILY_PAGE()));
     LayoutArticles->addWidget(family, 0 ,1);

     QPushButton *article = new QPushButton("Articles", frameArticles);
     this->setButtonAttributes(article,"Gestion of articles");
     connect(article, SIGNAL(clicked()), this, SLOT(emitLoadARTICLE_PAGE()));
     LayoutArticles->addWidget(article, 1, 0);

     QPushButton *articlesType = new QPushButton("Types of article", frameArticles);
     this->setButtonAttributes(articlesType,"Gestion of articles type");
     connect(articlesType, SIGNAL(clicked()), this, SLOT(emitLoadTYPE_ARTICLES_PAGE()));
     LayoutArticles->addWidget(articlesType, 1, 1);

     QPushButton *baseProducts = new QPushButton("Bases of product", frameArticles);
     this->setButtonAttributes(baseProducts,"Gestion of bases unit");
     connect(baseProducts, SIGNAL(clicked()), this, SLOT(emitLoadBASE_PAGE()));
     LayoutArticles->addWidget(baseProducts, 2, 0);

     QPushButton *changeLogo = new QPushButton("Change logo", frameArticles);
     this->setButtonAttributes(changeLogo,"Change the logo");
     connect(changeLogo, SIGNAL(clicked()), this, SLOT(defineLogo()));
     LayoutArticles->addWidget(changeLogo, 2, 1);

     //logo
     this->_logo = new QLabel(frameArticles);
     LayoutArticles->addWidget(this->_logo, 0, 3, 3, 3);


     frameArticles->setLayout(LayoutArticles);
     return (frameArticles);
 }

 QLayout* MainPage::getLayoutWindow(QWidget *parent)
 {
     QVBoxLayout *mainLayout = new QVBoxLayout(parent);
     mainLayout->addWidget(getFrameArtickes());
     mainLayout->addWidget(getFrameProducts());
     mainLayout->addWidget(getFrameCustomers());
     mainLayout->addWidget(getFrameSales());
     mainLayout->addWidget(getFrameGestion());
     return(mainLayout);
 }

 //SLOTS
 void MainPage::defineLogo()
 {
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose new logo"),"", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if (QString::compare(filename, QString()) != 0)
    {
        QImage image;
        bool valid = image.load(filename);

        if (valid)
        {
            image = image.scaledToWidth(this->_logo->width(), Qt::SmoothTransformation);
            this->_logo->setPixmap(QPixmap::fromImage(image));
        }
    }
 }
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
 void MainPage::emitLoadSALE_PAGE()
 {
    emit loadPageParent(Tools_LDDS::SALE_PAGE);
 }
 void MainPage::emitLoadBILL_PAGE()
 {
    emit loadPageParent(Tools_LDDS::BILL_PAGE);
 }
 void MainPage::emitLoadCUSTOMER_PAGE()
 {
    emit loadPageParent(Tools_LDDS::CUSTOMER_PAGE);
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

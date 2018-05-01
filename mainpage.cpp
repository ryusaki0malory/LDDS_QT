#include "mainpage.hpp"

MainPage::MainPage(DbManager &newDb, QWidget *parent) : QWidget(parent), db(newDb)
{

}

 MainPage::~MainPage()
 {

 }

 void   MainPage:: setGroupBoxAttributes(QGroupBox* groupBox, const QString name = "")
 {
     groupBox->setObjectName(name);
     groupBox->setStyleSheet("#"+name+" { border: 2px solid pink; }");
 }

 void    MainPage::setButtonAttributes(QPushButton* button, const QString toolTip = "")
 {
    button->setToolTip(toolTip);
    button->setFont(QFont("Times", 18, QFont::Bold));
 }

 void MainPage::setLogo()
 {
    QString path = this->db.getPathLogo();
    if (QString::compare(path,QString()) != 0)
    {
        QImage image;
        bool valid = image.load(path);

        if (valid)
        {
            //image = image.scaledToWidth(this->_logo->width(), Qt::SmoothTransformation);
            this->_logo->setPixmap(QPixmap::fromImage(image));
        }
    }
 }

 //frame
 void MainPage::createFrameProducts()
 {
     this->productGroupBox = new QGroupBox(tr("Products"));
     this->setGroupBoxAttributes(productGroupBox, "Products");
     QGridLayout *LayoutProducts = new QGridLayout(productGroupBox);

     QPushButton *products = new QPushButton("Products");
     this->setButtonAttributes(products, "Gestion of Products");
     connect(products, SIGNAL(clicked()), this, SLOT(emitLoadPRODUCT_PAGE()));
     LayoutProducts->addWidget(products, 0, 0);

     QPushButton *production = new QPushButton("Production");
     this->setButtonAttributes(production,"Gestion of Products");
     connect(production, SIGNAL(clicked()), this, SLOT(emitLoadPRODUCTION_PAGE()));
     LayoutProducts->addWidget(production, 0, 1);

     this->productGroupBox->setLayout(LayoutProducts);

 }

 void MainPage::createFrameGestion()
 {
     this->gestionGroupBox = new QGroupBox(tr("Gestion"));
     this->setGroupBoxAttributes(gestionGroupBox, "Gestion");
     QGridLayout *LayoutGestion = new QGridLayout(gestionGroupBox);

     QPushButton *stocks = new QPushButton("Stocks");
     this->setButtonAttributes(stocks,"Gestion of stocks");
     connect(stocks, SIGNAL(clicked()), this, SLOT(emitLoadSTOCK_PAGE()));
     LayoutGestion->addWidget(stocks, 0, 0);

     QPushButton *account = new QPushButton("Account");
     this->setButtonAttributes(account,"Gestion of account");
     connect(account, SIGNAL(clicked()), this, SLOT(emitLoadSTOCK_PAGE()));
     LayoutGestion->addWidget(account, 0, 1);

     QPushButton *parameters = new QPushButton("Parameters");
     this->setButtonAttributes(parameters,"Gestion of parameters");
     connect(parameters, SIGNAL(clicked()), this, SLOT(emitLoadPARAMETER_PAGE()));
     LayoutGestion->addWidget(parameters, 0, 2);

      this->gestionGroupBox->setLayout(LayoutGestion);
 }

 void MainPage::createFrameSales()
 {
     this->salesGroupBox = new QGroupBox(tr("Sales"));
     this->setGroupBoxAttributes(salesGroupBox, "Sales");
     QGridLayout *LayoutSales = new QGridLayout(salesGroupBox);

     QPushButton *sales = new QPushButton("Sales");
     this->setButtonAttributes(sales,"Gestion of sales");
     connect(sales, SIGNAL(clicked()), this, SLOT(emitLoadSALE_PAGE()));
     LayoutSales->addWidget(sales, 0, 0);

     QPushButton *bills = new QPushButton("Bills");
     this->setButtonAttributes(bills,"Gestion of bills");
     connect(bills, SIGNAL(clicked()), this, SLOT(emitLoadBILL_PAGE()));
     LayoutSales->addWidget(bills, 0, 1);

      this->salesGroupBox->setLayout(LayoutSales);
 }

 void MainPage::createFrameCustomers()
 {
     this->customersGroupBox = new QGroupBox(tr("Customers"));
     this->setGroupBoxAttributes(customersGroupBox, "Customers");
     QGridLayout *LayoutCustomers = new QGridLayout(customersGroupBox);

     QPushButton *customers = new QPushButton("Customers");
     this->setButtonAttributes(customers,"Gestion of customers");
     connect(customers, SIGNAL(clicked()), this, SLOT(emitLoadCUSTOMER_PAGE()));
     LayoutCustomers->addWidget(customers, 0, 0);

     QPushButton *payment = new QPushButton("Payment method");
     this->setButtonAttributes(payment,"Gestion of payment method");
     connect(payment, SIGNAL(clicked()), this, SLOT(emitLoadPAYMENT_PAGE()));
     LayoutCustomers->addWidget(payment, 0, 1);

      this->customersGroupBox->setLayout(LayoutCustomers);
 }

 void MainPage::createFrameArtickes()
 {
     this->articleGroupBox = new QGroupBox(tr("Articles"));
     this->setGroupBoxAttributes(articleGroupBox, "Articles");

     QGridLayout *LayoutArticles = new QGridLayout(articleGroupBox);
     //buttons
     QPushButton *retaillers = new QPushButton("Retaillers");
     this->setButtonAttributes(retaillers, "Gestion of retaillers");
     connect(retaillers, SIGNAL(clicked()), this, SLOT(emitLoadRETAILLER_PAGE()));
     LayoutArticles->addWidget(retaillers, 0, 0);

     QPushButton *family = new QPushButton("Family");
     this->setButtonAttributes(family,"Gestion of families");
     connect(family, SIGNAL(clicked()), this, SLOT(emitLoadFAMILY_PAGE()));
     LayoutArticles->addWidget(family, 0 ,1);

     QPushButton *article = new QPushButton("Articles");
     this->setButtonAttributes(article,"Gestion of articles");
     connect(article, SIGNAL(clicked()), this, SLOT(emitLoadARTICLE_PAGE()));
     LayoutArticles->addWidget(article, 1, 0);

     QPushButton *articlesType = new QPushButton("Types of article");
     this->setButtonAttributes(articlesType,"Gestion of articles type");
     connect(articlesType, SIGNAL(clicked()), this, SLOT(emitLoadTYPE_ARTICLES_PAGE()));
     LayoutArticles->addWidget(articlesType, 1, 1);

     QPushButton *baseProducts = new QPushButton("Bases of product");
     this->setButtonAttributes(baseProducts,"Gestion of bases unit");
     connect(baseProducts, SIGNAL(clicked()), this, SLOT(emitLoadBASE_PAGE()));
     LayoutArticles->addWidget(baseProducts, 2, 0);

     QPushButton *changeLogo = new QPushButton("Change logo");
     this->setButtonAttributes(changeLogo,"Change the logo");
     connect(changeLogo, SIGNAL(clicked()), this, SLOT(defineLogo()));
     LayoutArticles->addWidget(changeLogo, 2, 1);

     //logo
     this->_logo = new QLabel();
     LayoutArticles->addWidget(this->_logo, 0, 3, 3, 3);
     this->setLogo();

     this->articleGroupBox->setLayout(LayoutArticles);
 }

 void MainPage::setLayoutWindow()
 {
     QVBoxLayout *mainLayout = new QVBoxLayout();
     this->createFrameArtickes();
     mainLayout->addWidget(this->articleGroupBox);
     this->createFrameProducts();
     mainLayout->addWidget(this->productGroupBox);
     this->createFrameCustomers();
     mainLayout->addWidget(this->customersGroupBox);
     this->createFrameSales();
     mainLayout->addWidget(this->salesGroupBox);
     this->createFrameGestion();
     mainLayout->addWidget(this->gestionGroupBox);
     setLayout(mainLayout);
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

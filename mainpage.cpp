#include "mainpage.hpp"

MainPage::MainPage()
{

}

 MainPage::~MainPage()
 {

 }

 template<class T>
 QLayout* MainPage::getLayoutWindow(T view)
 {

     QGridLayout *gridLayout = new QGridLayout;

     QPushButton *article = new QPushButton("Articles");
     article->setFont(QFont("Times", 18, QFont::Bold));
    // connect(article, SIGNAL(clicked()), this->_view, SLOT(quit()));
     gridLayout->addWidget(article, 0, 0);

     QPushButton *retaillers = new QPushButton("Retaillers");
     article->setFont(QFont("Times", 18, QFont::Bold));
     gridLayout->addWidget(retaillers, 0, 1);

     QPushButton *familly = new QPushButton("Familly");
     article->setFont(QFont("Times", 18, QFont::Bold));
     gridLayout->addWidget(familly, 1, 0);

     QPushButton *baseProducts = new QPushButton("Base of products");
     article->setFont(QFont("Times", 18, QFont::Bold));
     gridLayout->addWidget(baseProducts, 1, 1);

     return(gridLayout);
 };

#include "parameterPage.hpp"

ParameterPage::ParameterPage(DbHandler &newDb, QWidget *parent) : QWidget(parent), db(newDb)
{

}

ParameterPage::~ParameterPage()
{

}

void ParameterPage::setLayoutWindow()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->createFrameParameters();
    mainLayout->addWidget(this->parameterGroupBox);
    setLayout(mainLayout);
}

//setAttibutes

void   ParameterPage:: setGroupBoxAttributes()
{
    this->setStyleSheet("QGroupBox {background-color: white; border-style: outset; border-width: 2px; border-color: beige; font: bold 14px;border: 2px solid white; border-bottom: 2px solid pink; }");
}

void    ParameterPage::setButtonAttributes(QPushButton* button, const QString toolTip = "")
{
   button->setToolTip(toolTip);
   button->setFont(QFont("Times", 18, QFont::Bold));
   button->setStyleSheet("QPushButton {background-color: white; border-width: 1px; border-color: grey; font: bold 14px;padding: 25px; }");
}

//Frames

void ParameterPage::createFrameParameters()
{
    this->parameterGroupBox = new QGroupBox(tr("Parameter"));
    QVBoxLayout *LayoutParameters = new QVBoxLayout(parameterGroupBox);

    QPushButton *But_return = new QPushButton("Return");
    this->setButtonAttributes(But_return, "Return to menu");
    connect(But_return, SIGNAL(clicked()), this, SLOT(emitLoadMAIN_PAGE()));
    LayoutParameters->addWidget(But_return);

    QPushButton *First_Init = new QPushButton("First initialisation");
    this->setButtonAttributes(First_Init,"First initialisation of the application");
    connect(First_Init, SIGNAL(clicked()), this, SLOT(firstInit()));
    LayoutParameters->addWidget(First_Init);

    QPushButton *Change_Logo = new QPushButton("Change logo");
    this->setButtonAttributes(Change_Logo,"Change the logo of main page");
    connect(Change_Logo, SIGNAL(clicked()), this, SLOT(changeLogo()));
    LayoutParameters->addWidget(Change_Logo);

    this->parameterGroupBox->setLayout(LayoutParameters);

}

//SLOTS
void ParameterPage::emitLoadMAIN_PAGE()
{
   emit loadPageParent(Tools_LDDS::MAIN_PAGE);
}

void ParameterPage::firstInit()
{

}

void ParameterPage::changeLogo()
{

}

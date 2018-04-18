#include "familyPage.hpp"

FamilyPage::FamilyPage(QWidget *parent) : QWidget(parent)
{
    setLayout(getLayoutWindow(parent));
}

QLayout* FamilyPage::getLayoutWindow(QWidget *parent)
{

    QGridLayout *gridLayout = new QGridLayout(parent);

    QPushButton *retaillers = new QPushButton("Retaillers");
    connect(retaillers, SIGNAL(clicked()), this, SLOT(emitLoadMAIN_PAGE()));
    gridLayout->addWidget(retaillers, 0, 0);

    return(gridLayout);
}

//SLOTS
void FamilyPage::emitLoadMAIN_PAGE()
{
   emit loadPageParent(Tools_LDDS::MAIN_PAGE);
}

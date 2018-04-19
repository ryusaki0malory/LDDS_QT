#include "familyPage.hpp"

FamilyPage::FamilyPage(QWidget *parent) : QWidget(parent)
{
}

void FamilyPage::setLayoutWindow(QWidget *parent)
{

    QGridLayout *gridLayout = new QGridLayout(parent);

    QPushButton *retaillers = new QPushButton("Retaillers");
    connect(retaillers, SIGNAL(clicked()), this, SLOT(emitLoadMAIN_PAGE()));
    gridLayout->addWidget(retaillers, 0, 0);

    setLayout(gridLayout);
}

//SLOTS
void FamilyPage::emitLoadMAIN_PAGE()
{
   emit loadPageParent(Tools_LDDS::MAIN_PAGE);
}

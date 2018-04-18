#include "view.hpp"
#include <iostream>

View::View()
{
    this->resize(800, 800);
    QString windowTitle = "LDDS project. Vers: " + static_cast<QString>(VERSION);
    this->setWindowTitle(windowTitle);
    this->_window.mainpage = 0;
    this->loadPage(Tools_LDDS::MAIN_PAGE);
}

View::~View()
{

};

bool View::loadPage(const Tools_LDDS::windowsName_t name)
{
    switch(name)
    {
        case Tools_LDDS::MAIN_PAGE:
            this->_window.mainpage = new MainPage(this);
            connect(this->_window.mainpage, SIGNAL(loadPageParent(const Tools_LDDS::windowsName_t)), this, SLOT(changePage(const Tools_LDDS::windowsName_t)));
            setCentralWidget(this->_window.mainpage);
            break;
        case Tools_LDDS::FAMILY_PAGE:
            this->_window.familyPage = new FamilyPage(this);
            connect(this->_window.familyPage, SIGNAL(loadPageParent(const Tools_LDDS::windowsName_t)), this, SLOT(changePage(const Tools_LDDS::windowsName_t)));
            setCentralWidget(this->_window.familyPage);
            break;
         case Tools_LDDS::ARTICLE_PAGE:
            std::cout << Tools_LDDS::ARTICLE_PAGE;
            break;
        case Tools_LDDS::BASE_PAGE:
            break;
    }
    return (true);
}

void View::changePage(const Tools_LDDS::windowsName_t name)
{
    loadPage(name);
}

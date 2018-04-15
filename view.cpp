#include "view.hpp"
#include <iostream>

View::View(QWidget *parent) : QWidget(parent)
{
    this->resize(800, 800);
    QString windowTitle = "LDDS project. Vers: " + static_cast<QString>(VERSION);
    this->setWindowTitle(windowTitle);
    this->_mainLayout = 0;
    this->_window.mainpage = 0;
    this->loadPage(MAIN_PAGE);
}

View::~View()
{
    this->freeView();
};

bool View::loadPage(const windowsName_t name)
{
    //this->freeView(true);
    switch(name)
    {
        case MAIN_PAGE:
            this->_window.mainpage = new MainPage();
            this->_mainLayout = this->_window.mainpage->getLayoutWindow<>(2);
            break;
        case RETAILLER_PAGE:
             std::cout << RETAILLER_PAGE;
            break;
        case FAMILY_PAGE:
             std::cout << FAMILY_PAGE;
            break;
         case ARTICLE_PAGE:
             std::cout << ARTICLE_PAGE;
            break;
        case BASE_PAGE:
            break;
    }
    if (this->_mainLayout != 0)
    {
        setLayout(this->_mainLayout);
    }
    return(true);
}

void View::freeView(const bool onlyWindow)
{
    if (onlyWindow == false)
    {
        if (this->_mainLayout != 0)
        {
            delete(this->_mainLayout);
        }
        this->_window.mainpage = 0;
    }
    //if (this->_window.mainpage != 0)
    //{
    //    delete(this->_window.mainpage);
    //}
    //this->_mainLayout = 0;
}

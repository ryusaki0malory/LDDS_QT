#include "view.hpp"

View::View(DbManager &newDb) : db(newDb)
{
    this->resize(600, 800);
    QString windowTitle = "LDDS project. Vers: " + static_cast<QString>(VERSION);
    this->setWindowTitle(windowTitle);
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
            this->_window.mainpage = new MainPage(db, this);
            connect(this->_window.mainpage, SIGNAL(loadPageParent(const Tools_LDDS::windowsName_t)), this, SLOT(changePage(const Tools_LDDS::windowsName_t)));
            setCentralWidget(this->_window.mainpage);
            this->_window.mainpage->setLayoutWindow();
            break;
        case Tools_LDDS::FAMILY_PAGE:
            this->_window.familyPage = new FamilyPage(db, this);
            connect(this->_window.familyPage, SIGNAL(loadPageParent(const Tools_LDDS::windowsName_t)), this, SLOT(changePage(const Tools_LDDS::windowsName_t)));
            setCentralWidget(this->_window.familyPage);
            this->_window.familyPage->setLayoutWindow();
            break;
         case Tools_LDDS::RETAILLER_PAGE:
            this->_window.retaillerPage = new RetaillerPage(db, this);
            connect(this->_window.familyPage, SIGNAL(loadPageParent(const Tools_LDDS::windowsName_t)), this, SLOT(changePage(const Tools_LDDS::windowsName_t)));
            setCentralWidget(this->_window.retaillerPage);
            this->_window.retaillerPage->setLayoutWindow();
            break;
        case Tools_LDDS::TYPE_ARTICLES_PAGE:
            this->_window.typeArticlesPage = new TypeArticlesPage(db, this);
            connect(this->_window.typeArticlesPage, SIGNAL(loadPageParent(const Tools_LDDS::windowsName_t)), this, SLOT(changePage(const Tools_LDDS::windowsName_t)));
            setCentralWidget(this->_window.typeArticlesPage);
            this->_window.typeArticlesPage->setLayoutWindow();
            break;
        case Tools_LDDS::BASE_PAGE:
            this->_window.baseunitPage = new BaseUnitPage(db, this);
            connect(this->_window.baseunitPage, SIGNAL(loadPageParent(const Tools_LDDS::windowsName_t)), this, SLOT(changePage(const Tools_LDDS::windowsName_t)));
            setCentralWidget(this->_window.baseunitPage);
            this->_window.baseunitPage->setLayoutWindow();
            break;
    }
    return (true);
}

void View::changePage(const Tools_LDDS::windowsName_t name)
{
    loadPage(name);
}

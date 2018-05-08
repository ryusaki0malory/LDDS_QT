#ifndef VIEW_HPP
#define VIEW_HPP

#include <QMainWindow>
#include <QLabel>
#include "mainPage.hpp"
#include "familyPage.hpp"
#include "retaillerPage.hpp"
#include "typeArticlesPage.hpp"
#include "baseUnitPage.hpp"
#include "paymentMethodPage.hpp"
#include "customerPage.hpp"
#include "articlePage.hpp"
#include "dbhandler.hpp"
#include "tools.hpp"

class View : public QMainWindow
{
    Q_OBJECT

public:
    explicit View(DbHandler&);
    ~View();

private:
    typedef union windows //Error of conception constructors cannot be called...My mistake
    {
        MainPage *mainpage;
        FamilyPage *familyPage;
        RetaillerPage *retaillerPage;
        TypeArticlesPage *typeArticlesPage;
        BaseUnitPage *baseunitPage;
        PaymentMethodPage *paymentMethodPage;
        CustomerPage *customerPage;
        ArticlePage *articlePage;
    }windows_t;
    windows_t _window; // enum of windows or page
    bool    loadPage(const Tools_LDDS::windowsName_t);// load the visual of this View
    DbHandler &db;

public slots:
    void changePage(const Tools_LDDS::windowsName_t);
};

#endif // VIEW_HPP

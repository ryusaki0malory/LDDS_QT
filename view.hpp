#ifndef VIEW_HPP
#define VIEW_HPP

#include <QWidget>
#include "mainpage.hpp"

typedef enum windowsName
{
    MAIN_PAGE
    ,RETAILLER_PAGE
    ,FAMILY_PAGE
    ,ARTICLE_PAGE
    ,BASE_PAGE
 } windowsName_t;

typedef union windows
{
    MainPage *mainpage;
}windows_t;

class View : public QWidget
{
private:
    windows_t _window; // enum of windows
    QLayout *_mainLayout; //the layout of this View
    void    freeView(const bool onlyWindow = false); //Clean all pointers or only the enum of windows


public:
    explicit View(QWidget *parent = nullptr);
    ~View();
    bool    loadPage(const windowsName_t);// load the visual of this View

};

#endif // VIEW_HPP

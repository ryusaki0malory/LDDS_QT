#ifndef VIEW_HPP
#define VIEW_HPP

#include <QMainWindow>
#include <QLabel>
#include "mainPage.hpp"
#include "familyPage.hpp"
#include "tools.hpp"

class View : public QMainWindow
{
    Q_OBJECT
    typedef union windows
    {
        MainPage *mainpage;
        FamilyPage *familyPage;
    }windows_t;

private:
    windows_t _window; // enum of windows

public:
    explicit View();
    ~View();
    bool    loadPage(const Tools_LDDS::windowsName_t);// load the visual of this View


public slots:
    void changePage(const Tools_LDDS::windowsName_t);
};

#endif // VIEW_HPP

#ifndef MAINPAGE_HPP
#define MAINPAGE_HPP

#include <QObject>
#include "windows.hpp"

class MainPage : public QObject, public Windows
{
    Q_OBJECT

private:

public:
    MainPage();
    ~MainPage();
    template<class T>
    QLayout* getLayoutWindow(T);

signals:

public slots:

};

#endif // MAINPAGE_HPP

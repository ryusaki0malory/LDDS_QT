#include <QApplication>
#include "view.hpp"
#include "dbmanager.hpp"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View mainView;
    mainView.show();

    return a.exec();
}

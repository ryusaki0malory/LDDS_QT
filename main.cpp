#include <QApplication>
#include "view.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View mainView;
    mainView.show();

    return a.exec();
}

#include <QApplication>
#include "view.hpp"
#include <QDebug>
#include "dbhandler.hpp"

bool init();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DbHandler db;
    if (!db.init("/Users/ryusaki0malory/Desktop/"))
    {
        QMessageBox::information(0, "error", "Initialisation impossible!\nPlease check your LDDS.ini");
        return a.exec();
    }
    View mainView(db);
    mainView.show();

    return a.exec();
}

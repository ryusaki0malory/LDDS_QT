#include <QApplication>
#include "view.hpp"
#include <QDebug>
#include "dbhandler.hpp"

bool init();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DbHandler db;
    //"/Users/ryusaki0malory/Desktop/")
    if (!db.init(qApp->applicationDirPath()))
    {
        qDebug() << qApp->applicationDirPath();
        QMessageBox::information(0, "error", "First initialisation required!\nPlease check Parameter->First init.\nOr your LDDS.ini");
    }
    View mainView(db);
    mainView.show();

    return a.exec();
}

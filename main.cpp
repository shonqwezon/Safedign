#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("SafeDign Inc.");
    QCoreApplication::setApplicationName("Safedign");

    QApplication a(argc, argv);
    MainWindow w;
    w.readPositionSettings();
    w.setWindowTitle("Safedign");
    //w.show();
    //w.hide();
    return a.exec();
}

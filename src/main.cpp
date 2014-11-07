#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "cxd_license.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    QStringList args = QCoreApplication::arguments();

    if (args.size() >= 2) w.setLineEdit(1, args.at(1));
    if (args.size() >= 3) w.setLineEdit(2, args.at(2));

    w.show();

    return a.exec();
}

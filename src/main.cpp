/* @file main.cpp
 *
 * @brief C++ Main
 *
 * @author Craig Dawson <Craig.Dawson@gmail.com>
 * @date 2014-11-14
 *
 */

#include "cxd_license.h"

#include "mainwindow.h"
#include <QApplication>
#include <iostream>

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

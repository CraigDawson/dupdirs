/* @file mainwindow.h
 *
 * @brief Qt main window header
 *
 * @author Craig Dawson <Craig.Dawson@gmail.com>
 * @date 2014-11-14
 *
 */

#pragma once

#include "cxd_license.h"

#include <QMainWindow>
#include <QStatusBar>
#include <string>
#include <utility>

#include "dd_types.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void createStatusBar();
    ~MainWindow();

    void status(const std::string& s);

    void out(const std::string& a, const std::string& b);
    void out2(const std::string& a, const std::string& b);
    void outEnd(const std::pair<int, int>& p, const pair_vector& roots);

    void outLine(const std::string& a);

    void setLineEdit(int n, QString str);

private slots:
    void on_actionAbout_triggered();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_pushButton_Exit_clicked();

    void on_pushButton_Go_clicked();

private:
    Ui::MainWindow *ui;
};


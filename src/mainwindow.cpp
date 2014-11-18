/* @file mainwindow.cpp
 *
 * @brief Qt main window procedures
 *
 * @author Craig Dawson <Craig.Dawson@gmail.com>
 * @date 2014-11-14
 *
 */

#include "cxd_license.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QStatusBar>
#include <QTextBrowser>
#include <QFileDialog>
#include <QScrollBar>
#include "dupdir.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createStatusBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About"), tr("DupDirs V1.0\nQuickly checks if two paths (roots) are the same.\nSee README.pdf for details and license information."));
}

void MainWindow::createStatusBar()
{
   statusBar()->showMessage(tr("Ready"));
}

void MainWindow::on_pushButton_Exit_clicked()
{
    close();
}

void MainWindow::setLineEdit(int n, QString str)
{
    if (n == 1)
    {
        ui->lineEdit->clear();
        ui->lineEdit->insert(str);
    }
    else if (n == 2)
    {
        ui->lineEdit_2->clear();
        ui->lineEdit_2->insert(str);
    }
}

void MainWindow::on_toolButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 ".",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    setLineEdit(1, dir);
}

void MainWindow::on_toolButton_2_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 ".",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    setLineEdit(2, dir);
}

/// Go button routine
void MainWindow::on_pushButton_Go_clicked()
{
    status("Go");
    FILE_LOG << "Go -----------------------------------------------";

    DupDir dd(this);

    QDir d1(ui->lineEdit->text());
    QDir d2(ui->lineEdit_2->text());

    FILE_LOG << "abs path1: " << d1.absolutePath().toStdString();
    FILE_LOG << "abs path2: " << d2.absolutePath().toStdString();

    dd.getListOfDirs(d1.absolutePath().toStdString());
    dd.getListOfDirs(d2.absolutePath().toStdString());

    dd.buildHashList();

    status("Final Process. . . Please Wait");

    auto p = dd.compSums();
    outEnd(p, roots);

    ui->textBrowser->verticalScrollBar()->setValue(ui->textBrowser->verticalScrollBar()->maximum());

    status("Completed.");
}

void MainWindow::status(const std::string& s)
{
    statusBar()->showMessage(s.c_str());
}

///
/// Output abstraction functions
///
void MainWindow::out(const std::string& a, const std::string& b)
{
    ui->textBrowser->insertHtml("<b>Duplicates:</b><br>");
    ui->textBrowser->insertPlainText(a.c_str());
    ui->textBrowser->insertPlainText("\n");
    ui->textBrowser->insertPlainText(b.c_str());
    ui->textBrowser->insertPlainText("\n");
}

void MainWindow::out2(const std::string& a, const std::string& b)
{
    ui->textBrowser->insertHtml("<b>Duplicates in same root directory:</b><br>");
    ui->textBrowser->insertPlainText(a.c_str());
    ui->textBrowser->insertPlainText("\n");
    ui->textBrowser->insertPlainText(b.c_str());
    ui->textBrowser->insertPlainText("\n");
}

void MainWindow::outEnd(const std::pair<int, int>& p, const pair_vector& roots)
{
    QString dups =  QString::number(p.first);
    QString dirs =  QString::number(p.second);

    ui->textBrowser->insertHtml("<b>"
            + dups
            + " duplicate pairs of directories out of "
            + dirs
            + " directories.</b><br><br>");

    bool match  {true};
    int  i      {1};
    for (auto root : roots)
    {
        QString rname = QString::fromStdString(root.first);
        QString ndirs = QString::number(root.second);

        if (ndirs != dups) match = false;

        QString num = QChar('0' + i);
        ui->textBrowser->insertHtml("<b>Root" + num + ": "
                + rname
                + "   "
                + ndirs
                + " directories</b><br>");
        ++i;
    }

    if (match)
    {
        ui->textBrowser->insertHtml("<br><b>First and Second directories <font color=\"green\">MATCH</font></b>");
    }
    else
    {
        ui->textBrowser->insertHtml("<br><b>First and Second directories <font color=\"red\">DO NOT MATCH</font></b>");
    }
}

void MainWindow::outLine(const std::string& a)
{
    ui->textBrowser->insertHtml("<i>" + QString::fromStdString(a) + "</i><br>");
}


#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{ 
    ui->setupUi(this);
    ui->labelIsPwnd->setVisible(false);
    ui->labelIsPwnd->setStyleSheet("QLabel { color : red; }");
    connect(&hibp, &HaveIBeenPwned::sendPwnedResult, this, &MainWindow::processReply);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbIsPwnd_clicked()
{
    hibp.isPasswordPwned(ui->lineEditPwd->text());
}

void MainWindow::processReply(QString pwned)
{
    ui->labelIsPwnd->setVisible(true);
    ui->labelIsPwnd->setText(pwned);
}

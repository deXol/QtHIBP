#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{ 
    ui->setupUi(this);
    ui->labelIsPwnd->setVisible(false);
    connect(&hibp, &HaveIBeenPwned::sendPwnedNumber, this, &MainWindow::processPwnedPwd);
    connect(&hibp, &HaveIBeenPwned::sendSafePwd, this, &MainWindow::processSafePwd);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbIsPwnd_clicked()
{
    hibp.isPasswordPwned(ui->lineEditPwd->text());
}

void MainWindow::processPwnedPwd(int num)
{
    ui->labelIsPwnd->setVisible(true);
    ui->labelIsPwnd->setStyleSheet("QLabel { color : red; }");
    ui->labelIsPwnd->setText("Password has been pwned " + QString::number(num) + " times before!");
}

void MainWindow::processSafePwd()
{
    ui->labelIsPwnd->setVisible(true);
    ui->labelIsPwnd->setStyleSheet("QLabel { color : green; }");
    ui->labelIsPwnd->setText("Password is safe");
}

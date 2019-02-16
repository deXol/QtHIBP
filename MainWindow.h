#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "HaveIBeenPwned.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pbIsPwnd_clicked();
    void processReply(QString pwned);

private:
    Ui::MainWindow *ui;
    HaveIBeenPwned hibp;
};

#endif // MAINWINDOW_H

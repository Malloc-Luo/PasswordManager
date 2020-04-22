#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "signin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Login * login;
    Signin * signin;

public:
    void connect_slot();

public slots:
    void create_newuser();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

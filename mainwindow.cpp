#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->login = new Login;

    this->connect_slot();
    this->login->show();
}

MainWindow::~MainWindow()
{
    delete login;
    delete ui;
}

void MainWindow::connect_slot()
{
    connect(this->login, &Login::open_createuser_windows, this, &MainWindow::create_newuser);
}

void MainWindow::create_newuser()
{
    this->login->hide();

    Signin * signin = new Signin;

    if (signin->exec() == QDialog::Accepted)
    {
        this->login->show();
    }
    else
    {
        this->login->close();
    }
}


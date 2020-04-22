#include "mainwindow.h"
#include "login.h"
#include "signin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    Login f;
//    f.show();
    w.show();
//    Signin f;
//    f.show();
    return a.exec();
}

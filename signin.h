#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>

namespace Ui {
class Signin;
}

class Signin : public QDialog
{
    Q_OBJECT

public:
    explicit Signin(QWidget *parent = nullptr);
    ~Signin();

public:
    void setWidget();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_close_clicked();

    bool eventFilter(QObject * obj, QEvent * event);

    void check_info();

    void check_tip();

    void on_next_clicked();

private:
    Ui::Signin *ui;
};

#endif // SIGNIN_H

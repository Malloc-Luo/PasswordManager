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

    //处理窗口的移动
    void mouseMoveEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_close_clicked();

    bool eventFilter(QObject * obj, QEvent * event);

    void check_info();

    void check_tip();

    void on_next_clicked();

    void on_return_2_clicked();

private:
    bool m_press;
    QPoint m_pos;

private:
    Ui::Signin *ui;
};

#endif // SIGNIN_H

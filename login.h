#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QTimer>
#include <QPoint>
#include <QMouseEvent>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
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

    void check_input_finished();

private:
    QTimer * timer;

    unsigned trycnt;

    bool m_press;
    QPoint m_pos;

private:
    Ui::Login *ui;
};

#endif // LOGIN_H

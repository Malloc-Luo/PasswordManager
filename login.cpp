#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include <QIcon>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    this->setWidget();
}

Login::~Login()
{
    delete ui;
}

void Login::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void Login::setWidget()
{
//    this->setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags (Qt::SplashScreen);
    this->ui->password->raise();
    this->ui->pswdIcon->raise();
    this->ui->userIcon->raise();
    this->ui->username->raise();

    this->ui->LoginInbtn->setEnabled(false);   //初始状态“进入”不可用

    this->ui->password->installEventFilter(this);
    this->ui->username->installEventFilter(this);
    this->ui->username->setFocus();

    //检查输入是否已经规范完成
    connect(this->ui->username, &QLineEdit::editingFinished, this, &Login::check_input_finished);
    connect(this->ui->password, &QLineEdit::editingFinished, this, &Login::check_input_finished);
    connect(this->ui->username, &QLineEdit::cursorPositionChanged, this, &Login::check_input_finished);
    connect(this->ui->password, &QLineEdit::cursorPositionChanged, this, &Login::check_input_finished);

}

void Login::on_close_clicked()
{
    this->close();
}


bool Login::eventFilter(QObject * watched, QEvent * event)
{
    if (watched == this->ui->username)
    {
        if (event->type() == QEvent::FocusIn)
        {
            this->ui->userLine->setStyleSheet("QFrame{border-top: 2px solid rgb(0, 170, 255); background-color:transparent;}");
            this->ui->userIcon->setIcon(QIcon(":icon1/usernameBLUE"));
        }
        else if (event->type() == QEvent::FocusOut)
        {
            this->ui->userLine->setStyleSheet("QFrame{border-top: 2px solid white; background-color:transparent;}");
            this->ui->userIcon->setIcon(QIcon(":icon1/usernameWHITE"));
        }
    }

    if (watched == this->ui->password)
    {
        if (event->type() == QEvent::FocusIn)
        {
            this->ui->pawdLine->setStyleSheet("QFrame{border-top: 2px solid rgb(0, 170, 255); background-color:transparent;}");
            this->ui->pswdIcon->setIcon(QIcon(":icon1/pswdBLUE"));
        }
        else if (event->type() == QEvent::FocusOut)
        {
            this->ui->pawdLine->setStyleSheet("QFrame{border-top: 2px solid white; background-color:transparent;}");
            this->ui->pswdIcon->setIcon(QIcon(":icon1/pswdWHITE"));
        }
    }

    return QWidget::eventFilter(watched, event);
}

void Login::check_input_finished()
{
    if (!this->ui->username->text().isEmpty() && !this->ui->password->text().isEmpty())
    {
        this->ui->LoginInbtn->setEnabled(true);
    }
    else
    {
        this->ui->LoginInbtn->setEnabled(false);
    }
}

/*
 * 处理窗口移动
 */
void Login::mouseMoveEvent(QMouseEvent *event)
{
    if (this->m_press)
    {
        this->move(event->pos() - m_pos + this->pos());
    }
}

void Login::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->m_press = true;
        this->m_pos = event->pos();
    }
}

void Login::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    this->m_press = false;
}





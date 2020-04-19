#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include <QIcon>
#include <QRegExp>
#include <QValidator>

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
    this->setWindowFlags(Qt::FramelessWindowHint);

    QRegExp rule("[0-9a-zA-Z]*");
    QValidator * validator1 = new QRegExpValidator(rule, this->ui->username);
    QValidator * validator2 = new QRegExpValidator(rule, this->ui->password);
    this->ui->username->setValidator(validator1);
    this->ui->password->setValidator(validator2);
    this->ui->password->raise();
    this->ui->pswdIcon->raise();
    this->ui->userIcon->raise();
    this->ui->username->raise();

    this->ui->LoginInbtn->setEnabled(false);   //初始状态“进入”不可用

    this->ui->password->installEventFilter(this);
    this->ui->username->installEventFilter(this);
    this->ui->Help->installEventFilter(this);
    this->setFocus();

    //检查输入是否已经规范完成
    connect(this->ui->username, &QLineEdit::editingFinished, this, &Login::check_input_finished);
    connect(this->ui->password, &QLineEdit::editingFinished, this, &Login::check_input_finished);
    connect(this->ui->username, &QLineEdit::cursorPositionChanged, this, &Login::check_input_finished);
    connect(this->ui->password, &QLineEdit::cursorPositionChanged, this, &Login::check_input_finished);

}

/*
 * 事件过滤器
 * 处理事件[光标focus在username Linetext][光标focus在password Linetext][光标悬停在Help按钮]
 */
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
    if (watched == this->ui->Help)
    {
        if (event->type() == QEvent::Enter)
        {
            this->ui->Help->setIcon(QIcon(":icon1/helpBLUE"));
        }
        else if (event->type() == QEvent::Leave)
        {
            this->ui->Help->setIcon(QIcon(":icon1/helpWHITE"));
        }
    }
    return QWidget::eventFilter(watched, event);
}

/*
 * 检查是否符合规范输入完成，若完成，使能"进入"按钮
 */
void Login::check_input_finished()
{
    if (!this->ui->username->text().isEmpty() && !this->ui->password->text().isEmpty() && this->ui->password->text().length() >= 6 && this->ui->username->text().length() >= 3)
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

/*
 *处理标题按键槽函数
 */
void Login::on_close_clicked()
{
    this->close();
}

void Login::on_setting_2_clicked()
{
    this->hide();
}

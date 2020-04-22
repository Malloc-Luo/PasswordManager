#include "signin.h"
#include "ui_signin.h"
#include <QDebug>
#include <QMouseEvent>

Signin::Signin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signin)
{
    ui->setupUi(this);
    this->setWidget();
}

Signin::~Signin()
{
    delete ui;
}

void Signin::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Signin::setWidget()
{
    this->setWindowFlags(Qt::FramelessWindowHint);

    this->ui->groupbox2->hide();
    this->ui->horizontalLayoutWidget->hide();
    this->ui->next->hide();
    this->ui->userwarning->hide();
    this->ui->pswdwarning->hide();
    this->ui->groupBox1->raise();
    this->ui->next->raise();

    this->ui->groupBox1->setGeometry(50, 170, 371, 111);
    this->ui->next->setGeometry(this->ui->next->x(), this->ui->next->y() + 80, this->ui->next->height(), this->ui->next->width());

    this->ui->username->installEventFilter(this);
    this->ui->pswd->installEventFilter(this);
    this->ui->inputtips->installEventFilter(this);
    this->ui->inputanswer->installEventFilter(this);

    connect(this->ui->username, &QLineEdit::editingFinished, this, &Signin::check_info);
    connect(this->ui->username, &QLineEdit::cursorPositionChanged, this, &Signin::check_info);
    connect(this->ui->pswd, &QLineEdit::editingFinished, this, &Signin::check_info);
    connect(this->ui->pswd, &QLineEdit::cursorPositionChanged, this, &Signin::check_info);

    connect(this->ui->inputtips, &QLineEdit::editingFinished, this, &Signin::check_tip);
    connect(this->ui->inputtips, &QLineEdit::cursorPositionChanged, this, &Signin::check_tip);
    connect(this->ui->inputanswer, &QLineEdit::editingFinished, this, &Signin::check_tip);
    connect(this->ui->inputanswer, &QLineEdit::cursorPositionChanged, this, &Signin::check_tip);

    this->setFocus();
}


/*
 * 实现部分组件动态效果
 */
bool Signin::eventFilter(QObject * watched, QEvent * event)
{
    if (watched == this->ui->username)
    {
        if (event->type() == QEvent::FocusIn)
        {
            this->ui->usericon->setEnabled(false);
            this->ui->userline->setStyleSheet("QFrame{border-top: 2px solid rgb(0, 170, 255); background-color:transparent;}");
            this->ui->username->setStyleSheet("QLineEdit{color:rgb(0, 170, 255)}");
        }
        else if (event->type() == QEvent::FocusOut)
        {
            this->ui->usericon->setEnabled(true);
            this->ui->userline->setStyleSheet("QFrame{border-top: 2px solid white; background-color:transparent;}");
            this->ui->username->setStyleSheet("QLineEdit{color:white}");
        }
    }

    if (watched == this->ui->pswd)
    {
        if (event->type() == QEvent::FocusIn)
        {
            this->ui->pswdicon->setEnabled(false);
            this->ui->pswdline->setStyleSheet("QFrame{border-top: 2px solid rgb(0, 170, 255); background-color:transparent;}");
            this->ui->pswd->setStyleSheet("QLineEdit{color:rgb(0, 170, 255)}");
        }
        else if (event->type() == QEvent::FocusOut)
        {
            this->ui->pswdicon->setEnabled(true);
            this->ui->pswdline->setStyleSheet("QFrame{border-top: 2px solid white; background-color:transparent;}");
            this->ui->pswd->setStyleSheet("QLineEdit{color:white}");
        }
    }

    if (watched == this->ui->inputtips)
    {
        if (event->type() == QEvent::FocusIn)
        {
            this->ui->tipicon->setEnabled(false);
            this->ui->tipline->setStyleSheet("QFrame{border-top: 2px solid rgb(0, 170, 255); background-color:transparent;}");
            this->ui->inputtips->setStyleSheet("QLineEdit{color:rgb(0, 170, 255)}");
        }
        else if (event->type() == QEvent::FocusOut)
        {
            this->ui->tipicon->setEnabled(true);
            this->ui->tipline->setStyleSheet("QFrame{border-top: 2px solid white; background-color:transparent;}");
            this->ui->inputtips->setStyleSheet("QLineEdit{color:white}");
        }
    }

    if (watched == this->ui->inputanswer)
    {
        if (event->type() == QEvent::FocusIn)
        {
            this->ui->ansicon->setEnabled(false);
            this->ui->ansline->setStyleSheet("QFrame{border-top: 2px solid rgb(0, 170, 255); background-color:transparent;}");
            this->ui->inputanswer->setStyleSheet("QLineEdit{color:rgb(0, 170, 255)}");
        }
        else if (event->type() == QEvent::FocusOut)
        {
            this->ui->ansicon->setEnabled(true);
            this->ui->ansline->setStyleSheet("QFrame{border-top: 2px solid white; background-color:transparent;}");
            this->ui->inputanswer->setStyleSheet("QLineEdit{color:white}");
        }
    }

    return QWidget::eventFilter(watched, event);
}

/*
 * 判断用户名和密码是否符合规范
 * UI动态效果实现
 */
void Signin::check_info()
{
    if (!this->ui->username->text().isEmpty() && this->ui->username->text().length() < 3)
    {
        this->ui->userwarning->show();
        this->ui->userwarning->setEnabled(false);
    }
    else if (this->ui->username->text().isEmpty())
    {
        this->ui->userwarning->hide();
        this->ui->userwarning->setEnabled(false);
    }
    else if (this->ui->username->text().length() >= 3)
    {
        this->ui->userwarning->show();
        this->ui->userwarning->setEnabled(true);
    }

    if (!this->ui->pswd->text().isEmpty() && this->ui->pswd->text().length() < 6)
    {
        this->ui->pswdwarning->show();
        this->ui->pswdwarning->setEnabled(false);
    }
    else if (this->ui->pswd->text().isEmpty())
    {
        this->ui->pswdwarning->hide();
        this->ui->pswdwarning->setEnabled(false);
    }
    else if (this->ui->pswd->text().length() >= 6)
    {
        this->ui->pswdwarning->show();
        this->ui->pswdwarning->setEnabled(true);
    }

    if (this->ui->userwarning->isVisible() || this->ui->pswdwarning->isVisible())
    {
        this->ui->groupBox1->setGeometry(40, 170, 371, 111);
        this->ui->groupbox2->hide();
        this->ui->pushButton->setText(tr("* 新建用户"));
    }
    else
    {
        this->ui->groupBox1->setGeometry(50, 170, 371, 111);
        this->ui->groupbox2->hide();
        this->ui->pushButton->setText(tr("新建用户"));
    }

    if (this->ui->userwarning->isEnabled() && this->ui->pswdwarning->isEnabled())
    {
        this->ui->next->setVisible(true);
        this->ui->next->setEnabled(true);
    }
    else
    {
        this->ui->next->setEnabled(false);
    }
}

void Signin::check_tip()
{
    if (this->ui->inputtips->text().length() >= 3 && this->ui->inputanswer->text().length())
    {
        this->ui->horizontalLayoutWidget->show();
    }
    else
    {
        this->ui->horizontalLayoutWidget->hide();
    }
}

/*
 * 按钮的槽函数
 */
void Signin::on_close_clicked()
{
    this->close();
}

void Signin::on_return_2_clicked()
{
    this->accept();
}

void Signin::on_next_clicked()
{
    this->ui->groupBox1->setGeometry(40, 80, 371, 111);
    this->ui->groupbox2->show();
    this->ui->next->hide();
}

/*
 * 窗口移动
 */
void Signin::mouseMoveEvent(QMouseEvent *event)
{
    //只有在标题栏才能移动
    if (this->m_press && this->m_pos.y() <= 40)
    {
        this->move(event->pos() - m_pos + this->pos());
    }
}

void Signin::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->m_press = true;
        this->m_pos = event->pos();
    }
}

void Signin::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    this->m_press = false;
}



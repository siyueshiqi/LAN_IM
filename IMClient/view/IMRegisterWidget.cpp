/*********************************************
File Name： IMRegisterWidget.cpp
Author： jet.F.R
Date： 2014.3.14
Description： 客户端注册界面
Changes：
********************************************/
#include "IMRegisterWidget.h"
#include "model/IMUser.h"
#include "control/IMRegisterCtrl.h"
#include "CustomLineEdit.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <qdebug.h>
#include <QTime>
#include "model/IMEncryption.h"
// mark: public:---------------------------------------------------------
IMRegisterWidget::IMRegisterWidget(QWidget *parent) :
    QWidget(parent)
{
    initIMRegisterWidget();
    linkSignalWithSlot();
    setWindowTitle(tr("注册IM帐号"));
}

IMRegisterWidget::~IMRegisterWidget()
{
    if (m_regCtrl != NULL)
    {
        delete m_regCtrl;
        m_regCtrl = NULL;
    }
}

// mark: public slots:--------------------------------------------------
/*************************************************
Function Name： resetBtnRegister()
Description: 重置注册按钮
Input： NULL
Output： NULL
Changes： NULL
*************************************************/
void IMRegisterWidget::resetBtnRegister(bool enable)
{
    m_btnRegister->setEnabled(enable);
}


// mark: protected:--------------------------------------------
void IMRegisterWidget::moveEvent(QMoveEvent *)
{
    m_leBirthday->moveCalendarPos();
}

// mark: private slots:---------------------------------------------------
/*************************************************
Function Name： onClickBtnRegister()
Description: 单击“注册”按钮
Input： NULL
Output： NULL
Changes： NULL
*************************************************/
void IMRegisterWidget::onClickBtnRegister()
{
    // 判断昵称是否为空
    if (m_leNickname->text().isEmpty())
    {
        QMessageBox::about(NULL, tr("提示"), tr("昵称不能为空"));
        return;
    }
    // 判断密码是否为空
    if (m_lePwd->text().isEmpty())
    {
        QMessageBox::about(NULL, tr("提示"), tr("密码不能为空"));
        return;
    }
    // 判断密码是否符合要求
    if (m_lePwd->text().length()>14 || m_lePwd->text().length()<6)
    {
        QMessageBox::about(NULL, tr("提示"), tr("密码长度不符合"));
        return;
    }
    // 判断确认密码是否为空
    if (m_leConfirmPwd->text().isEmpty())
    {
        QMessageBox::about(NULL, tr("提示"), tr("请确认密码"));
        return;
    }
    // 判断密码是否一致
    if (m_lePwd->text().compare(m_leConfirmPwd->text()) != 0)
    {
        QMessageBox::about(NULL, tr("提示"), tr("密码不一致"));
        return;
    }
    // 判断性别是否为空
    if (m_cbxSex->currentText().isEmpty())
    {
        QMessageBox::about(NULL, tr("提示"), tr("性别不能为空"));
        return;
    }
    // 判断生日是否为空
    if (m_leBirthday->text().isEmpty())
    {
        QMessageBox::about(NULL, tr("提示"), tr("生日不能为空"));
        return;
    }
    // 判断密保问题是否为空
    if (m_leQuestion->text().isEmpty())
    {
        QMessageBox::about(NULL, tr("提示"), tr("密保不能为空"));
        return;
    }
    // 判断问题答案是否为空
    if (m_leAnswer->text().isEmpty())
    {
        QMessageBox::about(NULL, tr("提示"), tr("问题答案不能为空"));
        return;
    }

//    QString sex = "";
//    switch (m_cbxSex->currentIndex())
//    {
//    case 0:
//        sex = "男";
//        break;
//    case 1:
//        sex = "女";
//        break;
//    default:
//        sex = "男";
//        break;
//    }

    m_userInf.m_nickname =  m_leNickname->text();
    m_userInf.m_password = IMEncryption::getInstace().
            getXorEncryptDecrypt(m_lePwd->text(), 10);
    m_userInf.m_sex = m_cbxSex->currentText();
    m_userInf.m_birthday = m_leBirthday->getDate();
    m_userInf.m_name = m_leName->text();
    m_userInf.m_phone = m_lePhone->text();
    m_userInf.m_address= m_leAddress->text();
    m_userInf.m_question = m_leQuestion->text();
    m_userInf.m_answer = m_leAnswer->text();
//    qDebug() << "time:" << QDateTime::currentDateTime();
//    m_userInf.m_regDateTime = QDateTime::currentDateTime();
//    qDebug() << "time:" << m_userInf.m_regDateTime;

    if ( 0 == m_userInf.m_sex.compare("男"))
    {
        m_userInf.m_headPortrait = 43;
    }
    else
        m_userInf.m_headPortrait = 20;

    if (m_regCtrl == NULL)
    {
        m_regCtrl = new IMRegisterCtrl;
        connect(m_regCtrl, SIGNAL(signalResetBtnRegister(bool )),
                this, SLOT(resetBtnRegister(bool )));
    }
    m_btnRegister->setEnabled(false);
    m_regCtrl->registerAccount(m_userInf);
}

/*************************************************
Function Name： conClickBtnCancel()
Description: 单击“取消”按钮
Input： NULL
Output： NULL
Changes： NULL
*************************************************/
void IMRegisterWidget::conClickBtnCancel()
{
    this->close();
}


// mark: private:-------------------------------------------------------
/*************************************************
Function Name： initIMRegisterWidget()
Description: 初始化注册界面
Input： NULL
Output： NULL
Changes： NULL
*************************************************/
void IMRegisterWidget::initIMRegisterWidget()
{
    m_regCtrl = NULL;
    // 整体区域 头部 标签
    m_labelHead = new QLabel(tr("注册用户信息"));
    m_labelHead->setAlignment(Qt::AlignCenter);
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::black);
    m_labelHead->setPalette(pa);
    QFont ft;
    ft.setPointSize(15);
    m_labelHead->setFont(ft);

    // 中间区域 左边 标签
    m_labelNickname = new QLabel(tr("昵称"));
    m_labelPwd = new QLabel(tr("密码"));
    m_labelConfirmPwd = new QLabel(tr("确认密码"));
    m_labelSex = new QLabel(tr("性别"));
    m_labelBirthday = new QLabel(tr("生日"));
    m_labelQuestion = new QLabel(tr("密保问题"));
    m_labelAnswer = new QLabel(tr("问题答案"));
    m_labelName = new QLabel(tr("真实姓名"));
    m_labelPhone = new QLabel(tr("电话"));
    m_labelAddress = new QLabel(tr("地址"));

    // 中间区域 中间 信息编辑
    m_leNickname = new QLineEdit;
    m_lePwd = new QLineEdit;
    m_lePwd->setEchoMode(QLineEdit::Password);
    m_lePwd->setMaxLength(14);
    m_leConfirmPwd = new QLineEdit;
    m_leConfirmPwd->setEchoMode(QLineEdit::Password);
    m_leConfirmPwd->setMaxLength(14);
    m_cbxSex = new QComboBox;
    m_cbxSex->addItem(tr("男"));
    m_cbxSex->addItem(tr("女"));
    m_leBirthday = new CustomLineEdit;
    m_leQuestion = new QLineEdit;
    m_leQuestion->setPlaceholderText(tr("比如：我初中老师的姓名"));
    m_leAnswer = new QLineEdit;
    m_leAnswer->setPlaceholderText(tr("比如：张三"));
    m_leName = new QLineEdit;
    m_lePhone = new QLineEdit;
    m_leAddress = new QLineEdit;
    m_btnRegister = new QPushButton;
    m_btnCancel = new QPushButton;

    // 中间区域 右边 信息描述
    m_labelDesNickname = new QLabel(tr("* 您独一无二的称谓"));
    m_labelDesPwd = new QLabel(tr("* 6～14个字符，不能包含空格"));
    m_labelDesConfirmPwd = new QLabel(tr("* 请再次输入密码"));
    m_labelDesSex = new QLabel(tr("* 您的性别"));
    m_labelDesBirthday = new QLabel(tr("* 您的出生日"));
    m_labelDesQuestion = new QLabel(tr("* 用于找回密码"));
    m_labelDesAnswer = new QLabel(tr("* 一定记住！！"));
    m_labelDesName = new QLabel(tr("  您的真实姓名"));
    m_labelDesPhone = new QLabel(tr("  您的手机号码"));
    m_labelDesAddress = new QLabel(tr("  您的地址"));

    // 整体区域 下面 按钮
    m_btnRegister = new QPushButton(tr("注册"));
    m_btnCancel = new QPushButton(tr("取消"));

    // 中间区域 左边 布局
    QVBoxLayout *vLayoutLeft = new QVBoxLayout;
    vLayoutLeft->addWidget(m_labelNickname);
    vLayoutLeft->addWidget(m_labelPwd);
    vLayoutLeft->addWidget(m_labelConfirmPwd);
    vLayoutLeft->addWidget(m_labelSex);
    vLayoutLeft->addWidget(m_labelBirthday);
    vLayoutLeft->addWidget(m_labelQuestion);
    vLayoutLeft->addWidget(m_labelAnswer);
    vLayoutLeft->addWidget(m_labelName);
    vLayoutLeft->addWidget(m_labelPhone);
    vLayoutLeft->addWidget(m_labelAddress);

    // 中间区域 中间 布局
    QVBoxLayout *vLayoutMid = new QVBoxLayout;
    vLayoutMid->addWidget(m_leNickname);
    vLayoutMid->addWidget(m_lePwd);
    vLayoutMid->addWidget(m_leConfirmPwd);
    vLayoutMid->addWidget(m_cbxSex);
    vLayoutMid->addWidget(m_leBirthday);
    vLayoutMid->addWidget(m_leQuestion);
    vLayoutMid->addWidget(m_leAnswer);
    vLayoutMid->addWidget(m_leName);
    vLayoutMid->addWidget(m_lePhone);
    vLayoutMid->addWidget(m_leAddress);

    // 中间区域 右边 布局
    QVBoxLayout *vLayoutRight = new QVBoxLayout;
    vLayoutRight->addWidget(m_labelDesNickname);
    vLayoutRight->addWidget(m_labelDesPwd);
    vLayoutRight->addWidget(m_labelDesConfirmPwd);
    vLayoutRight->addWidget(m_labelDesSex);
    vLayoutRight->addWidget(m_labelDesBirthday);
    vLayoutRight->addWidget(m_labelDesQuestion);
    vLayoutRight->addWidget(m_labelDesAnswer);
    vLayoutRight->addWidget(m_labelDesName);
    vLayoutRight->addWidget(m_labelDesPhone);
    vLayoutRight->addWidget(m_labelDesAddress);

    // 整体区域 中间 布局
    QHBoxLayout *hLayoutMid = new QHBoxLayout;
    hLayoutMid->addLayout(vLayoutLeft);
    hLayoutMid->addLayout(vLayoutMid);
    hLayoutMid->addLayout(vLayoutRight);

    // 整体区域 下面 布局
    QHBoxLayout *hLayoutBtm = new QHBoxLayout;
    hLayoutBtm->addStretch();
    hLayoutBtm->addWidget(m_btnRegister);
    hLayoutBtm->addStretch();
    hLayoutBtm->addWidget(m_btnCancel);
    hLayoutBtm->addStretch();

    // 星号信息 标签
    QLabel *labelAsterisk = new QLabel(tr("* 为必填"), this);
    QPalette pal;
    pal.setColor(QPalette::WindowText, Qt::red);
    labelAsterisk->setPalette(pal);
    QFont fot;
    fot.setPointSize(10);
    labelAsterisk->setFont(fot);

    // 整体区域 布局
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_labelHead);
    mainLayout->addLayout(hLayoutMid);
    mainLayout->addLayout(hLayoutBtm);
    mainLayout->addWidget(labelAsterisk);

    setLayout(mainLayout);
}

/*************************************************
Function Name： linkSignalWithSlot()
Description: 连接信号与槽
Input： NULL
Output： NULL
Changes： NULL
*************************************************/
void IMRegisterWidget::linkSignalWithSlot()
{
    connect(m_btnRegister, SIGNAL(clicked()),
            this, SLOT(onClickBtnRegister()));
    connect(m_btnCancel, SIGNAL(clicked()),
            this, SLOT(conClickBtnCancel()));

}


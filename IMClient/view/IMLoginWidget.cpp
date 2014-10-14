/*********************************************
File Name： IMLoginWidget.cpp
Author： jet.F.R
Date： 2014.3.10
Description： 客户端登录界面
Changes：
********************************************/

#include "IMLoginWidget.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDockWidget>
#include <QTime>
#include <QTimerEvent>
#include <QHostAddress>
#include <QInputDialog>

#include "IMMainWidget.h"
#include "view/IMClickLabel.h"
#include "IMRegisterWidget.h"
#include "IMForgotPwdWidget.h"
#include "model/IMTcpSocket.h"
#include "control/IMClientFileCtrl.h"
#include "control/IMLoginCtrl.h"
#include "model/IMEncryption.h"
static const QString AUTO_LOGIN_FILE_NAME = "resource/config/auto_login.im";

// mark public:--------------------------------------------------------------
IMLoginWidget::IMLoginWidget(QWidget *parent)
    : QWidget(parent)
{
    initIMLoginWidget();
    linkSignalWithSlot();
    setWindowTitle(tr("登录IM"));
}

IMLoginWidget::~IMLoginWidget()
{
    if (m_loginCtrl != NULL)
    {
        delete m_loginCtrl;
        m_loginCtrl = NULL;
    }

    if (m_timerID != 0)
    {
        killTimer(m_timerID);
        m_timerID = 0;
    }

}


// mark: public slots:-----------------------------------------------------
/*************************************************
Function Name： showMainWidget()
Description: 显示主界面
Input： NULL
Output： NULL
Changes： NULL
*************************************************/
void IMLoginWidget::showMainWidget()
{
}

/*************************************************
Function Name： setLabelStatus()
Description: 设置状态标签
*************************************************/
void IMLoginWidget::setLabelStatus(const QString &mes, bool isLogin,
                                   const UserInformation *me)
{
    closeTimer();

    if (isLogin == true)
    {
        m_btnLogin->setEnabled(false);
        m_btnLogin->setText(tr("取消"));
        m_labelStatus->setText(tr("%1").arg(mes));
        if (true == m_cbKeepPwd->isChecked())
        {
            if (!IMClientFileCtrl::writeAutoLogin(
                        AUTO_LOGIN_FILE_NAME,m_leUserID->text(),
                        m_leUserPwd->text(),m_cbAutoLogin->isChecked()))
            {
                qDebug() << "fail to write autoLogin file.";
            }
        }
        else
        {
            if (!IMClientFileCtrl::remove(AUTO_LOGIN_FILE_NAME))
            {
                qDebug() << "fail to write autoLogin file.";
            }
        }

        IMMainWidget *mainWidget = new IMMainWidget(*me);
//        mainWidget->setUserID(m_leUserID->text());
//        mainWidget->setNickname(mes);
//        mainWidget->setLoginStatus(m_status);

        mainWidget->getFriendsInformation();

        mainWidget->show();


//        mainWidget->getLatestMessage();


//        if (m_loginCtrl != NULL)
//        {
//            delete m_loginCtrl;
//            m_loginCtrl = NULL;
//        }
        close();
    }
    else
    {
        m_isLogin = true;
        m_btnLogin->setText(tr("登录"));
        m_labelStatus->setText(mes);
        m_leUserID->setReadOnly(false);
        m_leUserPwd->setReadOnly(false);
    }
}


/*************************************************
Function Name： getIsAutoLogin()
Description: 获取m_isAutoLogin
Input： QTimerEvent *event：定时器事件
Output： bool
Changes： NULL
*************************************************/
bool IMLoginWidget::getIsAutoLogin()
{
    return m_isAutoLogin;
}


/*************************************************
Function Name： onClickbtnLogin()
Description: 单击“登录”按钮
Input： NULL
Output： NULL
Changes： NULL
*************************************************/
void IMLoginWidget::onClickBtnLogin()
{
    setServer();

    m_leUserID->setReadOnly(true);
    m_leUserPwd->setReadOnly(true);

//      m_btnLogin->setEnabled(false);
    if (true == m_isLogin)
    {
        m_isLogin = false;
        m_btnLogin->setText(tr("取消"));

        m_closeTimer = false;
        m_timerID=startTimer(1000);//interval is 100ms

//        IMClientMessageCtrl::sm_hostAddress = address;
//        IMClientMessageCtrl::sm_hostPort = port;

        m_labelStatus->setText(tr("登录中"));

        if (m_loginCtrl == NULL)
        {
            m_loginCtrl = new IMLoginCtrl(this);
            connect(m_loginCtrl, SIGNAL(getLoginMessgae(QString,bool,const UserInformation*)),
                    this, SLOT(setLabelStatus(QString,bool,const UserInformation*)));
        }
        switch (m_cbxStatus->currentIndex())
        {
        case 0:
            m_status = ONLINE;
            break;
        case 1:
            m_status = INVISIBLE;
            break;
        case 2:
            m_status = BUSY;
            break;
        case 3:
            m_status = LEAVE;
            break;
        case 4:
            m_status = NOTDISTURB;
            break;
        default:
            m_status = ONLINE;
            break;
        }
        qDebug() << "status: " << m_status;
        QString pwd = IMEncryption::getInstace()
                .getXorEncryptDecrypt(m_leUserPwd->text(), 10);
        m_loginCtrl->login(m_leUserID->text(), pwd, m_status);
    }
    else
    {
        m_isLogin = true;
        m_btnLogin->setText(tr("登录"));
        m_labelStatus->setText(tr("你好,请登录系统."));

        if (m_loginCtrl != NULL)
        {
            delete m_loginCtrl;
            m_loginCtrl = NULL;
        }

        closeTimer();

    }

    //delete loginCtrl;
    //this->close();
}

// mark: protected:---------------------------------------------------------
/*************************************************
Function Name： timerEvent()
Description: 处理定时器事件
Input： QTimerEvent *event：定时器事件
Output： NULL
Changes： NULL
*************************************************/
void IMLoginWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timerID)
    {
        ++m_counter;
        switch (m_counter%4)
        {
        case 0:
            m_labelStatus->setText(tr("登录中"));
            break;
        case 1:
            m_labelStatus->setText(tr("登录中.."));
            break;
        case 2:
            m_labelStatus->setText(tr("登录中....."));
            break;
        case 3:
            m_labelStatus->setText(tr("登录中......."));
            break;
        }
    }
}


// mark: private slots:-----------------------------------------------------

/*************************************************
Function Name： onClickLabelRegister()
Description: 单击"注册帐号"标签
Input： NULL
Output： NULL
Changes： NULL
*************************************************/
void IMLoginWidget::onClickLabelRegister()
{
    setServer();
    IMRegisterWidget *registerWidget = new IMRegisterWidget;
    registerWidget->show();
    //delete this;
}

/*************************************************
Function Name： onClickLabelForgotPwd()
Description: 单击“忘记密码"标签
Input： NULL
Output： NULL
Changes： NULL
*************************************************/
void IMLoginWidget::onClickLabelForgotPwd()
{
    setServer();
//    IMForgotPwdWidget *forgotPwdWidget = new IMForgotPwdWidget;
//    forgotPwdWidget->show();
    //delete this;
    bool isOkMes = false;
    QString userID = QInputDialog::getText(NULL, "找回密码",
                                           "请输入帐号ID",
                                           QLineEdit::Normal,
                                           NULL,
                                           &isOkMes);
    if (!isOkMes)
        return;

    m_loginCtrl->getQuestionAndAnswer(userID);
}


/*************************************************
Function Name： onClickCbAutoLogin
Description: 自动登录选择框改变
Input： state
Output： NULL
Changes： NULL
*************************************************/
void IMLoginWidget::onClickCbAutoLogin(int state)
{
    if (state == Qt::Checked)
    {
        m_cbKeepPwd->setChecked(true);
    }
    else
        m_cbKeepPwd->setChecked(false);
}

// mark private:------------------------------------------------------------
/*************************************************
Function Name： initIMLoginWidget()
Description: 初始化登录界面
Input： NULL
Output： NULL
Changes： NULL
*************************************************/
void IMLoginWidget::initIMLoginWidget()
{
    m_isLogin = true;
    m_loginCtrl = new IMLoginCtrl(this);
    connect(m_loginCtrl, SIGNAL(getLoginMessgae(QString,bool,const UserInformation*)),
            this, SLOT(setLabelStatus(QString,bool,const UserInformation*)));
    m_counter = 0;
    m_closeTimer = true;
    m_timerID = 0;
    qsrand(time(NULL));

    QVBoxLayout *vLayoutMidTop   = new QVBoxLayout;
    QVBoxLayout *vLayoutRightTop = new QVBoxLayout;
    QHBoxLayout *hLayoutTop      = new QHBoxLayout;

    QHBoxLayout *hLayoutMid  = new QHBoxLayout;
    QHBoxLayout *hLayoutBtm  = new QHBoxLayout;
    QVBoxLayout *vLayoutMain = new QVBoxLayout;

    QLabel *labelHeadLine = new QLabel(tr("登录即时通信系统"));
    labelHeadLine->setAlignment(Qt::AlignCenter);
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::black);
    labelHeadLine->setPalette(pa);
    QFont ft;
    ft.setPointSize(15);
    labelHeadLine->setFont(ft);

//    QLabel *labelID = new QLabel(tr("ID"));
//    QLabel *labelPwd = new QLabel(tr("Password"));
//    vLayoutLeftTop->addWidget(labelID);
//    vLayoutLeftTop->addWidget(labelPwd);

    m_leUserID = new QLineEdit;
    m_leUserID->setPlaceholderText(tr("帐号"));
    m_leUserPwd = new QLineEdit;
    m_leUserPwd->setPlaceholderText(tr("密码"));
    m_leUserPwd->setEchoMode(QLineEdit::Password);
    vLayoutMidTop->addWidget(m_leUserID);
    vLayoutMidTop->addWidget(m_leUserPwd);

    m_labelRegister = new IMClickLabel;
    m_labelRegister->setText(tr("注册帐号"));
    m_labelForgotPwd = new IMClickLabel;
    m_labelForgotPwd->setText(tr("忘记密码"));
    vLayoutRightTop->addWidget(m_labelRegister);
    vLayoutRightTop->addWidget(m_labelForgotPwd);

//    hLayoutTop->addLayout(vLayoutLeftTop);
    hLayoutTop->addLayout(vLayoutMidTop);
    hLayoutTop->addLayout(vLayoutRightTop);
    hLayoutTop->setMargin(10);
    //end top

    //mid
    m_cbKeepPwd = new QCheckBox(tr("记住密码"));
    m_cbAutoLogin = new QCheckBox(tr("自动登录"));
    hLayoutMid->addWidget(m_cbKeepPwd);
    hLayoutMid->addWidget(m_cbAutoLogin);
    //end mid

    //bottom
    m_moreButton = new QPushButton(tr("设置"));
    m_moreButton->setCheckable(true);
    m_moreButton->setAutoDefault(false);
    m_cbxStatus = new QComboBox();
    m_cbxStatus->addItem(tr("在线"));
    m_cbxStatus->addItem(tr("隐身"));
    m_cbxStatus->addItem(tr("忙碌"));
    m_cbxStatus->addItem(tr("离开"));
    m_cbxStatus->addItem("请勿打扰");
    m_btnLogin = new QPushButton(tr("登录"));
    m_btnLogin->setDefault(true);

    hLayoutBtm->addWidget(m_moreButton);
    hLayoutBtm->addWidget(m_cbxStatus);
    hLayoutBtm->addWidget(m_btnLogin);
    //end bottom

    //hide
    m_hostAddress = new QLineEdit;;
    m_hostAddress->setPlaceholderText(tr("服务器IP地址"));
    m_hostPort = new QLineEdit;
    m_hostPort->setFixedWidth(60);
    m_hostPort->setPlaceholderText(tr("端口号"));
    m_extendedWidget = new QWidget;
    QHBoxLayout *hLayoutExtended = new QHBoxLayout;
    hLayoutExtended->setMargin(0);
    hLayoutExtended->addWidget(m_hostAddress);
    hLayoutExtended->addWidget(m_hostPort);
    m_extendedWidget->setLayout(hLayoutExtended);
    //end hide

    m_labelStatus = new QLabel;
    m_labelStatus->setText(tr("你好,请登录系统."));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_labelStatus->setSizePolicy(sizePolicy);

    vLayoutMain->setSizeConstraint(QLayout::SetFixedSize);
    vLayoutMain->addWidget(labelHeadLine);
    vLayoutMain->addLayout(hLayoutTop);
    vLayoutMain->addLayout(hLayoutMid);
    vLayoutMain->addLayout(hLayoutBtm);
    vLayoutMain->addWidget(m_extendedWidget);
    vLayoutMain->addWidget(m_labelStatus);
    vLayoutMain->setMargin(5);


    setLayout(vLayoutMain);
    //setFocusPolicy(Qt::ClickFocus);

    m_extendedWidget->hide();

    // 读取自动登录配置文件
    readAutoLoginFile(AUTO_LOGIN_FILE_NAME);
}

/*************************************************
Function Name： linkSignalWithSlot()
Description: 连接信号与槽
Input： NULL
Output： NULL
Changes： NULL
*************************************************/
void IMLoginWidget::linkSignalWithSlot()
{
    connect(m_btnLogin, SIGNAL(clicked()),
            this, SLOT(onClickBtnLogin()));

    connect(m_moreButton, SIGNAL(toggled(bool)),
            m_extendedWidget, SLOT(setVisible(bool)));

    connect(m_labelRegister, SIGNAL(clicked()),
            this, SLOT(onClickLabelRegister()));

    connect(m_labelForgotPwd, SIGNAL(clicked()),
            this, SLOT(onClickLabelForgotPwd()));

    connect(m_cbAutoLogin, SIGNAL(stateChanged(int)),
            this, SLOT(onClickCbAutoLogin(int)));

//    connect(m_loginCtrl, SIGNAL(getQuestionAndAnswerSuccess(TempStrings)),
//            this, SLOT());

//    connect(m_moreButton, SIGNAL(toggled(bool)), this, SLOT(setSettingMessage(bool)));
}

/*************************************************
Function Name： closeTimer()
Description: 关闭定时器
Input： NULL
Output： NULL
Changes： NULL
*************************************************/
void IMLoginWidget::closeTimer()
{
    if (m_timerID != 0)
    {
        m_closeTimer = true;
        killTimer(m_timerID);//kill timer
        m_timerID = 0;
        m_counter = 0;
    }
}


/*************************************************
Function Name： setServer()
Description: 设置服务器
Input：  ip地址，端口号
Output： NULL
Changes： NULL
*************************************************/
void IMLoginWidget::setServer(const QString & ip, const int port)
{

    QHostAddress serverAddress;
    int serverPort;
    if (m_hostAddress->text().isEmpty())
    {
        serverAddress = ip;
    }
    else
    {
        serverAddress = m_hostAddress->text();
    }
    if (m_hostPort->text().isEmpty())
    {
        serverPort = port;
    }
    else
    {
        serverPort = m_hostPort->text().toInt();
    }
    IMTcpSocket::s_hostAddress = serverAddress;
    IMTcpSocket::s_hostPort = serverPort;
//    qDebug() << "serverAddress:" << serverAddress
//             << " port:" << serverPort;
}


/*************************************************
Function Name： 读取自动登录配置文件()
Description: 设置服务器
Input：  ip地址，端口号
Output： NULL
Changes： NULL
*************************************************/
bool  IMLoginWidget::readAutoLoginFile(const QString & filename)
{
    QString tmpID;
    QString tmpPwd;
    bool isAuto = false;
    if (!IMClientFileCtrl::readAutoLogin(filename, tmpID, tmpPwd, isAuto))
    {
         m_isAutoLogin = false;
        qDebug() << "fail to read autoLogin file.";
        return false;
    }
    else
    {
        m_leUserID->setText(tmpID);
        m_leUserPwd->setText(tmpPwd);
        m_cbAutoLogin->setChecked(isAuto);
        m_isAutoLogin = isAuto;
        m_cbKeepPwd->setChecked(true);
    }

    return true;
}

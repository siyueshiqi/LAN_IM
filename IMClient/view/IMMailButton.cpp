#include "IMMailButton.h"
#include <QLabel>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QMenu>
#include <QMouseEvent>
#include <QDebug>
#include "view/IMMailWidget.h"
#include "control/IMMailCtrl.h"

IMMailButton::IMMailButton(const MailInformation & mail,
                           IMMailWidget * mailWidget,
                           QWidget *parent) :
    m_mail(mail), m_mailWidget(mailWidget), QPushButton(parent)
{
    if (NULL == m_mailWidget)
        return;
    m_mailCtrl = m_mailWidget->getMailCtrl();

    QHBoxLayout *layout = new QHBoxLayout;
    m_labelStatus = new QLabel(this);
    m_labelStatus->setFixedSize(HEAD_MINI_SIZE, HEAD_MINI_SIZE);
    m_labelSender = new QLabel(this);

    m_labelSender->setFixedWidth(170);
    m_labelTheme = new QLabel(this);

    m_labelTime = new QLabel(this);


    layout->addWidget(m_labelStatus);
    layout->addWidget(m_labelSender);
    layout->addWidget(m_labelTheme);
    layout->addStretch();
    layout->addWidget(m_labelTime);

    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);

    setButtonStatus();
    creatMenu();
    setStyleSheet("QPushButton{border: 0;}");

    setMinimumSize(100,30);
}

//remark:protected:----------------------------------------

/*************************************************
Function Name： mousePressEvent
Description: 鼠标单击事件
*************************************************/
void IMMailButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        onClickRightButton();
        return;
    }
    QPushButton::mousePressEvent(event);
}

/*************************************************
Function Name： mouseDoubleClickEvent
Description: 鼠标双击事件
*************************************************/
void IMMailButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
//        emit leftDoubleClickSignal();
        onDoubleClickDiscussionButton();
        return;
    }
    QPushButton::mouseDoubleClickEvent(event);
}




// private slots:----------------------------------------------------------
/*************************************************
Function Name： onClickDeleteMail()
Description: 删除邮件
*************************************************/
void IMMailButton::onClickDeleteMail()
{
    if (m_mailCtrl != NULL)
        m_mailCtrl->requestDeleteMail(m_mail);
}

/*************************************************
Function Name： onDoubleClickDiscussionButton()
Description: 左键 双击
*************************************************/
void IMMailButton::onDoubleClickDiscussionButton()
{
//    openMailInformation();
    m_mailWidget->showMailInformationWidget(m_mail);
    m_mail.m_status = MAIL_READ;
    setButtonStatus();
    if (m_mailCtrl != NULL)
        m_mailCtrl->requestSetMailRead(m_mail);
}

/*************************************************
Function Name： onClickRightButton()
Description: 右键点击按键
*************************************************/
void IMMailButton::onClickRightButton()
{
    if (m_menu == NULL)
    {
        //创建右键菜单
        creatMenu();
    }
    m_menu->exec(QCursor::pos());
}

// private:----------------------------------------------------------
/*************************************************
Function Name： setButtonStatus()
Description: 设置button显示信息
*************************************************/
void IMMailButton::setButtonStatus()
{
     QString str;
    if (MAIL_UNREAD == m_mail.m_status)
        str = QString(":/images/mailUnRead.png");
    else
        str= QString(":/images/mailRead.png");
    QPixmap pixmap;
    QIcon icon(str);
    pixmap = icon.pixmap(QSize(HEAD_MINI_SIZE, HEAD_MINI_SIZE));
    m_labelStatus->setPixmap(pixmap);

    QString senderStr;
    if (m_mailWidget->getMyID() ==  m_mail.m_receiverAddress)
        senderStr = m_mail.m_senderAddress;
    else
        senderStr = m_mail.m_receiverAddress;
    senderStr.append(MAIL_ADDRESS_FORMAT);
    m_labelSender->setText(senderStr);
    m_labelTheme->setText(m_mail.m_theme);
    m_labelTime->setText(m_mail.m_dateTime.toString("yyyy-MM-dd"));// hh:mm:ss"));
}

/*************************************************
Function Name： getStatusFromInt()
Description: 创建右键菜单
*************************************************/
void IMMailButton::creatMenu()
{
    m_menu = new QMenu(this);
    QAction *deleteMail = new QAction(tr("删除邮件"), m_menu);

    connect(deleteMail, SIGNAL(triggered()),
            this, SLOT(onClickDeleteMail()));
    m_menu->addAction(deleteMail);
}

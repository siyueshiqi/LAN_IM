#include "IMLinkFriendButton.h"
#include <QMenu>
#include <QBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include "IMFriendButton.h"

IMLinkFriendButton::IMLinkFriendButton(IMFriendButton *btn, QWidget *parent) :
    IMLinkButton(parent), m_friendBtn(btn)
{
    m_info = m_friendBtn->getInformation();

    setButtonStatus();
}


IMLinkFriendButton::~IMLinkFriendButton()
{
}


/*************************************************
Function Name： setButtonStatus()
Description:  设置button显示信息
*************************************************/
void IMLinkFriendButton::setButtonStatus()
{
    QString str = QString("resource/image/head/%1.bmp").
        arg(QString::number(m_info.m_headPortrait));
    QString text, mark;

    if(m_info.m_remarkName.isEmpty())
        mark = m_info.m_nickname;
    else
        mark = m_info.m_remarkName;

    QPixmap pixmap;
    QIcon icon(str);
    pixmap = icon.pixmap(QSize(HEAD_SMALL_SIZE, HEAD_SMALL_SIZE));
    m_labelHead->setPixmap(pixmap);

    text = QString("<font color=green>%1(%2)</font>").
            arg(m_info.m_userID).arg(mark);
    m_labelInfo->setText(text);;
}


//remark:public slots:---------------------------

/*************************************************
Function Name： onDoubleClickFriendButton()
Description: 左键 双击
*************************************************/
void IMLinkFriendButton::onDoubleClickButton()
{
    m_friendBtn->openChatRoom();
    m_friendBtn->showChatRoom();
    emit deleteLinkButton(m_info.m_userID);
}



/*************************************************
Function Name： ignoreMessage()
Description: 忽略消息
*************************************************/
void IMLinkFriendButton::ignoreMessage()
{
    emit deleteLinkButton(m_info.m_userID);
}




#include "IMLinkFlockButton.h"
#include "IMFlockButton.h"
#include <QLabel>

IMLinkFlockButton::IMLinkFlockButton(IMFlockButton *btn, QWidget *parent) :
    IMLinkButton(parent), m_flockBtn(btn)
{
    m_info = m_flockBtn->getInformation();

    setButtonStatus();
}

IMLinkFlockButton::~IMLinkFlockButton()
{
}

/*************************************************
Function Name： setButtonStatus()
Description:  设置button显示信息
*************************************************/
void IMLinkFlockButton::setButtonStatus()
{
    QString str = QString(":/images/flock.png");
    QPixmap pixmap;
    QIcon icon(str);
    pixmap = icon.pixmap(QSize(HEAD_SMALL_SIZE, HEAD_SMALL_SIZE));
    m_labelHead->setPixmap(pixmap);
    QString text = QString("<font color=green>%1</font>").
            arg(m_info.m_flockName);
    m_labelInfo->setText(text);;
}


//remark:public slots:---------------------------

/*************************************************
Function Name： onDoubleClickFriendButton()
Description: 左键 双击
*************************************************/
void IMLinkFlockButton::onDoubleClickButton()
{
    m_flockBtn->openChatRoom();
    m_flockBtn->showChatRoom();
    emit deleteLinkButton(m_info.m_flockID);
}



/*************************************************
Function Name： ignoreMessage()
Description: 忽略消息
*************************************************/
void IMLinkFlockButton::ignoreMessage()
{
    emit deleteLinkButton(m_info.m_flockID);
}

#include "IMLinkDiscussionButton.h"
#include <QLabel>
#include "IMDiscussionButton.h"

IMLinkDiscussionButton::IMLinkDiscussionButton(
        IMDiscussionButton * btn, QWidget *parent) :
    IMLinkButton(parent), m_discussionBtn(btn)
{
    m_info = m_discussionBtn->getInformation();

    setButtonStatus();
}


IMLinkDiscussionButton::~IMLinkDiscussionButton()
{
}


/*************************************************
Function Name： setButtonStatus()
Description:  设置button显示信息
*************************************************/
void IMLinkDiscussionButton::setButtonStatus()
{
    QString str = QString(":/images/discussion.png");
    QPixmap pixmap;
    QIcon icon(str);
    pixmap = icon.pixmap(QSize(HEAD_SMALL_SIZE, HEAD_SMALL_SIZE));
    m_labelHead->setPixmap(pixmap);

    QString text = QString("<font color=green>%1</font>").
            arg(m_info.m_discussionName);
    m_labelInfo->setText(text);;
}


//remark:public slots:---------------------------

/*************************************************
Function Name： onDoubleClickFriendButton()
Description: 左键 双击
*************************************************/
void IMLinkDiscussionButton::onDoubleClickButton()
{
    m_discussionBtn->openChatRoom();
    m_discussionBtn->showChatRoom();
    emit deleteLinkButton(m_info.m_discussionID);
}



/*************************************************
Function Name： ignoreMessage()
Description: 忽略消息
*************************************************/
void IMLinkDiscussionButton::ignoreMessage()
{
    emit deleteLinkButton(m_info.m_discussionID);
}

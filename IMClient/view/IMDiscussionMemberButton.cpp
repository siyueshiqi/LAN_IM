#include "IMDiscussionMemberButton.h"
#include <QMenu>
#include <QLabel>
#include "IMMainWidget.h"
#include "IMChatWidget.h"
#include "control/IMMainCtrl.h"
#include "IMDiscussionChatWidget.h"
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>

IMDiscussionMemberButton::IMDiscussionMemberButton(const DiscussionMember &discussionMember,
                                                   IMDiscussionChatWidget *discussionWidget,
                                                   IMMainWidget *mainWidget,
                                                   QWidget *parent) :
    QPushButton(parent)
{
    m_info = discussionMember;
    m_discussionWidget = discussionWidget;
    m_mainWidget = mainWidget;
    m_mainCtrl = m_mainWidget->getMainCtrl();
    m_isOpen = false;

    QHBoxLayout *layout = new QHBoxLayout;

    m_labelHead = new QLabel;
    m_labelHead->setFixedSize(HEAD_MINI_SIZE, HEAD_MINI_SIZE);
    m_labelMes = new QLabel;

    layout->addWidget(m_labelHead);
    layout->addWidget(m_labelMes);
    layout->addStretch();
    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);
    setMinimumHeight(25);

    m_menu = NULL;
    setButtonStatus();
    creatMenu();
    setStyleSheet("QPushButton{border: 0;}");
}


IMDiscussionMemberButton::~IMDiscussionMemberButton()
{
}


/*************************************************
Function Name： openChatRoom()
Description: 打开聊天窗口
*************************************************/
void IMDiscussionMemberButton::openChatRoom()
{
    qDebug() << "chat room with discussion member is open";
    if(m_isOpen)
    {
        m_discussionWidget->raise();
        m_discussionWidget->activateWindow();
        m_discussionWidget->show();
        return;
    }
    qDebug() << "create chat room with discussion member";
//    ChatInformation chatInf;
//    chatInf.m_headPortrait = m_info.m_headPortrait;
//    chatInf.m_friendID = m_info.m_userID;
////    chatInf.m_friendMark = m_info.m_mark;
//    chatInf.m_friendNickname = m_info.m_nickname;
//    chatInf.m_friendRemark = m_info.m_remarkName;

//    m_isOpen = true;
//    IMChatWidget *chatRoom = new IMChatWidget(chatInf);
//    m_discussionWidget = chatRoom;
//    m_mainWidget->insertChatRoomMap(chatInf.m_friendID, chatRoom);
//    connect(chatRoom, SIGNAL(sendMessagesFromChat(TalkMessage &)),
//            m_mainWidget, SLOT(receiveMessagesFromChat(TalkMessage &)));
//    connect(chatRoom, SIGNAL(roomQuitSignal()),  this, SLOT(chatRoomQuit()));
//    chatRoom->show();
}


/*************************************************
Function Name： closeChatRoom()
Description: 关闭聊天窗口
*************************************************/
void IMDiscussionMemberButton::closeChatRoom()
{
    if(m_isOpen)
    {
        m_discussionWidget->close();
        m_isOpen = false;
    }
}


/*************************************************
Function Name： setButtonStatus()
Description:  设置button显示信息
*************************************************/
void IMDiscussionMemberButton::setButtonStatus()
{
    QString str = QString("resource/image/head/%1.bmp").
        arg(QString::number(m_info.m_headPortrait));

    QString text, mark;
    m_strDiscussionStatus = getDiscussionStatusFromInt(m_info.m_discussionStatus);
    m_strLoginStatus = getLoginStatusFromInt(m_info.m_loginStatus);
//    if(m_info.m_remark.isEmpty())
        mark = m_info.m_nickname;
//    else
//        mark = m_info.m_remark;
    if(OFFLINE == m_info.m_loginStatus || INVISIBLE == m_info.m_loginStatus)
    {
        QPixmap pixmap;
        QIcon icon(str);
        pixmap = icon.pixmap(QSize(HEAD_MINI_SIZE, HEAD_MINI_SIZE),
                             QIcon::Disabled, QIcon::On);
        m_labelHead->setPixmap(pixmap);

        text = QString("<font size=\"FONT_SIEZE\" color=gray>[%1]%2(%3)[%4]</font>").
                arg(m_strDiscussionStatus, mark, m_info.m_userID, m_strLoginStatus);
    }
    else
    {
        QPixmap pixmap;
        QIcon icon(str);
        pixmap = icon.pixmap(QSize(HEAD_MINI_SIZE, HEAD_MINI_SIZE));
        m_labelHead->setPixmap(pixmap);

        text = QString("<font size=\"FONT_SIEZE\" color=red>[%1]</font>"
                       "<font size=\"FONT_SIEZE\" color=green>%2</font>"
                       "<font size=\"FONT_SIEZE\" color=blue>(%3)</font>"
                       "<font size=\"FONT_SIEZE\" color=black>[%4]</font>").
                arg(m_strDiscussionStatus, mark, m_info.m_userID, m_strLoginStatus);
    }
    //    text = QString("[%1]%2(%3)").arg(m_strStatus, mark, m_info.m_userID);

        //<font size=\"FONT_SIEZE\" color=green>%1    %2: </font>

    m_labelMes->setText(text);

}

//remark:public slots:-----------------------------------------------

// 右键点击按键
void IMDiscussionMemberButton::onClickRightButton(/*const QPoint &*/)
{
    if (m_menu == NULL)
    {
        //创建右键菜单
        creatMenu();
    }
    m_menu->exec(QCursor::pos());
}

/*************************************************
Function Name： onClickSendMessage()
Description: 发送即时消息
*************************************************/
void IMDiscussionMemberButton::onClickSendMessage()
{
    openChatRoom();
}

/*************************************************
Function Name： onClickSendMail()
Description: 发送电子邮件
*************************************************/
void IMDiscussionMemberButton::onClickSendMail()
{
}

/*************************************************
Function Name： onClickShowInformation()
Description: 显示成员详细信息
*************************************************/
void IMDiscussionMemberButton::onClickShowInformation()
{
    m_mainWidget->getFriendInformation(m_info.m_userID);
}

/*************************************************
Function Name： onClickChangeRemark()
Description: 修改群名片
*************************************************/
//void IMDiscussionMemberButton::onClickChangeRemark()
//{
//    bool isOk = false;
//    QString remark = QInputDialog::getText(NULL, "修改名片",
//                                           "请输入新的名片",
//                                           QLineEdit::Normal,
//                                           m_info.m_remark,
//                                           &isOk);

//    if (isOk && 0 != remark.compare(m_info.m_remark))
//    {
//        qDebug("request-change-remark");
//        TempStrings tmpStr;
//        tmpStr.m_one = m_info.m_discussionID;
//        tmpStr.m_two = m_info.m_userID;
//        tmpStr.m_three = remark;
//        m_mainWidget->changeDiscussionMemberRemark(tmpStr);
//    }

//}

/*************************************************
Function Name： onClickEnterSpace
Description: 进入空间
*************************************************/
void IMDiscussionMemberButton::onClickEnterSpace()
{
}

/*************************************************
Function Name： onClickRemoveMember
Description: 移除该成员
*************************************************/
void IMDiscussionMemberButton::onClickRemoveMember()
{
    QMessageBox::StandardButton returnBtn;

    returnBtn = QMessageBox::question(NULL, tr("移除讨论组成员"),
        QString(tr("你确定要将成员%1,从讨论组%2中移除吗？")).
            arg(m_info.m_userID,m_discussionWidget->getDiscussionInformation().m_discussionID),
        QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if (m_mainWidget == NULL)
        return;
    if(QMessageBox::Yes == returnBtn)
        m_mainWidget->leaveDiscussion(m_info.m_userID,
                                 m_discussionWidget->getDiscussionInformation().m_discussionID);
}


/*************************************************
Function Name： onClickAddFriend
Description: 加好友
*************************************************/
void IMDiscussionMemberButton::onClickAddFriend()
{
    m_mainWidget->addFriend(m_info.m_userID);
}


/*************************************************
Function Name： onDoubleClickMemberButton
Description: 左键 双击
*************************************************/
void IMDiscussionMemberButton::onDoubleClickMemberButton()
{
    openChatRoom();
}

/*************************************************
Function Name： chatRoomQuit
Description: 聊天窗口关闭了
*************************************************/
void IMDiscussionMemberButton::chatRoomQuit()
{
    m_isOpen = false;
//    if (NULL != m_discussionWidget)
//        m_discussionWidget->removeChatWidget(m_info.m_userID);
}


//remark:protected:----------------------------------------

/*************************************************
Function Name： mousePressEvent
Description: 鼠标单击事件
*************************************************/
void IMDiscussionMemberButton::mousePressEvent(QMouseEvent *event)
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
void IMDiscussionMemberButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
//        emit leftDoubleClickSignal();
        onDoubleClickMemberButton();
        return;
    }
    QPushButton::mouseDoubleClickEvent(event);
}



//remark:private:----------------------------------------

/*************************************************
Function Name： getDiscussionStatusFromInt()
Description: 将群成员身份从数字形式转换为字符串形式
*************************************************/
QString IMDiscussionMemberButton::getDiscussionStatusFromInt(const int n) const
{
    switch (n)
    {
    case DISCUSSION_HOST:
        return tr("组长");
        break;
    case DISCUSSION_MEMBER:
        return tr("成员");
        break;
    default:
        break;
    }
    return NULL;
}


/*************************************************
Function Name： getLoginStatusFromInt()
Description: 将好友在线状态从数字形式转换为字符串形式
*************************************************/
QString IMDiscussionMemberButton::getLoginStatusFromInt(const int n) const
{
    switch (n)
    {
    case ONLINE:
        return tr("在线");
        break;
    case OFFLINE:
    case INVISIBLE:
        return tr("离线");
        break;
    case BUSY:
        return tr("忙碌");
        break;
    case LEAVE:
        return tr("离开");
        break;
    case NOTDISTURB:
        return tr("请勿打扰");
        break;
    default:
        break;
    }
    return NULL;
}


/*************************************************
Function Name： getStatusFromInt()
Description: 创建右键菜单
*************************************************/
void IMDiscussionMemberButton::creatMenu(/*const QList<QString> *groutList*/)
{
    m_menu = new QMenu(this);
    QAction *sendMessage = new QAction(tr("发送即时消息"), m_menu);
    QAction *sendMail = new QAction(tr("发送电子邮件"), m_menu);
    QAction *showInfo = new QAction(tr("查看资料"), m_menu);
    QAction *enterSpace = new QAction(tr("进入空间"), m_menu);
    QAction *removeMember= new QAction(tr("移除该成员"), m_menu);
//    QAction *changeRemark = new QAction(tr("修改群名片"), m_menu);
    QAction *addRriend= new QAction(tr("加为好友"), m_menu);

    connect(sendMessage, SIGNAL(triggered()),
        this, SLOT(onClickSendMessage()));
    connect(sendMail, SIGNAL(triggered()),
        this, SLOT(onClickSendMail()));
    connect(showInfo, SIGNAL(triggered()),
        this, SLOT(onClickShowInformation()));
    connect(enterSpace, SIGNAL(triggered()),
        this, SLOT(onClickEnterSpace()));
    connect(removeMember, SIGNAL(triggered()),
        this, SLOT(onClickRemoveMember()));
//    connect(changeRemark, SIGNAL(triggered()),
//        this, SLOT(onClickChangeRemark()));
    connect(addRriend, SIGNAL(triggered()),
        this, SLOT(onClickAddFriend()));


    // 自己
    if (m_mainWidget->getLocalMyInformation().m_userID == m_info.m_userID)
    {
//        m_menu->addAction(showInfo);
        m_menu->addAction(enterSpace);
//        m_menu->addAction(changeRemark);

    }

    // 不是自己 - 是群主
    else if (m_mainWidget->getLocalMyInformation().m_userID ==
             m_discussionWidget->getDiscussionInformation().m_creatorID)
    {
        m_menu->addAction(sendMessage);
        m_menu->addAction(sendMail);
        m_menu->addAction(showInfo);
        m_menu->addAction(enterSpace);
        m_menu->addSeparator();
//        m_menu->addAction(changeRemark);
//        m_menu->addAction(removeMember);

        // 不是好友
        if (!m_mainWidget->isMyFriend(m_info.m_userID))
        {

            m_menu->addAction(addRriend);
        }
    }
    // 不是自己 - 不是群主
    else
    {
        m_menu->addAction(sendMessage);
        m_menu->addAction(sendMail);
        m_menu->addAction(showInfo);
        m_menu->addAction(enterSpace);
        m_menu->addSeparator();

        // 不是好友
        if (!m_mainWidget->isMyFriend(m_info.m_userID))
        {
            m_menu->addAction(addRriend);
        }
    }
}

#include "IMFriendButton.h"
#include <QMenu>
#include <QBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include "view/IMChatWidget.h"
#include "view/IMMainWidget.h"

IMFriendButton::IMFriendButton(const FriendInformation &info,
                               QList<QString> *groupList,
                               IMMainWidget *mainWidget,
                               QWidget *parent) :
    QPushButton(parent)
{
    m_info = info;
    m_mainWidget = mainWidget;
    m_isOpen = false;
    m_isShow = false;

//    setAutoRaise(TRUE);

    QHBoxLayout *layout = new QHBoxLayout;
//    m_iconHead = new QIcon;
    m_labelHead = new QLabel;
    m_labelHead->setFixedSize(HEAD_SMALL_SIZE, HEAD_SMALL_SIZE);
    m_labelMes = new QLabel;
//    layout->addSpacing(1);
//    layout->addWidget(m_iconHead);
    layout->addWidget(m_labelHead);
    layout->addWidget(m_labelMes);
    layout->addStretch();
    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);
    setMinimumSize(100,40);

    m_menu = NULL;
    m_moveFriendMenu = NULL;
    m_groupList = groupList;
    setButtonStatus();

//    connect(this, SIGNAL(clicked()), this, SLOT(onClickFriendButton()));
//    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
//        this, SLOT(onClickRightButton(const QPoint &)));

    setStyleSheet("QPushButton{border: 0;}");
}


IMFriendButton::~IMFriendButton()
{

}

/*************************************************
Function Name： openChatRoom()
Description: 打开聊天窗口
*************************************************/
void IMFriendButton::openChatRoom()
{
//    if(isOpen)
//        return;
//    isOpen = true;
//    room = new Chatroom(link, friInf, myAccount, myName, NULL);
//    connect(room, SIGNAL(roomQuitSignal()),  this, SLOT(chatRoomQuit()));
//    room->show();

    if(m_isOpen)
    {
//        m_chatRoom->raise();
//        m_chatRoom->activateWindow();
//        m_chatRoom->show();
        return;
    }
    ChatInformation chatInf;
    chatInf.m_myID = m_mainWidget->getLocalMyInformation().m_userID;
    chatInf.m_headPortrait = m_info.m_headPortrait;
    chatInf.m_friendID = m_info.m_userID;
//    chatInf.m_friendMark = m_info.m_mark;
    chatInf.m_friendNickname = m_info.m_nickname;
    chatInf.m_friendRemark = m_info.m_remarkName;
    chatInf.m_friendStatus = m_info.m_status;

    m_isOpen = true;
    IMChatWidget *chatRoom = new IMChatWidget(chatInf);

//    QString str = QString("resource/image/head/%1.bmp").
//        arg(QString::number(m_info.m_headPortrait));
//    QIcon icon(str);
//    chatRoom->setWindowIcon(icon);

    m_chatRoom = chatRoom;
    m_mainWidget->insertChatRoomMap(chatInf.m_friendID, chatRoom);
    connect(chatRoom, SIGNAL(sendMessagesFromChat(TalkMessage &)),
            m_mainWidget, SLOT(receiveMessagesFromChat(TalkMessage &)));
    connect(chatRoom, SIGNAL(roomQuitSignal()),  this, SLOT(chatRoomQuit()));
//    chatRoom->show();
}


/*************************************************
Function Name： showChatRoom()
Description: 显示聊天窗口
*************************************************/
void IMFriendButton::showChatRoom()
{
    m_chatRoom->raise();
    m_chatRoom->activateWindow();
    m_chatRoom->show();
    m_isShow = true;
}

/*************************************************
Function Name： closeChatRoom()
Description: 关闭聊天窗口
*************************************************/
void IMFriendButton::closeChatRoom()
{
    if(m_isOpen)
    {
        m_chatRoom->close();
        m_isOpen = false;
        m_isShow = false;
    }
}

/*************************************************
Function Name： setButtonStatus()
Description:  设置button显示信息
*************************************************/
void IMFriendButton::setButtonStatus()
{
    QString str = QString("resource/image/head/%1.bmp").
        arg(QString::number(m_info.m_headPortrait));

    QString text, mark;
    m_strStatus = getStatusFromInt(m_info.m_status);
    if(m_info.m_remarkName.isEmpty())
        mark = m_info.m_nickname;
    else
        mark = m_info.m_remarkName;
    if(OFFLINE == m_info.m_status || INVISIBLE == m_info.m_status)
    {
        QPixmap pixmap;
        QIcon icon(str);
        pixmap = icon.pixmap(QSize(HEAD_SMALL_SIZE, HEAD_SMALL_SIZE),
                             QIcon::Disabled, QIcon::On);
        m_labelHead->setPixmap(pixmap);

        text = QString("<font color=gray>%1(%2)<br>[%3]</font>").
                arg(m_info.m_userID).arg(mark).arg(m_strStatus);
    }
    else
    {
        m_labelHead->setPixmap(QPixmap(str));

        text = QString("<font color=green>%1(%2)<br>[%3]</font>").
                arg(m_info.m_userID).arg(mark).arg(m_strStatus);
    }
    m_labelMes->setText(text);
}


/*************************************************
Function Name： refreshMoveMenu()
Description: 刷新菜单中分组信息
*************************************************/
void IMFriendButton::refreshMoveMenu()
{
    if (m_menu == NULL || m_moveFriendMenu == NULL)
    {
        return;
    }

    m_moveFriendMenu->clear();
    QString groupName;
    for (int i = 0; i<m_groupList->size(); ++i)
    {
        groupName = m_groupList->value(i);
        if (0 != groupName.compare(m_info.m_groupName))
        {
            QAction * action = new QAction(groupName, m_moveFriendMenu);

            //remakr: todo : 重载action triggered 的时候 发送自定义信号
            m_moveFriendMenu->addAction(action);
            connect(action, SIGNAL(triggered()),
                        this, SLOT(onClickMove()));

            // 或者弹出一个选择框
        }
    }
}

//remark:public slots:---------------------------

/*************************************************
Function Name： onDoubleClickFriendButton()
Description: 左键 双击
*************************************************/
void IMFriendButton::onDoubleClickFriendButton()
{
    openChatRoom();
    showChatRoom();
    m_mainWidget->removeLinkButton(m_info.m_userID);
}


/*************************************************
Function Name： onClickRightButton()
Description: 右键 单击
*************************************************/
void IMFriendButton::onClickRightButton(/*const QPoint &*/)
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
void IMFriendButton::onClickSendMessage()
{
    openChatRoom();
}

/*************************************************
Function Name： onClickShowRecord()
Description: 查看消息记录
*************************************************/
void IMFriendButton::onClickShowRecord()
{
    m_mainWidget->showMessageWidget();
}

/*************************************************
Function Name： onClickSendMail()
Description: 发送电子邮件
*************************************************/
void IMFriendButton::onClickSendMail()
{
    m_mainWidget->showMailWriteWidget(m_info.m_userID);
}

/*************************************************
Function Name： onClickShowInformation()
Description: 显示好友详细信息
*************************************************/
void IMFriendButton::onClickShowInformation()
{
    m_mainWidget->getFriendInformation(m_info.m_userID);
}

/*************************************************
Function Name： onClickChangeRemark()
Description: 修改好友备注
*************************************************/
void IMFriendButton::onClickChangeRemark()
{
    bool isOk = false;
    QString remark = QInputDialog::getText(NULL, "修改好友备注",
                                           "请输入新的备注名称",
                                           QLineEdit::Normal,
                                           m_info.m_remarkName,
                                           &isOk);

    if (isOk && 0 != remark.compare(m_info.m_remarkName))
    {
        qDebug("request-change-remark");
        m_mainWidget->changeFriendRemark(m_info.m_userID, remark);
    }

}

/*************************************************
Function Name： onClickMove()
Description: 移动好友至其他分组
*************************************************/
void IMFriendButton::onClickMove()
{
    QAction* action = dynamic_cast<QAction*>(sender());
    m_mainWidget->moveFriendToBox(m_info.m_userID, m_info.m_groupName, action->text());
//    qDebug() << action->text();
}

/*************************************************
Function Name： onClickRemoveFriend()
Description: 删除好友
*************************************************/
void IMFriendButton::onClickRemoveFriend()
{
    QMessageBox::StandardButton returnBtn;

    returnBtn = QMessageBox::question(NULL, tr("删除好友"),
        QString(tr("你确定要删除好友(%1)吗？")).arg(m_info.m_userID),
        QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(QMessageBox::Yes == returnBtn)
        m_mainWidget->deleteFriend(m_info.m_userID);
}

/*************************************************
Function Name： chatRoomQuit()
Description: 进入空间
*************************************************/
void IMFriendButton::onClickEnterSpace()
{
}

/*************************************************
Function Name： chatRoomQuit()
Description: 聊天室被关闭
*************************************************/
void IMFriendButton::chatRoomQuit()
{
    m_isOpen = false;
    m_isShow = false;
    if (NULL != m_mainWidget)
        m_mainWidget->removeChatWidget(m_info.m_userID);
}

//remark:protected:----------------------------------------

/*************************************************
Function Name： mousePressEvent
Description: 鼠标单击事件
*************************************************/
void IMFriendButton::mousePressEvent(QMouseEvent *event)
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
void IMFriendButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
//        emit leftDoubleClickSignal();
        onDoubleClickFriendButton();
        return;
    }
    QPushButton::mouseDoubleClickEvent(event);
}



//remark:private:----------------------------------------

/*************************************************
Function Name： getStatusFromInt()
Description: 将好友状态从数字形式转换为字符串形式
*************************************************/
QString IMFriendButton::getStatusFromInt(const int n) const
{
//    ONLINE = 0,    // 在线
//    INVISIBLE = 1, // 隐身
//    BUSY = 2,      // 忙碌
//    LEAVE = 3,     // 离开
//    NOTDISTURB = 4 // 请勿打扰
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
void IMFriendButton::creatMenu(/*const QList<QString> *groutList*/)
{
    m_menu = new QMenu(this);
    QAction *sendMessage = new QAction(tr("发送即时消息"), m_menu);
    QAction *showRecord = new QAction(tr("查看消息记录"), m_menu);
    QAction *sendMail = new QAction(tr("发送电子邮件"), m_menu);

    QAction *showInfo = new QAction(tr("查看资料"), m_menu);
    QAction *changeRemar = new QAction(tr("修改备注名称"), m_menu);
    QAction *removeFriend = new QAction(tr("删除好友"), m_menu);
    QAction *enterSpace = new QAction(tr("进入好友空间"), m_menu);

    m_moveFriendMenu= new QMenu(tr("移动好友至"), m_menu);
    refreshMoveMenu();

    connect(sendMessage, SIGNAL(triggered()),
        this, SLOT(onDoubleClickFriendButton()));
    connect(showRecord, SIGNAL(triggered()),
        this, SLOT(onClickShowRecord()));
    connect(sendMail, SIGNAL(triggered()),
        this, SLOT(onClickSendMail()));

    connect(showInfo, SIGNAL(triggered()),
        this, SLOT(onClickShowInformation()));
    connect(changeRemar, SIGNAL(triggered()),
        this, SLOT(onClickChangeRemark()));
    connect(removeFriend, SIGNAL(triggered()),
        this, SLOT(onClickRemoveFriend()));
    connect(enterSpace, SIGNAL(triggered()),
        this, SLOT(onClickEnterSpace()));

    m_menu->addAction(sendMessage);
    m_menu->addAction(showRecord);
    m_menu->addAction(sendMail);
    m_menu->addAction(showInfo);
    m_menu->addAction(changeRemar);
    m_menu->addSeparator();

    m_menu->addMenu(m_moveFriendMenu);
    m_menu->addAction(removeFriend);
    m_menu->addAction(enterSpace);
}



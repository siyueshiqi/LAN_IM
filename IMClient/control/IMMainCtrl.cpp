#include "IMMainCtrl.h"
#include "model/IMTcpSocket.h"
#include "view/IMLoginWidget.h"
#include <QMessageBox>

// mark: public -----------------------------------------------------
IMMainCtrl::IMMainCtrl(const QString myID, QObject *parent) :
    m_myID(myID), QObject(parent)
{
    m_tcpSocket = new IMTcpSocket(this);
    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(requestGetFriendsInformation()));
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(closeWindow()));
}

void IMMainCtrl::closeConnect()
{
    m_tcpSocket->close();
}

/*************************************************
Function Name： getFriendsInformation
Description: 获取所有好友信息
*************************************************/
void IMMainCtrl::getFriendsInformation(const QString &id, const int status)
{
    m_myID = id;
    m_status = status;
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
    {
        requestGetFriendsInformation();
    }
    else
    {
        m_blockSize = 0;
        m_tcpSocket->requestConnect();
    }
}


/*************************************************
Function Name： getFlocksInformation
Description: 获取群信息列表
*************************************************/
void IMMainCtrl::getFlocksInformation(const QString & id)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestGetFlocksInformation(id);
}

/*************************************************
Function Name： getDiscussionsInformation
Description: 获取讨论组信息列表
*************************************************/
void IMMainCtrl::getDiscussionsInformation(const QString & id)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestGetDiscussionsInformation(id);
}

/*************************************************
Function Name： getLatestMessage
Description: 获取本地最近消息
*************************************************/
void IMMainCtrl::getLatestMessage(const QString & id)
{
    //访问本地数据库
}

/*************************************************
Function Name： getFlockMembers
Description: 获取群所有成员
*************************************************/
void IMMainCtrl::getFlockMembers(const QString & id)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestGetFlockMembers(id);
}

/*************************************************
Function Name： getDiscussionMembers
Description: 获取讨论组所有成员
*************************************************/
void IMMainCtrl::getDiscussionMembers(const QString & id)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestGetDiscussionMembers(id);
}

/*************************************************
Function Name： sendTalkMessage
Description: 发送聊天信息
*************************************************/
void IMMainCtrl::sendTalkMessage(TalkMessage &mes)
{
//    if (mes.m_type == TALK_MESSAGE)
    mes.m_senderID = m_myID;
    mes.m_senderIP = IMTcpSocket::getIP();
    m_messageVector.push_back(mes);
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
    {
        requestSendTalkMessage();
    }
//    else
//    {
//        m_blockSize = 0;
//        m_tcpSocket->requestConnect();
//    }
}


//// 发送群聊天信息
//void IMMainCtrl::sendFlockTalkMessage(TalkMessage & mes)
//{
//    if (NULL == m_tcpSocket)
//        return;
//    if (m_tcpSocket->isConnected())
//    {
//        requestSendFlockTalkMessage(mes);
//    }
//}

//// 发送讨论组聊天信息
//void IMMainCtrl::sendDiscussionTalkMessage(TalkMessage & mes)
//{
//    if (NULL == m_tcpSocket)
//        return;
//    if (m_tcpSocket->isConnected())
//    {
//        requestSendFlockTalkMessage(mes);
//    }
//}

/*************************************************
Function Name： getFriendInformation
Description: 获取好友详细信息
*************************************************/
void IMMainCtrl::getFriendInformation(const QString &id)
{
//    m_friendID = id;
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
    {
        requestGetFriendInformation(id);
    }
//    else
//    {
//        m_blockSize = 0;
//        m_tcpSocket->requestConnect();
//    }
}


/*************************************************
Function Name： getMynformation
Description: 获取自己详细信息
*************************************************/
void IMMainCtrl::getMynformation(const QString &id)
{
    m_myID = id;
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
    {
        requestGetMyInformation();
    }
    else
    {
        m_blockSize = 0;
        m_tcpSocket->requestConnect();
    }
}

/*************************************************
Function Name： changeMyInformation
Description: 修改自己的信息
*************************************************/
void IMMainCtrl::changeMyInformation(const UserInformation &me)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
    {
        requestChangeMyInformation(me);
    }
//    else
//    {
//        m_blockSize = 0;
//        m_tcpSocket->requestConnect();
//    }
}


/*************************************************
Function Name： changeMyStatus
Description: 修改自己的状态
*************************************************/
void IMMainCtrl::changeMyStatus(const QString id, const int status)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestChangeMyStatus(id, status);
}

/*************************************************
Function Name： changeFriendRemark
Description: 修改好友备注
*************************************************/
void IMMainCtrl::changeFriendRemark(const QString & myID,
                                    const QString & friendID,
                                    const QString & remark)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestChangeFriendRemark(myID, friendID, remark);
}

/*************************************************
Function Name： deleteFriend
Description: 删除好友
*************************************************/
void IMMainCtrl::deleteFriend(const QString & myID, const QString & friendID)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestDeleteFriend(myID, friendID);
}

/*************************************************
Function Name： addFriend
Description: 添加好友
*************************************************/
void IMMainCtrl::addFriend(const TalkMessage & mes)//const TempStrings & temp)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestAddFriend(mes);
}

/*************************************************
Function Name： addFlock
Description: 加入群
*************************************************/
void IMMainCtrl::addFlock(const TalkMessage & mes)//const TempStrings & temp)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestAddFlock(mes);
}


/*************************************************
Function Name： addDiscussion
Description: 加入讨论组
*************************************************/
void IMMainCtrl::addDiscussion(const TalkMessage & mes)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestAddDiscussion(mes);
}


/*************************************************
Function Name： dropFlock
Description: 解散群
*************************************************/
void IMMainCtrl::dropFlock(const QString & userID, const QString & flockID)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestDropFlock(userID, flockID);
}

/*************************************************
Function Name： dropFlock
Description: 解散讨论组
*************************************************/
void IMMainCtrl::dropDiscussion(const QString & userID, const QString & discussionID)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestDropDiscussion(userID, discussionID);
}

/*************************************************
Function Name： leaveFlock
Description: 退出群
*************************************************/
void IMMainCtrl::leaveFlock(const QString & userID, const QString & flockID)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestLeaveFlock(userID, flockID);
}

/*************************************************
Function Name： leaveDiscussion
Description: 退出讨论组
*************************************************/
void IMMainCtrl::leaveDiscussion(const QString & userID, const QString & discussionID)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestLeaveDiscussion(userID, discussionID);
}

/*************************************************
Function Name： createFlock
Description: 创建群
*************************************************/
void IMMainCtrl::createFlock(const TempStrings & tmpStr)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestCreateFlock(tmpStr);
}


/*************************************************
Function Name： createDiscussion
Description: 创建讨论组
*************************************************/
void IMMainCtrl::createDiscussion(const TempStrings & tmpStr)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestCreateDiscussion(tmpStr);
}

/*************************************************
Function Name： changeFlockInformation
Description: 修改群信息
*************************************************/
void IMMainCtrl::changeFlockInformation(const FlockInformation & flock)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestChangeFlockInformation(flock);
}

/*************************************************
Function Name： changeFlockMemberRemark
Description: 修改群成员名片
*************************************************/
void IMMainCtrl::changeFlockMemberRemark(const TempStrings & tmpStr)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestChangeFlockMemberRemark(tmpStr);
}



/*************************************************
Function Name： changeDiscussionInformation
Description: 修改讨论组信息
*************************************************/
void IMMainCtrl::changeDiscussionInformation(const DiscussionInformation & discussion)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestChangeDiscussionInformation(discussion);
}


/*************************************************
Function Name： resultOfFriendRequest
Description: 好友请求结果
*************************************************/
void IMMainCtrl::resultOfFriendRequest(const TalkMessage & mes)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestSendResultOfFriendRequest(mes);
}


/*************************************************
Function Name： resultOfFlockRequest
Description: 群请求结结果
*************************************************/
void IMMainCtrl::resultOfFlockRequest(const TalkMessage & mes)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestSendResultOfFlockRequest(mes);
}


/*************************************************
Function Name： removeBox
Description: 删除分组
*************************************************/
void IMMainCtrl::removeBox(const QString & title)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestRemoveBox(title);
}


/*************************************************
Function Name： renameBox
Description: 重命名分组
*************************************************/
void IMMainCtrl::renameBox(const QString & oldTitle, const QString & newTitle)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestRenameBox(oldTitle, newTitle);
}

/*************************************************
Function Name： moveFriendToBox
Description:  移动好友至其他分组
*************************************************/
void IMMainCtrl::moveFriendToBox(const QString &friendID, const QString &oldTitle,
                                 const QString & newTitle)
{
    if (NULL == m_tcpSocket)
        return;
    if (m_tcpSocket->isConnected())
        requestMoveFriendToBox(friendID, oldTitle, newTitle);
}



// mark: public slots:---------------------------------------------------
/*************************************************
Function Name： requestGetFriendsInformation()
Description: 发送获取所有好友信息的请求
*************************************************/
void IMMainCtrl::requestGetFriendsInformation()
{
    if (NULL == m_tcpSocket)
        return;
    qDebug() << "request friends: " << m_myID;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(GET_ALL_FRIENDS) << m_myID << m_status;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name： requestGetFlocksInformation()
Description: 发送获取所有群信息的请求
*************************************************/
void IMMainCtrl::requestGetFlocksInformation(const QString & id)
{
    if (NULL == m_tcpSocket)
        return;
    qDebug() << "request Flocks: " << id;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(GET_ALL_FLOCKS) << id;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： requestGetDiscussionsInformation()
Description: 发送获取所有讨论组信息的请求
*************************************************/
void IMMainCtrl::requestGetDiscussionsInformation(const QString & id)
{
    if (NULL == m_tcpSocket)
        return;
    qDebug() << "request Discussions: " << id;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(GET_ALL_DISCUSSIONS) << id;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name： requestGetFlockMembers()
Description: 发送获取群所有成员的请求
*************************************************/
void IMMainCtrl::requestGetFlockMembers(const QString & id)
{
    if (NULL == m_tcpSocket)
        return;
    qDebug() << "request flock members: " << id;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(GET_FLOCK_MEMBERS) << id;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name： requestGetDiscussionMembers()
Description: 发送获取讨论组所有成员的请求
*************************************************/
void IMMainCtrl::requestGetDiscussionMembers(const QString & id)
{
    if (NULL == m_tcpSocket)
        return;
    qDebug() << "request Discussion members: " << id;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(GET_DISCUSSIONS_MEMBERS) << id;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： requestGetFriendInformation()
Description: 发送获取好友详细信息的请求
*************************************************/
void IMMainCtrl::requestGetFriendInformation(const QString &id)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(GET_FRIEND_INFORMATION) << id;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： requestGetMyInformation()
Description: 发送获取自己详细信息的请求
*************************************************/
void IMMainCtrl::requestGetMyInformation()
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(GET_MYSELF_INFORMATION) << m_myID;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： requestChangeMyInformation()
Description: 发送修改自己信息的请求
*************************************************/
void IMMainCtrl::requestChangeMyInformation(const UserInformation &me)
{
    if (NULL == m_tcpSocket)
        return;

    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(CHANGE_INFORMATION) << me;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： requestChangeMyStatus()
Description: 发送修改自己状态的请求
*************************************************/
void IMMainCtrl::requestChangeMyStatus(const QString id, const int status)
{
    if (NULL == m_tcpSocket)
        return;

    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(CHANGE_STATUE) << id << status;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： requestChangeFriendRemark()
Description: 发送修改好友备注的请求
*************************************************/
void IMMainCtrl::requestChangeFriendRemark(const QString & myID,
                                           const QString & friendID,
                                           const QString &remark)
{
    if (NULL == m_tcpSocket)
        return;

    TempStrings tempStr;
    tempStr.m_one = myID;
    tempStr.m_two = friendID;
    tempStr.m_three = remark;

    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(CHANGE_REMARK) << tempStr;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name： requestDeleteFriend()
Description: 发送删除好友的请求
*************************************************/
void IMMainCtrl::requestDeleteFriend(const QString & myID,
                                     const QString & friendID)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(DELETE_FRIEND) << myID << friendID;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： requestAddFriend()
Description: 发送添加好友的请求
*************************************************/
void IMMainCtrl::requestAddFriend(const TalkMessage & mes)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(ADD_FRIEND) << mes;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： requestAddFlock()
Description: 发送加入群的请求
*************************************************/
void IMMainCtrl::requestAddFlock(const TalkMessage & mes)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(ADD_FLOCK) << mes;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name： requestAddDiscussion()
Description: 请求加入讨论组的请求
*************************************************/
void IMMainCtrl::requestAddDiscussion(const TalkMessage & mes)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(ADD_DISCUSSION) << mes;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： requestDropFlock()
Description: 发送解散群的请求
*************************************************/
void IMMainCtrl::requestDropFlock(const QString & userID, const QString & flockID)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(DROP_FLOCK) << userID << flockID;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name： requestDropDiscussion()
Description: 发送解散讨论组的请求
*************************************************/
void IMMainCtrl::requestDropDiscussion(const QString & userID, const QString & discussionID)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(DROP_DISCUSSION) << userID << discussionID;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： requestLeaveFlock()
Description: 发送退出群的请求
*************************************************/
void IMMainCtrl::requestLeaveFlock(const QString & userID, const QString & flockID)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(LEAVE_FLOCK) << userID << flockID;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name： requestLeaveDiscussion()
Description: 发送退出讨论组的请求
*************************************************/
void IMMainCtrl::requestLeaveDiscussion(const QString & userID,
                                        const QString & discussionID)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(LEAVE_DISCUSSION) << userID << discussionID;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： requestCreateFlock()
Description: 发送创建群的请求
*************************************************/
void IMMainCtrl::requestCreateFlock(const TempStrings & tmpStr)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(CREATE_FLOCK) << tmpStr;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name： requestCreateDiscussion()
Description: 发送创建群的请求
*************************************************/
void IMMainCtrl::requestCreateDiscussion(const TempStrings & tmpStr)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(CREATE_DISCUSSION) << tmpStr;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name： requestSendResultOfFriendRequest
Description: 发送处理好友请求结果的请求
*************************************************/
void IMMainCtrl::requestSendResultOfFriendRequest(const TalkMessage & mes)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(ADD_FRIEND) << mes;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name： requestSendResultOfFriendRequest
Description: 发送处理群请求结果的请求
*************************************************/
void IMMainCtrl::requestSendResultOfFlockRequest(const TalkMessage & mes)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(ADD_FLOCK) << mes;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}



/*************************************************
Function Name： requestChangeFlockInformation
Description: 发送修改群信息的请求
*************************************************/
void IMMainCtrl::requestChangeFlockInformation(const FlockInformation &flock)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(CHANGE_FLOCK) << flock;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name： requestChangeFlockMemberRemark
Description: 发送修改群成员名片的请求
*************************************************/
void IMMainCtrl::requestChangeFlockMemberRemark(const TempStrings & tmpStr)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(CHANGE_FLOCK_REMARK) << tmpStr;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}



/*************************************************
Function Name： requestChangeDiscussionInformation
Description: 发送修改讨论组信息的请求
*************************************************/
void IMMainCtrl::requestChangeDiscussionInformation(
        const DiscussionInformation & discussion)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(CHANGE_DISCUSSION) << discussion;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： requestSendTalkMessage
Description: 发送对话信息请求
*************************************************/
void IMMainCtrl::requestSendTalkMessage()
{
    if (NULL == m_tcpSocket)
        return;

    while (m_messageVector.size() > 0)
    {
        m_blockSize = 0;
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_8);
        out << quint16(0) << int(TALK)
            << m_messageVector.front();
        out.device()->seek(0);
        out << quint16(block.size() - sizeof(quint16));
        m_tcpSocket->write(block);

        m_messageVector.pop_front();
    }
}


/*************************************************
Function Name： requestRemoveBox
Description: 发送删除分组的请求
*************************************************/
void IMMainCtrl::requestRemoveBox(const QString & title)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(REMOVE_BOX) << m_myID << title;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： requestRenameBox
Description: 发送重命名分组的请求
*************************************************/
void IMMainCtrl::requestRenameBox(const QString & oldTitle, const QString & newTitle)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(RENAME_BOX) << m_myID << oldTitle << newTitle;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name： requestMoveFriendToBox
Description:  请求移动好友至其他分组
*************************************************/
void IMMainCtrl::requestMoveFriendToBox(const QString & friendID,
                                        const QString & oldTitle,
                                        const QString & newTitle)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(MOVE_FRIEND_BOX) << m_myID << friendID << oldTitle << newTitle;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name： requestGetNetWorkHistoryMessageOneFriendOneDate
Description:  获取某日某好友在服务器的消息
*************************************************/
void IMMainCtrl::requestGetNetWorkHistoryMessageOneFriendOneDate(
        const QString & friendID, const QDate & date)
{
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(GET_HISTORY_MESSAGE) << m_myID << friendID << date;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name： requestChangePwd
Description:  发送修改密码的请求
*************************************************/
void IMMainCtrl::requestChangePwd(const QString & oldPwd, const QString & newPwd)
{
    if (NULL == m_tcpSocket)
        return;

    TempStrings tmpStr;
    tmpStr.m_one = m_myID;
    tmpStr.m_two = oldPwd;
    tmpStr.m_three = newPwd;

    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(CHANGE_PASSWORD) << tmpStr;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： readMessage
Description: 读取信息
*************************************************/
void IMMainCtrl::readMessage()
{
    if (NULL == m_tcpSocket)
        return;

    QDataStream in(m_tcpSocket);
    in.setVersion(QDataStream::Qt_4_8);
    if (m_blockSize == 0)
    {
        if (m_tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> m_blockSize;
    }

    if (m_tcpSocket->bytesAvailable() < m_blockSize)
        return;
    int type;

    in >> type;
    int len;

    switch (type)
    {
    case NO_FRIEND:
    {
        requestGetFlocksInformation(m_myID);
        break;
    }
    case GET_ALL_FRIENDS_FAIL:
        break;
    case GET_ALL_FRIENDS_SUCCESS:
    {
        in >> len;
        m_friendsVec.clear();
        m_friendsVec.resize(len);
        for(int i=0; i<len; i++)
        {
            in >> m_friendsVec[i];
        }
        qDebug() << "friends len: " << len;
        emit getFriendsSuccess(m_friendsVec);
        break;
    }
    case NO_FLOCK:
    {
        requestGetDiscussionsInformation(m_myID);
        break;
    }
    case GET_ALL_FLOCKS_FAIL:
    {
        break;
    }
    case GET_ALL_FLOCKS_SUCCESS:
    {
        in >> len;
        m_flocksVec.clear();
        m_flocksVec.resize(len);
        for(int i=0; i<len; i++)
        {
            in >> m_flocksVec[i];
        }
        qDebug() << "flocks len: " << len;
        emit getFlocksSuccess(m_flocksVec);
        break;
    }
    case NO_DISCUSSION:
    {
        break;
    }
    case GET_ALL_DISCUSSIONS_FAIL:
    {
        break;
    }
    case GET_ALL_DISCUSSIONS_SUCCESS:
    {
        in >> len;
        m_discussionsVec.clear();
        m_discussionsVec.resize(len);
        for(int i=0; i<len; i++)
        {
            in >> m_discussionsVec[i];
        }
        qDebug() << "discussions len: " << len;
        emit getDiscussionsSuccess(m_discussionsVec);
        break;
    }
    case GET_FLOCK_MEMBERS_SUCCESS:
    {
        in >> len;
        m_flockMembersVec.clear();
        m_flockMembersVec.resize(len);
        for(int i=0; i<len; i++)
        {
            in >> m_flockMembersVec[i];
        }
        qDebug() << "flock-members len: " << len;
        emit getFlockMembersSuccess(m_flockMembersVec);
        break;
    }
    case GET_DISCUSSION_MEMBERS_SUCCESS:
    {
        in >> len;
        m_discussionMembersVec.clear();
        m_discussionMembersVec.resize(len);
        for(int i=0; i<len; i++)
        {
            in >> m_discussionMembersVec[i];
        }
        qDebug() << "discussion-members len: " << len;
        emit getDiscussionMembersSuccess(m_discussionMembersVec);
        break;
    }
    case GET_FRIEND_FAIL:
        break;
    case GET_FRIEND_SUCCESS:
    {
        in >> m_friInf;
        emit getFriendInformationSuccess(m_friInf);
        break;
    }
    case GET_MYSELF_FAIL:
    {
        break;
    }
    case GET_MYSELF_SUCCESS:
    {
        in >> m_myInf;
        emit getMyInformationSuccess(m_myInf);
        break;
    }
    case CHANGE_INFORMATION_FAIL:
    {
        QMessageBox::critical(NULL, tr("修改个人信息"), tr("修改个人信息失败"));
        break;
    }
    case CHANGE_INFORMATION_SUCCESS:
    {
        in >> m_myInf;
        emit changeMyInformationSuccess(m_myInf);
        QMessageBox::information(NULL, tr("修改个人信息"), tr("修改个人信息成功"));
        break;
    }
    case TALK:
    {
        in >> m_message;
        emit getFriendTalkMessage(m_message);
        break;
    }
    case CHANGE_STATUE:
    {
        in >> m_peerID >> m_peerStatus;
        emit getFriendChangedStatus(m_peerID, m_peerStatus);
        break;
    }
    case CHANGE_INFORMATION:
    {
        in >> m_friSimInf;
        emit getFriendChangedInformation(m_friSimInf);
        break;
    }
    case CHANGE_REMARK_SUCCESS:
    {
        in >> m_tempStr;
        emit changeFriendRemarkSuccess(m_tempStr);
        break;
    }
    case DELETE_FRIEND_SUCCESS:
    {
        in >> m_id >> m_peerID >> m_groupName;
        emit deleteFriendSuccess(m_id, m_peerID, m_groupName);
        break;
    }
    case DELETE_FRIEND_FAIL:
    {
        break;
    }
    case BE_DELETED:
    {
        in >> m_id >> m_peerID >> m_groupName;

        QString temp = QString(tr("你被好友(%1)删除了")).arg(m_peerID);
        QMessageBox::information(NULL, tr("消息"), temp);
        emit deleteFriendSuccess(m_id, m_peerID, m_groupName);
        break;
    }
    case ADD_FRIEND:
    {
        in >> m_message >> m_friInf;
        emit getFriendRequest(m_message, m_friInf);
        break;
    }
    case ADD_FLOCK:
    {
        in >> m_message >> m_flockMember >> m_flockInf;
        emit getFlockRequest(m_message, m_flockMember, m_flockInf);
        break;
    }
    case DROP_FLOCK_SUCCESS:
    {
        in >> m_flockID;
        emit dropFlockSuccess(m_flockID);
        break;
    }
    case LEAVE_FLOCK_SUCCESS:
    {
        in >> m_id >> m_flockID >> m_creatorID;
        emit leaveFlockSuccess(m_id, m_flockID, m_creatorID);
        break;
    }
    case LEAVE_FLOCK_MEMBER:
    {
        in >> m_id >> m_flockID >> m_creatorID;
        emit haveMemberleavedFlock(m_id, m_flockID, m_creatorID);
        break;
    }
    case CHANGE_FLOCK_SUCCESS:
    {
        in >> m_flockInf;
        emit changeFlockSuccess(m_flockInf);
        break;
    }
    case CHANGE_FLOCK_REMARK_SUCCESS:
    {
        in >> m_tempStr;
        emit changeFlockRemarkSuccess(m_tempStr);
        break;
    }
    case CREATE_FLOCK_SUCCESS:
    {
        in >> m_flockInf;
        emit createFlockSuccess(m_flockInf);
        break;
    }


    case ADD_DISCUSSION:
    {
        in >> m_message;
        if (ADD_DISCUSSION_SUCCESS == m_message.m_type)
            in >> m_discussionInf;
        else if (NEW_DISCUSSION_MEMBER == m_message.m_type)
            in >> m_discussionMember;

        emit getDiscussionRequest(m_message, m_discussionMember, m_discussionInf);
        break;
    }
    case DROP_DISCUSSION_SUCCESS:
    {
        in >> m_discussionID;
        emit dropDiscussionSuccess(m_discussionID);
        break;
    }
//    case LEAVE_DISCUSSION_SUCCESS:
//    {
//        in >> m_id >> m_discussionID >> m_creatorID;
//        emit leaveDiscussionSuccess(m_id, m_discussionID, m_creatorID);
//        break;
//    }
    case LEAVE_DISCUSSION_MEMBER:
    {
        in >> m_id >> m_discussionID;// >> m_creatorID;
        emit leaveDiscussionSuccess(m_id, m_discussionID);//, m_creatorID);
        break;
    }
    case CHANGE_DISCUSSION_SUCCESS:
    {
        in >> m_discussionInf;
        emit changeDiscussionSuccess(m_discussionInf);
        break;
    }

    case CREATE_DISCUSSION_SUCCESS:
    {
        in >> m_discussionInf;
        emit createDiscussionSuccess(m_discussionInf);
        break;
    }

    case RENAME_BOX_SUCCESS:
    {
        in >> m_id >> m_title >> m_newTitle;
        if (m_id == m_myID)
        {
            emit renameBoxSuccess(m_title, m_newTitle);
        }
        break;
    }

    case MOVE_FRIEND_BOX_SUCCESS:
    {
        in >> m_id >> m_peerID >> m_title >> m_newTitle;
        if (m_id == m_myID)
        {
            emit moveFriendToBoxSuccess(m_peerID, m_title, m_newTitle);
        }
        break;
    }

    case GET_HISTORY_MESSAGE_SUCCESS:
    {
        in >> m_id >> m_peerID >> m_date >> len;
        m_HistoryMessageVector.clear();
        m_HistoryMessageVector.resize(len);
        for(int i=0; i<len; i++)
        {
            in >> m_HistoryMessageVector[i];
        }
        qDebug() << "history message len: " << len;
        if (m_id == m_myID)
        {
            emit getNetworkHistoryMessagesSuccess(m_peerID, m_date,
                                           m_HistoryMessageVector);
        }
        break;
    }
    case CHANGE_PWD_FAIL:
    {
        QMessageBox::information(NULL, tr("修改密码"), tr("修改密码失败！"));
        break;
    }
    case CHANGE_PWD_SUCCESS:
    {
        m_tcpSocket->setFlag(1);
//        if (m_tcpSocket != NULL)
//        {
//            m_tcpSocket->close();
//            m_tcpSocket->deleteLater();
//        }

        QMessageBox::information(NULL, tr("修改密码"), tr("修改成功！请重新登录"));
        emit closeWindowSignal();
        IMLoginWidget *loginWidget = new IMLoginWidget;
        loginWidget->show();

//        closeWindow();
        break;
    }

    default:
        break;
    }
//    qDebug() << "size of quint16: " << sizeof(quint16);
//    qDebug() << "m_blockSize: " << m_blockSize;

    m_blockSize = 0;
    QByteArray data = m_tcpSocket->readAll();
    qDebug() << "leaved in socket: " << data.size();
}


/*************************************************
Function Name： closeWindow
Description: 关闭主程序
*************************************************/
void IMMainCtrl::closeWindow()
{
    if (m_tcpSocket->flag() == 0)
    {

        QMessageBox::information(NULL, tr("系统提示"),
                              tr("您的客户端已经与服务器断开连接，请重新登录。"));
        emit closeWindowSignal();
        IMLoginWidget *loginWidget = new IMLoginWidget;
        loginWidget->show();


    }
}

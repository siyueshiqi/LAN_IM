/*********************************************
File Name： IMClientSocketCtrl.cpp
Author： jet.F.R
Date： 2014.3.10
Description： 用于控制客户端socket的类
Changes：
********************************************/

#include "IMClientSocketCtrl.h"
#include "model/IMUser.h"
#include <QMultiMap>
#include <QDateTime>

// mark: public--------------------------------------------
IMClientSocketCtrl::IMClientSocketCtrl(QObject *parent):
    QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteScoket()));
    m_blockSize = 0;
    m_save.m_clientSocket = this;
}

IMClientSocketCtrl::~IMClientSocketCtrl()
{
    if (m_database.isOpen())
        m_database.close();
}

// mark: public slots-----------------------------------------

/*************************************************
Function Name： receiveMessage()
Description: 接收用户发送的信息
*************************************************/
void IMClientSocketCtrl::receiveMessage()

{
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_4_8);
    if (m_blockSize == 0)
    {
        if (bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> m_blockSize;
    }

    if (bytesAvailable() < m_blockSize)
        return;

    in >> m_save.m_requestKind;

    qDebug() << "receive message: " << m_save.m_requestKind;

    switch (m_save.m_requestKind)
    {
    case CHECK_CONNECTION:
    {
        m_save.m_replyKind = CHECK_CONNECTION;
        sendMessage(m_save);
        m_blockSize = 0;
        break;
    }
    case LOGIN:
    {
        in >> m_save.m_loginInf;
        m_save.m_myID = m_save.m_loginInf.m_userID;
        m_save.m_socketID = m_save.m_myID;
        break;
    }
    case CHECK_MESSAGE:
    {
        in >> m_save.m_myID;
        break;
    }
    case REGISTER:
    {
        in >> m_save.m_userInf;
        break;
    }
    case GET_QUESTION_ANSWER:
    {
        in >> m_save.m_myID;
        break;
    }
    case TALK:
    {
        in >> m_save.m_message;
        break;
    }
    case GET_ALL_FRIENDS:
    {
        in >> m_save.m_myID >> m_save.m_status;
        m_save.m_socketID = m_save.m_myID;
        break;
    }
    case GET_ALL_FLOCKS:
    {
        in >> m_save.m_myID;
        break;
    }
    case GET_ALL_DISCUSSIONS:
    {
        in >> m_save.m_myID;
        break;
    }
    case GET_FLOCK_MEMBERS:
    {
        in >> m_save.m_flockID;
        break;
    }
    case GET_DISCUSSIONS_MEMBERS:
    {
        in >> m_save.m_discussionID;
        break;
    }

    case GET_FRIEND_INFORMATION:
    {
        in >> m_save.m_peerID;
        break;
    }
    case GET_MYSELF_INFORMATION:
    {
        in >> m_save.m_myID;
        break;
    }
    case CHANGE_INFORMATION:
    {
        in >> m_save.m_userInf;
        break;
    }
    case CHANGE_REMARK:
    {
        in >> m_save.m_tempStr;
        break;
    }
    case CHANGE_STATUE:
    {
        in >> m_save.m_myID >> m_save.m_status;
        break;
    }
    case ADD_FRIEND:
    {
        in >> m_save.m_message;
        break;
    }
    case REFUSE_FRIEND:
    {
        //in >> m_save.m_peerID;
        break;
    }
    case DELETE_FRIEND:
    {
        in >> m_save.m_myID >> m_save.m_peerID;
        break;
    }

    case ADD_FLOCK:
    {
        in >> m_save.m_message;
        break;
    }
    case DROP_FLOCK:
    {
        in >> m_save.m_myID >> m_save.m_flockID;
        break;
    }
    case LEAVE_FLOCK:
    {
        in >> m_save.m_myID >> m_save.m_flockID;
        break;
    }
    case CHANGE_FLOCK:
    {
        in >> m_save.m_flockInf;
        break;
    }
    case CHANGE_FLOCK_REMARK:
    {
        in >> m_save.m_tempStr;
        break;
    }
    case CREATE_FLOCK:
    {
        in >> m_save.m_tempStr;
        break;
    }

    case ADD_DISCUSSION:
    {
        in >> m_save.m_message;
        break;
    }
    case DROP_DISCUSSION:
    {
        in >> m_save.m_myID >> m_save.m_discussionID;
        break;
    }
    case LEAVE_DISCUSSION:
    {
        in >> m_save.m_myID >> m_save.m_discussionID;
        break;
    }
    case CHANGE_DISCUSSION:
    {
        in >> m_save.m_discussionInf;
        break;
    }
    case CREATE_DISCUSSION:
    {
        in >> m_save.m_tempStr;
        break;
    }
    case GET_IN_MAILS:
    case GET_OUT_MAILS:
    {
        in >> m_save.m_myID;
        m_save.m_socketID = m_save.m_myID;
        m_save.m_socketID.append(MAIL_ADDRESS_FORMAT);
        break;
    }
    case DELETE_IN_MAIL:
    case DELETE_OUT_MAIL:
    case SET_MAIL_READ:
    {
        in >> m_save.m_myID >> m_save.m_mailID;
        break;
    }
    case SEND_MAIL:
    {
        in >> m_save.m_mail;
        break;
    }

    case REMOVE_BOX:
    case CREATE_BOX:
    {
        in >> m_save.m_myID >> m_save.m_title;
        break;
    }
    case MOVE_FRIEND_BOX:
    {
        in >> m_save.m_myID >> m_save.m_peerID
           >> m_save.m_title >> m_save.m_newTitle;
        break;
    }
    case RENAME_BOX:
    {
        in >> m_save.m_myID >> m_save.m_title >> m_save.m_newTitle;
        break;
    }
    case GET_HISTORY_MESSAGE:
    {
        in >> m_save.m_myID >> m_save.m_peerID >> m_save.m_date;
        break;
    }
    case CHANGE_PASSWORD:
    {
        in >> m_save.m_tempStr;
        break;
    }

    default:
        break;
    }


    QByteArray data = this->readAll();
    qDebug() << "leaved in socket: " << data.size();

    m_blockSize =0;
    emit sendSignal(m_save);
}
/*************************************************
Function Name： sendMessage()
Description: 发送信息
*************************************************/
void IMClientSocketCtrl::sendMessage(const SaveTmpInformation &temp)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << (int)temp.m_replyKind;

    switch (temp.m_replyKind)
    {
    case LOGIN_SUCCESS:
    {
        out << temp.m_userInf;
        break;
    }
    case REGISTER_SUCCESS:
    {
        out << temp.m_userInf.m_userID << temp.m_userInf.m_regDateTime;
        break;
    }
    case GET_QUESTION_ANSWER_SUCCESS:
    {
        out << temp.m_tempStr;
        break;
    }
    case GET_ALL_FRIENDS_SUCCESS:
    {
        int len = temp.m_friendsVec.size();
        out << len;
        for (int i=0; i<len; ++i)
            out << temp.m_friendsVec[i];
        break;
    }
    case GET_ALL_FLOCKS_SUCCESS:
    {
        int len = temp.m_flocksVec.size();
        out << len;
        for (int i=0; i<len; ++i)
            out << temp.m_flocksVec[i];
        break;
    }
    case GET_ALL_DISCUSSIONS_SUCCESS:
    {
        int len = temp.m_discussionsVec.size();
        out << len;
        for (int i=0; i<len; ++i)
            out << temp.m_discussionsVec[i];
        break;
    }
    case GET_FLOCK_MEMBERS_SUCCESS:
    {
        int len = temp.m_flockMembersVec.size();
        out << len;
        for (int i=0; i<len; ++i)
            out << temp.m_flockMembersVec[i];
        break;
    }
    case GET_DISCUSSION_MEMBERS_SUCCESS:
    {
        int len = temp.m_discussionMembersVec.size();
        out << len;
        for (int i=0; i<len; ++i)
            out << temp.m_discussionMembersVec[i];
        break;
    }


    case HAVE_MESSAGE:
        break;
    case CHANGE_STATUE:
        out << temp.m_peerID << temp.m_status;
        break;
    case GET_MYSELF_SUCCESS:
    {
        out << temp.m_userInf;
        break;
    }
    case DELETE_FRIEND_SUCCESS:
    {
        out << temp.m_myID << temp.m_peerID << temp.m_groupName;
        break;
    }
    case CHANGE_INFORMATION_SUCCESS:
    {
        out << temp.m_userInf;
        break;
    }
    case CHANGE_INFORMATION:
    {
        out << temp.m_friendInf;
        break;
    }
    case ADD_FRIEND:
    {
        out << temp.m_message << temp.m_userInf;
        break;
    }
    case GET_FRIEND_SUCCESS:
    {
        out << temp.m_userInf;
        break;
    }
    case TALK:
        out << temp.m_message;
        break;
    case CHANGE_REMARK_SUCCESS:
    {
        out << temp.m_tempStr;
        break;
    }
    case BE_DELETED:
    {
        out << temp.m_myID << temp.m_peerID << temp.m_groupNameF;
        break;
    }
    case REQUEST_FLOCK:
    {
        out << temp.m_message;
        break;
    }
    case ADD_FLOCK:
    {
        out << temp.m_message << temp.m_flockMember << temp.m_flockInf;
        break;
    }

    case DROP_FLOCK_SUCCESS:
    {
        out << temp.m_flockID;
        break;
    }
     case LEAVE_FLOCK_SUCCESS:
    {
        out << temp.m_myID << temp.m_flockID << temp.m_peerID;
        break;
    }
    case LEAVE_FLOCK_MEMBER:
    {
        out << temp.m_myID << temp.m_flockID << temp.m_peerID;
        break;
    }
    case CHANGE_FLOCK_SUCCESS:
    {
        out << temp.m_flockInf;
        break;
    }
    case CHANGE_FLOCK_REMARK_SUCCESS:
    {
        out << temp.m_tempStr;
        break;
    }
    case CREATE_FLOCK_SUCCESS:
    {
        out << temp.m_flockInf;
        break;
    }



    case ADD_DISCUSSION:
    {
        out << temp.m_message;
        if (ADD_DISCUSSION_SUCCESS == temp.m_message.m_type)
            out << temp.m_discussionInf;
        else if (NEW_DISCUSSION_MEMBER == temp.m_message.m_type)
            out << temp.m_discussionMember;
        break;
    }

    case DROP_DISCUSSION_SUCCESS:
    {
        out << temp.m_discussionID;
        break;
    }
     case LEAVE_DISCUSSION_MEMBER:
    {
        out << temp.m_myID << temp.m_discussionID;// << temp.m_peerID;
        break;
    }
    case CHANGE_DISCUSSION_SUCCESS:
    {
        out << temp.m_discussionInf;
        break;
    }

    case CREATE_DISCUSSION_SUCCESS:
    {
        out << temp.m_discussionInf;
        break;
    }
    /*****************mail*****************/
    case GET_IN_MAILS_SUCCESS:
    {
        int len = temp.m_inMailsVec.size();
        out << len;
        for (int i=0; i<len; ++i)
            out << temp.m_inMailsVec[i];
        break;
    }
    case GET_OUT_MAILS_SUCCESS:
    {
        int len = temp.m_outMailsVec.size();
        out << len;
        for (int i=0; i<len; ++i)
            out << temp.m_outMailsVec[i];
        break;
    }

    case DELETE_IN_MAIL_SUCCESS:
    case DELETE_OUT_MAIL_SUCCESS:
    {
        out << temp.m_myID << temp.m_mailID;
        break;
    }

    case SEND_MAIL_SUCCESS:
    case RECEIVE_MAIL:
    {
        out << temp.m_mail;
        break;
    }

    case RENAME_BOX_SUCCESS:
    {
        out << temp.m_myID << temp.m_title << temp.m_newTitle;
        break;
    }
    case MOVE_FRIEND_BOX_SUCCESS:
    {
        out << temp.m_myID << temp.m_peerID << temp.m_title << temp.m_newTitle;
        break;
    }
    case GET_HISTORY_MESSAGE_SUCCESS:
    {
        out << temp.m_myID << temp.m_peerID << temp.m_date;
        int len = temp.m_historyMessageVec.size();
        out << len;
        for (int i=0; i<len; ++i)
            out << temp.m_historyMessageVec[i];
        break;
    }
    default:
        break;
    }

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    write(block);
}

/*************************************************
Function Name： deleteScoket()
Description: 删除socket
*************************************************/
void IMClientSocketCtrl::deleteScoket()
{
    if (!m_save.m_socketID.isEmpty())
    {
        if ( LOGIN != m_save.m_requestKind)
        emit deleteSignal(m_save.m_socketID);
    }
    deleteLater();
}


/*************************************************
Function Name： readMessage()
Description: 发送用户的信息至另一个用户
*************************************************/
//void IMClientSocketCtrl::sendTalkMessage(TalkMessage mes)
//{
//    qDebug() << "sendCheckResult";
//    QByteArray block;
//    QDataStream out(&block, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_4_8);
//    out << quint16(0) << int(TALK_MESSAGE) <<  mes;
//    out.device()->seek(0);
//    out << quint16(block.size() - sizeof(quint16));
//    write(block);
//}


// mark: private slots--------------------------------------------------
/*************************************************
Function Name： readMessage()
Description: 读取用户发送的信息
Input： NULL
Output：NULL
Changes： NULL
*************************************************/
//void IMClientSocketCtrl::readMessage()
//{
//    QDataStream in(this);
//    in.setVersion(QDataStream::Qt_4_8);
//    if (m_blockSize == 0)
//    {
//        qDebug()<<"size"<<bytesAvailable();
//        if (bytesAvailable() < (int)sizeof(quint16))
//            return;
//        in >> m_blockSize;
//    }

//    if (bytesAvailable() < m_blockSize)
//    {
//        qDebug("here-43");

//        m_blockSize =0;
//        return;
//    }
//    int type;

//    in >> type;

//    QString id;
//    QString pwd;
//    int status;
//    QDateTime dateTime;
//    IMUser user;
//    TalkMessage talkMes;

//    switch (type)
//    {
//    case LOGIN:
//        in >> id >> pwd >> status >>dateTime;
//        checkUser(id, pwd, dateTime);
//        break;
//    case REGISTER:
//        in >> user;
//        qDebug() << "user:" << user.getName() << user.getPassword();
//        addUser(user);
//        break;
//    case GET_ALL_FRIENDS:
//        in >> id;
//        getFriends(id);
//        break;
//    case TALK_MESSAGE:
//        in >> talkMes;
//        qDebug() << "mes" /*<< talkMes.m_text*/ << talkMes.m_receiverID
//                    << talkMes.m_senderIP << talkMes.m_senderID;
//    default:
//        break;
//    }
//    m_blockSize =0;
//}


// mark: private-------------------------------------------------------------
/*************************************************
Function Name： checkLogin()
Description: 检测用户登录信息
Input： QString id：用户帐号id ，QString pwd：用户密码
Output： bool : 检测信息
Changes： NULL
*************************************************/
//bool IMClientSocketCtrl::checkUser(const QString & id, const QString & pwd,
//                                   const QDateTime & )
//{
//    //qDebug()<< "IMClientSocket:checkLogin:" << id << pwd << dateTime;
//    if (m_database.createConnection())
//    {
//        IMUser *user = NULL;
//        user = m_database.searchUserInUserInformation(id, pwd);
//        if (user != NULL)
//        {
//            sendMessage(LOGIN, true, NULL, user->getUserID(), user->getNickname());
//            delete user;
//            user = NULL;
//            return true;
//        }


//    }
//    sendMessage(LOGIN, false);
//    return false;
//}


/*************************************************
Function Name： addUser()
Description: 添加用户
Input： IMUser
Output： bool
Changes： NULL
*************************************************/
//bool IMClientSocketCtrl::addUser(IMUser &user)
//{

//    if (m_database.createConnection())
//    {
//        bool isSuccess = false;
//        QDateTime dateTime;
//        dateTime.setDate(QDate::currentDate());

//        int sum = m_database.countRegisteredInPeriod(dateTime, dateTime.addDays(1));
//        qDebug() << "sum of user" << sum;
//        if (0 == sum)
//        {
//            sendMessage(REGISTER, false);
//            return false;
//        }
//        QString id = dateTime.toString("yyyyMMdd");
//        id.append(QString::number(sum));
//        user.setUserID(id);
//        user.setRegDateTime(QDateTime::currentDateTime());
//        qDebug()<<"addUser: qusetion: " << user.getQuestion();

//        isSuccess = m_database.addUserInUserInformation(user);
//        if (isSuccess)
//        {
//            sendMessage(REGISTER, true, &user);
//            return true;
//        }
//    }
//    sendMessage(REGISTER, false);
//    return false;
//}


/*************************************************
Function Name： getFriends()
Description: 获取所有
*************************************************/
//bool IMClientSocketCtrl::getFriends(const QString &id)
//{
//    qDebug() << "get request getFriends: " << id;
//    if (!m_database.createConnection())
//    {
//        //sendMessage(GET_ALL_FRIENDS, false);
//        sendFriends(false);
//        return false;
//    }

//    QMultiMap<QString, FriendsInfo> *userMap= new QMultiMap<QString, FriendsInfo>;
//    bool result = m_database.searchFriendsInformation(id, userMap);
//    if (result == false)
//    {
//        //sendMessage(GET_ALL_FRIENDS, false);
//        sendFriends(false);
//        return false;
//    }
//    if (userMap == NULL)
//    {
//        // sendMessage(GET_ALL_FRIENDS, false);
//        sendFriends(false, NULL);
//        return true;
//    }
//    //sendMessage(GET_ALL_FRIENDS, true);
//    sendFriends(true, userMap);
//    return true;
//}

/*************************************************
Function Name： sendMessage()
Description: 发送信息
Input： MessageTyep type:信息类型, bool is: bool信息,
       int mes1: 信息1, QString mes2：信息2
Output：NULL
Changes： NULL
*************************************************/
//void IMClientSocketCtrl::sendMessage(MessageType type, bool isSuccess, const IMUser *user,
//                                     const QString &mes1, const QString &mes2)
//{
//    qDebug() << "sendMessage: " << isSuccess;
//    switch (type)
//    {
//    case LOGIN:
//        sendCheckResult(isSuccess, mes1, mes2);
//        break;
//    case REGISTER:
//        sendRegisterResult(isSuccess, user);
//    default:

//        break;
//    }
//}

/*************************************************
Function Name： sendCheckResult()
Description: 发送检测结果
Input：  bool: 是否成功, QString mes1: 信息1, QString mes2：信息2
Output：NULL
Changes： NULL
*************************************************/
//void IMClientSocketCtrl::sendCheckResult(bool isSuccess, const QString &id,
//                                         const QString &nick)
//{
//    qDebug() << "sendCheckResult";
//    QByteArray block;
//    QDataStream out(&block, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_4_8);
//    out << quint16(0) << int(LOGIN) <<  isSuccess;
//    if (isSuccess == true)
//    {
//        out << id << nick;
//    }
//    out.device()->seek(0);
//    out << quint16(block.size() - sizeof(quint16));
//    write(block);
//}


/*************************************************
Function Name： sendRegisterResult()
Description: 发送注册结果
Input： bool isSuccess: 是否成功,  const IMUser *： 用户信息
Output：NULL
Changes： NULL
*************************************************/
//void IMClientSocketCtrl::sendRegisterResult(bool isSuccess, const IMUser * user)
//{
//    if (user == NULL)
//        return;
//    qDebug() << "sendRegisterResult: " << isSuccess;
//    QByteArray block;
//    QDataStream out(&block, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_4_8);
//    out << quint16(0) << int(REGISTER) <<  isSuccess;
//    if (isSuccess == true)
//    {
//        out << *user;
//    }
//    out.device()->seek(0);
//    out << quint16(block.size() - sizeof(quint16));
//    write(block);
//}


/*************************************************
Function Name： sendFriends()
Description: 发送所有好友信息
Input： bool isSuccess: 是否成功,  map 好友信息
Output：NULL
Changes： NULL
*************************************************/
//void IMClientSocketCtrl::sendFriends(bool isSuccess, const QMultiMap<QString, FriendsInfo> *map)
//{
//    if (map == NULL)
//    {
//        return;
//    }
//    qDebug() << "sendGetFriendsResult: " << isSuccess;
//    QByteArray block;
//    QDataStream out(&block, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_4_8);
//    out << quint16(0) << int(GET_ALL_FRIENDS) <<  isSuccess;
//    if (isSuccess == true)
//    {
//        out << *map;
//    }
//    out.device()->seek(0);
//    out << quint16(block.size() - sizeof(quint16));
//    write(block);
//}

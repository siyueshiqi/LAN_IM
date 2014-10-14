/*********************************************
File Name： IMClientSocketCtrl.h
Author： jet.F.R
Date： 2014.3.10
Description： 用于控制客户端socket的类
Changes：
********************************************/

#ifndef IMCLIENTSOCKETCTRL_H
#define IMCLIENTSOCKETCTRL_H

#include <QTcpSocket>
#include "IMDatabaseCtrl.h"
#include "model/IMConstant.h"

class QDateTime;
class IMUser;


/*************************************************
Class Name： IMClientSocketCtrl
Description: 来自客户端socket，用于处理各种请求
*************************************************/
class IMClientSocketCtrl : public QTcpSocket
{
    Q_OBJECT
public:
    IMClientSocketCtrl(QObject *parent = 0);
    ~IMClientSocketCtrl();

signals:
//    void havaNewClientSocket(IMClientSocket *);
    // 请求server处理
    void sendSignal(const SaveTmpInformation &temp);
    // 用户登录
    void userLoginSignal(const UserInformation &user);
    //用户断开连接了
    void deleteSignal(const QString &acc);

public slots:
    // 接收信息
    void receiveMessage();
    // 发送信息
    void sendMessage(const SaveTmpInformation &temp);
    // 删除socket
    void deleteScoket();

private:
    quint16 m_blockSize;
    SaveTmpInformation m_save;

    /****************************************/
//public slots:
//    // 发送用户的信息至另一个用户
//    void sendTalkMessage(TalkMessage);

//private slots:
//    // 读取信息
//    void readMessage();

private:
//    // 检测登录信息
//    bool checkUser(const QString & id,const QString & pwd,
//                   const QDateTime &);

//    // 添加用户
//    bool addUser(IMUser &);

//    // 获取所有好友
//    bool getFriends(const QString &);

//    // 发送信息
//    void sendMessage(MessageType type,bool is = false,
//                     const IMUser *user = NULL,
//                     const QString &mes1 = "",
//                     const QString &mes2 = "");

//    // 发送检测结果
//    void sendCheckResult(bool isSuccess, const QString &id = "",
//                         const QString &nick = "");

//    // 发送注册结果
//    void sendRegisterResult(bool isSuccess, const IMUser * user = NULL);

//    // 发送所有好友信息
//    void sendFriends(bool isSuccess,
//                     const QMultiMap<QString, FriendInformation> * map = NULL);

private:
    IMDatabaseCtrl m_database;

};

#endif // IMCLIENTSOCKETCTRL_H

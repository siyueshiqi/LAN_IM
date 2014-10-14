/*********************************************
File Name： IMRegisterCtrl.h
Author： jet.F.R
Date： 2014.3.17
Description： 用于控制注册的类
Changes：
********************************************/

#ifndef IMREGISTERCTRL_H
#define IMREGISTERCTRL_H

#include <QObject>
#include "model/IMConstant.h"

class IMUser;
class IMTcpSocket;

/*************************************************
Class Name： IMRegisterCtrl
Description: 用于控制注册的类
*************************************************/
class IMRegisterCtrl : public QObject
{
    Q_OBJECT
public:
    explicit IMRegisterCtrl(QObject *parent = 0);

    ~IMRegisterCtrl();
    // 注册
    void registerAccount(const UserInformation &);
    
signals:
    void signalResetBtnRegister(bool );
public slots:

private slots:
    // 请求注册
    void requestRegister();
    // 读取信息
    void readMessage();
    // 重置按钮
    void resetBtnRegister();
private:
    
private:
    UserInformation m_user;
    quint16 m_blockSize;
    IMTcpSocket *m_tcpSocket;

};

#endif // IMREGISTERCTRL_H

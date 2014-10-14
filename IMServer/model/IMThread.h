/*********************************************
File Name： IMThread.h
Author： jet.F.R
Date： 2014.3.10
Description： 服务器用于处理socket通信的线程类
Changes：
********************************************/
#ifndef IMTHREAD_H
#define IMTHREAD_H

#include <QThread>
#include "model/IMConstant.h"

class IMClientSocketCtrl;


/*************************************************
Class Name： IMThread
Description: 处理socket通信的线程类
*************************************************/
class IMThread : public QThread
{
    Q_OBJECT
public:
    explicit IMThread(QObject *parent = 0);
    explicit IMThread( QObject * parent, int socketDescriptor);
    ~IMThread();

signals:

public slots:
//    void sendTalkMessage(TalkMessage mes);

private:
    void run(); // 线程运行时，会调用此函数

private:
    int m_socketDescriptor;
    IMClientSocketCtrl * m_clientSocket;

};

#endif // IMTHREAD_H

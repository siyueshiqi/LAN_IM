/*********************************************
File Name： IMServerMessageCtrl.h
Author： jet.F.R
Date： 2014.3.10
Description： 控制服务器类
Changes：
********************************************/

#ifndef IMSERVERMESSAGECTRL_H
#define IMSERVERMESSAGECTRL_H

#include <QObject>
#include "IMDatabaseCtrl.h"

class IMClientSocketCtrl;
class IMTcpServer;

class QStringListModel;
class QListView;

/*************************************************
Class Name： IMServerMessageCtrl
Description: 控制服务器
*************************************************/
class IMServerMessageCtrl : public QObject
{
    Q_OBJECT
public:
    IMServerMessageCtrl(QObject *parent = 0);
    ~IMServerMessageCtrl();
    void runServer(); // 用于启动服务器
    QListView *getIDListView();
    QListView *getAddressListView();

signals:

public slots:

private slots:
    void showConnectedMedssage();  //暂时没用，本来是用于显示链接信息 mark： Not used
    void readMessage(IMClientSocketCtrl *); //暂时没用，本来是用于读取信息 mark： Not used

    void insertIDData(const QString &id);
    void deleteIDData(const QString &id);

    void insertAddressData(const QString &address);
    void deleteAddressData(const QString &address);

private:

private:
    IMTcpServer *m_tcpServer;
    quint16 m_blockSize;  //暂时没用
    IMDatabaseCtrl m_databaseCtrl;

    QStringList m_listID;
    QStringListModel *m_modelID;
    QListView *m_listViewID;

    QStringList m_listAddress;
    QStringListModel *m_modelAddress;
    QListView *m_listViewAddress;
};

#endif // IMSERVERMESSAGECTRL_H

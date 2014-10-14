///*********************************************
//File Name： IMClientMessageCtrl.cpp
//Author： jet.F.R
//Date： 2014.3.10
//Description： 用于控制通信的类
//Changes：
//********************************************/

//#include "IMClientMessageCtrl.h"
//#include "model/IMTcpSocket.h"
//#include "model/IMUser.h"
//#include <QMessageBox>
//#include <QHostAddress>
//#include <QDataStream>
//#include <QDateTime>
//#include <QtNetwork>

//QHostAddress IMClientMessageCtrl::sm_hostAddress = QHostAddress::Any;
//qint16 IMClientMessageCtrl::sm_hostPort = 0;


//// mark: public-----------------------------------------------------------
//IMClientMessageCtrl::IMClientMessageCtrl(QObject *parent) :
//    QObject(parent)
//{
//    initIMClientMessageCtrl();
//    linkSignalWithSlot();
//}

//IMClientMessageCtrl::~IMClientMessageCtrl()
//{
//    if (m_tcpSocket != NULL)
//    {
//        m_tcpSocket->abort();
//        delete m_tcpSocket;
//        m_tcpSocket = NULL;
//    }
//}

///*************************************************
//Function Name： sendMessage()
//Description: 发送信息
//Input： MessageType type：信息类型, QString mes1：信息1, QString mes2：信息2
//Output： NULL
//Changes： NULL
//*************************************************/
//void IMClientMessageCtrl::sendMessage(MessageType type, const QString &mes1,
//                                      const QString &mes2, LoginStatus status,
//                                      const IMUser *user)
//{
//    switch (type)
//    {
//    case CONNECT:
//        m_status = status;
//        requestConnect(mes1, mes2);
//        break;
//    case LOGIN:
//        m_id = mes1;
//        m_pwd = mes2;
//        m_status = status;
//        requestLogin();
//        break;
//    case REGISTER:
//        requsetRegister(user);
//    default:
//        break;

//    }
//}



//// mark: private slots---------------------------------------------------------
///*************************************************
//Function Name： connectionClosedByServer()
//Description: 连接被客户端关闭
//Input： NULL
//Output： NULL
//Changes： NULL
//*************************************************/
//void IMClientMessageCtrl::connectionClosed()
//{
//    qDebug("连接断开");
//    m_isConnected = false;
//}

///*************************************************
//Function Name： readMessage()
//Description: 读取信息
//Input： NULL
//Output： NULL
//Changes： NULL
//*************************************************/
//void IMClientMessageCtrl::readMessage()
//{
//    qDebug() << "readMessage";
//    QDataStream in(m_tcpSocket);
//    in.setVersion(QDataStream::Qt_4_8);
//    if (m_blockSize == 0)
//    {
//        if (m_tcpSocket->bytesAvailable() < (int)sizeof(quint16))
//            return;
//        in >> m_blockSize;
//    }

//    if (m_tcpSocket->bytesAvailable() < m_blockSize)
//        return;
//    quint8 type;

//    in >> type;

//    QString id;
//    bool is;
//    QString nickName;

//    switch (type)
//    {
//    case LOGIN:
//        in >> is;
//        if (is)
//        {
//            in >> id >> nickName;
//            emit showLoginStatus(tr("%1").arg(nickName), true);
//        }
//        else
//        {
//            emit showLoginStatus(tr("登录失败.帐号或者密码错误."));
//        }
//        break;
//    }
//}

///*************************************************
//Function Name： dispalyError()
//Description: 显示错误
//Input： QAbstractSocket::SocketError socketError：错误信息
//Output： NULL
//Changes： NULL
//*************************************************/
//void IMClientMessageCtrl::dispalyError(QAbstractSocket::SocketError socketError)
//{
//    switch (socketError)
//    {
//    case QAbstractSocket::RemoteHostClosedError:
//        emit showLoginStatus(tr("登录失败.可能是因为服务器关闭."));
//        break;
//    case QAbstractSocket::HostNotFoundError:
//        emit showLoginStatus(tr("登录失败.可能是因为找不到服务器"));
//        QMessageBox::information(NULL, tr("登录失败"),
//                                 tr("This host was not found.Please check the"
//                                    "host name and port settings."));
//        break;
//    case QAbstractSocket::ConnectionRefusedError:
//        emit showLoginStatus(tr("登录失败.可能是因为连接被拒绝"));
//        QMessageBox::information(NULL, tr("登录失败"),
//                                 tr("The connection was refused by the peer."
//                                    "Make sure the IM server is running,"
//                                    "and check that the host name and port"
//                                    "settings are correct."));
//        break;
//    default:
//        emit showLoginStatus(tr("登录失败: %1.").arg(m_tcpSocket->errorString()));
//        QMessageBox::information(NULL, tr("登录失败"),
//                                 tr("The following errot occurred: %1.")
//                                 .arg(m_tcpSocket->errorString()));
//    }
//}

///*************************************************
//Function Name： requestLogin()
//Description: 请求登录
//Input： NULL
//Output： NULL
//Changes： NULL
//*************************************************/
//void IMClientMessageCtrl::requestLogin()
//{
//    m_isConnected = true;
//    QByteArray block;
//    QDataStream out(&block, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_4_8);
//    out << quint16(0) << quint8(LOGIN) << m_id << m_pwd
//        << quint8(m_status) << QDateTime::currentDateTime();
//    out.device()->seek(0);
//    out << quint16(block.size() - sizeof(quint16));
//    m_tcpSocket->write(block);
//}

///*************************************************
//Function Name： requestLogin()
//Description: 请求注册
//Input： NULL
//Output： NULL
//Changes： NULL
//*************************************************/
//void IMClientMessageCtrl::requsetRegister(const IMUser *)
//{

//}

//// mark: private-------------------------------------------------------------
///*************************************************
//Function Name： initIMClientMessageCtrl()
//Description: 初始化
//Input： NULL
//Output： NULL
//Changes： NULL
//*************************************************/
//void IMClientMessageCtrl::initIMClientMessageCtrl()
//{
//    m_tcpSocket = new IMTcpSocket(this);
//    m_id = "";
//    m_pwd = "";
//    m_status = ONLINE;
//    m_isConnected = false;
//}

///*************************************************
//Function Name： linkSignalWithSlot()
//Description: 链接信号与槽
//Input： NULL
//Output： NULL
//Changes： NULL
//*************************************************/
//void IMClientMessageCtrl::linkSignalWithSlot()
//{
//    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(connectionClosed()));
//    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
//    connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
//            this, SLOT(dispalyError(QAbstractSocket::SocketError)));
//    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(requestLogin()));
//}

///*************************************************
//Function Name： requestConnect()
//Description: 请求连接
//Input： const QString &id： 用户帐号, const QString &pwd：用户密码
//Output： NULL
//Changes： NULL
//*************************************************/
//void IMClientMessageCtrl::requestConnect()
//{
//    m_tcpSocket->abort();
//    m_tcpSocket->connectToHost(IMClientMessageCtrl::sm_hostAddress,
//                               IMClientMessageCtrl::sm_hostPort);
//}

///*************************************************
//Function Name： getIP()
//Description: 获取ip地址
//Input： NULL
//Output： QString
//Changes： NULL
//*************************************************/
//QString IMClientMessageCtrl::getIP()
//{
//    QList<QHostAddress> list = QNetworkInterface::allAddresses();
//    foreach (QHostAddress address, list)
//    {
//       if(address.protocol() == QAbstractSocket::IPv4Protocol) //我们使用IPv4地址
//        {
//           if(address.toString()!="127.0.0.1")
//                return address.toString();
//        }
//    }
//    return 0;
//}

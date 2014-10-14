///*********************************************
//File Name： IMClientMessageCtrl.h
//Author： jet.F.R
//Date： 2014.3.10
//Description： 用于控制通信的类
//Changes：
//********************************************/

//#ifndef IMCLIENTMESSAGECTRL_H
//#define IMCLIENTMESSAGECTRL_H

//#include <QObject>
//#include <QObject>
//#include <QHostAddress>

//class IMTcpSocket;
//class IMUser;

//enum MessageType
//{
//    CONNECT = 0,   // 连接
//    LOGIN   = 1,   // 登录
//    REGISTER = 2   // 注册
//};

//enum LoginStatus
//{
//    ONLINE = 0,    // 在线
//    INVISIBLE = 1, // 隐身
//    BUSY = 2,      // 忙碌
//    LEAVE = 3,     // 离开
//    NOTDISTURB = 4 // 请勿打扰
//};

///*************************************************
//Class Name： IMClientMessageCtrl
//Description: 用于控制通信的类
//*************************************************/
//class IMClientMessageCtrl : public QObject
//{
//    Q_OBJECT
//public:
//    explicit IMClientMessageCtrl(QObject *parent = 0);
//    ~IMClientMessageCtrl();
//    // 发送信息
//    void sendMessage(MessageType, const QString &mes1,
//                     const QString &mes2 = "", LoginStatus status = ONLINE,
//                     const IMUser * user = NULL);

//    static QHostAddress sm_hostAddress;
//    static qint16 sm_hostPort;

//signals:
//    void showLoginStatus(const QString &, bool isLogin = false);

//public slots:

//private slots:
//    // 连接被客户端关闭
//    //void connectionClosed();
//    // 读取信息
//    void readMessage();
//    // 显示错误
//    //void dispalyError(QAbstractSocket::SocketError);
//    // 发送登录请求
//    void requestLogin();
//    // 发送注册请求
//    void requsetRegister(const IMUser *);

//private:
//    // 初始化
//    void initIMClientMessageCtrl();
//    // 链接信号与槽
//    //void linkSignalWithSlot();
//    // 请求连接
//    void requestConnect();
//    // 获取ip
//    //QString getIP();

//private:
//    IMTcpSocket *m_tcpSocket;
//    quint16 m_blockSize;

//    QString m_id;
//    QString m_pwd;
//    LoginStatus m_status;

//    bool m_isConnected;

//};
//#endif // IMCLIENTMESSAGECTRL_H

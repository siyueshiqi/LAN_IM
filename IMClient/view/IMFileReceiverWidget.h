#ifndef IMFILERECEIVERWIDGET_H
#define IMFILERECEIVERWIDGET_H

#include <QWidget>
#include <QHostAddress>
#include <QTime>

class QProgressBar;
class QLabel;
class QPushButton;
class QPushButton;
class QTcpSocket;
class QTcpServer;
class QFile;
class QAbstractSocket;


class IMFileReceiverWidget : public QWidget
{
    Q_OBJECT
public:
    IMFileReceiverWidget(QWidget *parent = 0);
    ~IMFileReceiverWidget();

    // 设置文件名
    void setFileName(const QString & fileName);
    // 设置服务器地址并连接服务器
    void connectToHost(const QHostAddress & address);
    
signals:
    

    
private:
    // 初始化
    void initIMFileReceiverWidget();

public slots:
    // 点击“关闭”按钮
    void onClickBtnClose();
    // 点击“取消”按钮 中途取消的操作
    void onClickBtnCancel();
    // 读取收到的文件
    void readMessage();
    // 错误处理
    void displayError(QAbstractSocket::SocketError);
    // 连接断开
    void showClosedConnect();

private:
    QLabel *m_labelFileName;
    QLabel *m_labelFileStatus;
    QProgressBar *m_barFile;
    QPushButton *m_btnClose;
    QPushButton *m_btnCancel;

    QTcpSocket *m_fileReceiver;
    quint16 m_blockSize;
    QHostAddress m_hostAddress;
    qint16 m_tcpPort;

    qint64 m_totalBytes;
    qint64 m_bytesReceived;
    qint64 m_bytesToReceive;
    qint64 m_fileNameSize;
    QString m_fileName;
    QFile *m_localFile;
    QByteArray m_inBlock;

    QTime m_time;

};

#endif // IMFILERECEIVERWIDGET_H

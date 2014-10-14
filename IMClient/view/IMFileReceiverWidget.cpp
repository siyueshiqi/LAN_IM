#include "IMFileReceiverWidget.h"
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QTcpServer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>


IMFileReceiverWidget::IMFileReceiverWidget(QWidget *parent) :
    QWidget(parent)
{
    initIMFileReceiverWidget();
    setWindowTitle(tr("接收文件"));
}

IMFileReceiverWidget::~IMFileReceiverWidget()
{
}

/*************************************************
Function Name： setFileName()
Description: 设置文件名
*************************************************/
void IMFileReceiverWidget::setFileName(const QString & fileName)
{
    m_localFile = new QFile(fileName);

    m_labelFileName->setText(fileName.right(fileName.size()
                                            - fileName.lastIndexOf('/')-1));
}

/*************************************************
Function Name： connectToHost()
Description: 设置服务器地址并连接服务器
*************************************************/
void IMFileReceiverWidget::connectToHost(const QHostAddress & address)
{
    m_hostAddress = address;
    m_blockSize = 0;
    m_fileReceiver->abort();
    m_fileReceiver->connectToHost(m_hostAddress, m_tcpPort);
    m_time.start();
}

// private: ---------------------------------------------

/*************************************************
Function Name： initIMFileReceiverWidget()
Description: 初始化
*************************************************/
void IMFileReceiverWidget::initIMFileReceiverWidget()
{
    m_labelFileName = new QLabel(tr("文件名:"), this);
    m_labelFileStatus = new QLabel(tr("等待对方接受"), this);
    m_labelFileStatus->setFixedHeight(80);
    m_barFile = new QProgressBar(this);
    m_btnCancel = new QPushButton(tr("取消"), this);
    m_btnClose = new QPushButton(tr("关闭"), this);
    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(m_btnCancel);
    hlayout->addWidget(m_btnClose);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_labelFileName);
    layout->addWidget(m_barFile);
    layout->addWidget(m_labelFileStatus);
    layout->addLayout(hlayout);
    setLayout(layout);
    setFixedSize(400,200);

//    setFixedSize(350,180);

    m_totalBytes = 0;
    m_bytesReceived = 0;
    m_fileNameSize = 0;

    m_fileReceiver = new QTcpSocket(this);
    m_tcpPort = 6666;
    connect(m_fileReceiver, SIGNAL(readyRead()), this ,SLOT(readMessage()));
    connect(m_fileReceiver, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(m_fileReceiver, SIGNAL(disconnected()),
            this, SLOT(showClosedConnect()));

    connect(m_btnCancel, SIGNAL(clicked()),
            this, SLOT(onClickBtnCancel()));
    connect(m_btnClose, SIGNAL(clicked()),
            this, SLOT(onClickBtnClose()));

}

// private slot: ---------------------------------------------

/*************************************************
Function Name： onClickBtnClose()
Description: 点击“关闭”按钮
*************************************************/
void IMFileReceiverWidget::onClickBtnClose()
{
    onClickBtnCancel();
    close();
}

/*************************************************
Function Name： onClickBtnCancel()
Description: 点击“取消”按钮 中途取消的操作
*************************************************/
void IMFileReceiverWidget::onClickBtnCancel()
{
    m_fileReceiver->abort();
}

/*************************************************
Function Name： readMessage()
Description: 槽 读取收到的文件
*************************************************/
void IMFileReceiverWidget::readMessage()
{
    QDataStream in(m_fileReceiver);
    in.setVersion(QDataStream::Qt_4_6);

    float useTime = m_time.elapsed();
    if(m_bytesReceived <= sizeof(qint64)*2)
    {
        if((m_fileReceiver->bytesAvailable() >= sizeof(qint64)*2)
                && (m_fileNameSize == 0))
        {
            in >> m_totalBytes >> m_fileNameSize;
            m_bytesReceived += sizeof(qint64)*2;
        }
        if((m_fileReceiver->bytesAvailable() >= m_fileNameSize)
                && (m_fileNameSize != 0))
        {
            in >> m_fileName;
            m_bytesReceived += m_fileNameSize;

            if(!m_localFile->open(QFile::WriteOnly)){
                QMessageBox::warning(this,tr("应用程序"),tr("无法读取文件:\n%2.")
                                     .arg(m_localFile->errorString()));
                return;
            }
        }
        else
            return;
    }
    if(m_bytesReceived < m_totalBytes)
    {
        m_bytesReceived += m_fileReceiver->bytesAvailable();
        m_inBlock = m_fileReceiver->readAll();
        m_localFile->write(m_inBlock);
        m_inBlock.resize(0);
    }
    m_barFile->setMaximum(m_totalBytes);
    m_barFile->setValue(m_bytesReceived);
    qDebug() << m_bytesReceived << "received:" << m_totalBytes;

    double speed = m_bytesReceived / useTime;
    m_labelFileStatus->setText(tr("已接收 %1MB (%2MB/s) \n共%3MB 已用时:%4秒\n估计剩余时间：%5秒")
                                         .arg(m_bytesReceived / (1024*1024))   // 已接收
                                         .arg(speed*1000/(1024*1024),0,'f',2)  // 速度
                                         .arg(m_totalBytes / (1024 * 1024))    // 总大小
                                         .arg(useTime/1000,0,'f',0)            // 用时
                                         .arg(m_totalBytes/speed/1000 - useTime/1000,0,'f',0)); // 剩余时间

    if(m_bytesReceived == m_totalBytes)
    {
        m_fileReceiver->close();
        m_labelFileStatus->setText(tr("文件接收完毕"));
        m_localFile->close();   //接收完文件后，一定要关闭，不然可能出问题
    }
}

/*************************************************
Function Name： displayError()
Description:  错误处理
*************************************************/
void IMFileReceiverWidget::displayError(QAbstractSocket::SocketError socketError)
{
    switch(socketError)
    {
    case QAbstractSocket::RemoteHostClosedError :
        break;
    default :
        qDebug() << m_fileReceiver->errorString();
    }
}


/*************************************************
Function Name： showClosedConnect()
Description:  链接断开
*************************************************/
void IMFileReceiverWidget::showClosedConnect()
{
    m_labelFileStatus->setText(tr("文件接收被中断！"));

    if(m_bytesReceived == m_totalBytes)
    {
        m_labelFileStatus->setText(tr("文件接收完毕"));
    }
}

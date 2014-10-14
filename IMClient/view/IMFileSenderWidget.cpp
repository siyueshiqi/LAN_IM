#include "IMFileSenderWidget.h"
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QTcpServer>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTcpSocket>

//#include "model/IMTcpSocket.h"

IMFileSenderWidget::IMFileSenderWidget(QWidget *parent) :
    QWidget(parent)
{
    m_isStopped = true;
    initIMFileSenderWidget();
    setWindowTitle(tr("发送文件"));
}


IMFileSenderWidget::~IMFileSenderWidget()
{
    onClickBtnClose();
}

/*************************************************
Function Name： initSender()
Description: 初始化
*************************************************/
void IMFileSenderWidget::initSender()
{
    m_isStopped = true;
    m_loadSize = 4 * 1024;
    m_totalBytes = 0;
    m_bytesWritten = 0;
    m_bytesToWrite = 0;
    m_barFile->reset();
    m_fileSender->close();
}

/*************************************************
Function Name： showRefused()
Description: 被拒绝时触发  聊天窗体调用
*************************************************/
void IMFileSenderWidget::showRefused()
{
    m_isStopped = true;
    m_fileSender->close();
    m_labelFileStatus->setText(tr("对方拒绝接收！"));
}


/*************************************************
Function Name： startSending()
Description: 初始化文件服务器，监听对方
*************************************************/
bool IMFileSenderWidget::startSending(const QString & file)
{
    m_isStopped = false;
    m_filePath = file;
    m_fileName = m_filePath.right(m_filePath.size() - m_filePath.lastIndexOf('/')-1);
    m_labelFileName->setText(QString(tr("文件名: %1")).arg(m_fileName));
    // 开始监听
    if (!m_fileSender->listen(QHostAddress::Any, m_tcpPort))
    {
        qDebug() << "file server error: "<< m_fileSender->errorString();
        QMessageBox::critical(NULL, tr("IM FileSender"),
                              tr("Unable to start file server: %1")
                              .arg(m_fileSender->errorString()));
//        exit(EXIT_FAILURE);
        close();
        return false;
    }

    m_labelFileStatus->setText(tr("等待对方接受"));
    return true;
}


/*************************************************
Function Name： isStopped()
Description: 是否停止
*************************************************/
bool IMFileSenderWidget::isStopped()
{
    return m_isStopped;
}

// private:-----------------------------------------------------------------

/*************************************************
Function Name： initIMFileSenderWidget()
Description: 初始化文件发送界面
*************************************************/
void IMFileSenderWidget::initIMFileSenderWidget()
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
    m_tcpPort = 6666;

    m_fileSender = new QTcpServer(this);
    connect(m_fileSender, SIGNAL(newConnection()),
            this, SLOT(sendMessage()));
    connect(m_btnCancel, SIGNAL(clicked()),
            this, SLOT(onClickBtnCancel()));
    connect(m_btnClose, SIGNAL(clicked()),
            this, SLOT(onClickBtnClose()));

}





// private slots:-------------------------------------------------------

/*************************************************
Function Name： onClickBtnCancel()
Description: 取消发送
*************************************************/
void IMFileSenderWidget::onClickBtnCancel()
{
    if (m_fileSender != NULL && m_fileSender->isListening())
    {
//        m_fileSender->abort();
        if (m_clientConnection != NULL)
             m_clientConnection->abort();
        m_fileSender->close();
    }
    m_isStopped = true;
}

/*************************************************
Function Name： onClickBtnClose()
Description: 点击退出
*************************************************/
void IMFileSenderWidget::onClickBtnClose()
{
    onClickBtnCancel();
    close();
}


/*************************************************
Function Name： sendMessage()
Description: 当有新连接时触发 发送文件
*************************************************/
void IMFileSenderWidget::sendMessage()
{
    m_isStopped = false;
    m_clientConnection = m_fileSender->nextPendingConnection();
    connect(m_clientConnection, SIGNAL(bytesWritten(qint64)),
            this, SLOT(updateClientProgress(qint64)));
    connect(m_clientConnection, SIGNAL(disconnected()),
            this, SLOT(showClosedConnect()));

    m_labelFileStatus->setText(tr("开始传送文件！"));

    m_localFile = new QFile(m_filePath);

    if(!m_localFile->open((QFile::ReadOnly)))
    {//以只读方式打开
        QMessageBox::warning(this,tr("应用程序"),tr("无法读取文件:\n%2").arg(m_filePath).arg(m_localFile->errorString()));
        return;
    }
    m_totalBytes = m_localFile->size();
    QDataStream sendOut(&m_outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_6);
    m_time.start();  //开始计时
    QString currentFile = m_filePath.right(m_filePath.size() - m_filePath.lastIndexOf('/')-1);
    sendOut<<qint64(0)<<qint64(0)<<currentFile;
    m_totalBytes += m_outBlock.size();
    sendOut.device()->seek(0);
    sendOut<<m_totalBytes<<qint64((m_outBlock.size()-sizeof(qint64)*2));
    m_bytesToWrite = m_totalBytes - m_clientConnection->write(m_outBlock);
    qDebug()<<currentFile<<m_totalBytes;
    m_outBlock.resize(0);
}


/*************************************************
Function Name： updateClientProgress()
Description: 根据发送情况实时更新进度条
*************************************************/
void IMFileSenderWidget::updateClientProgress(qint64 numBytes)
{
    m_bytesWritten += (int)numBytes;
    if(m_bytesToWrite > 0){
        m_outBlock = m_localFile->read(qMin(m_bytesToWrite,m_loadSize));
        m_bytesToWrite -= (int)m_clientConnection->write(m_outBlock);
        m_outBlock.resize(0);
    }
    else{
        m_localFile->close();
    }
    m_barFile->setMaximum(m_totalBytes);
    m_barFile->setValue(m_bytesWritten);

   float useTime = m_time.elapsed();
   double speed = m_bytesWritten / useTime;
   m_labelFileStatus->setText(tr("已发送 %1MB (%2MB/s) \n共%3MB 已用时:%4秒\n估计剩余时间：%5秒")
                                  .arg(m_bytesWritten / (1024*1024))      // 已发送
                                  .arg(speed*1000/(1024*1024),0,'f',2)  // 速度
                                  .arg(m_totalBytes / (1024 * 1024))      // 总大小
                                  .arg(useTime/1000,0,'f',0)            // 用时
                                  .arg(m_totalBytes/speed/1000 - useTime/1000,0,'f',0)); // 剩余时间
    if(m_bytesWritten == m_totalBytes)
    {
        m_isStopped = true;
        m_labelFileStatus->setText(tr("传送文件成功"));
    }
}


/*************************************************
Function Name： showClosedConnect()
Description:  链接断开
*************************************************/
void IMFileSenderWidget::showClosedConnect()
{
    m_isStopped = true;
    m_labelFileStatus->setText(tr("文件传送被中断！"));

    if(m_bytesWritten == m_totalBytes)
        m_labelFileStatus->setText(tr("传送文件成功"));
}

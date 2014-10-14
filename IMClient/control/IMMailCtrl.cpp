#include "IMMailCtrl.h"

#include <QStandardItemModel>
#include <QTreeView>
#include <QHeaderView>
#include <QMessageBox>
#include <QString>
#include <iostream>
#include <QDebug>

#include "model/IMTcpSocket.h"

IMMailCtrl::IMMailCtrl(const QString & id, QObject *parent) :
    m_myID(id), QObject(parent)
{
    m_tcpSocket = new IMTcpSocket(this);
    m_tcpSocket->setFlag(1);
    m_tcpSocket->requestConnect();
    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(requestGetInMails()));
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
}


IMMailCtrl::~IMMailCtrl()
{
}



// private slots:------------------------------------------------------------
/*************************************************
Function Name： requestSendMail
Description: 请求发送邮件
*************************************************/
void IMMailCtrl::requestSendMail(const MailInformation &mail)
{
    qDebug() << "send mail: " << mail.m_theme;

    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(SEND_MAIL) << mail;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);

}

/*************************************************
Function Name： requestGetInMails
Description: 请求获取收件箱邮件
*************************************************/
void IMMailCtrl::requestGetInMails()
{
    qDebug() << "request in mails";
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(GET_IN_MAILS) << m_myID;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： requestGetOutMails
Description: 请求获取发件箱邮件
*************************************************/
void IMMailCtrl::requestGetOutMails()
{
    qDebug() << "request out mails";
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(GET_OUT_MAILS) << m_myID;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}


/*************************************************
Function Name： requestDeleteMail
Description: 请求删除邮件
*************************************************/
void IMMailCtrl::requestDeleteMail(const MailInformation & mail)
{
    qDebug() << "request delete mail:" << mail.m_mailID;
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0);

    if (mail.m_receiverAddress == m_myID)
        out << int(DELETE_IN_MAIL);
    else if (mail.m_senderAddress == m_myID)
        out << int(DELETE_OUT_MAIL);
    else
        return;
    out << m_myID << mail.m_mailID;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}



/*************************************************
Function Name： requestSetMailRead
Description: 请求修改邮件为已读
*************************************************/
void IMMailCtrl::requestSetMailRead(const MailInformation & mail)
{
    if (mail.m_senderAddress == m_myID)
        return;
    qDebug() << "request update mail status:" << mail.m_mailID;
    if (NULL == m_tcpSocket)
        return;
    m_blockSize = 0;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << int(SET_MAIL_READ) << m_myID << mail.m_mailID;

    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpSocket->write(block);
}

/*************************************************
Function Name： readMessage
Description: 读取信息
*************************************************/
void IMMailCtrl::readMessage()
{
    if (NULL == m_tcpSocket)
        return;
    QDataStream in(m_tcpSocket);
    in.setVersion(QDataStream::Qt_4_8);
    if (m_blockSize == 0)
    {
        if (m_tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> m_blockSize;
    }

    if (m_tcpSocket->bytesAvailable() < m_blockSize)
        return;
    int type;
    int len;
    in >> type;

    switch (type)
    {
    case GET_IN_MAILS_SUCCESS:
    {
        in >> len;
        m_inMailsVec.clear();
        m_inMailsVec.resize(len);
        for(int i=0; i<len; i++)
        {
            in >> m_inMailsVec[i];
        }
        qDebug() << "in mails len: " << len;
        emit getInMailsSuccess(m_inMailsVec);
        break;
    }
    case GET_OUT_MAILS_SUCCESS:
    {
        in >> len;
        m_outMailsVec.clear();
        m_outMailsVec.resize(len);
        for(int i=0; i<len; i++)
        {
            in >> m_outMailsVec[i];
        }
        qDebug() << "out mails len: " << len;
        emit getOutMailsSuccess(m_outMailsVec);
        break;
    }
    case DELETE_IN_MAIL_SUCCESS:
    case DELETE_OUT_MAIL_SUCCESS:
    {
        in >> m_peerID >> m_mailID;
        if (m_peerID == m_myID)
            emit deleteMailSuccess(m_mailID);
        break;
    }
    case SEND_MAIL_SUCCESS:
    {
        in >> m_mail;
        if (m_mail.m_senderAddress == m_myID)
            emit getOutMail(m_mail);
        QMessageBox::information(NULL, tr("写信"), tr("发送成功！"));
        break;
    }
    case SEND_MAIL_FAIL:
    {
        QMessageBox::information(NULL, tr("写信"), tr("发送失败！"));
        break;
    }
    case RECEIVE_MAIL:
    {
        in >> m_mail;
        if (m_mail.m_receiverAddress == m_myID)
            emit getInMail(m_mail);
        break;
    }
    default:
        break;
    }
//    qDebug() << "size of quint16: " << sizeof(quint16);
//    qDebug() << "m_blockSize: " << m_blockSize;

    m_blockSize = 0;
    QByteArray data = m_tcpSocket->readAll();
    qDebug() << "leaved in socket: " << data.size();

}

// private:------------------------------------------------------------

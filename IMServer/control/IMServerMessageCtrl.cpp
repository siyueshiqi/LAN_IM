/*********************************************
File Name： IMServerMessageCtrl.cpp
Author： jet.F.R
Date： 2014.3.10
Description： 控制服务器类
Changes：
********************************************/

#include "IMServerMessageCtrl.h"
#include "model/IMTcpServer.h"
#include "IMClientSocketCtrl.h"
#include <QMessageBox>
#include <QDateTime>
#include <QStringListModel>
#include <QListView>
#include <QStringList>
IMServerMessageCtrl::IMServerMessageCtrl(QObject *parent) :
    QObject(parent)
{
//    m_listID = new QStringList();
    m_modelID = new QStringListModel(this);
    m_modelID->setStringList(m_listID);
    m_listViewID = new QListView;
    m_listViewID->setModel(m_modelID);
    // 不可编辑
    m_listViewID->setEditTriggers(QAbstractItemView::NoEditTriggers);

//    m_listAddress = new QStringList();
    m_modelAddress = new QStringListModel(this);
    m_modelAddress->setStringList(m_listAddress);
    m_listViewAddress = new QListView;
    m_listViewAddress->setModel(m_modelAddress);
    // 不可编辑
    m_listViewAddress->setEditTriggers(QAbstractItemView::NoEditTriggers);

//    m_listViewID.setEditTriggers(QAbstractItemView.NoEditTriggers);
//    m_listViewAddress.setEditTriggers(QAbstractItemView.NoEditTriggers);

//    m_blockSize = 0;
}

IMServerMessageCtrl::~IMServerMessageCtrl()
{
//    if (m_listID != NULL)
//    {
//        delete m_listID;
//        m_listID = NULL;
//    }
//    if (m_listAddress != NULL)
//    {
//        delete m_listAddress;
//        m_listAddress = NULL;
//    }
    if (m_listViewID != NULL)
    {
        delete m_listViewID;
        m_listViewID = NULL;
    }
    if (m_listViewAddress != NULL)
    {
        delete m_listViewAddress;
        m_listViewAddress = NULL;
    }
}

/*************************************************
Function Name： runServer()
Description: 用于启动服务器
Input： NULL
Output：NULL
Changes： NULL
*************************************************/
void IMServerMessageCtrl::runServer()
{
   m_tcpServer = new IMTcpServer(this);
   connect(m_tcpServer, SIGNAL(haveNewID(QString)),
           this, SLOT(insertIDData(QString)));
   connect(m_tcpServer, SIGNAL(haveNewAddress(QString)),
           this, SLOT(insertAddressData(QString)));

   connect(m_tcpServer, SIGNAL(haveLeftID(QString)),
           this, SLOT(deleteIDData(QString)));
   connect(m_tcpServer, SIGNAL(haveLeftAddress(QString)),
           this, SLOT(deleteAddressData(QString)));


   if (!m_tcpServer->listen(QHostAddress::Any, 1234))
   {
       qDebug("run fail");
       QMessageBox::critical(NULL, tr("IM Server"),
                             tr("Unable to start the server: %1")
                             .arg(m_tcpServer->errorString()));
       exit(EXIT_FAILURE);
   }
   m_databaseCtrl.initDatabase();

   //   qDebug()<<tr("The server is running on port %1.").arg(m_tcpServer->serverPort());

   //connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(showConnectedMedssage()));
   //connect(m_tcpServer, SIGNAL(newClientSocket(IMClientSocket *)), this, SLOT(readMessage(IMClientSocket *)));

   // QMessageBox::information(NULL, tr("IM Client"),
   //                          tr("Runing to Server..."));
   //     if (m_tcpServer->isListening())
   //     {
   //         QMessageBox::information(NULL, tr("IM Client"),
   //                                  tr("The server is running on port %1.").arg(m_tcpServer->serverPort()));
   //     }
}


/*************************************************
Function Name： getIDListView()
Description: 获取listiew
*************************************************/
QListView * IMServerMessageCtrl::getIDListView()
{
    return m_listViewID;
}

/*************************************************
Function Name： getAddressListView()
Description: 获取listiew
*************************************************/
QListView * IMServerMessageCtrl::getAddressListView()
{
    return m_listViewAddress;
}

// mark: private slots---------------------------------------------------

/*************************************************
Function Name： showConnectedMedssage()
Description: Not used
Input： NULL
Output：NULL
Changes： NULL
*************************************************/
void IMServerMessageCtrl::showConnectedMedssage()
{
//     QTcpSocket *newClientSocket = m_tcpServer->nextPendingConnection();
//     QHostAddress newClientAddress = newClientSocket->peerAddress();
//     qDebug() << newClientAddress;
//     delete newClientSocket
}

/*************************************************
Function Name： readMessage()
Description: Not used
Input： IMClientSocketCtrl* socket：
Output：NULL
Changes： NULL
*************************************************/
void IMServerMessageCtrl::readMessage(IMClientSocketCtrl* socket)
{
    delete socket;

  //IMClientSocket *newClientSocket = socket;
//     if (!newClientSocket->waitForReadyRead(30000))
//     {
//         return;
//     }


//     QDataStream in(newClientSocket);
//     in.setVersion(QDataStream::Qt_4_8);
//     if (m_blockSize == 0)
//     {
//         qDebug()<<"size"<<newClientSocket->bytesAvailable();
//         if (newClientSocket->bytesAvailable() < sizeof(quint16))
//             return;
//         in >> m_blockSize;
//     }

//     if (newClientSocket->bytesAvailable() < m_blockSize)
//     {
//         qDebug("here-43");
//         return;
//     }
//     int type;
//     QString id;
//     QString pwd;
//     QDateTime dateTime;

//     in >> type;

//     switch (type)
//     {
//     case LOGIN:
//         in >> id >> pwd >>dateTime;
//         break;
//     default:
//         break;
//     }
//     qDebug() << m_blockSize << type << id << pwd << dateTime;
}


/*************************************************
Function Name： insertIDData()
Description: 插入数据
*************************************************/
void IMServerMessageCtrl::insertIDData(const QString & id)
{
//    int row = m_modelID->rowCount();
//    m_modelID->insertRows(row, 1);
//    QModelIndex index = m_modelID->index(row);
//    m_modelID->setData(index, id);
//    m_listViewID->setCurrentIndex(index);
    m_listID.append(id);
    m_modelID->setStringList(m_listID);
}

/*************************************************
Function Name： deleteIDData()
Description: 删除数据
*************************************************/
void IMServerMessageCtrl::deleteIDData(const QString &id)
{
//    if(m_modelID->rowCount() > 1)
//    {
//        m_modelID->removeRows(m_listViewID->currentIndex().row(), 1);
//    }
    int index = m_listID.indexOf(id);
    m_listID.removeAt(index);
    m_modelID->removeRow(index);
}

/*************************************************
Function Name： insertIDData()
Description: 插入数据
*************************************************/
void IMServerMessageCtrl::insertAddressData(const QString &address)
{
//    int row = m_modelAddress->rowCount();
//    m_modelAddress->insertRows(row, 1);
//    QModelIndex index = m_modelAddress->index(row);
//    m_modelAddress->setData(index, address);
//    m_listViewAddress->setCurrentIndex(index);

    m_listAddress.append(address);
    m_modelAddress->setStringList(m_listAddress);

}

/*************************************************
Function Name： deleteIDData()
Description: 删除数据
*************************************************/
void IMServerMessageCtrl::deleteAddressData(const QString & address)
{
    int index = m_listAddress.indexOf(address);
    m_listAddress.removeAt(index);
    m_modelAddress->removeRow(index);
}

 // mark: private----------------------------------------------------

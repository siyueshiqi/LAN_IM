#include "IMMailWidget.h"

#include <QTabWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QVBoxLayout>

#include "IMMailButton.h"
#include "IMMailInWidget.h"
#include "IMMailOutWidget.h"
#include "IMMailWriteWidget.h"
#include "control/IMMailCtrl.h"
#include "IMMailInformationWidget.h"

IMMailWidget::IMMailWidget(const QString & myID, QWidget *parent)
    : m_myID(myID), QWidget(parent)
{
    m_mailCtrl = new IMMailCtrl(myID, this);
    initIMMailWidget();
    linkSignalWithSlot();
    setWindowTitle(tr("IM邮件"));
}

IMMailWidget::~IMMailWidget()
{
    clearContainers();
}
/*************************************************
Function Name： getMailCtrl
Description: 获取mail控制对象
*************************************************/
IMMailCtrl* IMMailWidget::getMailCtrl()
{
    return m_mailCtrl;
}

/*************************************************
Function Name： getMyID
Description: 获取用户自己的ID
*************************************************/
QString IMMailWidget::getMyID()
{
    return m_myID;
}

/*************************************************
Function Name： getMailCtrl
Description: 获取mail控制对象
*************************************************/
void IMMailWidget::showMailInformationWidget(const MailInformation & mail)
{
    int count = m_tabWidget->count();
    if (count < 4)
    {
        m_tabWidget->addTab(m_informationWidget, tr("信件详情"));
    }
    m_informationWidget->setMailInformation(mail);
    m_tabWidget->setCurrentWidget(m_informationWidget);

}

/*************************************************
Function Name： showMailInWidget
Description: 显示收件箱
*************************************************/
void IMMailWidget::showMailInWidget()
{
    if (m_inWidget == NULL || m_tabWidget == NULL)
        return;
    m_tabWidget->setCurrentWidget(m_inWidget);
}

/*************************************************
Function Name： showMailWriteWidget
Description: 显示写信窗口
*************************************************/
void IMMailWidget::showMailWriteWidget(const QString & address)
{
    if (m_writeWidget == NULL || m_tabWidget == NULL)
    {
        return;
    }
    m_tabWidget->setCurrentWidget(m_writeWidget);
    m_writeWidget->setReceiverAddress(address);
}

//private slots:--------------------------------------------------------
/*************************************************
Function Name： setInMailsWidget
Description: 设置收件箱
*************************************************/
void IMMailWidget::setInMailsWidget(const QVector<MailInformation> & inMailsVec)
{
    int len = inMailsVec.size();
    for(int i=0; i<len; i++)
    {
        addInMailButton(inMailsVec[i]);
    }
    m_mailCtrl->requestGetOutMails();
}


/*************************************************
Function Name： setOutMailsWidget
Description: 设置发件箱
*************************************************/
void IMMailWidget::setOutMailsWidget(const QVector<MailInformation> & outMailVec)
{
    int len = outMailVec.size();
    for(int i=0; i<len; i++)
    {
        addOutMailButton(outMailVec[i]);
    }
}

/*************************************************
Function Name： addInMailButton
Description: 添加收件箱按钮
*************************************************/
bool IMMailWidget::addInMailButton(const MailInformation & mail)
{
    if (m_inMailMap.contains(mail.m_mailID))
        return false;

    IMMailButton *button = new IMMailButton(mail, this, this);
//    button->setAutoRaise(true);

    m_inMailMap.insert(mail.m_mailID, button);
    m_inWidget->addItem(button);

    return true;
}

/*************************************************
Function Name： addOutMailButton
Description: 添加发件箱按钮
*************************************************/
bool IMMailWidget::addOutMailButton(const MailInformation & mail)
{
    if (m_outMailMap.contains(mail.m_mailID))
        return false;

    IMMailButton *button = new IMMailButton(mail, this, this);
//    button->setAutoRaise(true);

    m_outMailMap.insert(mail.m_mailID, button);
    m_outWidget->addItem(button);

    return true;
}

/*************************************************
Function Name： deleteMail
Description: 删除邮件按钮
*************************************************/
void IMMailWidget::deleteMail(const int & mailID)
{
    if (m_inMailMap.contains(mailID))
    {
        m_inWidget->removeItem(m_inMailMap[mailID]);
        m_inMailMap[mailID]->deleteLater();
        m_inMailMap.remove(mailID);
    }

    if (m_outMailMap.contains(mailID))
    {
        m_outWidget->removeItem(m_outMailMap[mailID]);
        m_outMailMap[mailID]->deleteLater();
        m_outMailMap.remove(mailID);
    }
    if (m_tabWidget->currentIndex() == 3)
    {
        m_tabWidget->setCurrentIndex(0);
    }
    if (m_tabWidget->count() >= 4)
    {
        m_tabWidget->removeTab(3);
    }
}


/*************************************************
Function Name： deleteMail
Description: 添加新邮件到发件箱
*************************************************/
bool IMMailWidget::addNewOutMailButton(const MailInformation & mail)
{
    if (m_outMailMap.contains(mail.m_mailID))
        return false;

    IMMailButton *button = new IMMailButton(mail, this, this);

    m_outMailMap.insert(mail.m_mailID, button);
    m_outWidget->insertItem(0, button);

    return true;
}

/*************************************************
Function Name： deleteMail
Description: 添加新邮件到收件箱
*************************************************/
bool IMMailWidget::addNewInMailButton(const MailInformation & mail)
{
    if (m_inMailMap.contains(mail.m_mailID))
        return false;

    IMMailButton *button = new IMMailButton(mail, this, this);

    m_inMailMap.insert(mail.m_mailID, button);
    m_inWidget->insertItem(0, button);

    return true;
}


// private:-----------------------------------------------------------
/*************************************************
Function Name： initIMMainWidget
Description: 初始化
*************************************************/
void IMMailWidget::initIMMailWidget()
{
    m_tabWidget= new QTabWidget(this);
    m_outWidget = new IMMailOutWidget(m_mailCtrl, this);
    m_inWidget = new IMMailInWidget(m_mailCtrl, this);
    m_writeWidget = new IMMailWriteWidget(m_myID, m_mailCtrl, this);
    m_informationWidget = new IMMailInformationWidget(this, this);

    m_tabWidget->addTab(m_inWidget, tr("收件箱"));
    m_tabWidget->addTab(m_outWidget, tr("发件箱"));
    m_tabWidget->addTab(m_writeWidget, tr("写信"));
//    m_tabWidget->setTabPosition(QTabWidget::West);
    m_labelInformation = new QLabel(QString(tr("%1, 你好！")).arg(m_myID), this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_labelInformation);
    mainLayout->addWidget(m_tabWidget);

    setLayout(mainLayout);
}

/*************************************************
Function Name： linkSignalWithSlot
Description:  连接信号与槽
*************************************************/
void IMMailWidget::linkSignalWithSlot()
{
    connect(m_mailCtrl, SIGNAL(getInMailsSuccess(QVector<MailInformation>)),
            this, SLOT(setInMailsWidget(QVector<MailInformation>)));
    connect(m_mailCtrl, SIGNAL(getOutMailsSuccess(QVector<MailInformation>)),
            this, SLOT(setOutMailsWidget(QVector<MailInformation>)));

    connect(m_mailCtrl, SIGNAL(deleteMailSuccess(int)),
            this, SLOT(deleteMail(int)));
    connect(m_mailCtrl, SIGNAL(getInMail(MailInformation)),
            this, SLOT(addNewInMailButton(MailInformation)));
    connect(m_mailCtrl, SIGNAL(getOutMail(MailInformation)),
            this, SLOT(addNewOutMailButton(MailInformation)));
}

/*************************************************
Function Name： clearContainers
Description:  清理容器
*************************************************/
void IMMailWidget::clearContainers()
{
    qDeleteAll(m_inMailMap.begin(), m_inMailMap.end());
    m_inMailMap.clear();

    qDeleteAll(m_outMailMap.begin(), m_outMailMap.end());
    m_outMailMap.clear();
}

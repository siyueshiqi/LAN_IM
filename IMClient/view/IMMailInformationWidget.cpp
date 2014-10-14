#include "IMMailInformationWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextCharFormat>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <qdebug.h>
#include <QLineEdit>
#include <QTextEdit>
#include <QTextBrowser>
#include <QTextEdit>

#include "IMMailWidget.h"
#include "control/IMMailCtrl.h"

IMMailInformationWidget::IMMailInformationWidget(IMMailWidget * mailWidget,
                                                 QWidget *parent) :
     m_mailWidget(mailWidget), QWidget(parent)
{
    if (NULL == m_mailWidget)
        return;
    m_mailCtrl = m_mailWidget->getMailCtrl();

    initIMMailInformationWidget();
    linkSignalWithSlot();
}

/*************************************************
Function Name： setMailInformation()
Description:  设置邮件信息
*************************************************/
void IMMailInformationWidget::setMailInformation(const MailInformation & mail)
{
    m_mail = mail;
//    m_mailWidget->showMailInWidget();
    m_labelSenderAddress->setText(QString("%1%2").arg(m_mail.m_senderAddress)
                                  .arg(MAIL_ADDRESS_FORMAT));
    m_labelReceiverAddress->setText(QString("%1%2").arg(m_mail.m_receiverAddress)
                                    .arg(MAIL_ADDRESS_FORMAT));
    m_labelTime->setText(mail.m_dateTime.toString("yyyy-MM-dd hh:mm:ss"));
    m_labelTheme->setText(m_mail.m_theme);
    m_textContnet->clear();
    m_textContnet->append(m_mail.m_content);
//    m_textInput->append(m_mail.m_content);
}


// private slots:-----------------------------------------------------
/*************************************************
Function Name： onClickBtnDelete()
Description:  删除
*************************************************/
void IMMailInformationWidget::onClickBtnDelete()
{
    if (m_mailCtrl != NULL)
        m_mailCtrl->requestDeleteMail(m_mail);
}

/*************************************************
Function Name： onClickBtnClose()
Description:  关闭
*************************************************/
void IMMailInformationWidget::onClickBtnClose()
{
    m_mailWidget->showMailInWidget();
}

// private:-------------------------------------------------
/*************************************************
Function Name： initIMMailInformationWidget()
Description:  初始化
*************************************************/
void IMMailInformationWidget::initIMMailInformationWidget()
{


    // 左侧标签部分
    QLabel *labelSender = new QLabel(tr("发件人:"), this);
    QLabel *labelReceiver = new QLabel(tr("收件人:"), this);
    QLabel *labelTheme = new QLabel(tr("主    题:"), this);
    QLabel *labelTime = new QLabel(tr("时    间:"), this);
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->setAlignment(Qt::AlignRight);
    leftLayout->addWidget(labelSender, 0, Qt::AlignRight);
    leftLayout->addWidget(labelReceiver, 0, Qt::AlignRight);
    leftLayout->addWidget(labelTheme, 0, Qt::AlignRight);
    leftLayout->addWidget(labelTime, 0, Qt::AlignRight);

    // 右侧标签部分
    m_labelSenderAddress = new QLabel(this);
    m_labelReceiverAddress = new QLabel(this);
    m_labelTheme = new QLabel(this);
    m_labelTime = new QLabel(this);
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(m_labelSenderAddress);
    rightLayout->addWidget(m_labelReceiverAddress);
    rightLayout->addWidget(m_labelTheme);
    rightLayout->addWidget(m_labelTime);

    // 顶部部分
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addLayout(leftLayout);
    topLayout->addLayout(rightLayout);
    topLayout->addStretch();
//    topLayout->setContentsMargins(0,0,0,0);

    // 底部按钮部分
    m_btnDelete = new QPushButton(tr("删除"), this);
    m_btnClose = new QPushButton(tr("关闭"), this);
    m_btnClose->setDefault(true);
    QHBoxLayout *btmLayout = new QHBoxLayout;
    btmLayout->addStretch();
    btmLayout->addWidget(m_btnDelete);
    btmLayout->addWidget(m_btnClose);

    // 总体
//    m_textInput = new QTextEdit(this);////////
    m_textContnet = new QTextBrowser(this);
//    m_textContnet->setMinimumWidth(100);
//    m_textInput->setMaximumHeight(170);

    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->setContentsMargins(0, 0, 0, 0);
//    mainLayout->setSpacing(0);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(m_textContnet);
    mainLayout->addLayout(btmLayout);

    setLayout(mainLayout);
}

/*************************************************
Function Name： linkSignalWithSlot()
Description:  连接信号与槽
*************************************************/
void IMMailInformationWidget::linkSignalWithSlot()
{
    connect(m_btnClose, SIGNAL(clicked()),
            this, SLOT(onClickBtnClose()));
    connect(m_btnDelete, SIGNAL(clicked()),
            this, SLOT(onClickBtnDelete()));
}


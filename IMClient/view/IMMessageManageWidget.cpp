#include "IMMessageManageWidget.h"
#include <QTabWidget>
#include "IMLocalMessageWidget.h"
#include "IMNetWorkMessageWidget.h"
#include <QVBoxLayout>

IMMessageManageWidget::IMMessageManageWidget(IMMainWidget *mainWidget,
                                             QWidget *parent) :
    QWidget(parent), m_mainWidget(mainWidget)
{
    if (m_mainWidget == NULL)
    {
        return;
    }
    m_tabWidget= new QTabWidget(this);
    m_localWidget = new IMLocalMessageWidget(m_mainWidget, this);
    m_networkWidget = new IMNetWorkMessageWidget(m_mainWidget, this);
    setWindowTitle(tr("消息管理"));
    m_tabWidget->addTab(m_localWidget, tr("本地消息"));
    m_tabWidget->addTab(m_networkWidget, tr("网络消息"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_tabWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);

//    connect(m_localWidget, SIGNAL(currentIndexClicked(int)),
//            this, SLOT());
//    connect(m_networkWidget, SIGNAL(currentIndexClicked(int)),
//            this, SLOT());
}


IMMessageManageWidget::~IMMessageManageWidget()
{
}


void IMMessageManageWidget::setLocalMessageWidget(const QVector<TalkMessage> & mesVec)
{
    m_localWidget->setMessageShow(mesVec);
}

void IMMessageManageWidget::setNetworkMessageWidget(const QVector<TalkMessage> & mesVec)
{
    m_networkWidget->setMessageShow(mesVec);
}


void IMMessageManageWidget::setListModelGroup()
{
    m_localWidget->setListModelGroup();
    m_networkWidget->setListModelGroup();
}

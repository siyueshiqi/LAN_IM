#include "IMMessageWidget.h"
#include "CustomLineEdit.h"
#include <QMessageBox>
#include <QDateTime>
#include <QStringList>
#include <QStringListModel>
#include <QListView>
#include <QHBoxLayout>
#include <QToolButton>
#include <QTextBrowser>
#include <QTextCharFormat>
#include <QLabel>
#include <QModelIndex>
#include <QDebug>
#include "view/IMMainWidget.h"

IMMessageWidget::IMMessageWidget(IMMainWidget * mainWidget, QWidget *parent) :
    QWidget(parent), m_mainWidget(mainWidget)
{
    if (m_mainWidget == NULL)
        return;
    initIMMessageWidget();
    linkSignalWithSlot();
    setMinimumSize(600,350);
    setListModelGroup();
    m_indexOfFriendList = -1;
//    m_listViewGroup->setCurrentIndex(0);
}

IMMessageWidget::~IMMessageWidget()
{
}

/*************************************************
Function Name： setListModelGroup()
Description: 设置 分组 的model
*************************************************/
void IMMessageWidget::setListModelGroup(const QStringList & groupList)
{
    m_modelGroup->setStringList(groupList);
}


/*************************************************
Function Name： setListModelGroup()
Description: 设置 分组 的model
*************************************************/
void IMMessageWidget::setListModelGroup()
{
    m_groupList = m_mainWidget->getGroupList();
    m_modelGroup->setStringList(m_groupList);
}

/*************************************************
Function Name： setListModelFriend()
Description: 设置 好友 的model
*************************************************/
void IMMessageWidget::setListModelFriend(const QStringList & friendList)
{
    m_modelFriend->setStringList(friendList);
}

/*************************************************
Function Name： setListModelFriend()
Description: 设置 好友 的model
*************************************************/
void IMMessageWidget::setListModelFriend(const QString & groupName)
{
    m_friendList = m_mainWidget->getGroupFriendList(groupName);
    m_modelFriend->setStringList(m_friendList);
}


/*************************************************
Function Name： setShowMode()
Description: 设置显示的模式
*************************************************/
void IMMessageWidget::setShowMode(Mode mode)
{
    if (mode == LOCAL)
    {
        m_labelInformation->setText(tr("本地消息记录管理"));
        m_tooBtnImport->setVisible(true);
    }
    else if (mode == NETWORK)
    {
        m_labelInformation->setText(tr("网络消息记录管理"));
        m_tooBtnImport->setVisible(false);
        m_toolBtnExportAll->setVisible(false);
        m_toolBtnExportAll->setVisible(false);
        m_toolBtnDeleteOne->setVisible(false);
        m_toolBtnExportOne->setToolTip(tr("导出当前显示的消息"));
        m_toolBtnExportOne->setStatusTip(tr("导出当前显示的消息记录"));

        m_toolBtnDeleteAll->setVisible(false);
    }
}

/*************************************************
Function Name： setMessageShow()
Description: 设置显示的消息
*************************************************/
void IMMessageWidget::setMessageShow(const QVector<TalkMessage> & mesVec)
{
    m_tbMessageShow->clear();
    QString temp;
    TalkMessage mes;
    QString name;
    for (int i=0; i<mesVec.size(); ++i)
    {
        mes = mesVec[i];
        if (mes.m_senderID == m_mainWidget->getLocalMyInformation().m_userID)
            name = tr("我");
        else
            name = m_name;
        temp = QString("<font size=\"FONT_SIEZE\" color=blue>%1 %2: </font><br>%3")
                .arg(name).arg(mes.m_dateTime.toString("yyyy-MM-dd hh:mm:ss")).arg(mes.m_text);
        m_tbMessageShow->append(temp);
    }
//    m_tbMessageShow->scroll(-100, - 100);
}

/*************************************************
Function Name： setShowMode()
Description: 组列表
*************************************************/
void IMMessageWidget::groupItemClicked(const QModelIndex & index)
{
    setListModelFriend(index.data().toString());
}


/*************************************************
Function Name： friendItemClicked()
Description:  单击好友列表项
*************************************************/
void IMMessageWidget::friendItemClicked(const QModelIndex & index)
{
    qDebug() << "friend:" << index.row() << ":" << index.data().toString();

    m_indexOfFriendList = index.row();
    m_name = index.data().toString();
    emit currentIndexClicked(m_indexOfFriendList);
}

// private:-------------------------------------------------

/*************************************************
Function Name： initIMMessageWidget()
Description: 初始化
*************************************************/
void IMMessageWidget::initIMMessageWidget()
{
    /*********************顶部**************************/
    m_labelInformation = new QLabel(tr("消息管理"),this);

    m_toolBtnGetMessage= new QToolButton(this);
    m_toolBtnGetMessage->setIcon(QIcon(":/images/download_message.png"));
    m_toolBtnGetMessage->setAutoRaise(true);
    m_toolBtnGetMessage->setFocus();
    m_toolBtnGetMessage->setToolTip(tr("获取消息"));
    m_toolBtnGetMessage->setStatusTip(tr("获取与当前好友当前日期的消息记录"));

    m_leBirthday = new CustomLineEdit(this);
    m_leBirthday->setFixedWidth(100);
    m_leBirthday->setToolTip(tr("选择查看日期"));
    m_leBirthday->setStatusTip(tr("选择需要查看的日期"));

    m_tooBtnImport = new QToolButton(this);
    m_tooBtnImport->setIcon(QIcon(":/images/importAll.png"));
    m_tooBtnImport->setAutoRaise(true);
    m_tooBtnImport->setToolTip(tr("导入消息"));
    m_tooBtnImport->setStatusTip(tr("导入聊天记录"));

    m_toolBtnExportOne = new QToolButton(this);
    m_toolBtnExportOne->setIcon(QIcon(":/images/exportOne.png"));
    m_toolBtnExportOne->setAutoRaise(true);
    m_toolBtnExportOne->setToolTip(tr("导出当前好友消息"));
    m_toolBtnExportOne->setStatusTip(tr("导出当前与好友的消息记录"));

    m_toolBtnExportAll = new QToolButton(this);
    m_toolBtnExportAll->setIcon(QIcon(":/images/exportAll.png"));
    m_toolBtnExportAll->setAutoRaise(true);
    m_toolBtnExportAll->setToolTip(tr("导出所有消息"));
    m_toolBtnExportAll->setStatusTip(tr("导出所有消息记录"));

//    m_toolBtnDeleteDate= new QToolButton(this);
//    m_toolBtnDeleteDate->setIcon(QIcon(":/images/deleteDate.png"));
//    m_toolBtnDeleteDate->setAutoRaise(true);
//    m_toolBtnDeleteDate->setToolTip(tr("删除当前显示的消息记录"));
//    m_toolBtnDeleteDate->setStatusTip(tr("删除当先显示的消息记录"));

    m_toolBtnDeleteOne = new QToolButton(this);
    m_toolBtnDeleteOne->setIcon(QIcon(":/images/deleteOne.png"));
    m_toolBtnDeleteOne->setAutoRaise(true);
    m_toolBtnDeleteOne->setToolTip(tr("删除当前好友消息记录"));
    m_toolBtnDeleteOne->setStatusTip(tr("删除与当前好友的消息记录"));

    m_toolBtnDeleteAll = new QToolButton(this);
    m_toolBtnDeleteAll->setIcon(QIcon(":/images/deleteAll.png"));
    m_toolBtnDeleteAll->setAutoRaise(true);
    m_toolBtnDeleteAll->setToolTip(tr("删除所有消息记录"));
    m_toolBtnDeleteAll->setStatusTip(tr("删除所有的消息记录"));


    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(m_labelInformation);
    topLayout->addStretch();
    topLayout->addWidget(m_toolBtnGetMessage);
    topLayout->addWidget(m_leBirthday);
    topLayout->addWidget(m_tooBtnImport);
    topLayout->addWidget(m_toolBtnExportOne);
    topLayout->addWidget(m_toolBtnExportAll);
//    topLayout->addWidget(m_toolBtnDeleteDate);
    topLayout->addWidget(m_toolBtnDeleteOne);
    topLayout->addWidget(m_toolBtnDeleteAll);

    /********************中间**************************/
    m_modelGroup = new QStringListModel(this);
//    m_modelGroup->setStringList();
    m_listViewGroup = new QListView(this);
    m_listViewGroup->setFixedWidth(120);
    // 不可编辑
    m_listViewGroup->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_listViewGroup->setModel(m_modelGroup);
    m_listViewGroup->setToolTip(tr("分组列表"));
    m_listViewGroup->setStatusTip(tr("请选择分组"));

    m_modelFriend = new QStringListModel(this);
//    m_modelFriend->setStringList();
    m_listViewFriend = new QListView(this);
    m_listViewFriend->setFixedWidth(120);
    // 不可编辑
    m_listViewFriend->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_listViewFriend->setModel(m_modelFriend);
    m_listViewFriend->setToolTip(tr("好友列表"));
    m_listViewFriend->setStatusTip(tr("请选择好友"));

    m_tbMessageShow = new QTextBrowser(this);

    QHBoxLayout *midLayout = new QHBoxLayout;
    midLayout->addWidget(m_listViewGroup);
    midLayout->addWidget(m_listViewFriend);
    midLayout->addWidget(m_tbMessageShow);

    /********************整体*************************/
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(midLayout);

    setLayout(mainLayout);

}


/*************************************************
Function Name： linkSignalWithSlot
Description:  连接信号与槽
*************************************************/
void IMMessageWidget::linkSignalWithSlot()
{
//    connect(m_toolBtnDeleteDate, SIGNAL(clicked()),
//            this, SLOT(onClickDeleteDate()));
    connect(m_toolBtnDeleteOne, SIGNAL(clicked()),
            this, SLOT(onClickDeleteOne()));
    connect(m_toolBtnDeleteAll, SIGNAL(clicked()),
            this, SLOT(onClickDeleteAll()));
    connect(m_tooBtnImport, SIGNAL(clicked()),
            this, SLOT(onClickImport()));

    connect(m_toolBtnExportOne, SIGNAL(clicked()),
            this, SLOT(onClickExportOne()));
    connect(m_toolBtnExportAll, SIGNAL(clicked()),
            this, SLOT(onClickExportAll()));
    connect(m_toolBtnGetMessage, SIGNAL(clicked()),
            this, SLOT(onClickGetMessage()));

    connect(m_listViewGroup,SIGNAL(clicked(QModelIndex)),this,SLOT(groupItemClicked(QModelIndex)));
    connect(m_listViewFriend,SIGNAL(clicked(QModelIndex)),this,SLOT(friendItemClicked(QModelIndex)));
}

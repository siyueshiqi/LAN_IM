#include "IMFriendListWidget.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QDebug>
#include <QMouseEvent>
#include <QMenu>
#include "view/IMMainWidget.h"

IMFriendListWidget::IMFriendListWidget(IMMainWidget *mainWidget, QWidget *parent) :
    m_mainWidget(mainWidget), QWidget(parent), m_layout(new QVBoxLayout)
{
    QVBoxLayout *mainLayout=new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    m_contentsWidget = new QWidget;
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);
//    QSize AdjustSize = m_contentsWidget->size();
//    m_contentsWidget->setMinimumSize(AdjustSize);
    m_contentsWidget->setLayout(m_layout);

    m_friendsScrollArea = new QScrollArea(this);
//    m_friendsScrollArea->setObjectName(QString::fromUtf8("scrollArea"));
    m_friendsScrollArea->setWidgetResizable(true);
    m_friendsScrollArea->setAlignment(Qt::AlignLeft);
//    m_friendsScrollArea->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
//    m_contentsWidget->setGeometry(QRect(0, 0, 270, 100));
//    m_contentsWidget->setMinimumSize(270,100);
//    m_contentsWidget->showMaximized();
    //setMinimumSize(270, 600);
    m_friendsScrollArea->setWidget(m_contentsWidget);

    mainLayout->addWidget(m_friendsScrollArea);
    setLayout(mainLayout);

    setStyleSheet("QWidget{border: 0;}");

    creatMenu();
}

/*************************************************
Function Name： addItem()
Description:  添加
*************************************************/
void IMFriendListWidget::addItem(QWidget *item)
{
    // Remove last spacer item if present.
    int count = m_layout->count();
    if (count > 1)
    {
        m_layout->removeItem(m_layout->itemAt(count - 1));
    }

    // Add item and make sure it stretches the remaining space.
    m_layout->addWidget(item);
    m_layout->addStretch();
}

/*************************************************
Function Name： creatMenu
Description: 创建右键菜单
*************************************************/
void IMFriendListWidget:: creatMenu()
{
    m_menu = new QMenu(this);
    QAction *create = new QAction(tr("新建分组"), m_menu);
    QAction *refresh = new QAction(tr("刷新好友列表"), m_menu);
    QAction *addFriend = new QAction(tr("添加好友"), m_menu);

    connect(create, SIGNAL(triggered()),
            m_mainWidget, SLOT(createBox()));
    connect(refresh, SIGNAL(triggered()),
            m_mainWidget, SLOT(getFriendsInformation()));
    connect(addFriend, SIGNAL(triggered()),
            m_mainWidget, SLOT(onClickAddFriend()));

    m_menu->addAction(create);
    m_menu->addAction(refresh);
    m_menu->addAction(addFriend);
}


/*************************************************
Function Name： showMenu()
Description:  显示右键菜单
*************************************************/
void IMFriendListWidget::showMenu()
 {
    if (m_menu == NULL)
    {
        //创建右键菜单
        creatMenu();
    }
    m_menu->exec(QCursor::pos());
 }


// mark protected:------------------------------------------------------
/*************************************************
Function Name： mousePressEvent
Description: 鼠标点击事件
*************************************************/
void IMFriendListWidget:: mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        showMenu();
        return;
    }
    QWidget::mousePressEvent(event);
}

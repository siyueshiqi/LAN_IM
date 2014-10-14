#include "IMLatestMessageListWidget.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMenu>
#include "IMMainWidget.h"
#include <QDebug>
#include <QMouseEvent>

IMLatestMessageListWidget::IMLatestMessageListWidget(
        IMMainWidget *mainWidget, QWidget *parent) :
    QWidget(parent),  m_layout(new QVBoxLayout), m_mainWidget(mainWidget)
{
    m_mesCounter = 0;
    if (NULL == m_mainWidget)
        return;
    QVBoxLayout *mainLayout=new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    m_contentsWidget = new QWidget;
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);
    m_contentsWidget->setLayout(m_layout);
    m_contentsWidget->setStyleSheet("QWidget{border: 0;}");

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setAlignment(Qt::AlignLeft);

    m_scrollArea->setWidget(m_contentsWidget);

    mainLayout->addWidget(m_scrollArea);
    setLayout(mainLayout);

    setStyleSheet("QWidget{border: 0;}");

    //创建右键菜单
    creatMenu();
}

/*************************************************
Function Name： addItem()
Description:  添加
*************************************************/
void IMLatestMessageListWidget::addItem(QWidget *item)
{
    // Remove last spacer item if present.
    int count = m_layout->count();
//    if (count == 0)
//    {
//        delete m_layout;
//        m_layout = new QVBoxLayout();
//        m_layout->setContentsMargins(0,0,0,0);
//        m_layout->setSpacing(0);
//        m_contentsWidget->setLayout(m_layout);
//    }
    if (count > 1)
    {
        m_layout->removeItem(m_layout->itemAt(count - 1));
    }

    // Add item and make sure it stretches the remaining space.
    m_layout->addWidget(item);
    m_layout->addStretch();

    emit timerStatus(true);
}

/*************************************************
Function Name： removeItem()
Description:  删除
*************************************************/
void IMLatestMessageListWidget::removeItem(QWidget *item)
{
    m_layout->removeWidget(item);
    if (m_layout->count() == 1)
    {
        m_layout->removeItem(m_layout->itemAt(0));

        emit timerStatus(false);
    }
}

/*************************************************
Function Name： size()
Description:  size
*************************************************/
int IMLatestMessageListWidget::size()
{
   m_mesCounter = m_layout->count();
   if (m_mesCounter > 1)
       --m_mesCounter;

   return m_mesCounter;
}

/*************************************************
Function Name： creatMenu()
Description:  创建右键菜单
*************************************************/
void IMLatestMessageListWidget::creatMenu()
{
    m_menu = new QMenu(this);
    QAction *showAll = new QAction(tr("查看所有消息"), this);
    QAction *ignoreAll = new QAction(tr("忽略所有消息"), this);

    connect(showAll, SIGNAL(triggered()),
        m_mainWidget, SLOT(showAllChatRoom()));
    connect(ignoreAll, SIGNAL(triggered()),
        m_mainWidget, SLOT(removeAllLinkButton()));

    m_menu->addAction(showAll);
    m_menu->addAction(ignoreAll);
}


/*************************************************
Function Name： showMenu()
Description:  显示右键菜单
*************************************************/
void IMLatestMessageListWidget::showMenu()
 {
    if (m_menu == NULL)
    {
        //创建右键菜单
        creatMenu();
    }
    m_menu->exec(QCursor::pos());
 }


/*************************************************
Function Name： mousePressEvent
Description: 鼠标单击事件
*************************************************/
void IMLatestMessageListWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        showMenu();
        return;
    }
    QWidget::mousePressEvent(event);
}

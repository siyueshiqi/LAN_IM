#include "IMFlockChatWidget.h"
#include <QLabel>
#include <qdebug.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QPixmap>
#include <QPushButton>
#include <QFrame>
#include <QFontComboBox>
#include <QComboBox>
#include <QTextBrowser>
#include <QDockWidget>
#include "model/IMTcpSocket.h"
#include <QMessageBox>
#include "IMInputTextEdit.h"
#include "IMClickLabel.h"
#include <QCloseEvent>
#include <QColorDialog>
#include "IMClickLabel.h"
#include <QCloseEvent>
#include <QColorDialog>
#include <QTextCharFormat>
#include "IMFlockMemberButton.h"
#include "IMFlockMemberListWidget.h"
#include "IMMainWidget.h"
#include "control/IMClientFileCtrl.h"

IMFlockChatWidget::IMFlockChatWidget(const FlockInformation & flock,
                                     IMMainWidget * mainWidget,
                                     QWidget *parent) :
    QWidget(parent)
{
    m_mainWidget = mainWidget;
    m_flockInfor = flock;
    initIMFlockChatWidget();
    setLabelStatus();
    linkSignalWithSlot();

    setWindowTitle(tr("IM群聊窗口"));
}

IMFlockChatWidget::~IMFlockChatWidget()
{
    qDeleteAll(m_flockMemberMap.begin(), m_flockMemberMap.end());
    m_flockMemberMap.clear();

    m_messagesVec.clear();
}

/*************************************************
Function Name： appendMessageShow()
Description:  添加群成员发来的信息
*************************************************/
void IMFlockChatWidget::appendMessageShow(const TalkMessage &mes)

{
    //qDebug() << "flock receive mes:" << mes.m_senderID << m_flockInfor.m_flockID << mes.m_text;
    // using TalkMessage.m_senderID to find user's name
    if (m_flockMemberMap.size() == 0)
    {
        m_messagesVec.push_back(mes);
        return;
    }
    FlockMember member;
    if (!m_flockMemberMap.contains(mes.m_senderID))
    {
        return;
    }
    member = m_flockMemberMap[mes.m_senderID]->getInformation();

    QString  name;
    if(member.m_remark.isEmpty())
        name = member.m_nickname;
    else
        name = member.m_remark;

    //将（收到的）信息显示在输出栏
    QString dateTime = IMTcpSocket::getCurrentDateTime();
    QString temp = QString("<font size=\"FONT_SIEZE\" color=blue>%1    %2: </font>%3")
        .arg(name).arg(dateTime).arg(mes.m_text);
    m_tbMessageShow->append(temp);
}


/*************************************************
Function Name： setLabelStatus()
Description:  设置聊天窗口显示信息
*************************************************/
void IMFlockChatWidget::setLabelStatus()
{
    QString str = QString(":/images/flock.png");
    QPixmap pixmap;
    QIcon icon(str);
    pixmap = icon.pixmap(QSize(HEAD_BIG_SIZE, HEAD_BIG_SIZE));
    m_labelHead->setPixmap(pixmap);

    QString  name = QString(tr("%1\n%2")).arg(m_flockInfor.m_flockName,
                                              m_flockInfor.m_theme);
    m_labelInformation->setText(name);
}


/*************************************************
Function Name： setChatInformation()
Description:  设置群信息
*************************************************/
void IMFlockChatWidget::setChatInformation(const FlockInformation & flock)
{
    m_flockInfor.m_flockName = flock.m_flockName;
    m_flockInfor.m_theme = flock.m_theme;
    setLabelStatus();
}

/*************************************************
Function Name： setFlockMemberRemark()
Description:  设置群成员名片
*************************************************/
void IMFlockChatWidget::setFlockMemberRemark(const TempStrings & tmpStr)
{
    if (m_flockMemberMap.contains(tmpStr.m_two))
    {
        m_flockMemberMap[tmpStr.m_two]->setRemark(tmpStr);
    }
}

/*************************************************
Function Name： addFlockMemberButton()
Description:  添加群成员按钮
*************************************************/
bool IMFlockChatWidget::addFlockMemberButton(const FlockMember & memInfo)
{
//    qDebug() << "add flock member button:" << memInfo.m_userID;
    if (0 != m_flockInfor.m_flockID.compare(memInfo.m_flockID))
        return false;
    if (m_flockMemberMap.contains(memInfo.m_userID))
        return false;

    IMFlockMemberButton *button = new IMFlockMemberButton(memInfo, this,
                                                          m_mainWidget, this);
//    button->setAutoRaise(true);

    m_flockMemberMap.insert(memInfo.m_userID, button);
    m_memberListWidget->addItem(button);

    return true;
}

/*************************************************
Function Name： removeFlockMemberButton()
Description:  删除成员按钮
*************************************************/
bool IMFlockChatWidget::removeFlockMemberButton(const QString & memberID)
{
    if (!m_flockMemberMap.contains(memberID))
        return false;
    m_flockMemberMap[memberID]->deleteLater();
    m_flockMemberMap.remove(memberID);
//    m_memberListWidget->addItem(button);
}

// public slots:--------------------------------------------------------------

/*************************************************
Function Name： setFlockMemberList()
Description:  设置群成员列表
*************************************************/
void IMFlockChatWidget::setFlockMemberList(const QVector<FlockMember> & memberList)
{
    int len = memberList.size();
    if (len <= 0) return;
    if (memberList[0].m_flockID != m_flockInfor.m_flockID)
        return;

    qDeleteAll(m_flockMemberMap.begin(), m_flockMemberMap.end());
    m_flockMemberMap.clear();

    for(int i=0; i<len; i++)
    {
        addFlockMemberButton(memberList[i]);
    }

    while(m_messagesVec.size() > 0)
    {
        appendMessageShow( m_messagesVec.front());
        m_messagesVec.pop_front();
    }
}

// protected:--------------------------------------------------------------

/*************************************************
Function Name： closeEvent()
Description:  重载关闭事件
*************************************************/
void IMFlockChatWidget::closeEvent(QCloseEvent *event)
{
    qDebug() << "flock close:" << m_flockInfor.m_flockID;

    //向主界面发送退出信号
    emit roomQuitSignal();

    saveHistoryMessage();

    event->accept();
}



// private slots:-----------------------------------------------------
/*************************************************
Function Name： setInputTextFont()
Description:  字体样式
*************************************************/
void IMFlockChatWidget::setInputTextFont(const QFont &font)
{
    m_textInput->setCurrentFont(font);
    m_textInput->setFocus();
}

/*************************************************
Function Name： setInputTextSize()
Description:  字体大小
*************************************************/
void IMFlockChatWidget::setInputTextSize(const QString &size)
{
    m_textInput->setFontPointSize(size.toDouble());
    m_textInput->setFocus();
}


/*************************************************
Function Name： onClickBtnBold()
Description:  加粗
*************************************************/
void IMFlockChatWidget::onClickBtnBold(bool checked)
{
    if(checked)
        m_textInput->setFontWeight(QFont::Bold);
    else
        m_textInput->setFontWeight(QFont::Normal);
    m_textInput->setFocus();
}

/*************************************************
Function Name： onClickBtnItalic()
Description:  斜体
*************************************************/
void IMFlockChatWidget::onClickBtnItalic(bool checked)
{
    m_textInput->setFontItalic(checked);
    m_textInput->setFocus();
}


/*************************************************
Function Name： onClickBtnUnderline()
Description:  下划线
*************************************************/
void IMFlockChatWidget::onClickBtnUnderline(bool checked)
{
    m_textInput->setFontUnderline(checked);
    m_textInput->setFocus();
}

/*************************************************
Function Name： onClickBtnColor()
Description:  颜色
*************************************************/
void IMFlockChatWidget::onClickBtnColor()
{
    QColor color = QColorDialog::getColor(color,this);
    if(color.isValid())
    {
        m_textInput->setTextColor(color);
        m_textInput->setFocus();

        //    //设置字体的颜色，并将其写入文件
        //		saveFile.color = colorDialog->currentColor();
        //		saveFontColor();
    }

}

/*************************************************
Function Name： onClickBtnClear()
Description:  清空
*************************************************/
void IMFlockChatWidget::onClickBtnClear()
{
    saveHistoryMessage();
    m_tbMessageShow->clear();
}


/*************************************************
Function Name： onClickBtnHistory()
Description:  聊天历史记录
*************************************************/
void IMFlockChatWidget::onClickBtnHistory(bool checked)
{
    if (checked)
    {
        m_labelDockWidget->setText(tr("消息记录"));
        readHistoryMessage();
    }
    else
        m_labelDockWidget->setText(tr("群成员列表"));
    m_memberListWidget->setHidden(checked);
    m_tbHistoryShow->setHidden(!checked);
}

/*************************************************
Function Name： currentFormatChanged()
Description:  部件状态
*************************************************/
void IMFlockChatWidget::currentFormatChanged(const QTextCharFormat &format)
{//当编辑器的字体格式改变时，我们让部件状态也随之改变
    m_cbFont->setCurrentFont(format.font());

    if(format.fontPointSize()<9)  //如果字体大小出错，因为我们最小的字体为9
        m_cbSize->setCurrentIndex(3); //即显示12
    else m_cbSize->setCurrentIndex(
            m_cbSize->findText(QString::number(format.fontPointSize())));

    m_toolBtnBold->setChecked(format.font().bold());
    m_toolBtnItalic->setChecked(format.font().italic());
    m_toolBtnUnderline->setChecked(format.font().underline());
//    color = format.foreground().color();
}

/*************************************************
Function Name： onClickBtnClocse()
Description:  点击“关闭”按钮
*************************************************/
void IMFlockChatWidget::onClickBtnClose()
{
    this->close();
}


/*************************************************
Function Name： onClickBtnSend()
Description:  点击“发送”按钮
*************************************************/
void IMFlockChatWidget::onClickBtnSend()
{
    if (m_textInput->toPlainText().isEmpty())
        return;
    // 获取信息输入框的信息，并且更新信息输入框
    QString sendString = m_textInput->toHtml();
    m_textInput->clear();
    QString dateTime = IMTcpSocket::getCurrentDateTime();
    QString temp = QString("<font size=\"FONT_SIEZE\" color=green>%1    %2: </font>%3")
        .arg("我").arg(dateTime).arg(sendString);
    m_tbMessageShow->append(temp);

    m_mes.m_text = sendString;
    m_mes.m_type = TALK_FLOCK;
    m_mes.m_receiverID = m_flockInfor.m_flockID;
//    m_mes.m_senderID = m_chatInfor.m_;
//    m_mes.m_senderIP = IMTcpSocket::getIP();

    emit sendMessagesFromChat(m_mes);
}


// mark private:--------------------------------------------------


/*************************************************
Function Name： initIMFlockChatWidget()
Description:  初始化主界面
*************************************************/
void IMFlockChatWidget::initIMFlockChatWidget()
{
    setWidgetToolBtn();

    /*********好友信息以及交互工具栏**************/
    QHBoxLayout *hLayoutInformation = new QHBoxLayout;

    m_labelHead = new IMClickLabel;
    m_labelInformation = new QLabel();

    hLayoutInformation->addWidget(m_labelHead);
    hLayoutInformation->addWidget(m_labelInformation);
    hLayoutInformation->addStretch();

    /*********输入编辑框工具栏**************/
    QHBoxLayout *hLayoutInputTool = new QHBoxLayout;

    hLayoutInputTool->addWidget(m_cbFont);
    hLayoutInputTool->addWidget(m_cbSize);
    hLayoutInputTool->addStretch();

    hLayoutInputTool->addWidget(m_toolBtnBold);
    hLayoutInputTool->addWidget(m_toolBtnItalic);
    hLayoutInputTool->addWidget(m_toolBtnUnderline);
    hLayoutInputTool->addWidget(m_toolBtnColor);
    hLayoutInputTool->addWidget(m_toolBtnClear);
    hLayoutInputTool->addWidget(m_toolBtnHistory);


    /*********底部按钮**************/
    QHBoxLayout *hLayoutBtm = new QHBoxLayout;
    m_btnClose = new QPushButton(tr("关闭"));
    m_btnSend = new QPushButton(tr("发送"));
    m_btnSend->setDefault(true);
    hLayoutBtm->addStretch();
    hLayoutBtm->addWidget(m_btnClose);
    hLayoutBtm->addWidget(m_btnSend);

    /******************左侧布局**********************/
    m_tbMessageShow = new QTextBrowser;
    m_tbMessageShow->setMinimumSize(400, 280);
    m_textInput = new IMInputTextEdit;
    m_textInput->setMinimumWidth(100);
    m_textInput->setMaximumHeight(170);
    QVBoxLayout *vLayoutLeft = new QVBoxLayout;
    vLayoutLeft->addWidget(m_tbMessageShow);
    vLayoutLeft->addLayout(hLayoutInputTool);
    vLayoutLeft->addWidget(m_textInput);
    vLayoutLeft->addLayout(hLayoutBtm);

    /******************中间整体布局**********************/
    QHBoxLayout *hLayoutMid = new QHBoxLayout;

    m_dockWidget = new QWidget(this);
    m_dockWidget->setFixedWidth(250);

    m_tbHistoryShow = new QTextBrowser(m_dockWidget);
    m_labelDockWidget = new QLabel(m_dockWidget);
    m_labelDockWidget->setText(tr("群成员列表"));
    m_memberListWidget = new IMFlockMemberListWidget(m_dockWidget);
    QVBoxLayout *vLayoutHistory = new QVBoxLayout;
    vLayoutHistory->addWidget(m_labelDockWidget);
    vLayoutHistory->addWidget(m_tbHistoryShow);
    vLayoutHistory->addWidget(m_memberListWidget);
    m_tbHistoryShow->hide();
    vLayoutHistory->setContentsMargins(0,0,0,0);
    m_dockWidget->setLayout(vLayoutHistory);

    hLayoutMid->addLayout(vLayoutLeft);
    hLayoutMid->addWidget(m_dockWidget);

    /***********************整体布局**************************/


    QVBoxLayout *vLayoutMain = new QVBoxLayout(this);
    vLayoutMain->addLayout(hLayoutInformation);
    vLayoutMain->addLayout(hLayoutMid);
    setLayout(vLayoutMain);

    m_textInput->setFocus();
}



/*************************************************
Function Name： linkSignalWithSlot()
Description:  连接信号与槽
*************************************************/
void IMFlockChatWidget::linkSignalWithSlot()
{
    connect(m_textInput, SIGNAL(sendMessage()),
            this, SLOT(onClickBtnSend()));
    connect(m_btnSend, SIGNAL(clicked()),
            this, SLOT(onClickBtnSend()));
    connect(m_btnClose, SIGNAL(clicked()),
            this, SLOT(onClickBtnClose()));


    connect(m_cbFont, SIGNAL(currentFontChanged(QFont)),
            this, SLOT(setInputTextFont(QFont)));
    connect(m_cbSize, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(setInputTextSize(QString)));
    connect(m_toolBtnBold, SIGNAL(clicked(bool)),
            this, SLOT(onClickBtnBold(bool)));
    connect(m_toolBtnItalic, SIGNAL(clicked(bool)),
            this, SLOT(onClickBtnItalic(bool)));
    connect(m_toolBtnUnderline, SIGNAL(clicked(bool)),
            this, SLOT(onClickBtnUnderline(bool)));

    connect(m_toolBtnColor, SIGNAL(clicked()),
            this, SLOT(onClickBtnColor()));
    connect(m_toolBtnClear, SIGNAL(clicked()),
            this, SLOT(onClickBtnClear()));

    connect(m_toolBtnHistory, SIGNAL(clicked(bool)),
            this, SLOT(onClickBtnHistory(bool)));

//    connect(m_toolBtnHistory, SIGNAL(toggled(bool)),
//            m_dockWidget, SLOT(setVisible(bool)));

    connect(m_textInput, SIGNAL(currentCharFormatChanged(QTextCharFormat)),
            this, SLOT(currentFormatChanged(QTextCharFormat)));

}

/*************************************************
Function Name： setWidgetToolBtn()
Description:  设置面板图标
*************************************************/
void IMFlockChatWidget::setWidgetToolBtn()
{
    m_cbFont = new QFontComboBox;
    m_cbFont->setToolTip(tr("字体"));
    m_cbFont->setStatusTip(tr("设置字体"));
    m_cbSize = new QComboBox;
    m_cbSize->setToolTip(tr("大小"));
    m_cbSize->setStatusTip(tr("设置字体大小"));
    for (int i=9;  i<=22; ++i)
    {
        m_cbSize->addItem(QString::number(i));
    }
    m_cbSize->setCurrentIndex(0);

    m_cbSize->setMaxVisibleItems(10);
    m_cbFont->setMaxVisibleItems(10);

    m_toolBtnBold = new QToolButton;
    m_toolBtnBold->setCheckable(true);
    m_toolBtnBold->setIcon(QIcon(":/images/font_bold.png"));
    m_toolBtnBold->setAutoRaise(true);
    m_toolBtnBold->setIconSize(QSize(CHAT_WIDGET_TOOL_SMALL_SIZE,CHAT_WIDGET_TOOL_SMALL_SIZE));
    m_toolBtnBold->setToolTip(tr("加粗"));
    m_toolBtnBold->setStatusTip(tr("是否加粗"));

    m_toolBtnItalic = new QToolButton;
    m_toolBtnItalic->setCheckable(true);
    m_toolBtnItalic->setIcon(QIcon(":/images/font_italic.png"));
    m_toolBtnItalic->setAutoRaise(true);
    m_toolBtnItalic->setIconSize(QSize(CHAT_WIDGET_TOOL_SMALL_SIZE,CHAT_WIDGET_TOOL_SMALL_SIZE));
    m_toolBtnItalic->setToolTip(tr("倾斜"));
    m_toolBtnItalic->setStatusTip(tr("是否倾斜"));

    m_toolBtnUnderline = new QToolButton;
    m_toolBtnUnderline->setCheckable(true);
    m_toolBtnUnderline->setIcon(QIcon(":/images/font_underline.png"));
    m_toolBtnUnderline->setAutoRaise(true);
    m_toolBtnUnderline->setIconSize(QSize(CHAT_WIDGET_TOOL_SMALL_SIZE,CHAT_WIDGET_TOOL_SMALL_SIZE));
    m_toolBtnUnderline->setToolTip(tr("下划线"));
    m_toolBtnUnderline->setStatusTip(tr("是否添加下划线"));

    m_toolBtnColor = new QToolButton;
    m_toolBtnColor->setIcon(QIcon(":/images/colour.png"));
    m_toolBtnColor->setAutoRaise(true);
    m_toolBtnColor->setIconSize(QSize(CHAT_WIDGET_TOOL_SMALL_SIZE,CHAT_WIDGET_TOOL_SMALL_SIZE));
    m_toolBtnColor->setToolTip(tr("颜色"));
    m_toolBtnColor->setStatusTip(tr("设置颜色"));

    m_toolBtnClear = new QToolButton;
    m_toolBtnClear->setIcon(QIcon(":/images/clear.png"));
    m_toolBtnClear->setAutoRaise(true);
    m_toolBtnClear->setIconSize(QSize(CHAT_WIDGET_TOOL_SMALL_SIZE,CHAT_WIDGET_TOOL_SMALL_SIZE));
    m_toolBtnClear->setToolTip(tr("清空"));
    m_toolBtnClear->setStatusTip(tr("清空消息显示"));

    m_toolBtnHistory = new QToolButton;
    m_toolBtnHistory->setIcon(QIcon(":/images/message.png"));
    m_toolBtnHistory->setAutoRaise(true);
    m_toolBtnHistory->setCheckable(true);
    m_toolBtnHistory->setIconSize(QSize(CHAT_WIDGET_TOOL_SMALL_SIZE,CHAT_WIDGET_TOOL_SMALL_SIZE));
    m_toolBtnHistory->setToolTip(tr("消息记录"));
    m_toolBtnHistory->setStatusTip(tr("打开消息记录"));
}

/*************************************************
Function Name： saveHistoryMessage()
Description:  保存历史记录
*************************************************/
void IMFlockChatWidget::saveHistoryMessage()
{
    QString filePath = LOCAL_HISTORY_MESSAGE_PATH;
    filePath.append(m_mainWidget->getLocalMyInformation().m_userID);
    QString fileName = QString("%1_%2_flock.imres")
            .arg(m_mainWidget->getLocalMyInformation().m_userID,
                 m_flockInfor.m_flockID);

    IMClientFileCtrl::saveTalkHistory(filePath, fileName, m_tbMessageShow);
}

/*************************************************
Function Name： readHistoryMessage()
Description:  读取历史记录
*************************************************/
void IMFlockChatWidget::readHistoryMessage()
{
    QString filePath = LOCAL_HISTORY_MESSAGE_PATH;
    filePath.append(m_mainWidget->getLocalMyInformation().m_userID);
    QString fileName = QString("%1_%2_flock.imres")
            .arg(m_mainWidget->getLocalMyInformation().m_userID,
                 m_flockInfor.m_flockID);

    IMClientFileCtrl::readTalkHistory(filePath, fileName, m_tbHistoryShow);

//    tbHistory->verticalScrollBar()->setValue(
//                tbHistory->verticalScrollBar()->maximum());
}

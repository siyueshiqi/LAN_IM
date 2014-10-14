/*********************************************
File Name： IMChatWidget.h
Author： jet.F.R
Date： 2014.3.26
Description： 用于控制聊天界面的类
Changes：
********************************************/

#include "IMChatWidget.h"
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
//#include "H264CameraWidget.h"
#include "IMInputTextEdit.h"
//#include "ShowVideoWidget.h"
#include "view/IMClickLabel.h"
#include <QCloseEvent>
#include <QColorDialog>
#include <QTextCharFormat>
#include <QFileDialog>
#include "IMFileSenderWidget.h"
#include "IMFileReceiverWidget.h"
#include "control/IMClientFileCtrl.h"
// mark public:--------------------------------------------------------------

IMChatWidget::IMChatWidget(const ChatInformation &chatInf, QWidget *parent) :
    QWidget(parent)
{
    m_chatInfor = chatInf;
    m_fileSender = new IMFileSenderWidget();
//    m_fileSender->hide();
    initIMChatWidget();
    setLabelStatus();
    linkSignalWithSlot();
    setWindowTitle(tr("IM好友聊天窗口"));
}

//IMChatWidget::IMChatWidget(const QString &id, QWidget *parent) :
//    QWidget(parent)
//{
//    //m_chatInfor.m_friendID = id;
//    initIMMainWidget();
//    linkSignalWithSlot();
//    qDebug() << "fuck";
//}

IMChatWidget::~IMChatWidget()
{
    if (m_fileSender != NULL)
    {
        m_fileSender->close();
        m_fileSender->deleteLater();
        m_fileSender = NULL;
    }
}

/*************************************************
Function Name： appendMessageShow()
Description:  添加好友发来的信息
*************************************************/
void IMChatWidget::appendMessageShow(const TalkMessage &mes)
{
    QString  name;
    if(m_chatInfor.m_friendRemark.isEmpty())
        name = m_chatInfor.m_friendNickname;
    else
        name = m_chatInfor.m_friendRemark;

    //将（收到的）信息显示在输出栏
//    QString dateTime = IMTcpSocket::getCurrentDateTime();
    QString temp = QString("<font size=\"FONT_SIEZE\" color=blue>%1    %2: </font>%3")
        .arg(name).arg(mes.m_dateTime.toString("yyyy-MM-dd hh:mm:ss")).arg(mes.m_text);
    m_tbMessageShow->append(temp);
}


/*************************************************
Function Name： pendingFile()
Description:  有接收文件请求需要处理
*************************************************/
void IMChatWidget::pendingFile(const TalkMessage &mes)
{
    int btn = QMessageBox::information(this,tr("接受文件"),
                                       tr("来自%1(%2)的文件:\n%3\n是否接收？").
                                       arg(mes.m_senderID).
                                       arg(mes.m_senderIP).
                                       arg(mes.m_text),
                                       QMessageBox::Yes,QMessageBox::No);
    if(btn == QMessageBox::Yes)
    {
        QString name = QFileDialog::getSaveFileName(0,tr("保存文件"),mes.m_text);
        if(!name.isEmpty())
        {
                IMFileReceiverWidget *receiver = new IMFileReceiverWidget();
                receiver->setFileName(name);
                receiver->connectToHost(QHostAddress(mes.m_senderIP));
                receiver->move(500,200);
                receiver->show();
        }

    }
    else
    {
        m_mes.m_type = REFUSE_FILE;
        m_mes.m_receiverID = mes.m_senderID;
        m_mes.m_receiverIP = mes.m_senderIP;
        emit sendMessagesFromChat(m_mes);
    }
}


/*************************************************
Function Name： refusedSendFile()
Description:  拒绝文件
*************************************************/
void IMChatWidget::refusedSendFile()
{
    if (m_fileSender != NULL)
        m_fileSender->showRefused();
}

/*************************************************
Function Name： pendingVideo()
Description:  有接收视频请求需要处理
*************************************************/
void IMChatWidget::pendingVideo(const TalkMessage &mes)
{
//    qDebug() << "video-receiveIP:" << mes.m_receiverIP
//             << "sendIP: " << mes.m_senderIP;
//    if(mes.m_receiverIP != IMTcpSocket::getIP())
//    {
//        return;
//    }

    int btn = QMessageBox::information(this,tr("视频请求"),
                                       tr("来自%1(%2)的视频请求，是否接受？")
                                       .arg(m_chatInfor.m_friendNickname)
                                       .arg(mes.m_senderID),
                                       QMessageBox::Yes,QMessageBox::No);
    if(btn == QMessageBox::Yes)
    {
        m_toolBtnVideo->setEnabled(false);
        m_mes.m_type = AGREE_VOICE;
        m_mes.m_receiverID = mes.m_senderID;
        m_mes.m_receiverIP = mes.m_senderIP;
        m_mes.m_text = "port";

        qDebug() << "创建视频窗口";
        showCamera(mes);

        // 发送视频 接收视频
//            QString name = QFileDialog::getSaveFileName(0,tr("保存文件"),fileName);
//            if(!name.isEmpty())
//            {
//                fileReceiver *receiver = new fileReceiver(this);
//                receiver->setFileName(name);
//                receiver->setHostAddress(QHostAddress(serverAddress));
//                receiver->move(500,200);
//                receiver->show();
//            }
    }
    else
    {
        m_mes.m_type = REFUSE_VIDEO;
        m_mes.m_receiverID = mes.m_senderID;
        m_mes.m_receiverIP = mes.m_senderIP;
    //    m_mes.m_senderID = m_chatInfor.m_;
    //    m_mes.m_senderIP = IMTcpSocket::getIP();
    }
    emit sendMessagesFromChat(m_mes);
}

/*************************************************
Function Name： initIMMainWidget()
Description:  显示视频窗口
*************************************************/
void IMChatWidget::showVideoWidget(const TalkMessage &mes)
{
    qDebug() << "show video widget.";
}


/*************************************************
Function Name： showCamera()
Description:  显示采集视频窗口
*************************************************/
void IMChatWidget::showCamera(const TalkMessage &mes)
{
//    qDebug() << "port:" << mes.m_text.toInt()
//             << "IP" << mes.m_senderIP.toStdString().data();

//    m_camera = new H264CameraWidget(mes.m_text.toInt(),
//                                    mes.m_senderIP.toStdString().data());
//    m_camera->show();
//    m_camera->startCapture();
}


/*************************************************
Function Name： closeVideoWidget()
Description:  关闭视频窗口
*************************************************/
void IMChatWidget::closeVideoWidget()
{
}

/*************************************************
Function Name： setChatWidgetStatus()
Description:  设置聊天窗口显示信息
*************************************************/
void IMChatWidget::setLabelStatus()
{
    QString str = QString("resource/image/head/%1.bmp").
        arg(QString::number(m_chatInfor.m_headPortrait));

    QString  name;
    if(m_chatInfor.m_friendRemark.isEmpty())
        name = m_chatInfor.m_friendNickname;
    else
        name = m_chatInfor.m_friendRemark;

    QPixmap pixmap;
    QIcon icon(str);
    pixmap = icon.pixmap(QSize(HEAD_BIG_SIZE, HEAD_BIG_SIZE));
    m_labelHead->setPixmap(pixmap);
    m_labelName->setText(name);
    m_labelMark->setText(m_chatInfor.m_friendMark);

}

/*************************************************
Function Name： setChatInformation()
Description:  设置对方信息
*************************************************/
void IMChatWidget::setChatInformation(const ChatInformation & chatInfo)
{
    if (chatInfo.m_friendID != m_chatInfor.m_friendID)
        return;
    m_chatInfor.m_headPortrait = m_chatInfor.m_headPortrait;
    m_chatInfor.m_friendNickname = m_chatInfor.m_friendNickname;
    m_chatInfor.m_friendRemark = m_chatInfor.m_friendRemark;
    m_chatInfor.m_friendMark = m_chatInfor.m_friendMark;
    m_chatInfor.m_friendIP = m_chatInfor.m_friendIP;
    m_chatInfor.m_friendStatus = m_chatInfor.m_friendStatus;
}

/*************************************************
Function Name： setFriendIP()
Description:  设置对方ip
*************************************************/
void IMChatWidget::setFriendIP(const QString & ip)
{
    m_chatInfor.m_friendIP = ip;
    m_labelFriendIP->setText(QString(tr("好友IP: %1")).arg(ip));

}

/*************************************************
Function Name： closeEvent()
Description:  重载关闭事件
*************************************************/
void IMChatWidget::closeEvent(QCloseEvent *event)
{
    if (m_fileSender != 0)
    {
        if (!m_fileSender->isStopped())
        {
            QString temp = tr("文件还在发送中，您确定想要关闭聊天窗口？");
            QMessageBox::StandardButton rb;
            rb = QMessageBox::question(this, tr("关闭聊天"), temp,
                QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
            if(rb == QMessageBox::No)
            {
                event->ignore();
                return;
            }
        }
    }

    //向主界面发送退出信号
    emit roomQuitSignal();
    saveHistoryMessage();

    event->accept();
}

// mark private:--------------------------------------------------


/*************************************************
Function Name： initIMChatWidget()
Description:  初始化主界面
*************************************************/
void IMChatWidget::initIMChatWidget()
{
    setWidgetToolBtn();

    /*********好友信息以及交互工具栏**************/
    QHBoxLayout *hLayoutFriend = new QHBoxLayout;
    QVBoxLayout *vLayoutFriend = new QVBoxLayout;
    QVBoxLayout *vLayoutFriendInfo = new QVBoxLayout;
    QHBoxLayout *hLayoutFriendInter = new QHBoxLayout;

//    m_pmHeadPortrait = new QPixmap;
//    m_frameHeadPortrait = new QFrame;
    m_labelHead = new IMClickLabel;
    m_labelName = new QLabel();
    m_labelMark = new QLabel();

    vLayoutFriendInfo->addWidget(m_labelName);
    vLayoutFriendInfo->addWidget(m_labelMark);

    hLayoutFriendInter->addWidget(m_toolBtnVideo);
    hLayoutFriendInter->addWidget(m_toolBtnVoice);
    hLayoutFriendInter->addWidget(m_toolBtnFile);
    hLayoutFriendInter->addWidget(m_toolBtnSpace);
    hLayoutFriendInter->addStretch();

    hLayoutFriend->addWidget(m_labelHead);
    hLayoutFriend->addLayout(vLayoutFriendInfo);
    hLayoutFriend->addStretch();
//    vLayoutFriend->addLayout(hLayoutFriendInter);

//    hLayoutFriend->addWidget(m_frameHeadPortrait);
//    hLayoutFriend->addWidget(m_labelHead);
    vLayoutFriend->addLayout(hLayoutFriend);
    vLayoutFriend->addLayout(hLayoutFriendInter);
//    vLayoutFriend->addStretch();

    /*********输入编辑框工具栏**************/
    QHBoxLayout *hLayoutInputTool = new QHBoxLayout;

//    hLayoutInputTool->addWidget(m_toolBtnFont);
    hLayoutInputTool->addWidget(m_cbFont);
    hLayoutInputTool->addWidget(m_cbSize);
    hLayoutInputTool->addStretch();

    hLayoutInputTool->addWidget(m_toolBtnBold);
    hLayoutInputTool->addWidget(m_toolBtnItalic);
    hLayoutInputTool->addWidget(m_toolBtnUnderline);
    hLayoutInputTool->addWidget(m_toolBtnColor);
    hLayoutInputTool->addWidget(m_toolBtnClear);
    hLayoutInputTool->addWidget(m_toolBtnHistory);


    /*********底部ip显示以及按钮**************/
    QHBoxLayout *hLayoutBtm = new QHBoxLayout;
    m_labelFriendIP = new QLabel(tr("ip"));
    m_btnClose = new QPushButton(tr("关闭"));
    m_btnSend = new QPushButton(tr("发送"));
    m_btnSend->setDefault(true);
//    m_btnSend->setFocus();
    hLayoutBtm->addWidget(m_labelFriendIP);
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
    //vLayoutLeft->addLayout(hLayoutFriend);
    vLayoutLeft->addWidget(m_tbMessageShow);
    vLayoutLeft->addLayout(hLayoutInputTool);
    vLayoutLeft->addWidget(m_textInput);
    vLayoutLeft->addLayout(hLayoutBtm);

    /******************中间整体布局**********************/
    QHBoxLayout *hLayoutMid = new QHBoxLayout;


//    m_tbHistoryShow->setFixedWidth(300);
    m_dockHistoty = new QWidget;
    m_dockHistoty->hide();//setHidden(true);
    m_dockHistoty->setFixedWidth(250);
    m_tbHistoryShow = new QTextBrowser(m_dockHistoty);
    QLabel *lableHistory = new QLabel(tr("消息记录"));
    QVBoxLayout *vLayoutHistory = new QVBoxLayout;
    vLayoutHistory->addWidget(lableHistory);
    vLayoutHistory->addWidget(m_tbHistoryShow);
    vLayoutHistory->setContentsMargins(0,0,0,0);
    m_dockHistoty->setLayout(vLayoutHistory);
//    m_dockHistoty->setFeatures(QDockWidget::DockWidgetMovable
//                               | QDockWidget::DockWidgetFloatable
//                               | QDockWidget::DockWidgetClosable);
//    m_dockHistoty->setFeatures(QDockWidget::DockWidgetClosable);
//    m_dockHistoty->setAllowedAreas(Qt::RightDockWidgetArea);
//    m_dockHistoty->setWidget(m_tbHistoryShow);
//    this->addDockWidget(Qt::LeftDockWidgetArea,dock);
    //去除标题栏
//    QWidget* lTitleBar = m_dockHistoty->titleBarWidget();
//    QWidget* lEmptyWidget = new QWidget();
//    m_dockHistoty->setTitleBarWidget(lEmptyWidget);
//    delete lTitleBar;
    //end


    /*
    QDockWidget *dock = new QDockWidget(tr("DockWindow 1"),this);
    dock->setFeatures(QDockWidget::DockWidgetMovable);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    QTextEdit *title1 = new QTextEdit();
    title1->setText("Window 1");
    dock->setWidget(title1);
    this->addDockWidget(Qt::LeftDockWidgetArea,dock);
    */
    hLayoutMid->addLayout(vLayoutLeft);
    hLayoutMid->addWidget(m_dockHistoty);

    /***********************整体布局**************************/


    QVBoxLayout *vLayoutMain = new QVBoxLayout(this);

//    vLayoutMain->setSizeConstraint(QLayout::SetFixedSize);
    vLayoutMain->addLayout(vLayoutFriend);
    vLayoutMain->addLayout(hLayoutMid);
//    hLayoutMain->addWidget(m_tbHistoryShow);
//    hLayoutMain->addWidget(m_dockHistoty);
    setLayout(vLayoutMain);

//    setCentralWidget();
    m_textInput->setFocus();
}



/*************************************************
Function Name： linkSignalWithSlot()
Description:  连接信号与槽
*************************************************/
void IMChatWidget::linkSignalWithSlot()
{
    connect(m_textInput, SIGNAL(sendMessage()),
            this, SLOT(onClickBtnSend()));
    connect(m_btnSend, SIGNAL(clicked()),
            this, SLOT(onClickBtnSend()));
    connect(m_btnClose, SIGNAL(clicked()),
            this, SLOT(onClickBtnClose()));

    connect(m_toolBtnVideo, SIGNAL(clicked()),
            this, SLOT(onClickBtnVideo()));
    connect(m_toolBtnVoice, SIGNAL(clicked()),
            this, SLOT(onClickBtnVoice()));
    connect(m_toolBtnFile, SIGNAL(clicked()),
            this, SLOT(onClickBtnFile()));
    connect(m_toolBtnSpace, SIGNAL(clicked()),
            this, SLOT(onClickBtnSpace()));

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
//            m_dockHistoty, SLOT(setVisible(bool)));

    connect(m_textInput, SIGNAL(currentCharFormatChanged(QTextCharFormat)),
            this, SLOT(currentFormatChanged(QTextCharFormat)));

}

/*************************************************
Function Name： setWidgetToolBtn()
Description:  设置面板图标
*************************************************/
void IMChatWidget::setWidgetToolBtn()
{
    m_toolBtnVideo = new QToolButton;
//    m_toolBtnVideo->setStyleSheet("QToolButton { background-color: red; border: none; }");
//    m_toolBtnVideo->setStyleSheet("QToolButton { image:url(:/images/camera.png); border: none; width: CHAT_WIDGET_TOOL_SIZEpx; height: CHAT_WIDGET_TOOL_SIZEpx;}");
    m_toolBtnVideo->setIcon(QIcon(":/images/camera.png"));
    m_toolBtnVideo->setAutoRaise(true);
    m_toolBtnVideo->setToolTip(tr("视频"));
    m_toolBtnVideo->setStatusTip(tr("打开视频"));
//    m_toolBtnVideo->setAutoFillBackground(true);

//    m_toolBtnVideo->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_toolBtnVideo->setIconSize(QSize(CHAT_WIDGET_TOOL_SIZE,CHAT_WIDGET_TOOL_SIZE));
    //m_toolBtnVideo->setEnabled(true);

    m_toolBtnVoice = new QToolButton;
    m_toolBtnVoice->setIcon(QIcon(":/images/microphone.png"));
    m_toolBtnVoice->setAutoRaise(true);
    m_toolBtnVoice->setToolTip(tr("语音"));
    m_toolBtnVoice->setStatusTip(tr("打开语音"));
    m_toolBtnVoice->setIconSize(QSize(CHAT_WIDGET_TOOL_SIZE,CHAT_WIDGET_TOOL_SIZE));
//    connect(m_toolBtnVoice, SIGNAL(clicked()),
//            this, SLOT(onClickBtnVoice()));

    m_toolBtnFile = new QToolButton;
    m_toolBtnFile->setIcon(QIcon(":/images/send_file.png"));
    m_toolBtnFile->setAutoRaise(true);
    m_toolBtnFile->setToolTip(tr("发送文件"));
    m_toolBtnFile->setStatusTip(tr("发送文件"));
    m_toolBtnFile->setIconSize(QSize(CHAT_WIDGET_TOOL_SIZE,CHAT_WIDGET_TOOL_SIZE));

    m_toolBtnSpace = new QToolButton;
    m_toolBtnSpace->setIcon(QIcon(":/images/space.png"));
    m_toolBtnSpace->setAutoRaise(true);
    m_toolBtnSpace->setToolTip(tr("空间"));
    m_toolBtnSpace->setStatusTip(tr("打开空间"));
    m_toolBtnSpace->setIconSize(QSize(CHAT_WIDGET_TOOL_SIZE,CHAT_WIDGET_TOOL_SIZE));
//---------------------------------------------------------------------------
//    m_toolBtnFont = new QToolButton;
//    m_toolBtnFont->setIcon(QIcon(":/images/font.png"));
//    m_toolBtnFont->setAutoRaise(true);
//    m_toolBtnFont->setIconSize(QSize(CHAT_WIDGET_TOOL_SMALL_SIZE,CHAT_WIDGET_TOOL_SMALL_SIZE));

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
void IMChatWidget::saveHistoryMessage()
{
    QString filePath = LOCAL_HISTORY_MESSAGE_PATH;
    filePath.append(m_chatInfor.m_myID);
    QString fileName = QString("%1_%2_friend.imres")
            .arg(m_chatInfor.m_myID, m_chatInfor.m_friendID);

    IMClientFileCtrl::saveTalkHistory(filePath, fileName, m_tbMessageShow);
}

/*************************************************
Function Name： readHistoryMessage()
Description:  读取历史记录
*************************************************/
void IMChatWidget::readHistoryMessage()
{
    QString filePath = LOCAL_HISTORY_MESSAGE_PATH;
    filePath.append(m_chatInfor.m_myID);
    QString fileName = QString("%1_%2_friend.imres")
            .arg(m_chatInfor.m_myID, m_chatInfor.m_friendID);

    IMClientFileCtrl::readTalkHistory(filePath, fileName, m_tbHistoryShow);

//    tbHistory->verticalScrollBar()->setValue(
//                tbHistory->verticalScrollBar()->maximum());
}

// private slots:-----------------------------------------------------
/*************************************************
Function Name： onClickBtnVideo()
Description:  点击“视频”按钮
*************************************************/
void IMChatWidget::onClickBtnVideo()
{
//    m_toolBtnVideo->setEnabled(false);
//    m_mes.m_type = REQUEST_VIDEO;
//    m_mes.m_receiverID = m_chatInfor.m_friendID;
//    m_mes.m_text = "2222";
////    m_mes.m_senderID = m_chatInfor.m_;
////    m_mes.m_senderIP = IMTcpSocket::getIP();

//    qDebug() << "";
//    // show wait
//    m_videoShow = new ShowVideoWidget(2222);
//    // 聊天窗口关闭的时候 视频聊天也要关掉
//    // 最好先弹出提示，让用户选择.
//    connect(this, SIGNAL(destroyed()),
//            m_videoShow, SLOT(deleteLater()));
//    m_videoShow->show();

//    emit sendMessagesFromChat(m_mes);

}


/*************************************************
Function Name： onClickBtnVoice()
Description:  语音
*************************************************/
void IMChatWidget::onClickBtnVoice()
{
}


/*************************************************
Function Name： onClickBtnFile()
Description:  发送文件
*************************************************/
void IMChatWidget::onClickBtnFile()
{
    if (m_fileSender->isVisible())
    {
        return;
    }
    if (OFFLINE == m_chatInfor.m_friendStatus)
    {
        QMessageBox::critical(NULL, tr("发送文件"), tr("好友不在线，暂时无法发送"));
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName.isEmpty())
    {
        QMessageBox::information(this,tr("警告"),tr("请选择文件"));
        return;
    }
    m_fileSender->initSender();
    if (!m_fileSender->startSending(fileName))
        return;
    m_fileSender->move(500, 200);
    m_fileSender->show();

    //m_toolBtnFile->setEnabled(false);
    m_mes.m_type = REQUEST_FILE;
    m_mes.m_receiverID = m_chatInfor.m_friendID;
    m_mes.m_text = fileName;

    emit sendMessagesFromChat(m_mes);
}


/*************************************************
Function Name： onClickBtnSpace()
Description:  空间
*************************************************/
void IMChatWidget::onClickBtnSpace()
{
}


/*************************************************
Function Name： setInputTextFont()
Description:  字体样式
*************************************************/
void IMChatWidget::setInputTextFont(const QFont &font)
{
    m_textInput->setCurrentFont(font);
    m_textInput->setFocus();
}

/*************************************************
Function Name： setInputTextSize()
Description:  字体大小
*************************************************/
void IMChatWidget::setInputTextSize(const QString &size)
{
    m_textInput->setFontPointSize(size.toDouble());
    m_textInput->setFocus();
}


/*************************************************
Function Name： onClickBtnBold()
Description:  加粗
*************************************************/
void IMChatWidget::onClickBtnBold(bool checked)
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
void IMChatWidget::onClickBtnItalic(bool checked)
{
    m_textInput->setFontItalic(checked);
    m_textInput->setFocus();
}


/*************************************************
Function Name： onClickBtnUnderline()
Description:  下划线
*************************************************/
void IMChatWidget::onClickBtnUnderline(bool checked)
{
    m_textInput->setFontUnderline(checked);
    m_textInput->setFocus();
}

/*************************************************
Function Name： onClickBtnColor()
Description:  颜色
*************************************************/
void IMChatWidget::onClickBtnColor()
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
void IMChatWidget::onClickBtnClear()
{
    saveHistoryMessage();
    m_tbMessageShow->clear();
}


/*************************************************
Function Name： onClickBtnHistory()
Description:  聊天历史记录
*************************************************/
void IMChatWidget::onClickBtnHistory(bool checked)
{
    m_dockHistoty->setHidden(!checked);
    if (checked)
    {
        readHistoryMessage();
    }
}

/*************************************************
Function Name： currentFormatChanged()
Description:  部件状态
*************************************************/
void IMChatWidget::currentFormatChanged(const QTextCharFormat &format)
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
void IMChatWidget::onClickBtnClose()
{
    this->close();
}


/*************************************************
Function Name： onClickBtnSend()
Description:  点击“发送”按钮
*************************************************/
void IMChatWidget::onClickBtnSend()
{
    if (m_textInput->toPlainText().isEmpty())
        return;
    // 获取信息输入框的信息，并且更新信息输入框
    QString sendString = m_textInput->toHtml();
    m_textInput->clear();
//    QString dateTime = IMTcpSocket::getCurrentDateTime();
    QDateTime dateTime = QDateTime::currentDateTime();
    QString temp = QString("<font size=\"FONT_SIEZE\" color=green>%1    %2: </font>%3")
        .arg("我").arg(dateTime.toString("yyyy-MM-dd hh:mm:ss")).arg(sendString);
    m_tbMessageShow->append(temp);

    m_mes.m_text = sendString;
    m_mes.m_type = TALK_MESSAGE;
    m_mes.m_receiverID = m_chatInfor.m_friendID;
    m_mes.m_dateTime = dateTime;
//    m_mes.m_senderID = m_chatInfor.m_;
//    m_mes.m_senderIP = IMTcpSocket::getIP();

    emit sendMessagesFromChat(m_mes);
}

#include "IMMailWriteWidget.h"

#include <QCloseEvent>
#include <QColorDialog>
#include <QTextCharFormat>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFontComboBox>
#include <QComboBox>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <qdebug.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QLineEdit>
#include <QTextEdit>

#include "model/IMTcpSocket.h"
#include "control/IMMailCtrl.h"



IMMailWriteWidget::IMMailWriteWidget(QString id, IMMailCtrl * ctrl, QWidget *parent) :
    m_myID(id), m_mailCtrl(ctrl), QWidget(parent)
{
    initIMMailWriteWidget();
    linkSignalWithSlot();
}

void IMMailWriteWidget::setReceiverAddress(const QString & address)
{
    m_leReceiverAddress->setText(address);
}

// private slots:-----------------------------------------------------
/*************************************************
Function Name： setInputTextFont()
Description:  字体样式
*************************************************/
void IMMailWriteWidget::setInputTextFont(const QFont &font)
{
    m_textInput->setCurrentFont(font);
    m_textInput->setFocus();
}

/*************************************************
Function Name： setInputTextSize()
Description:  字体大小
*************************************************/
void IMMailWriteWidget::setInputTextSize(const QString &size)
{
    m_textInput->setFontPointSize(size.toDouble());
    m_textInput->setFocus();
}


/*************************************************
Function Name： onClickBtnBold()
Description:  加粗
*************************************************/
void IMMailWriteWidget::onClickBtnBold(bool checked)
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
void IMMailWriteWidget::onClickBtnItalic(bool checked)
{
    m_textInput->setFontItalic(checked);
    m_textInput->setFocus();
}


/*************************************************
Function Name： onClickBtnUnderline()
Description:  下划线
*************************************************/
void IMMailWriteWidget::onClickBtnUnderline(bool checked)
{
    m_textInput->setFontUnderline(checked);
    m_textInput->setFocus();
}

/*************************************************
Function Name： onClickBtnColor()
Description:  颜色
*************************************************/
void IMMailWriteWidget::onClickBtnColor()
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
Function Name： onClickBtnSend()
Description:  点击“发送”按钮
*************************************************/
void IMMailWriteWidget::onClickBtnSend()
{
    if (m_leReceiverAddress->text().isEmpty())
    {
        QMessageBox::about(NULL, tr("提示"), tr("收件人不能为空！"));
        return;
    }
    if (m_leReceiverAddress->text().compare(m_myID) == 0)
    {
        QMessageBox::about(NULL, tr("提示"), tr("不能给自己发送邮件！"));
        return;
    }
    if (m_leTheme->text().isEmpty())
    {
        QMessageBox::about(NULL, tr("提示"), tr("信件主题不能为空"));

        return;
    }
    if (m_textInput->toPlainText().isEmpty())
    {
        QMessageBox::about(NULL, tr("提示"), tr("信件内容不能为空！"));
        return;
    }

    // 获取信息输入框的信息
    getMailInformation();

    m_mailCtrl->requestSendMail(m_mail);
//    emit sendMessagesFromChat(m_mes);
}


// private:-------------------------------------------------
/*************************************************
Function Name： initIMMailWriteWidget()
Description:  初始化
*************************************************/
void IMMailWriteWidget::initIMMailWriteWidget()
{
    setWidgetToolBtn();
    // 输入编辑框工具栏
    QHBoxLayout *hLayoutInputTool = new QHBoxLayout;
    hLayoutInputTool->addWidget(m_cbFont);
    hLayoutInputTool->addWidget(m_cbSize);
    hLayoutInputTool->addWidget(m_toolBtnBold);
    hLayoutInputTool->addWidget(m_toolBtnItalic);
    hLayoutInputTool->addWidget(m_toolBtnUnderline);
    hLayoutInputTool->addWidget(m_toolBtnColor);
    hLayoutInputTool->addStretch();



    // 左侧标签部分
    QLabel *labelSender = new QLabel(tr("发件人:"), this);
    QLabel *labelReceiver = new QLabel(tr("收件人:"), this);
    QLabel *labelTheme = new QLabel(tr("主    题:"), this);
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->setAlignment(Qt::AlignRight);
    leftLayout->addWidget(labelSender);
    leftLayout->addWidget(labelReceiver);
    leftLayout->addWidget(labelTheme);

    // 右侧编辑部分
    QLabel *senderAddress = new QLabel(QString(tr("%1%2"))
                                       .arg(m_myID, MAIL_ADDRESS_FORMAT), this);
    m_leReceiverAddress = new QLineEdit(this);
    m_leReceiverAddress->setPlaceholderText(tr("请输入对方地址"));
    QLabel *labelAddressFormat = new QLabel(MAIL_ADDRESS_FORMAT);
//    m_leReceiverAddress->setText(MAIL_ADDRSS_FORMAT);
    QHBoxLayout *layoutReceiver = new QHBoxLayout;
    layoutReceiver->addWidget(m_leReceiverAddress);
    layoutReceiver->addWidget(labelAddressFormat);

    m_leTheme = new QLineEdit(this);
    m_leTheme->setPlaceholderText(tr("请输入主题"));
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(senderAddress);
    rightLayout->addLayout(layoutReceiver);
    rightLayout->addWidget(m_leTheme);

    // 顶部部分
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addLayout(leftLayout);
    topLayout->addLayout(rightLayout);
//    topLayout->setContentsMargins(0,0,0,0);

    // 底部按钮部分
    m_btnSend = new QPushButton(tr("发送"), this);
    m_btnSend->setDefault(true);
    QHBoxLayout *btmLayout = new QHBoxLayout;
    btmLayout->addStretch();
    btmLayout->addWidget(m_btnSend);

    // 总体
    m_textInput = new QTextEdit(this);
    m_textInput->setMinimumWidth(100);
//    m_textInput->setMaximumHeight(170);

    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->setContentsMargins(0, 0, 0, 0);
//    mainLayout->setSpacing(0);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(hLayoutInputTool);
    mainLayout->addWidget(m_textInput);
    mainLayout->addLayout(btmLayout);

    setLayout(mainLayout);
}

/*************************************************
Function Name： linkSignalWithSlot()
Description:  连接信号与槽
*************************************************/
void IMMailWriteWidget::linkSignalWithSlot()
{
    connect(m_btnSend, SIGNAL(clicked()),
            this, SLOT(onClickBtnSend()));
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
}


/*************************************************
Function Name： setWidgetToolBtn()
Description:  设置面板图标
*************************************************/
void IMMailWriteWidget::setWidgetToolBtn()
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
}

// 获取信息输入框的信息
/*************************************************
Function Name： setWidgetToolBtn()
Description:  设置面板图标
*************************************************/
void IMMailWriteWidget::getMailInformation()
{
    QString sendString = m_textInput->toHtml();
    //QString dateTime = IMTcpSocket::getCurrentDateTime();
    QDateTime dateTime = QDateTime::currentDateTime();

    m_mail.m_senderAddress = m_myID;
    m_mail.m_receiverAddress = m_leReceiverAddress->text();
    m_mail.m_theme = m_leTheme->text();
    m_mail.m_content = sendString;
    m_mail.m_dateTime= dateTime;
}

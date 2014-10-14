#ifndef IMDISCUSSIONCHATWIDGET_H
#define IMDISCUSSIONCHATWIDGET_H

#include <QWidget>
#include "model/IMConstant.h"
#include <QMap>

class QComboBox;
class QFontComboBox;
class IMInputTextEdit;
class QDockWidget;
class QPixmap;
class QFrame;
class QLabel;
class QPushButton;
class QToolButton;
class QTextBrowser;
class DiscussionInformation;
class IMClickLabel;
class QTextCharFormat;
class IMDiscussionMemberButton;
class IMDiscussionMemberListWidget;
class IMMainWidget;

class IMDiscussionChatWidget : public QWidget
{
    Q_OBJECT
public:
    IMDiscussionChatWidget(const DiscussionInformation & discussion,
                           IMMainWidget *,
                           QWidget *parent = 0);
    ~IMDiscussionChatWidget();

    // 添加讨论组成员发来的信息
    void appendMessageShow(const TalkMessage &mes);
    // 设置聊天窗口显示信息
    void setLabelStatus();
    // 设置讨论组信息
    void setChatInformation(const DiscussionInformation & discussion);

    // 设置成员名片
    //void setMemberRemark(const TempStrings &);

    // 获取群信息
    DiscussionInformation getDiscussionInformation() const
    {
        return m_discussionInfo;
    }

    // 添加成员按钮
    bool addDiscussionMemberButton(const DiscussionMember & memInfo);

    // 删除成员按钮
    bool removeDiscussionMemberButton(const QString & memberID);

signals:
    void sendMessagesFromChat(TalkMessage &);
    //退出信号
    void roomQuitSignal();

public slots:

    // 设置群成员列表
    void setDiscussionMemberList(const QVector<DiscussionMember> & memberList);

protected:
    //重载关闭事件
    void closeEvent(QCloseEvent *event);

private slots:
    // 字体样式
    void setInputTextFont(const QFont &font);
    // 字体大小
    void setInputTextSize(const QString & size);
    // 加粗
    void onClickBtnBold(bool checked);
    // 斜体
    void onClickBtnItalic(bool checked);
    // 下划线
    void onClickBtnUnderline(bool checked);
    // 颜色
    void onClickBtnColor();
    // 清空
    void onClickBtnClear();
    // 聊天历史记录
    void onClickBtnHistory(bool checked);
    // 当编辑器的字体格式改变时，我们让部件状态也随之改变
    void currentFormatChanged(const QTextCharFormat &format);
    // 关闭
    void onClickBtnClose();
    // 发送聊天信息
    void onClickBtnSend();

private:
    void initIMDiscussionChatWidget();
    void linkSignalWithSlot();
    void setWidgetToolBtn();
    void saveHistoryMessage();
    void readHistoryMessage();

private:
    IMClickLabel *m_labelHead;
    QLabel *m_labelInformation;      // 群名 群主题
//    QLabel *m_labelTheme;          // 群主题
    QTextBrowser *m_tbMessageShow;   // 显示聊天信息

    QFontComboBox *m_cbFont;         // 字体样式选择框
    QComboBox *m_cbSize;             // 字体大小选择框
    QToolButton *m_toolBtnBold;      // 加粗
    QToolButton *m_toolBtnItalic;    // 斜体
    QToolButton *m_toolBtnUnderline; // 下划线
    QToolButton *m_toolBtnColor;     // 颜色
    //    QToolButton *m_toolBtnExpression;// 表情---------
    //    QToolButton *m_toolBtnScreen;    // 截图---------
    QToolButton *m_toolBtnClear;     // 清空
    QToolButton *m_toolBtnHistory;   // 历史记录
    IMInputTextEdit *m_textInput;          // 信息输入框
    QPushButton *m_btnClose;            // 关闭按钮
    QPushButton *m_btnSend;             // 发送

    QWidget *m_dockWidget;
    QLabel *m_labelDockWidget;
    QTextBrowser *m_tbHistoryShow;   // 显示聊天历史记录
    IMDiscussionMemberListWidget *m_memberListWidget;
    DiscussionInformation m_discussionInfo;
    TalkMessage m_mes;

    // 成员ID 与 成员按钮 映射表
    QMap<QString, IMDiscussionMemberButton *> m_discussionMemberMap;

    IMMainWidget *m_mainWidget;

    QVector<TalkMessage> m_messagesVec;
    
};

#endif // IMDISCUSSIONCHATWIDGET_H

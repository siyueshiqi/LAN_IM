#ifndef IMFLOCKCHATWIDGET_H
#define IMFLOCKCHATWIDGET_H

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
class FlockInformation;
class IMClickLabel;
class QTextCharFormat;
class IMFlockMemberButton;
class IMFlockMemberListWidget;
class IMMainWidget;

class IMFlockChatWidget : public QWidget
{
    Q_OBJECT
public:
    IMFlockChatWidget(const FlockInformation & flock, IMMainWidget *,
                      QWidget *parent = 0);
    ~IMFlockChatWidget();
    // 添加群成员发来的信息
    void appendMessageShow(const TalkMessage &mes);
    // 设置聊天窗口显示信息
    void setLabelStatus();
    // 设置群信息
    void setChatInformation(const FlockInformation & flock);

    // 设置群成员名片
    void setFlockMemberRemark(const TempStrings &);

    // 获取群信息
    FlockInformation getFlockInformation() const
    {
        return m_flockInfor;
    }

    // 添加成员按钮
    bool addFlockMemberButton(const FlockMember &);

    // 删除成员按钮
    bool removeFlockMemberButton(const QString & memberID);

signals:
    void sendMessagesFromChat(TalkMessage &);
    //退出信号
    void roomQuitSignal();
    
public slots:

    // 设置群成员列表
    void setFlockMemberList(const QVector<FlockMember> &);

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
    void initIMFlockChatWidget();
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
    IMFlockMemberListWidget *m_memberListWidget;
    FlockInformation m_flockInfor;
    TalkMessage m_mes;

    QMap<QString, IMFlockMemberButton *> m_flockMemberMap; // 群成员ID 与 群成员按钮 映射表

    IMMainWidget *m_mainWidget;

    QVector<TalkMessage> m_messagesVec;
};

#endif // IMFLOCKCHATWIDGET_H

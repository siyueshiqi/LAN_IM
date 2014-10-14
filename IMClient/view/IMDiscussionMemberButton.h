#ifndef IMDISCUSSIONMEMBERBUTTON_H
#define IMDISCUSSIONMEMBERBUTTON_H

#include <QPushButton>
#include "model/IMConstant.h"

class QMenu;
class QLabel;
class IMDiscussionChatWidget;
class IMChatWidget;
class IMMainWidget;
class IMMainCtrl;


class IMDiscussionMemberButton : public QPushButton
{
    Q_OBJECT
public:
    IMDiscussionMemberButton(const DiscussionMember &, IMDiscussionChatWidget *,
                             IMMainWidget *, QWidget *parent = 0);
    
    ~IMDiscussionMemberButton();


    DiscussionMember &getInformation()
    {	return m_info;	}
    DiscussionMember getInformation() const
    {	return m_info;	}
    void setChangedInformation(const DiscussionMember & mem)
    {
        if (m_info.m_discussionID != mem.m_discussionID)
            return;
        if (m_info.m_discussionID != mem.m_userID)
            return;

        m_info.m_headPortrait = mem.m_headPortrait;
        m_info.m_nickname = mem.m_nickname;
        // m_loginStatus;
//        m_info.m_remark = mem.m_remark;
        // m_discussionStatus;
        // m_joinDate



    }

    //    void setRemark(const TempStrings & tmpStr)
    //    {
    //        if (0 != tmpStr.m_one.compare(m_info.m_discussionID))
    //            return;
    //        if (0 != tmpStr.m_two.compare(m_info.m_userID))
    //            return;

    //        m_info.m_remark = tmpStr.m_three;

    //        setButtonStatus();
    //    }

    // 打开聊天窗口
    void openChatRoom();
    // 关闭聊天窗口
    void closeChatRoom();
    // 设置button显示信息
    void setButtonStatus();

signals:
    void deleteMemberSignal(const QString &);
public slots:

    // 右键点击按键
    void onClickRightButton(/*const QPoint &*/);

    // 发送即时消息
    void onClickSendMessage();
    //  发送电子邮件
    void onClickSendMail();
    // 显示成员详细信息
    void onClickShowInformation();
    // 修改名片
    //void onClickChangeRemark();
    // 进入空间
    void onClickEnterSpace();
    // 移除该成员
    void onClickRemoveMember();
    // 加为好友
    void onClickAddFriend();

    // 左键 双击
    void onDoubleClickMemberButton();
    //聊天窗口关闭了
    void chatRoomQuit();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *);


private:
    // 将好友状态从数字形式转换为字符串形式
    QString getDiscussionStatusFromInt(const int n) const;

    // 将好友在线状态从数字形式转换为字符串形式
    QString getLoginStatusFromInt(const int n) const;
    // 创建右键菜单
    void creatMenu(/*const QList<QString> *groutList*/);


private:
    DiscussionMember m_info;
    QString m_strDiscussionStatus; // 身份
    QString m_strLoginStatus; // 在线状态
    // 聊天窗口是否打开了
    bool m_isOpen;

    // 右键菜单
    QMenu *m_menu;
//    IMChatWidget *m_chatRoom;
    IMDiscussionChatWidget *m_discussionWidget;
    IMMainWidget *m_mainWidget;
    IMMainCtrl *m_mainCtrl;

    QLabel *m_labelHead;
    QLabel *m_labelMes;
    
};

#endif // IMDISCUSSIONMEMBERBUTTON_H

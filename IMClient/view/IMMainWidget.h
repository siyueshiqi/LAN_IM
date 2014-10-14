/*********************************************
File Name： IMMainWidget.h
Author： jet.F.R
Date： 2014.3.14
Description： 客户端主界面
Changes：
********************************************/

#ifndef IMMAINWIDGET_H
#define IMMAINWIDGET_H

#include <QWidget>
#include <QMap>
#include "model/IMConstant.h"
#include "control/IMDatabaseCtrl.h"
//#include "model/IMEncryption.h"

class IMMainCtrl;
class QListWidget;
class IMChatWidget;
class IMFlockChatWidget;
class IMDiscussionChatWidget;
class QListWidgetItem;
class QGroupBox;
class QVBoxLayout;
class QToolBox;
class IMFriendButton;
class IMFlockButton;
class IMDiscussionButton;
class IMToolBox;
class IMToolItem;
class QFrame;
class QLabel;
class QComboBox;
class QToolButton;
class QLineEdit;
class QTabWidget;
class IMFriendListWidget;
class IMFlockListWidget;
class IMDiscussionListWidget;
class IMLatestMessageListWidget;
class IMInformationWidget;
class IMClickLabel;
class IMFlockInformationWidget;
class IMDiscussionInformationWidget;
class IMMailWidget;
class QMenu;
class IMMessageManageWidget;
class IMLinkButton;
class IMSearchListWidget;

//class QList;

/*************************************************
Class Name： IMMainWidget
Description: 客户端主界面
*************************************************/
class IMMainWidget : public QWidget
{
    Q_OBJECT
public:
    IMMainWidget( const UserInformation me, QWidget *parent = 0);
    ~IMMainWidget();

    IMMainCtrl * getMainCtrl() const
    {
        return m_mainCtrl;
    }

    UserInformation getLocalMyInformation() const;

    bool isMyFriend(const QString &id) const;

//    void setNickname(const QString &nickname);
//    void setUserID(const QString &id);
//    void setLoginStatus(const LoginStatus status);

    // 插入好友聊天室
    void insertChatRoomMap(const QString &, IMChatWidget *);
    // 插入群聊
    void insertFlockRoomMap(const QString &, IMFlockChatWidget *);
    // 插入组聊
    void insertDiscussionRoomMap(const QString &, IMDiscussionChatWidget*);
    // 获取好友信息（发送至服务器）
    void getFriendInformation(const QString &id);
    // 改变自己信息（发送至服务器）
    void changeMyInformation(const UserInformation &);
    // 改变好友备注（发送至服务器）
    void changeFriendRemark(const QString &, const QString &);
    // 删除好友（发送至服务器）
    void deleteFriend(const QString &);
    // 删除存储于m_informationMap中的信息窗口
    void removeInformationWidget(const QString &);
    // 删除存储与m_flockInformationMap中的信息窗口
    void removeFlockInformationWidget(const QString &);
    // 删除存储与m_discussionInformationMap中的信息窗口
    void removeDiscussionInformationWidget(const QString &);

    // 修改群信息（发送至服务器）
    void changeFlockInformation(const FlockInformation &);
    // 修改讨论组信息 （发送至服务器）
    void changeDiscussionInformation(const DiscussionInformation &);

    // 删除存储于m_chatRoomMap中的聊天窗口
    void removeChatWidget(const QString &);
    // 删除存储于m_flockRoomMap中的群聊窗口
    void removeFlockChatWidget(const QString &);
    // 删除存储于m_discussionChatWidget中的讨论组窗口
    void removeDiscussionChatWidget(const QString &);
    // 解散群 (发送至服务器)
    void dropFlock(const QString &);
    // 解散讨论组（发送至服务器）
    void dropDiscussion(const QString &);

    // 退出群（发送至服务器）
    void leaveFlock(const QString & memberID, const QString &flockID);

    // 退出讨论组 （发送至服务器）
    void leaveDiscussion(const QString & memberID, const QString &discussionID);

    // 添加好友（发送至服务器）
    void addFriend(const QString friendID);
    // 修改群成员名片（发送至服务器）
    void changeFlockMemberRemark(const TempStrings & tmpStr);

    // 移动好友至其他分组
    void moveFriendToBox(const QString & friendID, const QString & groupName, const QString &title);

    // 设置在线人数
    void setOnlineCounter(int num);


    // 获取所有分组
    QStringList getGroupList() const
    {
        return m_friendsGroupList;
    }

    // 获取所有分组
    QStringList getGroupFriendList(const QString & groupName);

    /*********************local database *******************/
    // 获取本地某日某好友的消息记录
    void getLocalHistoryMessage(const int index, const QDate &date);

    // 导出单个好友消息记录
    void exportLocalMessage(const int index);
    // 导出所有消息记录
    void exportLocalMessageAll();
    // 删除单个好友消息记录
    void deleteLocalMessage(const int index);
    // 删除所有消息记录
    void deleteLocalMessageAll();

    /*********************network database *******************/
    // 获取网络某日某好友的消息记录
    void getNetWorkHistoryMessage(const int index, const QDate &date);

//    // 导出单个好友消息记录
//    void exportNetWorkMessage(const int index);
//    // 导出所有消息记录
//    void exportNetWorkMessageAll();
//    // 删除单个好友消息记录
//    void deleteNetWorkMessage(const int index);
//    // 删除所有消息记录
//    void deleteNetWorkMessageAll();

signals:
    void exportHistoryMessageOneFriendSuccess(const QString &, const QString &,
                                              const QString &);
    void exportHistoryMessageAllSuccess(const QString &, const QString &);
public slots:

    // 获取好友信息列表（发送至服务器）
    void getFriendsInformation();
    // 获取群信息列表（发送至服务器）
    void getFlocksInformation();
    // 获取讨论组信息列表（发送至.服务器）
    void getDiscussionsInformation();
    // 获取本地最近消息（访问本地数据库）
    void getLatestMessage();

    // 设置消息界面
    void setNetworkMessageWidget(const QString & friendID, const QDate & date,
                                 const QVector<TalkMessage> & mesVec);

    // 设置好友列表
    void setFriendListWidget(const QVector<FriendInformation> &);
    // 设置群列表
    void setFlockListWidget(const QVector<FlockInformation> &);
    // 设置讨论组列表
    void setDiscussionListWidget(const QVector<DiscussionInformation> &);

    // 添加好友按钮
    bool addFriendButton(const FriendInformation &);
    // 添加群按钮
    bool addFlockButton(const FlockInformation & flcokInfo);
    // 添加讨论组按钮
    bool addDiscussionButton(const DiscussionInformation & disInfo);

    // 获取好友发来的消息
    void receiveFriendTalkMessage(const TalkMessage &);
    // 设置好友状态
    void setFriendStatus(const QString &, int);
    // 设置好友信息
    void setFriendInformation(const FriendInformation &);
    // 显示好友信息
    void showFriendInformation(const UserInformation &);
    // 显示自己的信息
    void showMyInformation(const UserInformation &);
    // 设置个人信息
    void setMyInformation(const UserInformation &);

    // 显示群信息
    void showFlockInformation(const FlockInformation &);
    // 显示讨论组信息
    void showDiscussionInformation(const DiscussionInformation &);

    // 设置群信息
    void setFlockInformation(const FlockInformation &);
    // 设置讨论组信息
    void setDiscussionInformation(const DiscussionInformation &);

    // 设置群成员名片
    void setFlockMemberRemark(const TempStrings &);

    // 设置好友备注
    void setFriendRemark(const TempStrings&);
    // 已删除好友
    void deletedFriend(const QString &, const QString &, const QString &);

    // 已删除群
    void dropedFlock(const QString &);
    // 已删除讨论组
    void dropedDiscussion(const QString & discussionID);

    // 已退出群
    void leavedFlock(const QString &, const QString &, const QString &);
    // 已退出讨论组
    void leavedDiscussion(const QString &, const QString &);

    // 创建群成功
    void createFlockSuccess(const FlockInformation &);
    // 创建讨论组成功
    void createDiscussionSuccess(const DiscussionInformation &);

    // 搜索友好
    void searchFriend(const QString & text);
    //  点击“搜索”按钮
    void onClickSearchFriend();

    // 点击“添加好友”按钮
    void onClickAddFriend();
    // 添加群
    void onClickAddFlock();
    // 修改密码
    void onClickChangePwd();
    // 创建群
    void createFlock();
    // 创建讨论组
    void createDiscussion();
    // 添加讨论组
//    void addDiscussion();

    // 显示消息管理窗口
    void showMessageWidget();
    // 显示邮箱
    void showMailWidget();
    // 显示邮箱中写信窗口
    void showMailWriteWidget(const QString & address);
    // 显示最新消息窗口
    void showLatestMessageWidget();
    // 设置显示有新消息的定时器
    void setTimerStatus(bool isOpen);

    // 重命名分组成功
    void renameBoxSuccess(const QString & title, const QString & newTitle);
    // 移动好友至其他分组
    void moveFriendToBoxSuccess(const QString &, const QString &, const QString &);

    void onClickRightButton();
    // 创建组
    void createBox();

    /*****************link button*****************************/
    // 删除新消息连接按钮
    void removeLinkButton(const QString & id);
    // 删除所有消息连接按钮
    void removeAllLinkButton();
    // 显示所有聊天窗口
    void showAllChatRoom();

protected:
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *);

private slots:

    // 关闭主窗口
    void closeWindow();
    // 关闭所有别的窗口
    void closeAllWindows();

    // 获取自己信息（发送至服务器）
    void getMyInformation();

    //void createChatRoom(QListWidgetItem *);

    // 获取好友聊天室发出的消息
    void receiveMessagesFromChat(TalkMessage &);
    // 获取群发出的消息
    // void receiveMessagesFromFlockChat(TalkMessage &);
    // 获取讨论组发出的消息
    // void receiveMessagesFromDiscussionChat(TalkMessage &);


    // 改变个人状态（发送至服务器）
    void changeMyStatus(const int index);

    // 接收并且处理好友的请求
    void receiveFriendRequest(const TalkMessage &, const UserInformation &);

    // 接收并且处理群的请求
    void receiveFlockRequest(const TalkMessage &,
                             const FlockMember &,
                             const FlockInformation &);
    // 接收并处理讨论组请求
    void receiveDiscussionRequest(const TalkMessage & mes,
                                  const DiscussionMember & member,
                                  const DiscussionInformation & discussion);

    // 删除组
    void removeBox(const QString &);
    // 重命名组
    void renameBox(const QString &);


private:
    void initIMMainWidget();
    void linkSignalWithSlot();
    void clearContainers();
    void creatMenu();
    void refreshFriendButtonMenu();
    //询问用户是否真的要退出
    bool continueToClose();
private:
    IMMainCtrl *m_mainCtrl;
    int m_onlineCounter;
    //IMUser *m_myself;
    UserInformation m_myself;

//    QListWidget * m_friendsList;

    //IMChatWidget *m_chatRoom;
    QMap<QString,IMChatWidget *> m_chatRoomMap; // 好友ID 与 聊天室 映射表
    QMap<QString,IMFlockChatWidget *> m_flockRoomMap; // 群ID 与 群聊 映射表
    QMap<QString,IMDiscussionChatWidget *> m_discussionRoomMap; // 讨论组ID 与 讨论室 映射表

    QMap<QString, IMInformationWidget *> m_informationMap;
    QMap<QString, IMFlockInformationWidget *> m_flockInformationMap;
    QMap<QString, IMDiscussionInformationWidget *> m_discussionInformationMap;

    QStringList m_friendsGroupList;  // 分组名 列表
    QStringList m_friendsMarkList; // 某分组中好友 备注名 列表
    QStringList m_friendsIDList; // 某分组中好友 ID  列表

    QVector<IMToolItem *> m_toolItemsFriendsVec;  // 存储每个分组的向量

    QMap<QString, int> m_indexFriendsGroupMap; // 组名 与 下标 映射表

    QMap<QString, IMFriendButton *> m_friendMap; // 好友帐号 与 好友按钮 映射表

    QMap<QString, IMFlockButton *> m_flockMap; // 群ID 与 群按钮 映射表

    QMap<QString, IMDiscussionButton *> m_discussionMap; // 讨论组ID 与 讨论组按钮 映射表

    QMap<QString, IMLinkButton*> m_linkMap; //ID 链接按钮 映射表


//    QFrame *m_frameHead;
    IMClickLabel *m_labelHead;
    QLabel *m_labelNickname;
    QComboBox *m_cbStatus;
    QLabel *m_labelMark;
    QToolButton *m_toolBtnSpace;
    QToolButton *m_toolBtnMail;
    QToolButton *m_toolBtnMesBox;
    QToolButton *m_toolBtnNewMes;

    QLineEdit *m_leSearch;
    QToolButton *m_toolBtnSearch;
//    QLabel *m_labelSearch;

    QLabel *m_labelOnlineNum;
    QToolButton *m_toolBtnAddFlock;
//    QToolButton *m_toolBtnAddDiscussion;
    QToolButton *m_toolBtnAddFriend;
//    QToolButton *m_toolBtnSearchAdd;
    QToolButton *m_toolBtnConfig;

    QTabWidget *m_tabWidget;
    IMFriendListWidget *m_friendListWidget;
    IMFlockListWidget *m_flockListWidget;
    IMDiscussionListWidget *m_discussionListWidget;
    IMLatestMessageListWidget *m_messageListWidget;
    IMSearchListWidget *m_searchListWidget;
    int m_timerId; //ID of timer


    IMMailWidget *m_mailWidget;
    IMMessageManageWidget *m_messageManWidget;
    QMenu *m_menu;

    int m_flag;

    // 操作数据库
    IMDatabaseCtrl m_database;
    QVector<TalkMessage> m_localHistoryMessageVec;
    QVector<TalkMessage> m_networkHistoryMessageVec;
//    QMap<QString, QVector<TalkMessage> > m_local
};

#endif // IMMAINWIDGET_H

/*********************************************
File Name： IMLoginWidget.h
Author： jet.F.R
Date： 2014.3.10
Description： 客户端登录界面
Changes：
********************************************/

#ifndef IMLOGINWIDGET_H
#define IMLOGINWIDGET_H

#include <QtGui/QWidget>

class QPushButton;
class QLabel;
class QLineEdit;
class QCheckBox;
class QComboBox;
class IMClickLabel;
class IMLoginCtrl;
struct UserInformation;

/*************************************************
Class Name： IMLoginWidget
Description: 客户端登录界面类
*************************************************/
class IMLoginWidget : public QWidget
{
    Q_OBJECT
    
public:
    IMLoginWidget(QWidget *parent = 0);
    ~IMLoginWidget();
signals:

public slots:
    // 显示主界面
    void showMainWidget();
    // 设置状态标签
    void setLabelStatus(const QString &mes, bool isLogin,
                        const UserInformation *me = 0);
    // 获取m_isAutoLogin
    bool getIsAutoLogin();
    // 单击“登录”按钮
    void onClickBtnLogin();

protected:
    // 处理定时器事件
    void timerEvent(QTimerEvent * event);
private slots:
    // 单击"注册帐号"标签
    void onClickLabelRegister();
    // 单击“忘记密码"标签
    void onClickLabelForgotPwd();
    // 自动登录选择框改变
    void onClickCbAutoLogin(int state);
private:
    // 初始化登录界面
    void initIMLoginWidget();
    // 连接信号与槽
    void linkSignalWithSlot();
    // 关闭定时器
    void closeTimer();
    // 设置服务器信息
    void setServer(const QString &ip = "127.0.0.1", const int port = 1234);
    // 读取自动登录配置文件
    bool readAutoLoginFile(const QString &);

private:
    QLineEdit *m_leUserID;    // id
    QLineEdit *m_leUserPwd;   // 密码
    IMClickLabel *m_labelRegister;  // 注册帐号
    IMClickLabel *m_labelForgotPwd; // 忘记密码
    QCheckBox *m_cbKeepPwd;   // 记住密码
    QCheckBox *m_cbAutoLogin; // 自动登录
    QComboBox *m_cbxStatus;   // 登录状态
    QPushButton *m_btnLogin;  // 登录按钮

    QPushButton *m_moreButton;// 拓展按钮
    QWidget *m_extendedWidget;// 拓展界面
    QLineEdit *m_hostAddress; // 服务器ip地址
    QLineEdit *m_hostPort;    // 服务器端口

    QLabel *m_labelStatus;    // 状态标签
    bool m_isLogin;           // 是否能登录
    IMLoginCtrl *m_loginCtrl; // 用于控制登录

    int m_timerID;            // 定时器ID
    bool m_closeTimer;        // 定时器是否关闭
    int m_counter;            // 计数器
    bool m_isAutoLogin;         // 是否自动登录

    int m_status;
};

#endif // IMLOGINWIDGET_H

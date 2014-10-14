#ifndef IMINFORMATIONWIDGET_H
#define IMINFORMATIONWIDGET_H

#include <QWidget>
#include "model/IMConstant.h"

class QPushButton;
class QLabel;
class QLineEdit;
class QCheckBox;
class QComboBox;
class QFrame;
class CustomLineEdit;
class IMMainWidget;

static const int MAX_NUM = 133;			//总头像数

class IMInformationWidget : public QWidget
{
    Q_OBJECT
public:
    IMInformationWidget(IMMainWidget *mainWidget, QWidget *parent = 0);
     ~IMInformationWidget();

    void setReadOnly(bool isReadOnly, bool isEdit);
//    void setWrite();
    void setUserInformation(const UserInformation &user);
    UserInformation getInformation();
protected:
    void closeEvent(QCloseEvent *);
signals:
//    void sendInformation(const UserInformation &user);
public slots:
    void onClickCancelButton();
    void onClickOKButton();
    void onClickPretButton();
    void onClickNextButton();

private:
    void initIMLoginWidget();

protected:
    QLabel *m_labelUserID;    // 用户帐号
    QLineEdit *m_leUserID;
//     QLabel *m_labelDesUserID;
    QLabel *m_labelNickname;   // 用户昵称
    QLineEdit *m_leNickname;

    QFrame *m_frameHead;
    QLabel *m_labelHead;
//    QLabel *m_labelHeadMes;
    QPushButton *m_btnNext;
    QPushButton *m_btnPre;
//        QLabel *m_labelDesNickname;// 昵称描述
//        QLabel *m_labelPwd;        // 用户密码
//        QLineEdit *m_lePwd;
//        QLabel *m_labelDesPwd;
        QLabel *m_labelConfirmPwd;  // 确认密码
        QLineEdit *m_leConfirmPwd;
//        QLabel *m_labelDesConfirmPwd;
        QLabel *m_labelSex;        // 性别
        QComboBox *m_cbxSex;
//        QLabel *m_labelDesSex;
        QLabel *m_labelBirthday;   // 生日
        CustomLineEdit *m_leBirthday;
//        QLabel *m_labelDesBirthday;
//        QLabel *m_labelQuestion;   // 密保问题
//        QLineEdit *m_leQuestion;
//        QLabel *m_labelDesQuestion;
//        QLabel *m_labelAnswer;     // 问题答案
//        QLineEdit *m_leAnswer;
//        QLabel *m_labelDesAnswer;
        QLabel *m_labelName;       // 真实姓名
        QLineEdit *m_leName;
//        QLabel *m_labelDesName;
        QLabel *m_labelPhone;      // 电话
        QLineEdit *m_lePhone;
//        QLabel *m_labelDesPhone;
        QLabel *m_labelAddress;    // 地址
        QLineEdit *m_leAddress;
//        QLabel *m_labelDesAddress;

        QPushButton *m_btnOk;// "注册" 按钮
        QPushButton *m_btnCancel;  // "取消" 按钮

        int m_headNum;
        bool m_isReadOnly;
        bool m_isEdit;

        UserInformation m_userInf;
        IMMainWidget *m_mainWidget;
};

#endif // IMINFORMATIONWIDGET_H

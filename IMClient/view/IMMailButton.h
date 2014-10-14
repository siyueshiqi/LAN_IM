#ifndef IMMAILBUTTON_H
#define IMMAILBUTTON_H

#include <QPushButton>
#include "model/IMConstant.h"

class QCheckBox;
class QLabel;
class IMMailWidget;
class IMMailCtrl;

class IMMailButton : public QPushButton
{
    Q_OBJECT
public:
    IMMailButton(const MailInformation &, IMMailWidget *, QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *);

signals:
    
public slots:

private slots:
    // 点击删除邮件
    void onClickDeleteMail();
    // 左键 双击
    void onDoubleClickDiscussionButton();
    // 右键点击按键
    void onClickRightButton();

private:
    // 设置button显示信息
    void setButtonStatus();
    // 创建右键菜单
    void creatMenu();

private:
//    QCheckBox m_cbSelected;
    QLabel *m_labelStatus;
    QLabel *m_labelSender;
    QLabel *m_labelTheme;
    QLabel *m_labelTime;
    QMenu *m_menu;
    IMMailWidget *m_mailWidget;
    IMMailCtrl *m_mailCtrl;
    MailInformation m_mail;
};

#endif // IMMAILBUTTON_H

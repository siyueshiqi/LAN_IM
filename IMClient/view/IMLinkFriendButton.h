#ifndef IMLINKFRIENDBUTTON_H
#define IMLINKFRIENDBUTTON_H

#include <QPushButton>
#include "IMLinkButton.h"
#include "model/IMConstant.h"

class QLabel;
class IMFriendButton;

class IMLinkFriendButton : public IMLinkButton
{
    Q_OBJECT
public:
    IMLinkFriendButton(IMFriendButton * btn, QWidget *parent = 0);
    ~IMLinkFriendButton();


    // 设置button显示信息
    void setButtonStatus();

public slots:
    // 左键 双击
    void onDoubleClickButton();
    // 忽略消息
    void ignoreMessage();


private:
    IMFriendButton * m_friendBtn;
    FriendInformation m_info;

};

#endif // IMLinkFriendButton_H

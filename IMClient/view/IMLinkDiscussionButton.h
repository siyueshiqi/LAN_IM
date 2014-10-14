#ifndef IMLINKDISCUSSIONBUTTON_H
#define IMLINKDISCUSSIONBUTTON_H

#include "IMLinkButton.h"
#include "model/IMConstant.h"

class QLabel;
class IMDiscussionButton;

class IMLinkDiscussionButton : public IMLinkButton
{
    Q_OBJECT
public:
    IMLinkDiscussionButton(IMDiscussionButton * btn, QWidget *parent = 0);
    ~IMLinkDiscussionButton();

    // 设置button显示信息
    void setButtonStatus();

signals:
    
public slots:
    // 左键 双击
    void onDoubleClickButton();
    // 忽略消息
    void ignoreMessage();

private:
    IMDiscussionButton *m_discussionBtn;
    DiscussionInformation m_info;
    
};

#endif // IMLINKDISCUSSIONBUTTON_H

#ifndef IMMAILINFORMATIONWIDGET_H
#define IMMAILINFORMATIONWIDGET_H

#include <QWidget>
#include "model/IMConstant.h"

class QLineEdit;
class QLabel;
class QPushButton;
class QTextCharFormat;
class QTextEdit;
class IMMailCtrl;
class IMMailWidget;
class QTextBrowser;
class QTextEdit;


class IMMailInformationWidget : public QWidget
{
    Q_OBJECT
public:
    IMMailInformationWidget(IMMailWidget *, QWidget *parent = 0);
    void setMailInformation(const MailInformation &);
    
signals:
    
private slots:
    // 删除
    void onClickBtnDelete();
    // 关闭
    void onClickBtnClose();
private:
    void initIMMailInformationWidget();
    void linkSignalWithSlot();
private:
    QLabel *m_labelSenderAddress;
    QLabel *m_labelReceiverAddress;
    QLabel *m_labelTheme;
    QLabel *m_labelTime;
    QTextBrowser *m_textContnet;
//    QTextEdit *m_textInput;

    QPushButton *m_btnDelete;
    QPushButton *m_btnClose;

    MailInformation m_mail;

    IMMailWidget *m_mailWidget;
    IMMailCtrl *m_mailCtrl;

};

#endif // IMMAILINFORMATIONWIDGET_H

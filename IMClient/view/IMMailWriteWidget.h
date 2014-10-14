#ifndef IMMAILWRITEWIDGET_H
#define IMMAILWRITEWIDGET_H

#include <QWidget>
#include "model/IMConstant.h"

class QLineEdit;
class QComboBox;
class QFontComboBox;
class QLabel;
class QPushButton;
class QToolButton;
class QTextCharFormat;
class QTextEdit;
class IMMailCtrl;

class IMMailWriteWidget : public QWidget
{
    Q_OBJECT
public:
    IMMailWriteWidget(QString, IMMailCtrl *, QWidget *parent = 0);
    
    void setReceiverAddress(const QString & address);

signals:
    
public slots:

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
    // 发送聊天信息
    void onClickBtnSend();

private:
    void initIMMailWriteWidget();
    void linkSignalWithSlot();
    void setWidgetToolBtn();
    // 获取信息输入框的信息
    void getMailInformation();

private:
    QLineEdit *m_leReceiverAddress;
    QLineEdit *m_leTheme;
    QTextEdit *m_textInput;

    QFontComboBox *m_cbFont;         // 字体样式选择框
    QComboBox *m_cbSize;             // 字体大小选择框
    QToolButton *m_toolBtnBold;      // 加粗
    QToolButton *m_toolBtnItalic;    // 斜体
    QToolButton *m_toolBtnUnderline; // 下划线
    QToolButton *m_toolBtnColor;     // 颜色

    QPushButton *m_btnSend;

    MailInformation m_mail;
    QString m_myID;
    IMMailCtrl *m_mailCtrl;
};

#endif // IMMAILWRITEWIDGET_H

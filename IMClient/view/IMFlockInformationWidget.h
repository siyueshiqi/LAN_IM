#ifndef IMFLOCKINFORMATIONWIDGET_H
#define IMFLOCKINFORMATIONWIDGET_H

#include <QWidget>
#include "model/IMConstant.h"
class QPushButton;
class QLabel;
class QLineEdit;
class IMMainWidget;

class IMFlockInformationWidget : public QWidget
{
    Q_OBJECT
public:
    IMFlockInformationWidget(IMMainWidget *mainWidget, QWidget *parent = 0);
    ~IMFlockInformationWidget();
    void setReadOnly(bool isReadOnly, bool isEdit);
    void setFlockInformation(const FlockInformation &);
    FlockInformation getInformation();
signals:

protected:
    void closeEvent(QCloseEvent *);
public slots:
    void onClickCancelButton();
    void onClickOKButton();
private:
    void initIMLoginWidget();

     QLabel *m_labelFlockHead;
     QLabel *m_labelFlockName;
     QLabel *m_labelFlockID;
     QLabel *m_labelCreatorID;
     QLabel *m_labelTheme;
     QLabel *m_labelCreateDate;

     QLineEdit *m_leFlockName;
     QLineEdit *m_leFlockID;
     QLineEdit *m_leCreatorID;
     QLineEdit *m_leTheme;
     QLineEdit *m_leCreateDate;

     QPushButton *m_btnOk;// "注册" 按钮
     QPushButton *m_btnCancel;  // "取消" 按钮

     bool m_isReadOnly;
     bool m_isEdit;

     FlockInformation m_flockInf;
     IMMainWidget *m_mainWidget;
};

#endif // IMFLOCKINFORMATIONWIDGET_H

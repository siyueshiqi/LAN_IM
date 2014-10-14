#ifndef IMMESSAGEMANAGEWIDGET_H
#define IMMESSAGEMANAGEWIDGET_H

#include <QWidget>
#include "model/IMConstant.h"
class IMMainWidget;
class QTabWidget;
class IMLocalMessageWidget;
class IMNetWorkMessageWidget;

class IMMessageManageWidget : public QWidget
{
    Q_OBJECT
public:
    IMMessageManageWidget(IMMainWidget *, QWidget *parent = 0);
    ~IMMessageManageWidget();

    void setLocalMessageWidget(const QVector<TalkMessage> &mesVec);
    void setNetworkMessageWidget(const QVector<TalkMessage> &mesVec);

    void setListModelGroup();

signals:
    
public slots:

private:
    IMMainWidget * m_mainWidget;
    QTabWidget *m_tabWidget;
    IMLocalMessageWidget *m_localWidget;
    IMNetWorkMessageWidget *m_networkWidget;

};

#endif // IMMESSAGEMANAGEWIDGET_H

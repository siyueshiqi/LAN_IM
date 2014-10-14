#ifndef IMMAILINWIDGET_H
#define IMMAILINWIDGET_H

//#include <QWidget>
#include "IMMailListWidget.h"

class IMMailCtrl;

class IMMailInWidget : public IMMailListWidget
{
    Q_OBJECT
public:
    IMMailInWidget(IMMailCtrl *, QWidget *parent = 0);
    
signals:
    
public slots:

private:

private:
    IMMailCtrl *m_mailCtrl;

};

#endif // IMMAILINWIDGET_H

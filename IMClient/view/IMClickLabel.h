/*********************************************
File Name： IMClickLabel.h
Author： jet.F.R
Date： 2014.3.10
Description： 具有单击相应的标签类
Changes：
********************************************/

#ifndef IMCLICKLABEL_H
#define IMCLICKLABEL_H

#include <QLabel>


/*************************************************
Class Name： IMClickLabel
Description: 具有单击相应的标签类
*************************************************/
class IMClickLabel : public QLabel
{
    Q_OBJECT
public:
    explicit IMClickLabel(QWidget *parent = 0);
    IMClickLabel(const QString &text, QWidget *parent=0);
signals:
    // 鼠标单击信号
    void clicked();//IMClickLabel* label);

protected:
    // 鼠标单击事件
    void mouseReleaseEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
public slots:
    
};

#endif // IMCLICKLABEL_H

#ifndef IMMAILLISTWIDGET_H
#define IMMAILLISTWIDGET_H

#include <QWidget>

class QVBoxLayout;
class QScrollArea;

class IMMailListWidget : public QWidget
{
    Q_OBJECT
public:
    IMMailListWidget(QWidget *parent = 0);
    void addItem(QWidget *item);
    void removeItem(QWidget *item);
    void insertItem(int index, QWidget * widget);
    
    //创建右键菜单
//    void creatMenu();
signals:
    
public slots:
    
private:
    QVBoxLayout *m_layout;
    QWidget *m_contentsWidget;
    QScrollArea *m_flocksScrollArea;
};

#endif // IMMAILLISTWIDGET_H

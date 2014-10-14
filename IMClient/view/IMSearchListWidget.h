#ifndef IMSEARCHLISTWIDGET_H
#define IMSEARCHLISTWIDGET_H

#include <QWidget>

class QVBoxLayout;
class QScrollArea;
class QMenu;
class IMMainWidget;

class IMSearchListWidget : public QWidget
{
    Q_OBJECT
public:
    IMSearchListWidget(QWidget *parent = 0);
    void addItem(QWidget *item);
    void removeItem(QWidget *item);
    int size();
    void clearAll();
    
signals:
    
public slots:

private:
    QVBoxLayout *m_layout;
    QWidget *m_contentsWidget;
    QScrollArea *m_scrollArea;
    IMMainWidget *m_mainWidget;

    int m_mesCounter;
};

#endif // IMSEARCHLISTWIDGET_H

#ifndef IMDISCUSSIONLISTWIDGET_H
#define IMDISCUSSIONLISTWIDGET_H

#include <QWidget>

class QVBoxLayout;
class QScrollArea;
class QMenu;
class IMMainWidget;

class IMDiscussionListWidget : public QWidget
{
    Q_OBJECT
public:
    IMDiscussionListWidget(IMMainWidget *mainWidget, QWidget *parent = 0);
    void addItem(QWidget *item);
    void removeItem(QWidget *item);

    //创建右键菜单
    void creatMenu();

signals:

public slots:
    void showMenu();

protected:
    void mousePressEvent(QMouseEvent *e);

private:
    QVBoxLayout *m_layout;
    QWidget *m_contentsWidget;
    QScrollArea *m_discussionsScrollArea;

    //右键菜单
    QMenu *m_menu;

    IMMainWidget *m_mainWidget;

};

#endif // IMDISCUSSIONLISTWIDGET_H

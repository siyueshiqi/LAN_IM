#ifndef IMTOOLBOX_H
#define IMTOOLBOX_H

#include <QWidget>
class QVBoxLayout;
class QLabel;
class QMenu;

class IMToolItem : public QWidget {
    Q_OBJECT
public:
    IMToolItem(const QString &title, QWidget *parent = 0);

    void addItem(QWidget *item);

    void removeItem(QWidget *item);

    void setTile(const QString &);

    int getSize();

    QList<QWidget *> * getWidgetList()
    {
        return &m_itemList;
    }

signals:
    void renameBoxSignal(const QString & title);
    void removeBoxSignal(const QString & title);

protected:
    void mousePressEvent(QMouseEvent *event);

private slots:
    void renameBox();
    void removeBox();
    void onClickRightButton();

private:
    void creatMenu();

private:
    QList<QWidget *> m_itemList;
    QVBoxLayout *m_layout;
    bool m_isVisable;
    QMenu *m_menu;
    QLabel *m_label;
};


class IMToolBox : public QWidget {
    Q_OBJECT
public:

    IMToolBox(QWidget *parent = 0);
    void addItem(IMToolItem *item);

signals:

public slots:

private:
    QVBoxLayout *m_layout;
};

#endif // IMTOOLBOX_H

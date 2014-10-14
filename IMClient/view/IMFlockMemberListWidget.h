#ifndef IMFLOCKMEMBERLISTWIDGET_H
#define IMFLOCKMEMBERLISTWIDGET_H

#include <QWidget>

class QVBoxLayout;
class QScrollArea;

class IMFlockMemberListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IMFlockMemberListWidget(QWidget *parent = 0);
    void addItem(QWidget *item);

signals:

public slots:

private:
    QVBoxLayout *m_layout;
    QWidget *m_contentsWidget;
    QScrollArea *m_flocksScrollArea;
};

#endif // IMFLOCKMEMBERLISTWIDGET_H

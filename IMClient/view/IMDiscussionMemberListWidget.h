#ifndef IMDISCUSSIONMEMBERLISTWIDGET_H
#define IMDISCUSSIONMEMBERLISTWIDGET_H

#include <QWidget>

class QVBoxLayout;
class QScrollArea;

class IMDiscussionMemberListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IMDiscussionMemberListWidget(QWidget *parent = 0);
    void addItem(QWidget *item);

signals:

public slots:

private:
    QVBoxLayout *m_layout;
    QWidget *m_contentsWidget;
    QScrollArea *m_flocksScrollArea;
};

#endif // IMDISCUSSIONMEMBERLISTWIDGET_H

#ifndef IMDATABASECTRL_H
#define IMDATABASECTRL_H

#include <QObject>
#include "model/IMConstant.h"

class QSqlQuery;
class QSqlDatabase;
class QDateTime;

class IMDatabaseCtrl : public QObject
{
    Q_OBJECT
public:
    IMDatabaseCtrl(const QString myID, QObject *parent = 0);
    ~IMDatabaseCtrl();
    // 创建连接
    bool createConnection();
    // 关闭数据库
    void close();
    // 打开数据库
    bool isOpen();

    /************消息管理*********************/
    // 存储历史记录
    bool addHistoryMessage(const TalkMessage &);
    // 获取某日的消息记录
    bool searchHistoryMessage(const QString &myID , const QString &friendID,
                              const QDate &date, QVector<TalkMessage> &mesVec);
    // 导出与某位好友的消息记录
    int exportHistoryMessageOneFriend(const QString &myID ,
                                      const QString &friendID,
                                      const QString &fileName);
    // 导出所有好友消息记录
    int exportHistoryMessageAll(const QString &myID, const QString &fileName);

    // 删除单个好友消息记录
    int deleteHistoryMessageOneFriend(const QString myID, const QString friendID);
    // 删除所有好友消息记录
    int deleteHistoryMessageAll(const QString myID);

signals:
    
public slots:

private:
    //检查SQL语句的正确性
    void errorSQLOrder(QSqlQuery query, QString mark);
    //创建数据库表格
    void createTable();
private:
    QSqlDatabase *m_db;
    QString m_myID;
    QString m_localHistoryTableName;
};

#endif // IMDATABASECTRL_H

/*********************************************
File Name： IMUser.h
Author： jet.F.R
Date： 2014.3.17
Description： 用户类
Changes：
********************************************/
#ifndef IMUSER_H
#define IMUSER_H

#include <QObject>
#include <QDateTime>
#include "model/IMConstant.h"

class IMUser : public QObject
{
    Q_OBJECT
public:
    IMUser(QObject *parent = 0);
    IMUser(QString id, const QString &nick, const QString &pwd = "",
           const QString &sex = "",
           const QDate birth = QDate::currentDate(),
           const QString &name ="", const QString &addr = "",
           const QString &phone = "",const QString &ques = "",
           const QString &ans = "",
           const QDateTime regDate = QDateTime::currentDateTime(),
           const int status = ONLINE);

    QString getUserID() const;
    QString getNickname() const;
    QString getPassword() const;
    QString getSex() const;
    QDate getBirthday() const;
    QString getQuestion() const;
    QString getAnswer() const;
    QString getName() const;
    QString getPhone() const;
    QString getAddress() const;
    QDateTime getRegDateTime() const;
    int getStatus() const;

    void setUserID(const QString &);
    void setNickname(const QString &);
    void setPassword(const QString &);
    void setSex(const QString &);
    void setBirthday(const QDate &);
    void setQusetion(const QString &);
    void setAnswer(const QString &);
    void setName(const QString &);
    void setPhone(const QString &);
    void setAddress(const QString &);
    void setRegDateTime(const QDateTime &);
    void setStatus(const int status);

signals:

public slots:

private:
    QString m_userID;
    QString m_nickname;
    QString m_password;
    QString m_sex;
    QDate m_birthday;
    QString m_question;
    QString m_answer;
    QString m_name;
    QString m_phone;
    QString m_address;
    QDateTime m_regDateTime;
    int m_status;

    friend QDataStream &operator<<(QDataStream &out, const IMUser &user);

    friend QDataStream &operator>>(QDataStream &in, IMUser &user);
};




#endif // IMUSER_H

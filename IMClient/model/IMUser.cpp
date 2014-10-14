/*********************************************
File Name： IMUser.cpp
Author： jet.F.R
Date： 2014.3.17
Description： 用户类
Changes：
********************************************/

#include "IMUser.h"



// mark: public------------------------------------------------------
IMUser::IMUser(QObject *parent) :
    QObject(parent)
{
}

IMUser::IMUser(QString id, const QString &nick, const QString &pwd, const QString &sex,
               const QDate birth, const QString &name, const QString &addr,
               const QString &phone, const QString &ques, const QString &ans,
               const QDateTime regDate, const int status)
{
    m_userID = id;
    m_nickname = nick;
    m_password = pwd;
    m_sex = sex;
    m_birthday = birth;
    m_question = ques;
    m_answer = ans;
    m_name = name;
    m_phone = phone;
    m_address = addr;
    m_regDateTime = regDate;
    m_status = status;
}


/*************************************************
Function Name： getXX()
Description: 获取用户信息
Input： NULL
Output：**(QString / int / QDateTime)
Changes： NULL
*************************************************/

/********************* bgein getXX()****************************/
QString IMUser::getUserID() const { return m_userID; }

QString IMUser::getNickname() const { return m_nickname; }

QString IMUser::getPassword() const { return m_password; }

QString IMUser::getSex() const { return m_sex; }

QDate IMUser::getBirthday() const { return m_birthday;}

QString IMUser::getQuestion() const { return m_question; }

QString IMUser::getAnswer() const { return m_answer; }

QString IMUser::getName() const { return m_name; }

QString IMUser::getPhone() const { return m_phone; }

QString IMUser::getAddress() const { return m_address; }

QDateTime IMUser::getRegDateTime() const { return m_regDateTime; }

int IMUser::getStatus() const {return m_status; }

/********************* end getXX()******************************/

/********************* bgein setXX()****************************/
 void IMUser::setUserID(const QString &id) { m_userID = id; }
 void IMUser::setNickname(const QString &nick) { m_nickname = nick; }
 void IMUser::setPassword(const QString &pwd) { m_password = pwd; }
 void IMUser::setSex(const QString &sex) { m_sex = sex; }
 void IMUser::setBirthday(const QDate &birth) { m_birthday = birth; }
 void IMUser::setQusetion(const QString &ques) { m_question = ques; }
 void IMUser::setAnswer(const QString &ans) { m_answer = ans; }
 void IMUser::setName(const QString &name) { m_name = name; }
 void IMUser::setPhone(const QString &phone) { m_phone = phone; }
 void IMUser::setAddress(const QString & add) { m_address = add; }
 void IMUser::setRegDateTime(const QDateTime &date) { m_regDateTime = date; }
 void IMUser::setStatus(const int status) { m_status = status; }
/********************* end setXX()******************************/


 QDataStream &operator<<(QDataStream &out, const IMUser &user)
 {
     out << user.m_userID << user.m_nickname << user.m_password
         << user.m_sex << user.m_birthday << user.m_question
         << user.m_answer << user.m_name << user.m_phone
         << user.m_address << user.m_regDateTime << user.m_status;
     return out;
 }

 QDataStream &operator>>(QDataStream &in, IMUser &user)
 {
     in >> user.m_userID >> user.m_nickname >> user.m_password
        >> user.m_sex >> user.m_birthday >> user.m_question
        >> user.m_answer >> user.m_name >>  user.m_phone
        >> user.m_address >> user.m_regDateTime >> user.m_status;
     return in;
 }

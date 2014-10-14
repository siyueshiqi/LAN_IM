/*********************************************
File Name： IMClientFileCtrl.h
Author： jet.F.R
Date： 2014.3.23
Description： xml文件读写
Changes：
********************************************/
#ifndef IMCLIENTFILECTRL_H
#define IMCLIENTFILECTRL_H

#include <QObject>
class QXmlStreamWriter;
class QXmlStreamReader;
class QTextBrowser;

class IMClientFileCtrl : public QObject
{
    Q_OBJECT
public:
    explicit IMClientFileCtrl(QObject *parent = 0);
    // 写自动登录的文件
    static bool writeAutoLogin(const QString &fileName, const QString &id,
                        const QString &pwd, const bool isAuto = false);
    // 读自动登录的文件
    static bool readAutoLogin(const QString &fileName,QString &id,
                         QString &pwd, bool &isAuto);

    // 删除文件
    static bool remove(const QString &filename);

    static QString simplifyRichText(QString richText);

    static void saveTalkHistory(const QString filePath, const QString fileName,
                                const QTextBrowser *messagaShow);
    static void readTalkHistory(const QString filePath, const QString fileName,
                                QTextBrowser *messagaShow);

signals:
    
public slots:

private:
//    QXmlStreamWriter m_write;
//    QXmlStreamReader m_read;

};

#endif // IMCLIENTFILECTRL_H

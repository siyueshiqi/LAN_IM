/*********************************************
File Name： IMClientFileCtrl.cpp
Author： jet.F.R
Date： 2014.3.23
Description： xml文件读写
Changes：
********************************************/

#include "IMClientFileCtrl.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDataStream>
#include <QDir>
#include <QFile>
#include <qdebug.h>
#include <QRegExp>
#include <QTextDocument>
#include <QTextBrowser>

IMClientFileCtrl::IMClientFileCtrl(QObject *parent) :
    QObject(parent)
{
}


/*************************************************
Function Name： writeAutoLogin()
Description: 写自动登录的文件
Input： 文件路径,帐号,密码,是否自动登录
*************************************************/
bool IMClientFileCtrl::writeAutoLogin(const QString &fileName, const QString &id,
                    const QString &pwd, const bool isAuto)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Cannor open file for writing: "
                 << qPrintable(file.errorString()) << endl;
        return false;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_8);
    out << id << pwd << isAuto;
    file.close();
    return true;
}

/*************************************************
Function Name： readAutoLogin()
Description: 读自动登录的xml文件
Input： 文件路径,帐号,密码
Output： bool
Changes： NULL
*************************************************/
bool IMClientFileCtrl::readAutoLogin(const QString &fileName,QString &id,
                     QString &pwd, bool &isAuto)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Cannor open file for writing: "
                 << qPrintable(file.errorString()) << endl;
        return false;
    }
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_8);
    in >>id >> pwd >> isAuto;
    file.close();
    return true;
}

/*************************************************
Function Name： remove()
Description: 删除文件
Input： 文件路径
Output： bool
Changes： NULL
*************************************************/
bool IMClientFileCtrl::remove(const QString &filename)
{
    QFile file(filename);
//    if (!file.open(QIODevice::ReadWrite))
//    {
//        qDebug() << "Cannor open file for writing: "
//                 << qPrintable(file.errorString()) << endl;
//        return false;
//    }
    return file.remove()? true : false;
}


/*************************************************
Function Name： simplifyRichText()
Description: 将html格式的qstring转换
*************************************************/
QString IMClientFileCtrl::simplifyRichText( QString richText )
{
    QTextDocument doc;
    doc.setHtml(richText);
    qDebug() << "say:"<< doc.toPlainText();
    return doc.toPlainText();
}
//    QRegExp rxrichText("<richText[^>]*>(.*)</richText>");
//    if(rxrichText.indexIn(richText))
//    {
//        richText = rxrichText.cap(1); // throw away anything not in the richText, and the richText tags as well
//        richText.replace(QRegExp("^\\s+"),""); // throw away any leading whitespace (be it new lines or spaces)
//    }
//    QRegExp rxrichText1("<span[^>]*>(.*)</span>");
//    if(richText.indexOf(rxrichText1) != -1){
//        if(rxrichText1.indexIn(richText))
//        {
//            richText = rxrichText1.cap(1); // throw away anything not in the richText, and the richText tags as well
//            richText.replace(QRegExp("^\\s+"),""); // throw away any leading whitespace (be it new lines or spaces)
//        }
//    }
//    richText.replace(QRegExp("<p style=\"[^\"]*\">"),"<p>"); // throw away paragraph styles


//    if(richText == "<p></p>") // thats what we get for an empty QTextEdit
//        return QString();
//    richText.replace("<p>","");
//    richText.replace("</p>","");

//    return richText;
//}


//QString CleanTag( QString richText )
//{
//    qDebug() << "### start clean tag "; /* &nbsp; */
//    richText.replace("&nbsp;"," ");
//    richText.replace("<br>","##break##");
//    richText.replace("</br>","##break##");
//    richText.replace("</p>","##break##");
//    richText.replace("</td>","##break##");
//    richText.remove(QRegExp("<head>(.*)</head>",Qt::CaseInsensitive));
//    richText.remove(QRegExp("<form(.)[^>]*</form>",Qt::CaseInsensitive));
//    richText.remove(QRegExp("<script(.)[^>]*</script>",Qt::CaseInsensitive));
//    richText.remove(QRegExp("<style(.)[^>]*</style>",Qt::CaseInsensitive));
//    //richText.remove(QRegExp("<span(.)[^>]*</span>",Qt::CaseInsensitive));
//    richText.remove(QRegExp("<(.)[^>]*>"));
//    richText.replace("##break##","");
//    qDebug() << "### newrichText " << richText;
//    return richText;
//}

//QXmlStreamReader xml(richText);
//QString textString;
//while (!xml.atEnd()) {
//    if ( xml.readNext() == QXmlStreamReader::Characters ) {
//        textString += xml.text();
//    }
//}
//qDebug() << "### newrichText " << textString;
//return textString;


//}

/*************************************************
Function Name： saveTalkHistory()
Description: 保存历史记录
*************************************************/
void IMClientFileCtrl::saveTalkHistory(const QString filePath,
                                       const QString fileName,
                                       const QTextBrowser *messagaShow)
{
    QDir dir = QDir::current();
    if (!dir.exists(filePath))
        dir.mkpath(filePath);

    QString fileLoad = QString("%1/%2").arg(filePath).arg(fileName);
//    fileLoad = QDir::toNativeSeparators(fileLoad);

    QFile file(fileLoad);
    bool isOpen = file.open(QIODevice::WriteOnly | QIODevice::Append);
    if(!isOpen)
        return;

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_8);

    //如果聊天记录是空的，就不用保存了
    if(messagaShow->toPlainText().isEmpty())
        return;

    QString talkRecord = messagaShow->toHtml();
    out << talkRecord;
    file.close();
}

/*************************************************
Function Name： readTalkHistory()
Description: 读取历史记录
*************************************************/
void IMClientFileCtrl::readTalkHistory(const QString filePath,
                                       const QString fileName,
                                       QTextBrowser *messagaShow)
{
    QDir dir = QDir::current();
    if (!dir.exists(filePath))
        dir.mkpath(filePath);

    QString fileLoad = QString("%1/%2").arg(filePath).arg(fileName);
//    fileLoad = QDir::toNativeSeparators(fileLoad);

    QFile file(fileLoad);
    bool isOpen = file.open(QIODevice::ReadOnly);
    if(!isOpen)
        return;

    QString allRecord;
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_8);

    QString tempString;
    //从文件中读取全部的字符串
    while( !file.atEnd() )
    {
        in >> tempString;
        allRecord += tempString;
    }
    file.close();
    messagaShow->setText(allRecord);
}

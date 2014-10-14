#include "view/IMServerWindow.h"
#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 以下部分解决中文乱码
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
    // 以上部分解决中文乱码

//    //确保只运行一次
//    QSystemSemaphore sema("IMServerKey",1,QSystemSemaphore::Open);
//    //在临界区操作共享内存
//    sema.acquire();
//    QSharedMemory mem("IMServerObject");

//    // 如果全局对象以存在则退出
//    if (!mem.create(1))
//    {
//        QMessageBox::warning(NULL, "error",
//            "A server has already been running.");
//        sema.release();
//        return 0;
//    }
//    sema.release();

    IMServerWindow w;
    w.show();
    
    return a.exec();
}

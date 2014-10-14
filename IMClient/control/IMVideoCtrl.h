#ifndef IMVIDEOCTRL_H
#define IMVIDEOCTRL_H

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <asm/types.h>
#include <linux/videodev2.h>
#include <QString>
#include <QObject>

#define CLEAR(x) memset(&(x), 0, sizeof(x))

class IMVideoCtrl : public QObject
{
    Q_OBJECT
public:
    IMVideoCtrl(const QString & devName = "/dev/video0",  QObject *parent = 0);
    ~IMVideoCtrl();

    int openDevice();
    int closeDevice();
    int initDevice();
    int startCapturing();
    int stopCapturing();
    int uninitDevice();
    int getFrame(void **, size_t*);
    int ungetFrame();

signals:
    void displayError(QString);
public slots:

private:
    int initMmap();

    struct buffer
    {
        void * m_start;
        size_t m_length;
    };
    QString m_devName;
    int m_fd;
    buffer* m_buffers;

    unsigned int m_nBuffers;
    int m_index;
};

#endif // IMVIDEOCTRL_H

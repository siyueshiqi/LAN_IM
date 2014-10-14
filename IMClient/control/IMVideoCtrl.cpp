#include "IMVideoCtrl.h"

IMVideoCtrl::IMVideoCtrl(const QString & devName, QObject *parent) :
    QObject(parent)
{
    m_devName = devName;
    m_fd = -1;
    m_buffers = NULL;
    m_nBuffers = 0;
    m_index = -1;
}

IMVideoCtrl::~IMVideoCtrl()
{
    stopCapturing();
    uninitDevice();
    closeDevice();
    free(m_buffers);
}

int IMVideoCtrl::openDevice()
{
    m_fd = open(m_devName.toStdString().c_str(), O_RDWR/*|O_NONBLOCK*/, 0);

    if(-1 == m_fd)
    {
        emit displayError(tr("open device: %1").arg(QString(strerror(errno))));
        return -1;
    }
    return 0;
}

int IMVideoCtrl::closeDevice()
{
    if(-1 == close(m_fd))
    {
        emit displayError(tr("close: %1").arg(QString(strerror(errno))));
        return -1;
    }
    return 0;
}

int IMVideoCtrl::initDevice()
{
    v4l2_capability cap;
    v4l2_cropcap cropcap;
    v4l2_crop crop;
    v4l2_format fmt;

    // 查询当前视频支持标准
    if(-1 == ioctl(m_fd, VIDIOC_QUERYCAP, &cap))
    {
        if(EINVAL == errno)
        {
            emit displayError(tr("%1 is no V4l2 device").arg(m_devName));
        }
        else
        {
            emit displayError(tr("VIDIOC_QUERYCAP: %1").arg(QString(strerror(errno))));
        }
        return -1;
    }

    if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
        emit displayError(tr("%1 is no video capture device").arg(m_devName));
        return -1;
    }

    if(!(cap.capabilities & V4L2_CAP_STREAMING))
    {
        emit displayError(tr("%1 does not support streaming i/o").arg(m_devName));
        return -1;
    }

    CLEAR(cropcap);

    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if(0 == ioctl(m_fd, VIDIOC_CROPCAP, &cropcap))
    {
        CLEAR(crop);
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect;

        if(-1 == ioctl(m_fd, VIDIOC_S_CROP, &crop))
        {
            if(EINVAL == errno)
            {
//                emit displayError(tr("VIDIOC_S_CROP not supported")); // 注释
            }
            else
            {
                emit displayError(tr("VIDIOC_S_CROP: %1").arg(QString(strerror(errno))));
                return -1;

            }
        }
    }
    else
    {
        emit displayError(tr("VIDIOC_CROPCAP: %1").arg(QString(strerror(errno))));
        return -1;
    }

    CLEAR(fmt);

    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = 320;
    fmt.fmt.pix.height = 240;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

    if(-1 == ioctl(m_fd, VIDIOC_S_FMT, &fmt))
    {
        emit displayError(tr("VIDIOC_S_FMT").arg(QString(strerror(errno))));
        return -1;
    }

    if(-1 == initMmap())
    {
        return -1;
    }

    return 0;
}


int IMVideoCtrl::initMmap()
{
    v4l2_requestbuffers req;
    CLEAR(req);

    req.count = 4;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if(-1 == ioctl(m_fd, VIDIOC_REQBUFS, &req))
    {
        if(EINVAL == errno)
        {
            emit displayError(tr("%1 does not support memory mapping").arg(m_devName));
            return -1;
        }
        else
        {
            emit displayError(tr("VIDIOC_REQBUFS %1").arg(QString(strerror(errno))));
            return -1;
        }
    }

    if(req.count < 2)
    {
        emit displayError(tr("Insufficient buffer memory on %1").arg(m_devName));
        return -1;
    }

    m_buffers = (buffer*)calloc(req.count, sizeof(*m_buffers));

    if(!m_buffers)
    {
        emit displayError(tr("out of memory"));
        return -1;
    }

    for(m_nBuffers = 0; m_nBuffers < req.count; ++m_nBuffers)
    {
        v4l2_buffer buf;
        CLEAR(buf);

        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = m_nBuffers;

        if(-1 == ioctl(m_fd, VIDIOC_QUERYBUF, &buf))
        {
            emit displayError(tr("VIDIOC_QUERYBUF: %1").arg(QString(strerror(errno))));
            return -1;
        }

        m_buffers[m_nBuffers].m_length = buf.length;
        m_buffers[m_nBuffers].m_start =
                mmap(NULL, // start anywhere
                     buf.length,
                     PROT_READ | PROT_WRITE,
                     MAP_SHARED,
                     m_fd, buf.m.offset);

        if(MAP_FAILED == m_buffers[m_nBuffers].m_start)
        {
            emit displayError(tr("mmap %1").arg(QString(strerror(errno))));
            return -1;
        }
    }
    return 0;
}

int IMVideoCtrl::startCapturing()
{
    unsigned int i;
    for(i = 0; i < m_nBuffers; ++i)
    {
        v4l2_buffer buf;
        CLEAR(buf);

        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory =V4L2_MEMORY_MMAP;
        buf.index = i;
//        fprintf(stderr, "m_nBuffers: %d\n", i);

        if(-1 == ioctl(m_fd, VIDIOC_QBUF, &buf))
        {
            emit displayError(tr("VIDIOC_QBUF: %1").arg(QString(strerror(errno))));
            return -1;
        }
    }

    v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if(-1 == ioctl(m_fd, VIDIOC_STREAMON, &type))
    {
        emit displayError(tr("VIDIOC_STREAMON: %1").arg(QString(strerror(errno))));
        return -1;
    }
    return 0;
}


int IMVideoCtrl::stopCapturing()
{
    v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if(-1 == ioctl(m_fd, VIDIOC_STREAMOFF, &type))
    {
        emit displayError(tr("VIDIOC_STREAMOFF: %1").arg(QString(strerror(errno))));
        return -1;
    }
    return 0;
}

int IMVideoCtrl::uninitDevice()
{
    unsigned int i;
    for(i = 0; i < m_nBuffers; ++i)
    {
        if(-1 == munmap(m_buffers[i].m_start, m_buffers[i].m_length))
        {
            emit displayError(tr("munmap: %1").arg(QString(strerror(errno))));
            return -1;
        }

    }
    free(m_buffers);
    return 0;
}

int IMVideoCtrl::getFrame(void **frame_buf, size_t* len)
{
    v4l2_buffer queue_buf;
    CLEAR(queue_buf);

    queue_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    queue_buf.memory = V4L2_MEMORY_MMAP;

    if(-1 == ioctl(m_fd, VIDIOC_DQBUF, &queue_buf))
    {
        switch(errno)
        {
        case EAGAIN:
//            perror("dqbuf");
            return -1;
        case EIO:
            return -1 ;
        default:
            emit displayError(tr("VIDIOC_DQBUF: %1").arg(QString(strerror(errno))));
            return -1;
        }
    }

    *frame_buf = m_buffers[queue_buf.index].m_start;
    *len = m_buffers[queue_buf.index].m_length;
    m_index = queue_buf.index;

    return 0;

}

int IMVideoCtrl::ungetFrame()
{
    if(m_index != -1)
    {
        v4l2_buffer queue_buf;
        CLEAR(queue_buf);

        queue_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        queue_buf.memory = V4L2_MEMORY_MMAP;
        queue_buf.index = m_index;

        if(-1 == ioctl(m_fd, VIDIOC_QBUF, &queue_buf))
        {
            emit displayError(tr("VIDIOC_QBUF: %1").arg(QString(strerror(errno))));
            return -1;
        }
        return 0;
    }
    return -1;
}

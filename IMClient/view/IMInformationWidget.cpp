#include "IMInformationWidget.h"
#include "CustomLineEdit.h"
#include "IMMainWidget.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

IMInformationWidget::IMInformationWidget(IMMainWidget *mainWidget, QWidget *parent) :
    QWidget(parent)
{
    m_mainWidget = mainWidget;
    initIMLoginWidget();

    connect(m_btnCancel, SIGNAL(clicked()),
        this, SLOT(onClickCancelButton()));
    connect(m_btnOk, SIGNAL(clicked()),
        this, SLOT(onClickOKButton()));
    connect(m_btnNext, SIGNAL(clicked()),
        this, SLOT(onClickNextButton()));
    connect(m_btnPre, SIGNAL(clicked()),
        this, SLOT(onClickPretButton()));

    setWindowTitle(tr("个人信息"));
}

IMInformationWidget::~IMInformationWidget()
{}

void IMInformationWidget::setReadOnly(bool isReadOnly, bool isEdit)
{
    m_isReadOnly = isReadOnly;
    m_isEdit = isEdit;
    m_leUserID->setReadOnly(true);
    m_leNickname->setReadOnly(isReadOnly);
    m_cbxSex->setEnabled(!isReadOnly);
//    m_leBirthday->setReadOnly(isReadOnly);
    m_leBirthday->setEnabled(!isReadOnly);
    m_leName->setReadOnly(isReadOnly);
    m_lePhone->setReadOnly(isReadOnly);
    m_leAddress->setReadOnly(isReadOnly);
    m_btnPre->setVisible(!isReadOnly);
    m_btnNext->setVisible(!isReadOnly);

    m_btnOk->setVisible(isEdit);

    if (isEdit)
    {
        if (isReadOnly)
        {
            m_btnCancel->setText(tr("关闭"));
            m_btnOk->setText(tr("编辑"));
        }
        else
        {
            m_btnCancel->setText(tr("取消"));
            m_btnOk->setText(tr("保存"));
        }
    }
    else
    {
        m_btnCancel->setText(tr("关闭"));
    }
}

//void IMInformationWidget::setWrite()
//{}

void IMInformationWidget::setUserInformation(const UserInformation &user)
{
    m_userInf = user;
    m_leUserID->setText(m_userInf.m_userID);
    m_leNickname->setText(m_userInf.m_nickname);
    if (0 == m_userInf.m_sex.compare("男"))
        m_cbxSex->setCurrentIndex(0);
    else
        m_cbxSex->setCurrentIndex(1);
    m_leBirthday->setText(m_userInf.m_birthday.toString("yyyy-MM-dd"));
    m_leName->setText(m_userInf.m_name);
    m_lePhone->setText(m_userInf.m_phone);
    m_leAddress->setText(m_userInf.m_address);

    m_headNum = m_userInf.m_headPortrait;
    QString labelStr = QString("头像: %1 / %2").arg(QString::number(m_headNum)).
        arg(QString::number(MAX_NUM));
    QString str = QString("QFrame#avatar{border-image:url(resource/image/head/%1.bmp)}")
        .arg(QString::number(m_headNum));
    m_frameHead->setStyleSheet(str);
    if (m_isEdit)
        m_labelHead->setText(labelStr);
    else
        m_labelHead->setText(tr("头像"));
}

UserInformation IMInformationWidget::getInformation()
{
//    m_userInf.m_userID
    //            .getDate()
    m_userInf.m_nickname = m_leNickname->text();
    m_userInf.m_sex = m_cbxSex->currentText();
    m_userInf.m_birthday = m_leBirthday->getDate();
    m_userInf.m_name = m_leName->text();
    m_userInf.m_phone = m_lePhone->text();
    m_userInf.m_address = m_leAddress->text();
    m_userInf.m_headPortrait = m_headNum;

    return m_userInf;
}

// protected:----------------------------------------

//聊天窗口关闭槽函数  发送信号 让主窗体删除 map 表项
void IMInformationWidget::closeEvent(QCloseEvent *)//离开时触发的  应该检查窗口是否都关闭了！！
{
//    emit closeChat(secretAddress);
    if (NULL != m_mainWidget)
        m_mainWidget->removeInformationWidget(m_userInf.m_userID);
    //    this->destroyed(0);
}



// public slots:---------------------------------
void IMInformationWidget::onClickCancelButton()
{
    if (!m_isReadOnly)
    {
        setUserInformation(m_userInf);
        setReadOnly(!m_isReadOnly, m_isEdit);
    }
    else
        close();
}

void IMInformationWidget::onClickOKButton()
{
    if (!m_isReadOnly)
    {
        getInformation();
//        emit sendInformation(m_userInf);
        m_mainWidget->changeMyInformation(m_userInf);
    }
    setReadOnly(!m_isReadOnly, true);
}

void IMInformationWidget::onClickPretButton()
{
    --m_headNum;
    if(m_headNum < 1)
        m_headNum = MAX_NUM;
    QString labelStr = QString("头像: %1 / %2").arg(QString::number(m_headNum)).
        arg(QString::number(MAX_NUM));
    QString str = QString("QFrame#avatar{border-image:url(resource/image/head/%1.bmp)}")
        .arg(QString::number(m_headNum));
    m_frameHead->setStyleSheet(str);
    m_labelHead->setText(labelStr);
}

void IMInformationWidget::onClickNextButton()
{
    ++m_headNum;
    if(m_headNum > MAX_NUM)
        m_headNum = 1;
    QString labelStr = QString("头像: %1 / %2").arg(QString::number(m_headNum)).
        arg(QString::number(MAX_NUM));
    QString str = QString("QFrame#avatar{border-image:url(resource/image/head/%1.bmp)}")
        .arg(QString::number(m_headNum));
    m_frameHead->setStyleSheet(str);
    m_labelHead->setText(labelStr);
}

// private:----------------------------------------
void IMInformationWidget::initIMLoginWidget()
{
    m_isReadOnly = true;
    m_isEdit = false;

    // 左边标签
    m_labelUserID = new QLabel(tr("帐号:"));
    m_labelNickname = new QLabel(tr("昵称:"));
    m_labelSex = new QLabel(tr("性别:"));
    m_labelBirthday = new QLabel(tr("生日:"));
    m_labelName = new QLabel(tr("姓名:"));
    m_labelPhone = new QLabel(tr("电话"));
    m_labelAddress = new QLabel(tr("地址"));
    QVBoxLayout *vLayoutLabelLeft= new QVBoxLayout;
    vLayoutLabelLeft->addWidget(m_labelUserID);
    vLayoutLabelLeft->addWidget(m_labelNickname);
    vLayoutLabelLeft->addWidget(m_labelSex);
    vLayoutLabelLeft->addWidget(m_labelBirthday);
    vLayoutLabelLeft->addWidget(m_labelName);
    vLayoutLabelLeft->addWidget(m_labelPhone);
    vLayoutLabelLeft->addWidget(m_labelAddress);

    // 中间区域 信息编辑
    m_leUserID = new QLineEdit;
    m_leNickname = new QLineEdit;
    m_cbxSex = new QComboBox;
    m_cbxSex->addItem(tr("男"));
    m_cbxSex->addItem(tr("女"));
    m_leBirthday = new CustomLineEdit;
    m_leName = new QLineEdit;
    QVBoxLayout *vLayoutEditMid = new QVBoxLayout;
    vLayoutEditMid->addWidget(m_leUserID);
    vLayoutEditMid->addWidget(m_leNickname);
    vLayoutEditMid->addWidget(m_cbxSex);
    vLayoutEditMid->addWidget(m_leBirthday);
    vLayoutEditMid->addWidget(m_leName);

    // 右边 按钮 以及 头像
    m_btnNext = new QPushButton(tr("下一张"));
    m_btnPre = new QPushButton(tr("上一张"));
    QHBoxLayout *hLayoutBtnEdit = new QHBoxLayout;
    hLayoutBtnEdit->addWidget(m_btnPre);
    hLayoutBtnEdit->addWidget(m_btnNext);
    m_btnOk = new QPushButton(tr("编辑"));
    m_btnCancel = new QPushButton(tr("取消"));
    QHBoxLayout *hLayoutBtnHead = new QHBoxLayout;
    hLayoutBtnHead->addWidget(m_btnOk);
    hLayoutBtnHead->addWidget(m_btnCancel);
    m_labelHead = new QLabel(tr("头像"));
    m_frameHead = new QFrame;
//    m_frameHead->setFixedSize(50,50);
    QVBoxLayout *vLayoutRight = new QVBoxLayout;
//    vLayoutRight->addStretch();
    vLayoutRight->addLayout(hLayoutBtnHead);
    vLayoutRight->addWidget(m_labelHead);
    vLayoutRight->addWidget(m_frameHead);
    vLayoutRight->addLayout(hLayoutBtnEdit);
    vLayoutRight->addStretch();
    // 上面整体
    QHBoxLayout *hLayoutTop = new QHBoxLayout;
    hLayoutTop->addLayout(vLayoutEditMid);
    hLayoutTop->addLayout(vLayoutRight);
    hLayoutTop->addStretch();

    // 下面 编辑框
    m_lePhone = new QLineEdit;
    m_leAddress = new QLineEdit;
    QVBoxLayout *vLayoutEditBtm = new QVBoxLayout;
    vLayoutEditBtm->addWidget(m_lePhone);
    vLayoutEditBtm->addWidget(m_leAddress);

    // 右边整体
    QVBoxLayout *vLayoutMainRight = new QVBoxLayout;
    vLayoutMainRight->addLayout(hLayoutTop);
    vLayoutMainRight->addLayout(vLayoutEditBtm);

    // 整体
    QHBoxLayout *hLayoutMain = new QHBoxLayout;
    hLayoutMain->addLayout(vLayoutLabelLeft);
    hLayoutMain->addLayout(vLayoutMainRight);

    setLayout(hLayoutMain);

    setFixedSize(400, 250);

    // 设置背景图片
//    QPalette pal;
//    QPixmap pixmap(":/iamge/information.jpg" );
//    pal.setBrush(QPalette::Window,QBrush(pixmap));
//    setPalette(pal);

    m_frameHead->setFixedSize(40,40);
//    m_frameHead->setObjectName("headFrame");
//    QString str = QString("QFrame#headFrame{border-image:url(resource/image/head/%1.bmp);}")
//            .arg(QString::number(m_myself.m_headPortrait));
//    m_frameHead->setStyleSheet(str);

    m_headNum = 1;
    m_frameHead->setObjectName("avatar");
    QString str = QString("QFrame#avatar{border-image:url(resource/image/head/1.bmp);}");
    m_frameHead->setStyleSheet(str);
    m_labelHead->setText("头像: 1 / 133");
}

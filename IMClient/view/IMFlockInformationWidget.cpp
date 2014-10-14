#include "IMFlockInformationWidget.h"
#include "IMMainWidget.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QMessageBox>


// public: ---------------------------------------
IMFlockInformationWidget::IMFlockInformationWidget(IMMainWidget *mainWidget,
                                                   QWidget *parent) :
    QWidget(parent)
{
    m_mainWidget = mainWidget;
    initIMLoginWidget();
    setWindowTitle(tr("群信息"));

    setReadOnly(true, false);

    connect(m_btnCancel, SIGNAL(clicked()),
        this, SLOT(onClickCancelButton()));
    connect(m_btnOk, SIGNAL(clicked()),
        this, SLOT(onClickOKButton()));
}


IMFlockInformationWidget::~IMFlockInformationWidget()
{
}

void IMFlockInformationWidget::setReadOnly(bool isReadOnly, bool isEdit)
{
    m_isReadOnly = isReadOnly;
    m_isEdit = isEdit;

    m_leFlockID->setReadOnly(true);
    m_leCreatorID->setReadOnly(true);
    m_leCreateDate->setReadOnly(true);

    m_leFlockName->setReadOnly(isReadOnly);
    m_leTheme->setReadOnly(isReadOnly);

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

void IMFlockInformationWidget::setFlockInformation(const FlockInformation & flock)
{
    m_flockInf = flock;
    m_leFlockID->setText(m_flockInf.m_flockID);
    m_leFlockName->setText(m_flockInf.m_flockName);
    m_leTheme->setText(m_flockInf.m_theme);
    m_leCreatorID->setText(m_flockInf.m_creatorID);
    // m_leBirthday->setText(m_userInf.m_birthday.toString("yyyy-MM-dd"));
    m_leCreateDate->setText(m_flockInf.m_createDate.toString("yyyy-MM-dd"));
}

FlockInformation IMFlockInformationWidget::getInformation()
{
    m_flockInf.m_flockName = m_leFlockName->text();
    m_flockInf.m_theme = m_leTheme->text();
    return m_flockInf;
}


// protected:----------------------------------------
void IMFlockInformationWidget::closeEvent(QCloseEvent *)
{
    if (NULL != m_mainWidget)
        m_mainWidget->removeFlockInformationWidget(m_flockInf.m_flockID);
}


// public slots:-------------------------------------------
void IMFlockInformationWidget::onClickCancelButton()
{
    if (!m_isReadOnly)
    {
        setFlockInformation(m_flockInf);
        setReadOnly(!m_isReadOnly, m_isEdit);
    }
    else
        close();
}

void IMFlockInformationWidget::onClickOKButton()
{
    if (!m_isReadOnly)
    {
        getInformation();
        m_mainWidget->changeFlockInformation(m_flockInf);
    }
    setReadOnly(!m_isReadOnly, true);
}


// private:------------------------------------------------
void IMFlockInformationWidget::initIMLoginWidget()
{
    m_isReadOnly = true;
    m_isEdit = false;

    m_labelFlockHead = new QLabel(this);

    QString str = QString(":/images/flock.png");
    QPixmap pixmap;
    QIcon icon(str);
    pixmap = icon.pixmap(QSize(HEAD_BIG_SIZE, HEAD_BIG_SIZE));
    m_labelFlockHead->setPixmap(pixmap);

//    m_labelFlockHead->setPixmap(QPixmap(":/images/flock.png"));
    m_labelFlockName = new QLabel(tr("群名称:"), this);
    m_labelFlockID = new QLabel(tr("群帐号:"), this);
    m_labelTheme = new QLabel(tr("群主题:"), this);
    m_labelCreatorID = new QLabel(tr("创建者帐号:"), this);
    m_labelCreateDate = new QLabel(tr("创建时间:"), this);

    m_leFlockName = new QLineEdit(this);
    m_leFlockID = new QLineEdit(this);
    m_leCreatorID = new QLineEdit(this);
    m_leTheme = new QLineEdit(this);
    m_leCreateDate = new QLineEdit(this);

    m_btnOk = new QPushButton(tr("确定"), this);
    m_btnOk->setFixedWidth(100);
    m_btnOk->setVisible(false);
    m_btnCancel = new QPushButton(tr("关闭"), this);
    m_btnCancel->setFixedWidth(100);

    QGridLayout *gridLayout = new QGridLayout(this);

    gridLayout->addWidget(m_labelFlockID, 0, 0, Qt::AlignRight);
    gridLayout->addWidget(m_leFlockID, 0, 1);
    gridLayout->addWidget(m_labelFlockName, 1, 0, Qt::AlignRight);
    gridLayout->addWidget(m_leFlockName, 1, 1);

    gridLayout->addWidget(m_labelFlockHead, 0, 2, 2, 1);

    gridLayout->addWidget(m_labelCreatorID, 2, 0, Qt::AlignRight);
    gridLayout->addWidget(m_leCreatorID, 2, 1);
    gridLayout->addWidget(m_labelTheme, 3, 0, Qt::AlignRight);
    gridLayout->addWidget(m_leTheme, 3, 1);

    gridLayout->addWidget(m_labelCreateDate, 4, 0, Qt::AlignRight);
    gridLayout->addWidget(m_leCreateDate, 4, 1);

    gridLayout->addWidget(m_btnOk, 5, 1);
    gridLayout->addWidget(m_btnCancel, 5, 0);
    setLayout(gridLayout);

}

#include "IMDiscussionInformationWidget.h"
#include "IMMainWidget.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QMessageBox>

IMDiscussionInformationWidget::IMDiscussionInformationWidget(IMMainWidget *mainWidget,
                                                             QWidget *parent) :
    QWidget(parent)
{
    m_mainWidget = mainWidget;
    initIMLoginWidget();
    setWindowTitle(tr("讨论组信息"));

    setReadOnly(true, false);

    connect(m_btnCancel, SIGNAL(clicked()),
      this, SLOT(onClickCancelButton()));
    connect(m_btnOk, SIGNAL(clicked()),
      this, SLOT(onClickOKButton()));
}


IMDiscussionInformationWidget::~IMDiscussionInformationWidget()
{
}


void IMDiscussionInformationWidget::setReadOnly(bool isReadOnly, bool isEdit)
{
    m_isReadOnly = isReadOnly;
    m_isEdit = isEdit;

    m_leDiscussionID->setReadOnly(true);
    m_leCreatorID->setReadOnly(true);
    m_leCreateDate->setReadOnly(true);

    m_leDiscussionName->setReadOnly(isReadOnly);
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


void IMDiscussionInformationWidget::setDiscussionInformation(
        const DiscussionInformation & discussion)
{
    m_discussionInf = discussion;
    m_leDiscussionID->setText(m_discussionInf.m_discussionID);
    m_leDiscussionName->setText(m_discussionInf.m_discussionName);
    m_leTheme->setText(m_discussionInf.m_theme);
    m_leCreatorID->setText(m_discussionInf.m_creatorID);
    // m_leBirthday->setText(m_userInf.m_birthday.toString("yyyy-MM-dd"));
    m_leCreateDate->setText(m_discussionInf.m_createDate.toString("yyyy-MM-dd"));
}

DiscussionInformation IMDiscussionInformationWidget::getInformation()
{
    m_discussionInf.m_discussionName = m_leDiscussionName->text();
    m_discussionInf.m_theme = m_leTheme->text();
    return m_discussionInf;
}


// protected:--------------------------------------------------------
void IMDiscussionInformationWidget::closeEvent(QCloseEvent *)
{
    if (NULL != m_mainWidget)
        m_mainWidget->removeDiscussionInformationWidget(m_discussionInf.m_discussionID);
}

// public slots:-----------------------------------------------------
void IMDiscussionInformationWidget::onClickCancelButton()
{
    if (!m_isReadOnly)
    {
        setDiscussionInformation(m_discussionInf);
        setReadOnly(!m_isReadOnly, m_isEdit);
    }
    else
        close();
}

void IMDiscussionInformationWidget::onClickOKButton()
{
    if (!m_isReadOnly)
    {
        getInformation();
        m_mainWidget->changeDiscussionInformation(m_discussionInf);
    }
    setReadOnly(!m_isReadOnly, true);
}

// private:-------------------------------------------------------
void IMDiscussionInformationWidget::initIMLoginWidget()
{
    m_isReadOnly = true;
    m_isEdit = false;

    m_labelDiscussionHead = new QLabel(this);

    QString str = QString(":/images/discussion.png");
    QPixmap pixmap;
    QIcon icon(str);
    pixmap = icon.pixmap(QSize(HEAD_BIG_SIZE, HEAD_BIG_SIZE));
    m_labelDiscussionHead->setPixmap(pixmap);

//    m_labelDiscussionHead->setPixmap(QPixmap(":/images/discussion.png"));
    m_labelDiscussionName = new QLabel(tr("讨论组名称:"), this);
    m_labelDiscussionID = new QLabel(tr("讨论组帐号:"), this);
    m_labelTheme = new QLabel(tr("讨论组主题:"), this);
    m_labelCreatorID = new QLabel(tr("创建者帐号:"), this);
    m_labelCreateDate = new QLabel(tr("创建时间:"), this);

    m_leDiscussionName = new QLineEdit(this);
    m_leDiscussionID = new QLineEdit(this);
    m_leCreatorID = new QLineEdit(this);
    m_leTheme = new QLineEdit(this);
    m_leCreateDate = new QLineEdit(this);

    m_btnOk = new QPushButton(tr("确定"), this);
    m_btnOk->setFixedWidth(100);
    m_btnOk->setVisible(false);
    m_btnCancel = new QPushButton(tr("关闭"), this);
    m_btnCancel->setFixedWidth(100);

    QGridLayout *gridLayout = new QGridLayout(this);

    gridLayout->addWidget(m_labelDiscussionID, 0, 0, Qt::AlignRight);
    gridLayout->addWidget(m_leDiscussionID, 0, 1);
    gridLayout->addWidget(m_labelDiscussionName, 1, 0, Qt::AlignRight);
    gridLayout->addWidget(m_leDiscussionName, 1, 1);

    gridLayout->addWidget(m_labelDiscussionHead, 0, 2, 2, 1);

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

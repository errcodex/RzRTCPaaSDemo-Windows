#include "TipDialog.h"
#include <QFile>
#include <QApplication>
TipDialog::TipDialog(QDialog* parent)
    : QDialog(parent)
{
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::Tool);

    QFile qssFile("./resource/tip.qss");
    if (!qssFile.open(QFile::ReadOnly))
        return; //TODO:

    this->setStyleSheet(QString(qssFile.readAll()));
    this->setFixedSize(240, 280);
    qssFile.close();
    drawWindow();
}

TipDialog::~TipDialog()
{
    delete labelHeader;
    delete buttonClose;
    delete info;
}

void TipDialog::setContent(const char* title, const char* content)
{
    labelHeader->setText(QString::fromLocal8Bit(title));
    info->setText(QString::fromLocal8Bit(content));
}

void TipDialog::slotClose()
{
    this->close();
}

void TipDialog::drawWindow()
{
    labelHeader = new QLabel(QString::fromLocal8Bit("ʧ��"), this);
    labelHeader->setObjectName("labelHeader");
    labelHeader->move(20, 20);

    info = new QTextEdit(this);
    info->setObjectName("info");
    info->setGeometry(20, 58, 200, 118);
    info->setEnabled(false);
    info->setText(QString::fromLocal8Bit("��ȡ��������Դʧ��\n�����룺107"));

    buttonClose = new QPushButton(QString::fromLocal8Bit("ȷ��"), this);
    buttonClose->setObjectName("buttonClose");
    buttonClose->move(20, 228);
    connect(buttonClose, SIGNAL(clicked()), this, SLOT(slotClose()));
}

#include "WelcomeUI.h"
#include <QFile>

WelcomeUI::WelcomeUI()
{
	loadStyle();
	this->setFixedSize(1200, 720);
	drawWindow();
	eventRegister();
}

void WelcomeUI::drawWindow()
{
	// labelTitle
	logo = std::make_shared<QLabel>("H264.Demo", this);
	logo->setObjectName("logo");
	logo->move(182, 252);

	cid = std::make_shared<WelcomeUIInputGroup>(this, QString::fromLocal8Bit("频道ID"), 647, 214);
	uid = std::make_shared<WelcomeUIInputGroup>(this, QString::fromLocal8Bit("用户ID"), 647, 279);
	// TODO: delete 2 lines test code behind this
	cid->text("2020");
	uid->text("0101");

	// button
	btnEnter = std::make_shared<QPushButton>(QString::fromLocal8Bit("进入频道"), this);
	btnEnter->setObjectName("btnEnter");
	btnEnter->move(647, 352);

	btnMini = std::make_shared<QPushButton>("_",this);
	btnMini->setObjectName("btnMini");
	btnMini->move(1100, 20);

	btnClose = std::make_shared<QPushButton>("X" ,this);
	btnClose->setObjectName("btnClose");
	btnClose->move(1144, 20);

	splitLine = std::make_shared<QPushButton>(this);
	splitLine->setObjectName("splitLine");
	splitLine->setFocusPolicy(Qt::NoFocus);
	splitLine->setGeometry(567, 223, 1, 160);
}

void WelcomeUI::loadStyle()
{
	QFile windowStyleFile("./resource/welcome.qss");
	if (!windowStyleFile.open(QFile::ReadOnly))
		; //TODO:

	this->setStyleSheet(QString(windowStyleFile.readAll()));
	windowStyleFile.close();
}

void WelcomeUI::eventRegister()
{
	connect(btnEnter.get(), SIGNAL(clicked()), this, SLOT(SlotTryEnter()));
	connect(btnClose.get(), SIGNAL(clicked()), this, SLOT(SlotClose()));
	connect(btnMini.get(), SIGNAL(clicked()), this, SLOT(SlotMini()));
}


WelcomeUIInputGroup::WelcomeUIInputGroup(QWidget* parent, QString text, int x, int y)
{
	title = std::make_shared<QLabel>(text, parent);
	title->setStyleSheet("width: 46px; height: 19px;font-size: 14px;font-weight: bold; text-align: left;color: #ffffff;");
	title->move(x, y);

	tip = std::make_shared<QLabel>(QString::fromLocal8Bit("（请输入") + text + QString::fromLocal8Bit("）"), parent);
	tip->setStyleSheet("font-size: 14px;font-weight: bold;color: #ffa62f;");
	tip->move(x + 46, y);
	tip->hide();

	input = std::make_shared<QLineEdit>(parent);
	input->setStyleSheet("width: 327px;background-color: #1e6ceb;border:none;border-bottom: 1px solid #ffffff;color:white;");
	input->move(x, y + 28);
}

bool WelcomeUIInputGroup::empty() const
{
	return text().isEmpty();
}

void WelcomeUIInputGroup::showTip() const
{
	tip->show();
}

void WelcomeUIInputGroup::hideTip() const
{
	tip->hide();
}

QString&& WelcomeUIInputGroup::text() const
{
	return input->text();
}

void WelcomeUIInputGroup::text(const QString s) const
{
	input->setText(s);
}

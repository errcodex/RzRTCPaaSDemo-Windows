#include "ChannelUI.h"
#include <QFile>
#include "VideoCapture.h"
#include "SlotMgr.h"

ChannelUI::ChannelUI() : WindowInterface(nullptr, 0, 0, 1400, 60)
{
	loadStyle();
	this->setFixedSize(1400, 768);
	drawWindow();
	eventRegister();
}

void ChannelUI::drawWindow()
{
	btnMini = std::make_shared<QPushButton>("_", this);
	btnMini->setObjectName("btnMini");
	btnMini->move(1296, 20);

	btnClose = std::make_shared<QPushButton>("X", this);
	btnClose->setObjectName("btnClose");
	btnClose->move(1340, 20);

	self = std::make_shared<ChannelUIVideoCanvas>(this, QString::fromLocal8Bit("0101(我)"), 100, 60);
	remote = std::make_shared<ChannelUIVideoCanvas>(this, "0202", 700, 60);
}

void ChannelUI::loadStyle()
{
	QFile windowStyleFile("./resource/channel.qss");
	if (!windowStyleFile.open(QFile::ReadOnly))
		; //TODO:

	this->setStyleSheet(QString(windowStyleFile.readAll()));
	windowStyleFile.close();
}

void ChannelUI::setChannel(QString s)
{
	channel->setText(QString::fromLocal8Bit("频道ID：") + s);
}

void ChannelUI::eventRegister()
{
	connectionList.push_back(connect(btnClose.get(), SIGNAL(clicked()), this, SLOT(SlotClose())));
	connectionList.push_back(connect(btnMini.get(), SIGNAL(clicked()), this, SLOT(SlotMini())));

	// 视频数据回调
	connectionList.push_back(connect(SlotMgr::instance(), &SlotMgrSingleton::YuvData, this, &ChannelUI::SlotVideoData));
	connectionList.push_back(connect(SlotMgr::instance(), &SlotMgrSingleton::RemoteYuvData, this, &ChannelUI::SlotRemoteVideoData));
	VideoCapture::instance()->start();
}

void ChannelUI::eventdisRegister()
{
	// 断开所有信号槽的连接
	for_each(connectionList.begin(), connectionList.end(), [](QMetaObject::Connection c) {
		disconnect(c);
	});
}

ChannelUIVideoCanvas::ChannelUIVideoCanvas(QWidget* parent, QString text, int x, int y) : QWidget(parent)
{
	move(x, y);
	video = std::make_shared<GLYuvWidget>(this);
	video->setGeometry(0, 0, 600, 448);

	uid = std::make_shared<QLabel>(text, this);
	uid->setStyleSheet("width: 46px; height: 19px;font-size: 14px;font-weight: bold; text-align: left;color: #ffffff;");
	uid->setText(text);
	uid->move(12, 7);

	onYuvData = std::bind(&GLYuvWidget::SlotShowYuv, video, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

void ChannelUIVideoCanvas::setUid(QString uid)
{
	this->uid->setText(uid);
}

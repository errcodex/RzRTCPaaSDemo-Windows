#pragma once

#include "WindowInterface.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QOpenGLWidget>
#include "GLYuvWidget.h"
class ChannelUIVideoCanvas;

class ChannelUI : public WindowInterface
{
	Q_OBJECT
public:
	ChannelUI();
	~ChannelUI() = default;

	void setChannel(QString s);

private:
	void eventRegister();
	void eventdisRegister();
	virtual void drawWindow() override;
	virtual void loadStyle() override;

private:
	std::shared_ptr<QLabel> channel;
	std::shared_ptr<QPushButton> btnEnter, btnClose, btnMini, splitLine;
	std::shared_ptr<ChannelUIVideoCanvas> self, remote;
	std::vector<QMetaObject::Connection> connectionList;

private slots:
	void SlotClose();
	void SlotMini();
	void SlotVideoData(const QByteArray& arr, const uint w, const uint h);
	void SlotRemoteVideoData(const QByteArray& arr, const uint w, const uint h);
};

// µ¥¸öÊÓÆµ
class ChannelUIVideoCanvas : public QWidget
{
public:
	ChannelUIVideoCanvas(QWidget* parent = nullptr, QString text = "", int x = 0, int y = 0);
	void setUid(QString uid);
	std::function<void(const QByteArray&, const uint, const uint)> onYuvData;

private:
	std::shared_ptr<QLabel> uid;
	std::shared_ptr<GLYuvWidget> video;
};
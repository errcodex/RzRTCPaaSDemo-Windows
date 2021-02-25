#include "WelcomeUI.h"
#include "ChannelUI.h"
#include "StreamH264Demo.h"
#include "VideoCapture.h"
#include "RTC.h"
void WelcomeUI::SlotTryEnter() {
	uid->hideTip();
	cid->hideTip();
	if (uid->empty() || cid->empty()) {
		if (uid->empty())
			uid->showTip();
		if (cid->empty())
			cid->showTip();
		return;
	}
	// TODO:
	if (!RTC::instance()->CreateChannel("2020") || !RTC::instance()->JoinChannel("0101"))
	{
		return;
	}
	this->hide();
	StreamH264Demo::instance()->createWindow(H264_WINDOW::CHANNEL)->show();
}

void WelcomeUI::SlotClose()
{
	hide();
	RTC::release();
	close();
}

void WelcomeUI::SlotMini()
{
	showMinimized();
}

void ChannelUI::SlotClose()
{
	hide();
	VideoCapture::instance()->stop();
	RTC::instance()->LeaveChannel();
	StreamH264Demo::instance()->releaseWindow(H264_WINDOW::CHANNEL);
	StreamH264Demo::instance()->getWindow(H264_WINDOW::WELCOME)->show();
}

void ChannelUI::SlotMini()
{
	showMinimized();
}

void ChannelUI::SlotVideoData(const QByteArray& arr, const uint w, const uint h)
{
	self->onYuvData(arr, w, h);
}

void ChannelUI::SlotRemoteVideoData(const QByteArray& arr, const uint w, const uint h)
{
	remote->onYuvData(arr, w, h);
}

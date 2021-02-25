#include "MyChannelEventHandler.h"
#include "RTC.h"

void MyChannelEventHandler::onError(rz::IRtcChannel* channel, int err, const char* msg)
{
	return;
}

void MyChannelEventHandler::onJoinChannelSuccess(rz::IRtcChannel* channel, const char* uid, int elapsed)
{
	RTC::instance()->Publish();
}

void MyChannelEventHandler::onUserJoined(rz::IRtcChannel* channel, const char* uid, int elapsed)
{
	RTC::instance()->SetRemoteVideoSink(uid);
}


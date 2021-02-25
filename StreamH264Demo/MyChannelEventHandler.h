#pragma once
#include <IRtcChannelEventHandler.h>

class MyChannelEventHandler : public rz::IRtcChannelEventHandler
{
	virtual void onError(rz::IRtcChannel* channel, int err, const char* msg);

	virtual void onJoinChannelSuccess(rz::IRtcChannel* channel, const char* uid, int elapsed);

	virtual void onUserJoined(rz::IRtcChannel* channel, const char* uid, int elapsed);
};
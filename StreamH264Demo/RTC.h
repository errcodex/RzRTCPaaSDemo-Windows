#pragma once
#include "SingletonGC.h"
#include "IRtcEngine.h"
#include "CustomVideoSource.h"
#include "MyChannelEventHandler.h"
#include "CustomVideoSink.h"
#include "VideoConvertor.h"

// ÉùÃ÷µ¥ÀýÀàStreamH264Demo
class RTCSingleton;
typedef SingletonGC<RTCSingleton> RTC;

class RTCSingleton : public SingletonBase<RTCSingleton>
{
	friend RTC;

public:
	bool CreateChannel(std::string cid);
	bool JoinChannel(std::string cid);
	void SetRemoteVideoSink(std::string uid);
	void Publish();
	void LeaveChannel();
	VideoConvertor* GetVideoConvertor();
protected:
	RTCSingleton();
	~RTCSingleton();

private:
	const static char* appID;
	std::shared_ptr<rz::IRtcEngineEventHandler> engineEventHandler;
	std::shared_ptr<rz::IRtcStreamEventHandler> streamEventHandler;
	std::shared_ptr<MyChannelEventHandler> channelEventHandler;
	std::shared_ptr<CustomVideoSource> videoSource;
	std::shared_ptr<CustomVideoSink> videoSink;
	rz::IRtcEngine* engine = nullptr;
	rz::IRtcChannel* channel = nullptr;
	rz::IRtcStream* stream = nullptr;
	
	std::shared_ptr<VideoConvertor> videoConvertor;
};

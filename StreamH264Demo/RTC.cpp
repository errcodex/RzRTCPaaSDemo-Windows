#include "RTC.h"
const char* RTCSingleton::appID = "Drv4Q0KB14Y85qma";

bool RTCSingleton::CreateChannel(std::string cid)
{
	if (channel)
		return false;

	channel = engine->createChannel(rz::CHANNEL_PROFILE_COMMUNICATION, cid.c_str(), channelEventHandler.get());

	// cid is invalid
	if (!channel)
		return false;

	stream = channel->createVideoStream("first", videoSource.get(), rz::VIDEO_STREAM_H264, streamEventHandler.get(), rz::VideoEncoderConfiguration{ 1280, 720, 1200, 1200, 15, 15 });

	return true;
}

bool RTCSingleton::JoinChannel(std::string uid)
{
	if (!channel)
		return false;

	// 先离开频道，防止因特殊原因没退出频道
	channel->leaveChannel();

	int ret = channel->joinChannel(uid.c_str());

	if (ret == 0)
		return true;
	//TODO:
	//if (ret < 0)
	//{
	//	if (ret == -2)
	//		showTipDialog(nullptr, "加入频道失败", "当前用户ID不合法");
	//	else if (ret == -3)
	//		showTipDialog(nullptr, "加入频道失败", "用于已加入频道或调用被拒绝");
	//	else
	//		showTipDialog(nullptr, "加入频道失败", "未知错误");
	//	return false;
	//}
	return false;
}

void RTCSingleton::SetRemoteVideoSink(std::string uid)
{
	channel->setRemoteVideoSink(uid.c_str(), "first", videoSink.get());
}

void RTCSingleton::Publish()
{
	channel->publish(rz::PUBLISH_AUDIO);
	stream->publish();
}

void RTCSingleton::LeaveChannel()
{
	if (!channel)
		return;
	channel->leaveChannel();
	channel->release();
	//stream->release();
	channel = nullptr;
}

VideoConvertor* RTCSingleton::GetVideoConvertor()
{
	if (!videoConvertor)
		videoConvertor = std::make_shared<VideoConvertor>();
	return videoConvertor.get();
}

RTCSingleton::RTCSingleton()
{
	engineEventHandler = std::make_shared<rz::IRtcEngineEventHandler>();
	streamEventHandler = std::make_shared<rz::IRtcStreamEventHandler>();
	channelEventHandler = std::make_shared<MyChannelEventHandler>();
	videoSource = std::make_shared<CustomVideoSource>();
	videoSink = std::make_shared<CustomVideoSink>();

	rz::RtcEngineContext ctx{ appID, engineEventHandler.get() };
	engine = rz::createRZRtcEngine(ctx);
	if (!engine)
		return;

	if (engine->enableLocalVideo(true) < 0)
	{
		//TODO:
		//showTipDialog(nullptr, "初始化失败", "启用本地视频设备失败");
	}

	if (engine->enableLocalAudio(true) < 0)
	{
		//TODO:
		//showTipDialog(nullptr, "初始化失败", "启用本地视音频设备失败");
	}
}

RTCSingleton::~RTCSingleton()
{
	if (engine)
		engine->release(true);
	//TODO: 是否要释放其他对象的空间得看engine->release是否已经释放过
	engine = nullptr;
}

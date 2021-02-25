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

	// ���뿪Ƶ������ֹ������ԭ��û�˳�Ƶ��
	channel->leaveChannel();

	int ret = channel->joinChannel(uid.c_str());

	if (ret == 0)
		return true;
	//TODO:
	//if (ret < 0)
	//{
	//	if (ret == -2)
	//		showTipDialog(nullptr, "����Ƶ��ʧ��", "��ǰ�û�ID���Ϸ�");
	//	else if (ret == -3)
	//		showTipDialog(nullptr, "����Ƶ��ʧ��", "�����Ѽ���Ƶ������ñ��ܾ�");
	//	else
	//		showTipDialog(nullptr, "����Ƶ��ʧ��", "δ֪����");
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
		//showTipDialog(nullptr, "��ʼ��ʧ��", "���ñ�����Ƶ�豸ʧ��");
	}

	if (engine->enableLocalAudio(true) < 0)
	{
		//TODO:
		//showTipDialog(nullptr, "��ʼ��ʧ��", "���ñ�������Ƶ�豸ʧ��");
	}
}

RTCSingleton::~RTCSingleton()
{
	if (engine)
		engine->release(true);
	//TODO: �Ƿ�Ҫ�ͷ���������Ŀռ�ÿ�engine->release�Ƿ��Ѿ��ͷŹ�
	engine = nullptr;
}

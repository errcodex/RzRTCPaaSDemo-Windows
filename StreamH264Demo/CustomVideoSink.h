#pragma once
#include "IMediaSink.h"

class CustomVideoSink :public rz::IVideoSink
{
	// Í¨¹ý IVideoSink ¼Ì³Ð
	virtual bool onInitialize() override;
	virtual bool onStart() override;
	virtual void onStop() override;
	virtual void onDispose() override;
	virtual rz::VideoSinkConfig getSinkConfig() override;
	virtual void consumeVideoFrame(const unsigned char* buffer, rz::VIDEO_PIXEL_FORMAT frameType, int width, int height, long timestamp) override;
	virtual void consumeVideoPacket(const unsigned char* buffer, long length, rz::VIDEO_STREAM_TYPE streamType, bool isKey, long timestamp) override;
};

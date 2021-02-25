#include "CustomVideoSource.h"
#include "VideoCapture.h"
#include <Windows.h>
#include "RTC.h"

bool CustomVideoSource::onInitialize(rz::IVideoFrameConsumer* consumer)
{
	this->consumer = consumer;
	return true;
}

void CustomVideoSource::onDispose()
{
	this->consumer = nullptr;
}

int CustomVideoSource::onStart()
{
	VideoCapture::instance()->yuvCB = std::bind(&CustomVideoSource::onVideoData, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	return 0;
}

void CustomVideoSource::onStop()
{
	VideoCapture::instance()->yuvCB = nullptr;
}

void CustomVideoSource::onVideoData(const uint8_t* yuvData, const int w, const int h) const
{
	//consumer->consumeVideoFrame(yuvData, rz::VIDEO_PIXEL_I420, w, h, GetTickCount());
	static uint8_t* out = nullptr; //TODO: release *out
	int size;
	bool iskey;
	RTC::instance()->GetVideoConvertor()->encode(yuvData, &out, size, iskey);
	consumer->consumeVideoPacket(out, size, rz::VIDEO_STREAM_FRAME, iskey, GetTickCount());
}

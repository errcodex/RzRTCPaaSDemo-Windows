#include "CustomVideoSink.h"
#include "SlotMgr.h"
#include "RTC.h"
bool CustomVideoSink::onInitialize()
{
	return true;
}

bool CustomVideoSink::onStart()
{
	return true;
}

void CustomVideoSink::onStop()
{
}

void CustomVideoSink::onDispose()
{
}

rz::VideoSinkConfig CustomVideoSink::getSinkConfig()
{
	return rz::VideoSinkConfig{ rz::VIDEO_STREAM_H264, rz::VIDEO_PIXEL_UNAVILABLE };
}

void CustomVideoSink::consumeVideoFrame(const unsigned char* buffer, rz::VIDEO_PIXEL_FORMAT frameType, int width, int height, long timestamp)
{
	QByteArray arr((char*)buffer, width * height * 3 / 2);
	QMetaObject::invokeMethod(SlotMgr::instance(), "RemoteYuvData", Qt::DirectConnection, Q_ARG(const QByteArray&, arr), Q_ARG(uint, width), Q_ARG(uint, height));
}

void CustomVideoSink::consumeVideoPacket(const unsigned char* buffer, long length, rz::VIDEO_STREAM_TYPE streamType, bool isKey, long timestamp)
{
	RTC::instance()->GetVideoConvertor()->decode(buffer, length, [](uint8_t* data, int width, int height) {
		QByteArray arr((char*)data, width * height * 3 / 2);
		QMetaObject::invokeMethod(SlotMgr::instance(), "RemoteYuvData", Qt::DirectConnection, Q_ARG(const QByteArray&, arr), Q_ARG(uint, width), Q_ARG(uint, height));
	});
}

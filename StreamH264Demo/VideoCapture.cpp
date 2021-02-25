#include "VideoCapture.h"
#include "videoInput.h"
#include "libyuv.h"
#include <QByteArray>
#include <QMetaObject>
#include "SlotMgr.h"
void VideoCaptureSingleton::start()
{
	if (running)
		return;

	if (th.joinable())
		th.join();

	th = std::thread(&VideoCaptureSingleton::work, this);

	running = true;
}

void VideoCaptureSingleton::stop()
{
	running = false;
	if (th.joinable())
		th.join();
}

void VideoCaptureSingleton::work()
{
	videoInput vi;
	std::vector<std::string> deviceList = vi.getDeviceList();
	if (deviceList.empty())
		return;

	uint8_t deviceIdx = 0;
	vi.setupDevice(deviceIdx, 1920, 1080);
	if (!vi.isDeviceSetup(0))
	{
		// print
		return;
	}

	int width = vi.getWidth(deviceIdx);
	int height = vi.getHeight(deviceIdx);
	int size = vi.getSize(deviceIdx);

	std::shared_ptr<uint8_t[]> rgbData(new uint8_t[size]);
	uint8_t* rgbBuffer = rgbData.get();
	std::shared_ptr<uint8_t[]> yuvData(new uint8_t[width * height * 3 / 2]);
	uint8_t* yuvBuffer = yuvData.get();

	int noFrameCount = 0;
	while (running)
	{
		if (noFrameCount > 100)
		{
			// TODO: error
			running = false;
			break;
		}

		if (!vi.isFrameNew(deviceIdx))
		{
			Sleep(50);
			++noFrameCount;
			continue;
		}
		noFrameCount = 0;

		if (!vi.getPixels(deviceIdx, rgbBuffer, true, true))
		{
			Sleep(5);
			continue;
		}

		libyuv::RGB24ToI420(rgbBuffer, width * 3, yuvBuffer, width, yuvBuffer + height * width * 5 / 4, width / 2, yuvBuffer + height * width, width / 2, width, height);

		// 本地显示
		QByteArray arr((char*)yuvBuffer, width * height * 3 / 2);
		QMetaObject::invokeMethod(SlotMgr::instance(), "YuvData", Qt::DirectConnection, Q_ARG(const QByteArray&, arr), Q_ARG(const uint, width), Q_ARG(const uint, height));
		
		// 自定义源
		if (yuvCB)
			yuvCB(yuvBuffer, width, height);
	}

	running = false;
	vi.stopDevice(deviceIdx);
}

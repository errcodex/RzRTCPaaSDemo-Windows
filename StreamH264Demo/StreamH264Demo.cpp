#include "StreamH264Demo.h"
#include "WelcomeUI.h"
#include "ChannelUI.h"

void StreamH264DemoSingleton::initialize()
{
}

void StreamH264DemoSingleton::release()
{
}

QWidget* StreamH264DemoSingleton::getWindow(H264_WINDOW e)
{
	auto it = windowList.find(e);
	if (it == windowList.end())
		return nullptr;
	return it->second.get();
}

void StreamH264DemoSingleton::releaseWindow(H264_WINDOW e)
{
	QWidget* w = getWindow(e);
	if (w == nullptr)
		return;
	w->close();
	windowList.erase(e);
}

QWidget* StreamH264DemoSingleton::createWindow(H264_WINDOW e)
{
	if (getWindow(e) == nullptr)
		switch (e)
		{
		case H264_WINDOW::WELCOME:
			windowList[e] = std::make_shared<WelcomeUI>();
			break;
		case H264_WINDOW::CHANNEL:
			windowList[e] = std::make_shared<ChannelUI>();
			break;
		}

	return getWindow(e);
}

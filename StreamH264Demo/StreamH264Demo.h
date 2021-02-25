#pragma once
#include "SingletonGC.h"
#include "WindowInterface.h"
#include <map>

// ����������StreamH264Demo
class StreamH264DemoSingleton;
typedef SingletonGC<StreamH264DemoSingleton> StreamH264Demo;

class QWidget;

// Demo ���д���
enum class H264_WINDOW
{
	WELCOME,
	CHANNEL,
};

class StreamH264DemoSingleton : public SingletonBase<StreamH264DemoSingleton>
{
	friend StreamH264Demo;

public:
	void initialize();
	void release();
	QWidget* getWindow(H264_WINDOW e);
	void releaseWindow(H264_WINDOW e);
	QWidget* createWindow(H264_WINDOW e);

protected:
	StreamH264DemoSingleton() = default;

private:
	std::map<enum H264_WINDOW, std::shared_ptr<WindowInterface>> windowList;
};
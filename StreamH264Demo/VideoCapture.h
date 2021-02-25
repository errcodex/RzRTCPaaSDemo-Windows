#pragma once
#include "SingletonGC.h"
#include <functional>
// ÉùÃ÷µ¥ÀıÀàVideoCapture
class VideoCaptureSingleton;
typedef SingletonGC<VideoCaptureSingleton> VideoCapture;

class VideoCaptureSingleton : public SingletonBase<VideoCaptureSingleton>
{
	friend VideoCapture;

public:
	void start();
	void stop();
	std::function<void(uint8_t*, int, int)> yuvCB = nullptr;

protected:
	VideoCaptureSingleton() = default;

private:
	void work();

private:
	volatile bool running = false;
	std::thread th;
};
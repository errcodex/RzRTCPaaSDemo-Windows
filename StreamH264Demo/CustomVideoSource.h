#pragma once
#include "IMediaSource.h"

class CustomVideoSource : public rz::IVideoSource
{
public:
private:
	// ͨ�� IVideoSource �̳�
	virtual bool onInitialize(rz::IVideoFrameConsumer* consumer) override;
	virtual void onDispose() override;
	virtual int onStart() override;
	virtual void onStop() override;
	void onVideoData(const uint8_t* yuvData, const int w, const int h) const;

private:
	rz::IVideoFrameConsumer* consumer = nullptr;
};

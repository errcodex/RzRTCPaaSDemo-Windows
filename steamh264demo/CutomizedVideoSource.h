#pragma once
/*
* �Զ�����Ƶ��Ⱦ���ݽӿ�
* 
*/
#include <mutex>
#include <thread>
#include <queue>
#include "IMediaSource.h"
using namespace rz;

class CutomizedVideoSource : public IVideoSource
{
public:
    /**
      *��ƵԴ��ʼ���ص�
      *SDK �������һ����SDKʵ�ֵ� IVideoFrameConsumer ���󡣱���ö��󣬲�����ƵԴ������ͨ������������Ƶ֡���� SDK����� IVideoFrameConsumer��
      *
      *return value
      *true: �Զ������ƵԴ�Ѿ�����˳�ʼ��������
      *false: �Զ������ƵԴ�豸û׼���û��߳�ʼ��ʧ�ܣ�SDK ��ͣ�������ϱ�����
      */
    virtual bool onInitialize(IVideoFrameConsumer* consumer) override;

    /**
    *�ͷ���ƵԴ�ص���
    *SDK �����ûص�������ر���ƵԴ�豸���ûص�֪ͨ�� SDK �������� IVideoFrameConsumer ���� �յ��ûص�������ȷ������ʹ�� IVideoFrameConsumer ����
    */
    virtual void onDispose() override;

    /**
    *������ƵԴ�ص���
    *SDK �����ûص�������������Ƶ֡�ɼ��������ɹ���SDK ��� IVideoFrameConsumer �Ŀ��أ�������ɼ�����Ƶ֡�� ����Ҫͨ������ֵ��֪ SDK �Զ������ƵԴ�Ƿ��Ѿ��ɹ�������
    */
    virtual int onStart() override;

    /**
    *ֹͣ��ƵԴ�ص���
    *SDK �����ûص�������ֹͣ��Ƶ֡�ɼ����ûص�֪ͨ�� IVideoFrameConsumer �Ŀ��صļ����رգ�SDK ���������֮��ɼ�����Ƶ֡��
    */
    virtual void onStop() override;
    void SetParams(const std::string& channelId, const std::string &streamName);
public:
    void onVideoData(uint8_t* y, int w, int h);

private:
    IVideoFrameConsumer* m_pConsumer = nullptr;
    std::mutex m_mutex;
    volatile bool m_isStart = false;
    std::condition_variable m_cv;
    uint64_t m_last = 0;
    std::string m_strChannelId;
    std::string m_strStreamName;
};

#pragma once
#include "IMediaSink.h"

class CustomizedVideoSink : public rz::IVideoSink
{
public:
    /**
        *��ʼ����Ⱦ����
        *Media Engine ��ʼ����Ⱦ����ʱ��������������
        *�����߿������������������Ⱦ���ĳ�ʼ������������Ǻ�ʱ������Ҳ������ǰ��ʼ���ã�Ȼ������������и�֪ Media Engine �Զ�����Ⱦ���ѳ�ʼ���á��÷�����Ҫ�������Լ����� true �� false���Ը�֪ Media Engine �Զ�����Ⱦ����״̬��
        *
        *return value
        *true��Media Engine ����Ϊ�Զ������Ⱦ���Ѿ���ʼ����
        *false��Media Engine ����Ϊ�Զ������Ⱦ����ʼ��ʧ�ܣ���������������
        */
    virtual bool onInitialize() override;

    /**
        *������Ⱦ����
        *Media Engine �ڿ�����Ⱦ���ܵ�ʱ���ص���������������߿��������������������Ⱦ�����÷�����Ҫ���������� true �� false��Media Engine ����ݷ���ֵ����Ӧ�Ķ�����
        *
        *����
        *true��Media Engine ����������Ⱦ
        *false��Media Engine ��Ϊ�����ֹͣ��Ⱦ���Ĺ���
        */
    virtual bool onStart() override;

    /**
        *ֹͣ��Ⱦ����
        *Media Engine ��ֹͣ��Ⱦ���ܵ�ʱ���ص���������������߿��������������ֹͣ��Ⱦ��
        */
    virtual void onStop() override;

    /**
        *�ͷ���Ⱦ����
        *Media Engine ֪ͨ��������Ⱦ���������������� onDispose() ����֮�󣬿����߾Ϳ����ͷŵ���Դ�ˡ�
        */
    virtual void onDispose() override;

    /**
         * ��ȡ��Ⱦ����Ҫ�����ݸ�ʽ
         * @return ��Ƶ��Ⱦ����Ҫ�����ݸ�ʽ
         */
    virtual rz::VideoSinkConfig getSinkConfig() override;

    virtual void consumeVideoFrame(const unsigned char* buffer, rz::VIDEO_PIXEL_FORMAT frameType, int width, int height, long timestamp) override;

    void consumeVideoPacket(const unsigned char* buffer, long length, rz::VIDEO_STREAM_TYPE streamType, bool isKey, long timestamp) override;
    
};

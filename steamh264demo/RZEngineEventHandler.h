#pragma once
#include "RtcEngineEventHandler.h"

class RZEngineEventHandler : public rz::IRtcEngineEventHandler
{
public:
    RZEngineEventHandler();
    ~RZEngineEventHandler();

    // ������Ƶ״̬�����ı�ص�����
    // ������Ƶ��״̬�����ı�ʱ������������˷�¼��״̬����Ƶ����״̬���� SDK �ᴥ���ûص����浱ǰ�ı�����Ƶ״̬��
    virtual void onLocalAudioStateChanged(rz::LOCAL_AUDIO_STREAM_STATE state, rz::LOCAL_AUDIO_STREAM_ERROR error) override;

    // �ѷ���������Ƶ��֡�ص�.
    virtual void onFirstLocalAudioFramePublished(int elapsed) override;
};
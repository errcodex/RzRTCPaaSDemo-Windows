#pragma once
#include "IRtcChannelEventHandler.h"

class RZRtcChannelEventHandler : public rz::IRtcChannelEventHandler
{
public:
    RZRtcChannelEventHandler();
    ~RZRtcChannelEventHandler();

    // ע�� onJoinChannelSuccess �ص���
    // �����û��ɹ�����Ƶ��ʱ���ᴥ���ûص���
    virtual void onJoinChannelSuccess(rz::IRtcChannel* rtcChannel, const char* uid, int elapsed) override;

    // ע�� onLeaveChannel �ص���
    // �����û��ɹ��뿪Ƶ��ʱ���ᴥ���ûص���
    virtual void onLeaveChannel(rz::IRtcChannel* rtcChannel, const rz::RtcStats& stat) override;

    // ע�� onFirstRemoteVideoDecoded �ص���
    // SDK ���յ���һ֡Զ����Ƶ���ɹ�����ʱ���ᴥ���ûص���
    // �����ڸûص��е��� setupRemoteVideo ��������Զ����ͼ��
    virtual void onFirstRemoteVideoFrame(rz::IRtcChannel* rtcChannel, const char* uid, const char* streamName, int width, int height, int elapsed) override;

    // ע�� onUserOffline �ص���
    // Զ���û��뿪Ƶ�������ʱ���ᴥ���ûص���
    virtual void onUserOffline(rz::IRtcChannel* rtcChannel, const char* uid, rz::USER_OFFLINE_REASON_TYPE reason) override;


    virtual void onUserJoined(rz::IRtcChannel* channel, const char* uid, int elapsed) override;


    virtual void onError(rz::IRtcChannel* channel, int err, const char* msg) override;
};

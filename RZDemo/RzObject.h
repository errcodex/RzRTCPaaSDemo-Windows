#pragma once
#include <QObject>
#include <QString>
#include <IRtcEngine.h>
#include "PrivateIRtcChannelEventHandler.h"
#include "PrivateIRtcEngineEventHandler.h"
#include "PrivateIRtcStreamEventHandler.h"
using namespace rz;

#define APPID_DEV "2020112714291613322098613675048981332168688175226882"
#define APPID_PRD "Drv4Q0KB14Y85qma"
#define ENV_CONFIG "{\"api\":\"https://api.rzrtc.com\",\"log\":\"http://data-center.duobeiyun.com\"}"
class RzObject : QObject
{
	Q_OBJECT
public:
	static RzObject* instance();
	IRtcEngine* GetIRtcEngine();	//����Ƶ��ǰ�ٴ���
	IRtcStream* GetIRtcStream1();
	IRtcStream* GetIRtcStream2();
	IRtcChannel* GetIRtcChannel();
public:
	bool init();	//true: ��Ҫ���´�����false ����Ҫ���´���
	int JoinChannel();
	int EnableLocalAudio(bool enabled);
	int EnableLocalVideo(bool enabled);
	int MuteLocalVideoStream(bool mute, QString streamName = "");
	int MuteLocalAudioStream(bool mute);
	int SetupLocalVideo(VideoCanvas& canvas, QString streamName = "");
	int SetupRemoteVideo(QString uid, QString streamName, VideoCanvas& canvas);
	
	int Publish();
	int UnPublish();
	int SetClientRole(CLIENT_ROLE_TYPE role);
	int MuteAllRemoteVideoStreams(bool mute);
	int MuteAllRemoteAudioStreams(bool mute);
	int SetLocalRenderMode();
	int SetRemoteRenderMode(QString uid, QString streamName/*, RENDER_MODE_TYPE renderMode,
		VIDEO_MIRROR_MODE_TYPE mirrorMode*/);
	//HD
	int SetRemoteVideoStreamType(QString uid, QString streamName, bool type);

	int SetVideoResolution(QString resolution);
	int SetVideoFrameRate(QString frameRate);
	int SetVideoDir(QString dir);
	int SetVideoPushStreamMode(QString mode);
	int SetVideoMirror(bool enable);	//TODO������

	int GetCamDeviceCount();
	int GetCamDevice(int index, QString& deviceName, QString& deviceId);	//ĳ���豸
	int GetCamDevice(QString& deviceId); //��ǰ�豸
	int SetCamDevice(QString deviceId);

	int GetMicDeviceCount();
	int GetMicDevice(int index, QString& deviceName, QString& deviceId);	//ĳ���豸
	int GetMicDevice(QString& deviceId); //��ǰ�豸
	int SetMicDevice(QString deviceId);
	int GetMicVolume();

	int GetSpeakerDeviceCount();
	int GetSpeakerDevice(int index, QString& deviceName, QString& deviceId);	//ĳ���豸
	int GetSpeakerDevice(QString& deviceId); //��ǰ�豸
	int SetSpeakerDevice(QString deviceId);

	RENDER_MODE_TYPE GetRenderMode();

	int StartLastmileProbeTest();
	int StopLastmileProbeTest();

	void Release();

	void Reset();
public:
	bool isSelfPubStream();
	bool isSelfRender();
	bool isAudience();

private:
	void getSdkParams();
	void setSdkParams();
private:
	static RzObject* m_pRzObject;
	IRtcEngine* m_pIRtcEngine = nullptr;
	IRtcChannel* m_pIRtcChannel = nullptr;
	IRtcStream* m_pIRtcStream = nullptr;
	IRtcStream* m_pIRtcStream2 = nullptr;
	PrivateIRtcEngineEventHandler* m_pPrivateIRtcEngineEventHandler = nullptr;
	PrivateIRtcChannelEventHandler* m_pPrivateIRtcChannelEventHandler = nullptr;
	PrivateIRtcStreamEventHandler* m_pPrivateIRtcStreamEventHandler1 = nullptr;
	PrivateIRtcStreamEventHandler* m_pPrivateIRtcStreamEventHandler2 = nullptr;
	QString m_strAppId = APPID_DEV;
	QString m_strEnv;
	int m_nCodecPriority = 0;
	CHANNEL_PROFILE_TYPE m_profile = CHANNEL_PROFILE_COMMUNICATION;
	CLIENT_ROLE_TYPE m_role;
	std::string m_strChannelId;
	std::string m_strUid;

	bool m_isStreamDual = false;	//Ĭ�ϻ����Զ����һ·
	bool m_isStreamDual2 = false;	//Ĭ�ϻ����Զ����һ·
	QString m_strStreamResolution = "1280*720";	//Ĭ�ϻ����Զ����һ·
	QString m_strStream2Resolution = "1280*720";

	ORIENTATION_MODE m_orientationMode = ORIENTATION_MODE_ADAPTIVE;	//Ĭ�ϻ����Զ����һ·���뷽��
	ORIENTATION_MODE m_orientationMode2 = ORIENTATION_MODE_ADAPTIVE;

	int m_nFrameRate = 15;
	int m_nFrameRate2 = 15;
	bool m_isEnableCam = false;
	bool m_isEnableMic = false;
	bool m_isEnableSpeaker = false;

	//����Ĭ���Ƿ���
	bool m_isDefMuteAllAudio = true;
	bool m_isDefMuteAllVideo = true;

	//�ݲ�����
	bool m_isMuteAllVideo = false;
	bool m_isMuteAllAudio = false;

	RENDER_MODE_TYPE m_renderMode;
	VIDEO_MIRROR_MODE_TYPE m_mirrorMode;
	RtcEngineContext m_ctx;
};

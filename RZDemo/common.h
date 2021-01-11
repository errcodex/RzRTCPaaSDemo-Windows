#pragma once
#include <QMap>

//static QMap<QString, QString> s_ConfigMap{ 
//		{QString::fromLocal8Bit("���Ի���"), "0"},
//		{QString::fromLocal8Bit("��ʽ����"), "34"},
//		{QString::fromLocal8Bit("�Զ��廷��"), "34"},
//		{QString::fromLocal8Bit("��������ģʽ"), "34"},
//		{QString::fromLocal8Bit("Ӳ�������ģʽ"), "34"},
//		{QString::fromLocal8Bit("������Ⱦ��"), "34"},
//		{QString::fromLocal8Bit("�Զ�����Ⱦ��"), "34"},
//		{QString::fromLocal8Bit("�ȱ�����"), "34"},
//		{QString::fromLocal8Bit("���"), "34"},
//		{QString::fromLocal8Bit("����"), "34"},
//		{QString::fromLocal8Bit("����"), "34"},
//		{QString::fromLocal8Bit("˫��"), "34"},
//		{QString::fromLocal8Bit("120 * 120"), "34"},
//		{QString::fromLocal8Bit("160 * 120"), "34"},
//		{QString::fromLocal8Bit("180 * 120"), "34"},
//		{QString::fromLocal8Bit("240 * 180"), "34"},
//		{QString::fromLocal8Bit("320 * 180"), "34"},
//		{QString::fromLocal8Bit("240 * 240"), "34"},
//		{QString::fromLocal8Bit("320 * 240"), "34"},
//		{QString::fromLocal8Bit("424 * 240"), "34"},
//		{QString::fromLocal8Bit("360 * 360"), "34"},
//		{QString::fromLocal8Bit("480 * 360"), "34"},
//		{QString::fromLocal8Bit("640 * 360"), "34"},
//		{QString::fromLocal8Bit("480 * 480"), "34"},
//		{QString::fromLocal8Bit("640 * 480"), "34"},
//		{QString::fromLocal8Bit("840 * 360"), "34"},
//		{QString::fromLocal8Bit("960 * 720"), "34"},
//		{QString::fromLocal8Bit("1280 * 720"), "34"},
//		{QString::fromLocal8Bit("1920 * 1080"), "34"},
//		{QString::fromLocal8Bit("7 FPS"), "34"},
//		{QString::fromLocal8Bit("15 FPS"), "34"},
//		{QString::fromLocal8Bit("25 FPS"), "34"},
//		{QString::fromLocal8Bit("30 FPS"), "34"}
//};

//QStringList itemTextLst;
//itemTextLst << " *120" << "120 * 120" << "160 * 120" << ""


static QMap<QString, QString> s_ConfigMap{
		{"TestEnv", QString::fromLocal8Bit("���Ի���")},
		{"Codec", QString::fromLocal8Bit("�����")},
		{"RenderDevice", QString::fromLocal8Bit("��Ⱦ��")},
		{"RenderMode", QString::fromLocal8Bit("��Ⱦ��ʽ")}
};

enum E_BING_TYPE {
	e_bind_role,
	e_bind_receive_a_stream,
	e_bind_receive_v_stream,
	e_bind_render_mode, 
	e_bind_open_log,
	e_bind_select_cam,
	e_bind_select_mic,
	e_bind_select_speaker, 
	e_bind_stream1_resolution, 
	e_bind_stream1_framerate, 
	e_bind_stream1_direction,
	e_bind_stream1_pushstreammode, 
	e_bind_stream1_mirror_mode,
	e_bind_stream2_resolution,
	e_bind_stream2_framerate,
	e_bind_stream2_direction,
	e_bind_stream2_pushstreammode,
	e_bind_stream2_mirror_mode
};
enum E_REMOTE_INFO_TYPE { 
	e_re_user_id,
	e_re_user_stream,
	e_re_video,
	e_re_video_state,
	e_re_resolution,
	e_re_resolution_value,
	e_re_framerate,
	e_re_framerate_value,
	e_re_audio,
	e_re_audio_state,
	e_re_volume,
	e_re_volume_value,
	e_re_bit,
	e_re_bit_value,
	e_re_loss,
	e_re_loss_value,
	e_re_netquality,
	e_re_netquality_value
};

enum E_SELECT_LIST_TYPE {
	e_select_device_cam,
	e_select_device_mic,
	e_select_device_speaker,
	e_select_device_render_mode,
	e_select_stream1_resolution,
	e_select_stream1_fps,
	e_select_stream1_pushstreammode,
	e_select_stream1_encodedir,
	e_select_stream1_mirror,
	e_select_stream2_resolution,
	e_select_stream2_fps,
	e_select_stream2_pushstreammode,
	e_select_stream2_encodedir,
	e_select_stream2_mirror
};

enum E_VIDEO_ITEM_TYPE {
	e_local_user,
	e_remote_user,
	e_init
};

typedef struct STREAMINFO_ {
	std::string uid;
	std::string streamName;
	STREAMINFO_() {}
	STREAMINFO_(std::string uid, std::string streamName)
	{
		this->uid = uid;
		this->streamName = streamName;
	}
	bool operator < (const STREAMINFO_& a) const
	{
		if (this->uid < a.uid || (this->uid == a.uid && this->streamName < a.streamName)) 
		{
			return true;
		}
		return false;
	}
} STREAMINFO;


typedef struct VIDEOFRAMESIZE_
{
	int w = 0;
	int h = 0;
	VIDEOFRAMESIZE_() {}
	VIDEOFRAMESIZE_(int w, int h)
	{
		this->w = w;
		this->h = h;
	}
}VIDEOFRAMESIZE;


typedef struct AUDIOVOLUMEINFO_
{
	QString uid;
	QString channelid;
	int volume;
	int vad;

}AUDIOVOLUMEINFO;

typedef struct REMOTEVIDEOSTATS_
{
	QString uid;                                         //�û�ID
	QString streamName;                                  //������
	int width = 0;                                                     //��Ƶ�������أ���
	int height = 0;                                                    //��Ƶ���ߣ����أ���
	int receivedBitrate = 0;                                           //���ϴ�ͳ�ƺ󣩵Ľ�������(Kbps)��
	int decoderOutputFrameRate = 0;                                    //Զ����Ƶ�����������֡�ʣ���λΪ fps��
	int packetLossRate = 0;                                            //Զ����Ƶ��ʹ�ÿ���������֮��Ķ�����(%)��
	int totalFrozenTime = 0;                                           //����Ƶ�����Զ����Ƶ��������Ƶ���ٵ��ۼ�ʱ����ms����ͨ�������У���Ƶ֡�����ò����� 5 fps ʱ��������Ⱦ����֡��Ƶ֮�������� 500 ms�����Ϊһ����Ƶ���١�
	int frozenRate = 0;                                                //����Ƶ�����Զ����Ƶ��������Ƶ���ٵ��ۼ�ʱ��ռ��Ƶ����Чʱ���İٷֱ� (%)����Ƶ��Чʱ����ָԶ���û�����Ƶ������Ƶδ��ֹͣ���ͻ���յ�ʱ����
	int totalActiveTime = 0;                                           //��Ƶ��Чʱ�������룩����Զ���û�/��������Ƶ����û��ֹͣ������Ƶ����ͨ��ʱ����
	int publishDuration = 0;
}REMOTEVIDEOSTATS;
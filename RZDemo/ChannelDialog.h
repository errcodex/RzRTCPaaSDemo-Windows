#pragma once

#include <QDialog>
#include "ui_ChannelDialog.h"
#include "MainVideoItemBgDialog.h"
#include <IRtcEngineState.h>
#include "VideoItem.h"
#include "MoreInfoDialog.h"
using namespace rz;
class ChannelDialog : public QDialog
{
	Q_OBJECT

public:
	ChannelDialog(QWidget *parent = Q_NULLPTR);
	~ChannelDialog();
signals:
	void SigBack(int, int); //���ص�¼ҳ��
public slots:
	//�˵���
	void SlotBack();
	void SlotMin();
	void SlotMax();
	void SlotClose();
	void SlotMoreInfo();
	//��ƵItem�Ŵ�
	//�û�������
	void SlotUserJoined(const QString& channelid, const QString& uid, int elapsed);
	void SlotUserOffline(const QString& channelid, const QString& uid, USER_OFFLINE_REASON_TYPE reason);
	
	void SlotRejoinChannelSuccess(const QString& channelid, const QString& uid, int elapsed);
	void SlotLeaveChannel(const QString& channelid, const RtcStats& stats);
	void SlotConnectionLost(const QString& channelid);
	void SlotConnectionStateChanged(const QString& channelid, CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason);
	//�����·����Ƶ���ڶ�·�����ߵ����������canvas
	void SlotVideoSubscribeStateChanged(const QString& channelid, const QString& uid, const QString& streamName, SUBSCRIBE_STREAM_STATE state, int elapsed);
	//���� ����
	void SlotWarning(int warn, const QString& msg);
	void SlotError(int err, const QString& msg);

	void SlotWarning(const QString& channelid, int warn, const QString& msg);
	
	void SlotError(const QString& chnnelid, int err, const QString& msg);
	//������Ⱦ��ʽ
	void SlotRenderMode();
	void SlotLossLeave();	//����ǿ���˳�
	void SlotRtcStats(QString channelid, const RtcStats& stats);
	//TEST
	void SlotDelItem();
	void SlotTimer();

protected:
	void changeEvent(QEvent* event) override;
	void showEvent(QShowEvent* event) override;
	void closeEvent(QCloseEvent* event) override;
private:
	void initStyleSheetFile();
	void initTableWidget();
	void initConnect();
	void initInfo();
	void initVideoItem();
	void initUserCount();
	void initMoreInfoDialog();
private:
	VideoItem* addVideoItem(QString channelid, QString uid, QString streamName);
	void delVideoItem(QString channelid, QString uid, QString streamName, bool isAll = false);
	void getItemIndex(int oldrow, int oldcolum, int& row, int& column);	//item�ƶ��󣬻�ȡ�µ�λ�� ��ʱ����
	VideoItem* getVideoItem(int row, int column);//��ʱ����
	bool getLastItemInfo(E_VIDEO_ITEM_TYPE& type, QString& channelid, QString& uid, QString& streamName);
	VideoItem* getVideoItem(QString uid, QString streamName);
	bool isVideoItemExist(QString uid);
	//�л�������
	void moveItem();
	VideoItem* moveVideoItem(int idx, E_VIDEO_ITEM_TYPE type, QString channelid, QString uid, QString streamName);
	void showTipDialog(int error, QString msg);
private:
	Ui::ChannelDialog ui;

	MainVideoItemBgDialog* m_pMainVideoItemBgDialog = nullptr;
	QString m_strChannelId;
	QString m_strUid;
	int m_nVideoCount = 0;
	MoreInfoDialog* m_pMoreInfoDialog = nullptr;
	bool m_isIgnoreCloseEvent = true;
};

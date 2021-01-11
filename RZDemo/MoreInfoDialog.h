#pragma once

#include <QDialog>
#include "ui_MoreInfoDialog.h"
#include <QListWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QStringList>
#include <QTabBar>
#include <QSize>
#include "common.h"
#include "UserStateSingleton.h"
class MoreInfoDialog : public QDialog
{
	Q_OBJECT
public:
	MoreInfoDialog(QWidget *parent = Q_NULLPTR);
	~MoreInfoDialog();
signals:
	void SigRenderMode();
public slots:
	void SlotClose();

	void SlotSelectCam();
	void SlotSelectMic();
	void SlotSelectSpeaker();

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* ev) override;
	void paintEvent(QPaintEvent* event) override;

private:
	void init();
	void initStyleSheetFile();
	void initTabWidget();
	void initListStreamSet();
	void initConnect();
	void initSdkParams();
	void initRemoteStats(QString uid, QString streamName);
private:
	void setTab(QTabBar* bar, int index, QString text, QString label1style, QString label2style);
	//Ƶ������
	void SetListChannelSetUid(QListWidget* lst, QString iconText, QString valueText);
	void SetListChannelSetSwitchRole(QListWidget* lst, QString iconText, QString valueText, QString bgcolor);
	void SetListSwitchButton(QListWidget* lst, QString iconText, E_BING_TYPE type, QString bgcolor, bool isEnabled = false);	//������ť
	void SetListChannelSetLog(QListWidget* lst, QString iconText, QString labelText);
	//��������
	void SetListComboBoxSelect(QListWidget* lst, QString iconText, QString buttonValue, E_BING_TYPE type, QString bgcolor = "background-color:white;");	//����combobox
	//�û���Ϣ
	void SetListRemoteUserInfo(QListWidget* lst, E_REMOTE_INFO_TYPE type);
	//��ʼ����������
	void SetParams();
	void BindSlot(QWidget* bt, E_BING_TYPE);
	void SetScene(QString& scene, QString& role);

	//��ȡ��Ӧ��list��
	void UpdateRemoteUserInfoInList(E_REMOTE_INFO_TYPE type, QString uid, QString streamid, QString value);
	void UpdateRemoteUserInfoInList(E_REMOTE_INFO_TYPE type, QString uid, QString value);
	void UpdateRemoteUserDefaultObjectName(QString uid, QString streamid);
	//Զ���û����߶�Ӧ��·�����ߣ�ɾ����Ӧ����Ϣ
	void AddRemoteUserInfoList(QString uid);
	void DelRemoteUserAllInfoList(QString uid);
	void DelRemoteUserInfoInList(QString uid, QString streamid);
	bool isRemoteUserExist(QString uid);
	bool isRemoteStreamExist(QString uid, QString streamName);
private:
	Ui::MoreInfoDialog ui;
	QString m_strStyle1;
	QString m_strStyle2;
	QString m_strStyle3;
	QString m_strStyle4;
	QStringList m_bgColorLst;
	QMap<E_REMOTE_INFO_TYPE, QString> m_remoteUserStyleMap;
	QMap<E_REMOTE_INFO_TYPE, QString> m_remoteUserBgColorMap;
	QMap<E_REMOTE_INFO_TYPE, QSize> m_remoteUserSizeMap;
	QMap<E_REMOTE_INFO_TYPE, QString> m_remoteUserAttrNameMap;
	QMap<E_REMOTE_INFO_TYPE, QString> m_remoteUserAttrValueMap;
	QMap<E_REMOTE_INFO_TYPE, int> m_remoteUserLeftPaddingMap;	//���label paddding
	
	QString m_strUid;
	QString m_strChannelId;
};

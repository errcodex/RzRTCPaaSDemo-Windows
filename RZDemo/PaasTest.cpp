#include "PaasTest.h"
#include <QDebug>
#include <QFileInfo>
#include <QFile>
#include <QTimer>
#include "ChannelDialog.h"
#include "Settings.h"
#include "UserStateSingleton.h"
#include "RzObject.h"
#include "LoadingDialog.h"
#include <QMessageBox>
#include "LostDialog.h"
PaasTest::PaasTest(QWidget *parent)
    : QDialog(parent)
{
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    ui.setupUi(this);
	init();
}

void PaasTest::SlotMin()
{
	this->showMinimized();
}

void PaasTest::SlotClose()
{
	RzObject::instance()->Release();
	this->close();
}

void PaasTest::SlotReEnter(int x, int y)
{
	//TODO::���³�ʼ��sdk 
	initSdk();
	initStyleSheetFile();
	initUserInfo();
	this->show();
}

void PaasTest::SlotLoading()
{
	if (judgeInfo() == false)
		return;

	this->hide();

	int ret = RzObject::instance()->JoinChannel();
	if (ret != 0)
	{
		this->show();
		if(ret == -2)
			showTipDialog(ret, "");
		return;
	}
		
	QVariant value;
	Settings::instance()->Read("scene", value, "SceneMode");
	if (value.toString() != QString::fromLocal8Bit("ֱ������"))
	{
		Settings::instance()->Read("mic", value, "Device");
		bool isMicOpen = value.toString() == QString::fromLocal8Bit("�ر���˷�") ? false : true;
		RzObject::instance()->EnableLocalAudio(isMicOpen);
		Settings::instance()->Read("cam", value, "Device");
		bool isCamOpen = value.toString() == QString::fromLocal8Bit("�ر�����ͷ") ? false : true;
		RzObject::instance()->EnableLocalVideo(isCamOpen);
	}

	//LoadingDialog dlg;
	//connect(this, SIGNAL(SigCloseLoading()), &dlg, SLOT(SlotClose()));
	//connect(UserStateNotifySingleton::instance(), SIGNAL(SigCloseSigtonDlg()), &dlg, SLOT(SlotClose()));
	//dlg.exec();
}

void PaasTest::SlotJoinChannel()
{
	this->hide();
	ChannelDialog dlg;
	connect(&dlg, SIGNAL(SigBack(int, int)), this, SLOT(SlotReEnter(int, int)));
	dlg.exec();
}

void PaasTest::SlotLossLeave()
{
	if (RzObject::instance()->GetIRtcChannel() == nullptr)
		return;
	int ret = RzObject::instance()->GetIRtcChannel()->leaveChannel();
	RzObject::instance()->EnableLocalAudio(false);
	RzObject::instance()->EnableLocalVideo(false);
	UserStateSingleton::instance()->Clear();
}

void PaasTest::SlotWarning(int warn, const QString& msg)
{

}

void PaasTest::SlotError(int err, const QString& msg)
{
	LostDialog dlg;
	connect(&dlg, SIGNAL(SigBack()), this, SLOT(SlotLossLeave()));
	dlg.setFixedSize(this->width(), this->height());
	dlg.setGeometry(this->x(), this->y(), dlg.width(), dlg.height());
	dlg.SetButton(QString::fromLocal8Bit("ȷ��"));
	switch (err)
	{
	case 101:
	{
		//dlg.SetText(QString::fromLocal8Bit("����Ƶ��ʧ��"), QString::fromLocal8Bit("��ǰƵ�� ID ���Ϸ�"));
		//dlg.exec();
		break;
	}
	case 102:
	{
		dlg.SetText(QString::fromLocal8Bit("����Ƶ��ʧ��"), QString::fromLocal8Bit("��ǰ Appid ���Ϸ�"));
		dlg.exec();
		break;
	}
	case 103:
	{
		dlg.SetText(QString::fromLocal8Bit("����Ƶ��ʧ��"), QString::fromLocal8Bit("��ǰƵ�� ID ���Ϸ�"));
		dlg.exec();
		break;
	}
	case 104:
	{
		dlg.SetText(QString::fromLocal8Bit("����Ƶ��ʧ��"), QString::fromLocal8Bit("��ȡ��������Դʧ��\n �����룺104"));
		dlg.exec();
		break;
	}
	case 105:
	{
		dlg.SetText(QString::fromLocal8Bit("�����룺%1").arg(err), msg);
		dlg.exec();
		break;
	}
	case 106:
	{
		dlg.SetText(QString::fromLocal8Bit("�����룺%1").arg(err), msg);
		dlg.exec();
		break;
	}
	case 107:
	{
		dlg.SetText(QString::fromLocal8Bit("�����룺%1").arg(err), msg);
		dlg.exec();
		break;
	}
	default:
		break;
	}
	
	qDebug() << "PaasTest::SlotError " << msg;
}

void PaasTest::SlotError(const QString& channelid, int err, const QString& msg)
{
	this->show();
	LostDialog dlg;
	connect(&dlg, SIGNAL(SigBack()), this, SLOT(SlotLossLeave()));
	dlg.setFixedSize(this->width(), this->height());
	dlg.setGeometry(this->x(), this->y(), dlg.width(), dlg.height());
	dlg.SetButton(QString::fromLocal8Bit("ȷ��"));
	switch (err)
	{
	case 104:
	case 106:
	case 107:
	{
		dlg.SetText(QString::fromLocal8Bit("����Ƶ��ʧ��"), QString::fromLocal8Bit("��ȡ��������Դʧ��\n �����룺104"));
		dlg.exec();
		break;
	}
	
	default:
		break;
	}
}

void PaasTest::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_leftButtonPressed = true;
		m_start = event->globalPos();
		m_clickPos = event->pos();
	}
	//qDebug() << "this->width = " << this->width() << "  this->height = " << this->height();
}

void PaasTest::SlotJoinChannelSuccess(const QString& channelid, const QString& uid, int elapsed)
{
	QVariant value;
	Settings::instance()->Read("channel", value, "Info");
	if (channelid != value.toString()) return;
	Settings::instance()->Read("user", value, "Info");
	if (uid != value.toString()) return;

	//this->hide();
	emit SigCloseLoading();

	//UserStateSingleton::instance()->SetProcessData(QString::fromLocal8Bit("����Ƶ���ɹ���"));

	RzObject::instance()->Publish();
	ChannelDialog dlg;
	connect(&dlg, SIGNAL(SigBack(int, int)), this, SLOT(SlotReEnter(int, int)));
	dlg.exec();
}

void PaasTest::SlotConnectionStateChanged(const QString& channelid, CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason)
{
	/*
	* TODO
	* CONNECTION_CHANGED_REJECTED_BY_SERVER ����
	*/
	switch (state)
	{
	case rz::CONNECTION_STATE_DISCONNECTED:
	{
		//UserStateSingleton::instance()->SetProcessData(QString::fromLocal8Bit("�������ӶϿ�"));
		break;
	}
	case rz::CONNECTION_STATE_CONNECTING:
	{
		//UserStateSingleton::instance()->SetProcessData(QString::fromLocal8Bit("��������������"));
		break;
	}
	case rz::CONNECTION_STATE_CONNECTED:
	{
		//UserStateSingleton::instance()->SetProcessData(QString::fromLocal8Bit("����������."));
		break;
	}
	case rz::CONNECTION_STATE_RECONNECTING:
	{
		//UserStateSingleton::instance()->SetProcessData(QString::fromLocal8Bit("���½�������������..."));
		break;
	}
	case rz::CONNECTION_STATE_FAILED:
	{
		QString str = QString::fromLocal8Bit("��������ʧ��");
		switch (reason)
		{
		case rz::CONNECTION_CHANGED_CONNECTING:
		{
			str = QString::fromLocal8Bit("��������ʧ��, ԭ�򣺽�������������");
			break;
		}

		case rz::CONNECTION_CHANGED_JOIN_SUCCESS:
		{
			str = QString::fromLocal8Bit("��������ʧ��, ԭ�򣺳ɹ�����Ƶ��");
			break;
		}
		case rz::CONNECTION_CHANGED_INTERRUPTED:
		{
			str = QString::fromLocal8Bit("��������ʧ��, ԭ�����������ж�");
			break;
		}
		case rz::CONNECTION_CHANGED_BANNED_BY_SERVER:
		{
			str = QString::fromLocal8Bit("��������ʧ��, ԭ���������ӱ���������ֹ");
			break;
		}
		case rz::CONNECTION_CHANGED_JOIN_FAILED:
		{
			str = QString::fromLocal8Bit("��������ʧ��, ԭ�����������ѳ�ʱ");
			LostDialog dlg;
			dlg.SetText(QString::fromLocal8Bit("�ѶϿ�����"), QString::fromLocal8Bit("���������ѳ�ʱ���뷵�ص�¼�����ԡ�"));
			connect(&dlg, SIGNAL(SigBack()), this, SLOT(SlotLossLeave()));
			dlg.setFixedSize(this->width(), this->height());
			dlg.setGeometry(this->x(), this->y(), dlg.width(), dlg.height());
			dlg.exec();
			break;
		}
		case rz::CONNECTION_CHANGED_LEAVE_CHANNEL:
		{
			str = QString::fromLocal8Bit("��������ʧ��, ԭ���뿪Ƶ��");
			break;
		}
		case rz::CONNECTION_CHANGED_INVALID_CHANNEL_ID:
		{
			str = QString::fromLocal8Bit("��������ʧ��, ԭ�򣺲�����Ч��Ƶ��ID");
			break;
		}
		case rz::CONNECTION_CHANGED_REJECTED_BY_SERVER:
		{
			LostDialog dlg;
			QString str1 = QString::fromLocal8Bit("��⵽���������豸��¼���뷵�ص�¼��");
			QString str2 = QString::fromLocal8Bit("���ԡ�");
			dlg.SetText(QString::fromLocal8Bit("�ѶϿ�����"), str1, str2);
			connect(&dlg, SIGNAL(SigBack()), this, SLOT(SlotLossLeave()));
			dlg.setFixedSize(this->width(), this->height());
			dlg.setGeometry(this->x(), this->y(), dlg.width(), dlg.height());
			dlg.exec();
			break;
		}
		case rz::CONNECTION_CHANGED_CLIENT_IP_ADDRESS_CHANGED:
		{
			str = QString::fromLocal8Bit("��������ʧ��, ԭ�򣺿ͻ��� IP ��ַ���");
			break;
		}
		case rz::CONNECTION_CHANGED_KEEP_ALIVE_TIMEOUT:
		{
			str = QString::fromLocal8Bit("��������ʧ��, ԭ��SDK �ͷ��������ӱ��ʱ");
			break;
		}
		case rz::CONNECTION_CHANGED_INVALID_APP_ID:
		{
			str = QString::fromLocal8Bit("��������ʧ��, ԭ�򣺲�����Ч�� APP ID");
			LostDialog dlg;
			dlg.SetText(QString::fromLocal8Bit("�ѶϿ�����"), QString::fromLocal8Bit("APPID����"));
			connect(&dlg, SIGNAL(SigBack()), this, SLOT(SlotLossLeave()));
			dlg.setFixedSize(this->width(), this->height());
			dlg.setGeometry(this->x(), this->y(), dlg.width(), dlg.height());
			dlg.exec();
			break;
		}
		default:
			break;
		}
		//UserStateSingleton::instance()->SetProcessData(str);
		break;
	}
	default:
		break;
	}
}

void PaasTest::mouseMoveEvent(QMouseEvent* event)
{
	if (m_leftButtonPressed)
	{
		move(event->globalPos() - m_clickPos);
		m_start = event->globalPos();
	}
	//qDebug() << "this->width = " << this->width() << "  this->height = " << this->height();
}

void PaasTest::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_leftButtonPressed = false;
	}
	
	//qDebug() << "this->width = " << this->width() << "  this->height = " << this->height();
}

void PaasTest::closeEvent(QCloseEvent* event)
{
	if (this->isHidden())
		return;
	else
	{
		RzObject::instance()->Release();
		this->close();
	}
}

void PaasTest::init()
{
	UserStateNotifySingleton::instance();
	UserStateSingleton::instance();
	initStyleSheetFile();
	initUserInfo();
	initConnect();
	initSdk();
	RzObject::instance()->StartLastmileProbeTest();
	QTimer::singleShot(10*1000, this, SLOT(SlotTimer()));
}


void PaasTest::initStyleSheetFile()
{
	QFile styleFile("./resource/login.qss");
	QFileInfo fileInfo("./resource/login.qss");
	//QString str = fileInfo.absolutePath();

	styleFile.open(QIODevice::ReadOnly);
	this->setStyleSheet(QString(styleFile.readAll()));
}

void PaasTest::initUserInfo()
{
	ui.label_channelid_tip->hide();
	ui.label_uid_tip->hide();
	QVariant value;
	Settings::instance()->Read("channel", value, "Info");
	if (value.toString().isEmpty() == false)
		ui.lineEdit_channelid->setText(value.toString());
	value.clear();
	Settings::instance()->Read("user", value, "Info");
	if (value.toString().isEmpty() == false)
		ui.lineEdit_uid->setText(value.toString());
}

void PaasTest::initConnect()
{
	connect(ui.pushButton_join, SIGNAL(clicked()), this, SLOT(SlotLoading()));
	connect(ui.pushButton_min, SIGNAL(clicked()), this, SLOT(SlotMin()));
	connect(ui.pushButton_close, SIGNAL(clicked()), this, SLOT(SlotClose()));
	
	connect(UserStateNotifySingleton::instance(), SIGNAL(SigJoinChannelSuccess(const QString&, const QString&, int)), this, SLOT(SlotJoinChannelSuccess(const QString&, const QString&, int)));
	connect(UserStateNotifySingleton::instance(), SIGNAL(SigWarning(int, const QString&)), this, SLOT(SlotWarning(int, const QString&)));
	connect(UserStateNotifySingleton::instance(), SIGNAL(SigError(int, const QString&)), this, SLOT(SlotError(int, const QString&)));
	connect(UserStateNotifySingleton::instance(), SIGNAL(SigError(const QString&, int, const QString&)), this, SLOT(SlotError(const QString&, int, const QString&)));
	connect(UserStateNotifySingleton::instance(), SIGNAL(SigConnectionStateChanged(const QString&, CONNECTION_STATE_TYPE, CONNECTION_CHANGED_REASON_TYPE)), this, SLOT(SlotConnectionStateChanged(const QString&, CONNECTION_STATE_TYPE, CONNECTION_CHANGED_REASON_TYPE)));
}

void PaasTest::initSdk()
{
	RzObject::instance()->init();
	RzObject::instance()->GetIRtcEngine();
}

bool PaasTest::judgeInfo()
{
	//�ж�Ƶ��id�� �û�id�Ƿ�Ϊ��
	if (ui.lineEdit_channelid->text().isEmpty())
		ui.label_channelid_tip->show();

	if (ui.lineEdit_uid->text().isEmpty())
		ui.label_uid_tip->show();

	if (ui.lineEdit_channelid->text().isEmpty() || ui.label_uid_tip->text().isEmpty())
		return false;

	Settings::instance()->Write("channel", ui.lineEdit_channelid->text(), "Info");
	Settings::instance()->Write("user", ui.lineEdit_uid->text(), "Info");
	return true;
}

void PaasTest::showTipDialog(int error, QString msg)
{
	if (error = -2)
	{
		LostDialog dlg;
		dlg.SetText(QString::fromLocal8Bit("����Ƶ��ʧ��"), QString::fromLocal8Bit("��ǰ�û� ID ���Ϸ�"));
		dlg.SetButton(QString::fromLocal8Bit("ȷ��"));
		connect(&dlg, SIGNAL(SigBack()), this, SLOT(SlotLossLeave()));
		dlg.setFixedSize(this->width(), this->height());
		dlg.setGeometry(this->x(), this->y(), dlg.width(), dlg.height());
		dlg.exec();
	}
	else
	{
		LostDialog dlg;
		dlg.SetText(msg, QString::fromLocal8Bit("�����룺%1").arg(error));
		dlg.SetButton(QString::fromLocal8Bit("ȷ��"));
		connect(&dlg, SIGNAL(SigBack()), this, SLOT(SlotLossLeave()));
		dlg.setFixedSize(this->width(), this->height());
		dlg.setGeometry(this->x(), this->y(), dlg.width(), dlg.height());
		dlg.exec();
	}
}

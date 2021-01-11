#pragma once

#include <QtWidgets/QDialog>
#include <QMouseEvent>
#include "ui_PaasTest.h"
#include <IRtcEngineState.h>

using namespace rz;
class PaasTest : public QDialog
{
    Q_OBJECT

public:
    PaasTest(QWidget *parent = Q_NULLPTR);
signals:
    void SigCloseLoading();
    void SigStartProgressBar();
public slots:
    void SlotMin();
    void SlotClose();
    void SlotReEnter(int, int); //���ص�ǰҳ��
    void SlotLoading(); //�������ҳ�棬����sdk�ӿ�
    void SlotJoinChannel(); //����loading�ӿ� sdk���óɹ��������¼����ҳ��
    void SlotJoinChannelSuccess(const QString& channelid, const QString& uid, int elapsed);
    void SlotConnectionStateChanged(const QString& channelid, CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason);
    //TODO TEST
    void SlotLossLeave();
    void SlotWarning(int warn, const QString& msg);
    void SlotError(int err, const QString& msg);
    void SlotError(const QString& channelid, int err, const QString& msg);
protected:
    void mousePressEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
    void closeEvent(QCloseEvent* event) override;
private:
    void init();
    void initStyleSheetFile();
    void initUserInfo();
    void initConnect();
    void initSdk();
private:
    bool judgeInfo();
    void showTipDialog(int error = 200000, QString msg = "");
private:
    Ui::PaasTestClass ui;

    QPoint m_start;
    QPoint m_clickPos;
    bool m_leftButtonPressed = false;
};

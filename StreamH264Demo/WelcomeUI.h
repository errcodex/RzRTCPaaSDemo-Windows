#pragma once

#include "WindowInterface.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class WelcomeUIInputGroup;

class WelcomeUI : public WindowInterface
{
	Q_OBJECT
public:
	WelcomeUI();
	~WelcomeUI() = default;



private:
	virtual void drawWindow() override;
	virtual void loadStyle() override;
	void eventRegister();

private:
	std::shared_ptr<QLabel> logo;			   // ��ߴ�LOGO
	std::shared_ptr<WelcomeUIInputGroup> uid, cid; // �û�ID��Ƶ��ID
	std::shared_ptr<QPushButton> btnEnter, btnClose, btnMini, splitLine;

private slots:
	void SlotTryEnter();
	void SlotClose();
	void SlotMini();
};

// һ�������飨���⡢��ʾ��������
class WelcomeUIInputGroup
{
public:
	WelcomeUIInputGroup(QWidget* parent = nullptr, QString text = "", int x = 0, int y = 0);
	QString&& text() const;
	void text(const QString s) const;
	bool empty() const;
	void showTip() const;
	void hideTip() const;

private:
	std::shared_ptr<QLabel> title, tip;
	std::shared_ptr<QLineEdit> input;
};
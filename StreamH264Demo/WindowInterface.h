#pragma once
#include <QtWidgets/QMainWindow>
#include <QMouseEvent>
class WindowInterface : public QWidget
{
public:
	WindowInterface(QWidget* parent = Q_NULLPTR, const uint32_t x1 = 0U, const uint32_t y1 = 0U, const uint32_t x2 = UINT32_MAX, const uint32_t y2 = UINT32_MAX);
	virtual ~WindowInterface() = default;

	void mousePressEvent(QMouseEvent* e) override;
	void mouseMoveEvent(QMouseEvent* e) override;
	void mouseReleaseEvent(QMouseEvent* e) override;

private:
	// ���ƴ���
	virtual void drawWindow(){};
	virtual void loadStyle(){};

	// �����ƶ�
	QPoint start;
	QPoint clickPos;
	bool leftButtonPressed = false;
	const uint32_t x1, y1, x2, y2;
};

#include "WindowInterface.h"

WindowInterface::WindowInterface(QWidget* parent, const uint32_t x1, const uint32_t y1, const uint32_t x2, const uint32_t y2) : QWidget(parent), x1(x1), x2(x2), y1(y1), y2(y2)
{
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
	this->loadStyle();
}

void WindowInterface::mousePressEvent(QMouseEvent* e)
{
	if (e->button() != Qt::LeftButton)
		return;
	start = e->globalPos();
	clickPos = e->pos();

	// Ö¸¶¨ÇøÓò
	if (clickPos.x() < x1 || clickPos.x() > x2)
		return;
	if (clickPos.y() < y1 || clickPos.y() > y2)
		return;

	leftButtonPressed = true;
}

void WindowInterface::mouseMoveEvent(QMouseEvent* e)
{
	if (!leftButtonPressed)
		return;
	move(e->globalPos() - clickPos);
	start = e->globalPos();
}

void WindowInterface::mouseReleaseEvent(QMouseEvent* e)
{
	if (e->button() != Qt::LeftButton)
		return;
	leftButtonPressed = false;
}
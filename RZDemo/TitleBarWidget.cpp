#include "TitleBarWidget.h"
#include <QDebug>
TitleBarWidget::TitleBarWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

TitleBarWidget::~TitleBarWidget()
{
}

void TitleBarWidget::mousePressEvent(QMouseEvent* event)
{
    // �����������¼�
    if (event->button() == Qt::LeftButton)
    {
        // ��¼������״̬
        m_leftButtonPressed = true;
        //��¼�������Ļ�е�λ��
        m_start = event->globalPos();
    }

}

void TitleBarWidget::mouseMoveEvent(QMouseEvent* event)
{
    // ������ס������Ӧ�¼�
    if (m_leftButtonPressed)
    {
        //���������ƶ���������ԭ����λ�ü�������ƶ���λ�ã�event->globalPos()-m_start
        parentWidget()->move(parentWidget()->geometry().topLeft() + event->globalPos() - m_start);
        //���������Ļ�е�λ���滻Ϊ�µ�λ��
        m_start = event->globalPos();
    }
}

void TitleBarWidget::mouseReleaseEvent(QMouseEvent* event)
{
    // �������ͷ�
    if (event->button() == Qt::LeftButton)
    {
        // ��¼���״̬
        m_leftButtonPressed = false;
    }
}

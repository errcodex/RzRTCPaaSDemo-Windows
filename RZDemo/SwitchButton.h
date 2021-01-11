#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class SwitchButton : public QWidget
{
	Q_OBJECT

public:
	SwitchButton(QWidget* parent);
	~SwitchButton();
public:
	void SetState(bool state);
private:
	bool bSwitch;                     //����״̬:��true����false

	QColor bgColorOn;                 //��״̬ʱ�ı�����ɫ
	QColor bgColorOff;                //��״̬ʱ�ı�����ɫ

	QColor sliderColor;
	QColor sliderColorOn;             //��״̬ʱ����ı�����ɫ
	QColor sliderColorOff;            //��״̬ʱ����ı�����ɫ

	QColor textColorOn;               //��״̬ʱ������ɫ
	QColor textColorOff;              //��״̬ʱ������ɫ

	QString strText;                  //��������

	QPoint startPoint;                //�����ƶ�����ʼ��
	QPoint endPoint;                  //�����ƶ����յ�   
	QPoint centerPoint;               //�����ƶ����м�ĳ��

	int mouseX;

	bool bPress;                      //����Ƿ���

	bool bSelfState = false;		//�ֶ�����

	bool bMove = false;
private:
	void paintEvent(QPaintEvent* e);
	void resizeEvent(QResizeEvent* e);
	void mousePressEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void drawBg(QPainter& painter);        //���Ʊ���
	void drawSlidBlock(QPainter& painter); //���ƻ���
	void drawText(QPainter& painter);      //��������

signals:
	void btnState(bool bswitch);
};

#endif // SWITCHBUTTON_H
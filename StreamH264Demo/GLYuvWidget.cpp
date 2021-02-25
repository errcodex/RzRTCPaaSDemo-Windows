#include "GLYuvWidget.h"
#include <libyuv.h>


GLYuvWidget::GLYuvWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	render = std::make_shared<YUV420P_Render>();
	this->setStyleSheet("background-color:transparent");
	// TODO: set rendermod 
	//m_renderMode = value.toString() == QString::fromLocal8Bit("Ìî³ä") ? RENDER_MODE_HIDDEN : value.toString() == QString::fromLocal8Bit("µÈ±ÈËõ·Å") ? RENDER_MODE_FIT : RENDER_MODE_FILL;
}

void GLYuvWidget::SetChangeMirror(VIDEO_MIRROR_MODE_TYPE mirror)
{
	m_mirrorMode = mirror;
}

void GLYuvWidget::SetChangeRenderMode(RENDER_MODE_TYPE render)
{
	m_renderMode = render;
}

void GLYuvWidget::Clear()
{
	m_w = 0;
	update();
}

void GLYuvWidget::initializeGL()
{
	render->initialize();
}


void GLYuvWidget::paintGL()
{
	if (m_ba.size() == 0 || m_w == 0 || m_h == 0)
	{
		render->clear();
		return;
	}

	int x, y, w, h;

	RECT rc;
	if (m_renderMode == RENDER_MODE_FIT)
	{
		
		double fper1, fper2;
		double rcW = width();
		double rcH = height();
		fper1 = rcW / rcH;
		fper2 = (double)m_w / (double)m_h;
		if (/*(fper1 - 1.f) > EPSILON &&*/ (fper1 - fper2) > 1e-6) {
			y = 0;
			h = rcH;
			int tempw = fper2 * rcH;
			x = fabs(rcW - tempw) / 2;
			w = tempw;
		}
		else
		{
			x = 0;
			w = rcW;
			double tempH = (double)rcW / fper2;
			y = fabs(rcH - tempH) / 2;
			h = tempH;
		}
		render->setGLView(x, y, w, h);
	}
	else if (m_renderMode == RENDER_MODE_HIDDEN)
	{
		//if (rc.top != m_rtDestRect.top || rc.bottom != m_rtDestRect.bottom || rc.left != m_rtDestRect.left || rc.right != m_rtDestRect.right)
		{
			double fper1, fper2;
			double rcW = width();
			double rcH = height();
			fper1 = rcW / rcH;
			fper2 = (double)m_w / (double)m_h;
			if (/*(fper1 - 1.f) > EPSILON &&*/ (fper1 - fper2) > 1e-6) {
				x = 0;
				w = rcW;
				double tempH = (double)rcW / fper2;
				y = (rcH - tempH) / 2;
				h = tempH;
			}
			else
			{
				y = 0;
				h = rcH;
				int tempw = fper2 * rcH;
				x = (rcW - tempw) / 2;
				w = tempw;
			}
			render->setGLView(x, y, w, h);
		}
	}
	else if (m_renderMode == RENDER_MODE_FILL)
	{
		render->setGLView(0, 0, width(), height());
	}

	render->render(m_ba, m_w, m_h, 0);
	m_ba.clear();
	m_w = 0;
	m_h = 0;
}

void GLYuvWidget::SlotShowYuv(const QByteArray& ptr, const uint width, const uint height)
{
 	if (ptr.isEmpty() || width == 0 || height == 0)
		return;

	if (m_mirrorMode == VIDEO_MIRROR_MODE_ENABLED)
	{
		int yuvSize = ptr.size();
		int ySize = width * height;
		int uSize = width * height / 4;

		std::unique_ptr<uint8_t> mirrorData(new uint8_t[yuvSize]);

		uint8_t* py = (uint8_t*)ptr.data();
		uint8_t* pu = py + ySize;
		uint8_t* pv = pu + uSize;

		uint8_t* py1 = mirrorData.get();
		uint8_t* pu1 = py1 + ySize;
		uint8_t* pv1 = pu1 + uSize;
		libyuv::I420Mirror(py, width, pu, width / 2, pv, width / 2, py1, width, pu1, width / 2, pv1, width / 2, width, height);
		m_ba = QByteArray((char*)mirrorData.get(), ptr.size());
	}
	else
		m_ba = ptr;
	
	m_w = width;
	m_h = height;
	update();
}

void GLYuvWidget::resizeGL(int w, int h)
{
	update();
}

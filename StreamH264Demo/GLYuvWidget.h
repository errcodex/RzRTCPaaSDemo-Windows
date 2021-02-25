#pragma once

// MyOpenGLWidget.h

#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <IRtcEngineState.h>
#include "YUV420P_Render.h"

using namespace rz;

struct FrameData
{
	uint8_t* y;
	uint8_t* u;
	uint8_t* v;
	int y_linesize;
	int u_linesize;
	int v_linesize;
	int width;
	int height;
};

class GLYuvWidget : public QOpenGLWidget
{
	Q_OBJECT
public:
	explicit GLYuvWidget(QWidget* parent = nullptr);
	virtual ~GLYuvWidget() = default;

	void SetChangeMirror(VIDEO_MIRROR_MODE_TYPE mirror);
	void SetChangeRenderMode(RENDER_MODE_TYPE render);
	void Clear();

public slots:
	void SlotShowYuv(const QByteArray& ptr, const uint width, const uint height);

protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;

private:
	std::shared_ptr<YUV420P_Render> render;
	QByteArray m_ba;
	uint m_w = 0;
	uint m_h = 0;
	VIDEO_MIRROR_MODE_TYPE m_mirrorMode = VIDEO_MIRROR_MODE_DISABLED;
	RENDER_MODE_TYPE m_renderMode = RENDER_MODE_FIT;
};

#endif // MYOPENGLWIDGET_H
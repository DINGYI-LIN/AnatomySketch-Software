/*
	������Ӱ�߿�
	�����ڵĸ���
*/

#pragma once

//#include "common.h"
#include <QDialog>
#include <QWidget>
#include <QMouseEvent>

enum Direction { UP = 0, DOWN = 1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };
#define SHADOW_WIDTH	5		//�����ڱ߿���Ӱ���
#define PADDING			5		//�߽���������Ŀ��,�ڽ���߽����࣬Ŀǰ�����д��PADDING��SHADOW_WIDTH������ȣ�������Ҫ�޸�ASDropShadowWidget.cpp��getRregion()

class ASDropShadowWidget : public QDialog
{
	Q_OBJECT

public:
	explicit ASDropShadowWidget(QWidget *parent);
	~ASDropShadowWidget();

	void setBorderDragEnabled(bool enabel);

protected:

	virtual void paintEvent(QPaintEvent *event);

	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);

private:

	//�������Ļ������������ڵ����������϶��߽繦��
	void getRregion(const QPoint &cursorGlobalPoint);

	Direction m_currentDir;
	QPoint m_dragPosition;   // �����ƶ��϶�ʱ��Ҫ��ס�ĵ�
	bool m_isLeftPressDown;  // �ж�����Ƿ���
	bool m_BorderDragEnabled;// ��־�߽���ק�����Ƿ���

public slots:

	// �������Ĳ�
	void slotBackgroundChange(bool checked);
};

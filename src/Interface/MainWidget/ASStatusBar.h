#pragma once

#include <QStatusBar>
#include <QLabel>

#define STATUSBAR_HEIGHT 30         // ״̬���߶�;

class ASStatusBar : public QStatusBar
{
	Q_OBJECT

public:
	ASStatusBar(QWidget *parent);
	~ASStatusBar();

private:

	QLabel* m_PermanentWidget;
	QLabel* m_Origin;

	public slots:

	//����ı����״̬�㽹����Ϣ��ʾ
	void slotStatusBarFocusInformationRefresh(double* Pos, int* Index, double PixValue, int* extent, double* space, double* origin, double* windowlevel);
};

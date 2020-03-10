#pragma once
#include "ASTransmissionBase.h"
#include <QKeyEvent>

class ASTransStatusBarGeneral : public ASTransmissionBase
{
	Q_OBJECT

public:
	ASTransStatusBarGeneral(QObject *parent = 0);
	~ASTransStatusBarGeneral();

	// Ψһ����
	static ASTransStatusBarGeneral* GetSelfPointer();

	// ����״̬���Ҳཹ����Ϣ
	static void RefreshStatusBarFocusInfo();

private:
	// Ψһ����
	static ASTransStatusBarGeneral* ms_TransStatusBarGeneral;

signals:
	// ����״̬��������Ϣ
	void signalStatusBarFocusInformationRefresh(double* Pos, int* Index, double PixValue, int* extent, double* space, double* origin, double* windowlevel);
};

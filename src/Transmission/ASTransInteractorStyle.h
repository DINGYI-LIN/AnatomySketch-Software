#pragma once
#include "ASTransmissionBase.h"

class ASTransInteractorStyle : public ASTransmissionBase
{
	Q_OBJECT

public:
	ASTransInteractorStyle(QObject *parent = 0);
	~ASTransInteractorStyle();

	// Ψһ����
	static ASTransInteractorStyle* GetSelfPointer();
	// ���õ�ǰ2D������ʽ��InteractorStyle2D_
	static void SetInteratorStyle2D(const int c_Interactor);
	// ����˫ָƽ�������в�
	static void TouchPan(const int c_ViewLabel, double* pos);
	static void TouchZoom(const int c_ViewLabel, const double c_Factor);
	static void TouchWheel(const int c_ViewLabel, const double c_dis);

private:

	// Ψһ����
	static ASTransInteractorStyle* ms_GeneralInteractor;

signals:

	// ��ǰ2D������ʽ�ı�
	void signalInteractorStyle2DChanged(int interactor);
};

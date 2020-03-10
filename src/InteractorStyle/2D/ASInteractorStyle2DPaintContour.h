#pragma once

#include "ASInteractorStyle2DGeneral.h"
#include "ASArrayImageData.h"

#define TouchThresholdCoeff 1.5

class ASInteractorStyle2DPaintContour : public ASInteractorStyle2DGeneral
{
public:
	static ASInteractorStyle2DPaintContour *New();
	vtkTypeMacro(ASInteractorStyle2DPaintContour, ASInteractorStyle2DGeneral);

	// ��д����϶�����
	virtual void OnMouseMove();
	virtual void OnLeftButtonDown();
	virtual void OnLeftButtonUp();
	virtual void OnMouseWheelForward();
	virtual void OnMouseWheelBackward();
	virtual void OnKeyPress();
	virtual void OnKeyRelease();

private:
	ASInteractorStyle2DPaintContour();
	~ASInteractorStyle2DPaintContour();

	// -1: �����л�����; 0: �޶���; 1: ��ӿ��Ƶ�ʱ���ƶ�; 2: ƽ�ƿ��Ƶ�ʱ���ƶ�; 
	// 3: ������Ƶ�ʱ�ƶ�; 4: ��ӿ��Ƶ�ʱ�ƶ����պ�; 5: ����ģʽ�ƶ�
	int m_MoveState = 0; 
	// ����ģʽ�е���һ�����Ƶ�����
	double m_TouchLastCtr[3];

	// ����״̬״̬
	bool m_isKey_a_down = false;
	bool m_isKey_d_down = false;
	bool m_isKey_q_down = false;
	bool m_isKey_Ctrl_down = false;

};

#pragma once

#include "ASInteractorStyle2DGeneral.h"
#include "ASArrayImageData.h"

class ASInteractorStyle2DPaintLandmark : public ASInteractorStyle2DGeneral
{
public:
	static ASInteractorStyle2DPaintLandmark *New();
	vtkTypeMacro(ASInteractorStyle2DPaintLandmark, ASInteractorStyle2DGeneral);

	// ��д����϶�����
	virtual void OnMouseMove();
	virtual void OnLeftButtonDown();
	//virtual void OnLeftButtonUp();
	//virtual void OnMouseWheelForward();
	//virtual void OnMouseWheelBackward();
	//virtual void OnKeyPress();
	//virtual void OnKeyRelease();

private:
	ASInteractorStyle2DPaintLandmark();
	~ASInteractorStyle2DPaintLandmark();

	int m_MoveState = 0; // -1: �����л�����; 0: �޶���; 1: ƽ�ƿ��Ƶ�ʱ���ƶ�;

};

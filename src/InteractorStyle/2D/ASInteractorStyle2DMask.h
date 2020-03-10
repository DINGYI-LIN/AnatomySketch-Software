#pragma once

#include "ASInteractorStyle2DGeneral.h"
#include "ASArrayImageData.h"

class ASInteractorStyle2DMask : public ASInteractorStyle2DGeneral
{
public:
	static ASInteractorStyle2DMask *New();
	vtkTypeMacro(ASInteractorStyle2DMask, ASInteractorStyle2DGeneral);

	// ��д����϶�����
	virtual void OnMouseMove();
	virtual void OnLeftButtonDown();

private:
	ASInteractorStyle2DMask();
	~ASInteractorStyle2DMask();

	int m_MoveState = 0; // 0:�����л����� 1:ѡ������

};

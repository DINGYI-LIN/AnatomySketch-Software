#pragma once

#include "ASInteractorStyle2DGeneral.h"
#include "ASArrayImageData.h"

class ASInteractorStyle2DPaintSeeds : public ASInteractorStyle2DGeneral
{
public:
	static ASInteractorStyle2DPaintSeeds *New();
	vtkTypeMacro(ASInteractorStyle2DPaintSeeds, ASInteractorStyle2DGeneral);

	// ��д����϶�����
	virtual void OnMouseMove();
	virtual void OnLeftButtonDown();
	virtual void OnLeftButtonUp();

private:
	ASInteractorStyle2DPaintSeeds();
	~ASInteractorStyle2DPaintSeeds();

	bool m_isPaintingSeeds = false;

};

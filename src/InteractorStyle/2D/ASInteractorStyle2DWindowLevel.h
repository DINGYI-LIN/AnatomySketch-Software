#pragma once

#include "ASInteractorStyle2DGeneral.h"
#include "ASArrayImageData.h"

// !!!����!!!

class ASInteractorStyle2DWindowLevel : public ASInteractorStyle2DGeneral
{
public:
	static ASInteractorStyle2DWindowLevel *New();
	vtkTypeMacro(ASInteractorStyle2DWindowLevel, ASInteractorStyle2DGeneral);

	// ��д����϶�����
	virtual void OnMouseMove();
	virtual void OnLeftButtonDown();

private:
	ASInteractorStyle2DWindowLevel();
	~ASInteractorStyle2DWindowLevel();

	//��λ�������
	double m_LevelWindowInitial[2];
	double m_LevelWindowStartPosition[2];
	double m_LevelWindowCurrentPosition[2];
	// ��ǰ����������
	ASArrayImageData* m_crntTopData;


};

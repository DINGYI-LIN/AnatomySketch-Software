#pragma once
#include "ASPipelineBase.h"
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>

class ASPipelineOuterBorder3D : public ASPipelineBase
{
public:
	ASPipelineOuterBorder3D(const int c_ID);
	~ASPipelineOuterBorder3D();

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type);
	virtual bool isTypeAbsolute(const int c_Type);

	// ������ʾ����
	static void setShown(const bool c_Shown);
	static void setCrossShairShown(const bool c_Shown);
	// ˢ����ʾ
	void Update();

	// �麯������ͼ����ı�
	virtual void Update2DTransformMatrix();

private:

	// �ù�����Ψһ�ģ�Ψһ����
	static ASPipelineOuterBorder3D* ms_SelfPointer;

	// ���߽ṹ
	vtkSmartPointer<vtkPoints>			m_pFrameLinePoints[3];
	vtkSmartPointer<vtkCellArray>		m_pFrameLineCells[3];
	vtkSmartPointer<vtkActor>			m_pFrameLineActor[3];
	vtkSmartPointer<vtkPolyData>		m_pFrameLineData[3];
	vtkSmartPointer<vtkProperty>		m_pFrameLineProperty[3];
	vtkSmartPointer<vtkPolyDataMapper>	m_pFramelineMapper[3];
	vtkSmartPointer<vtkRenderer>		m_pRenderer3D;


	// ��ʾ����
	bool m_isShown = false;
	bool m_isCrossShairShown = true;
	
};

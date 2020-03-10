#pragma once
#include "ASPipelineBase.h"
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>

class ASPipelineCrossLine2D : public ASPipelineBase
{
public:
	ASPipelineCrossLine2D(const int c_ID);
	~ASPipelineCrossLine2D();

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type);
	virtual bool isTypeAbsolute(const int c_Type);
	virtual void DeleteNode();	// ���ô˺������ͷŹ���

	// ������ʾ����
	static void setShown(const bool c_Shown);
	// ˢ����ʾ
	void Update();

	// �麯������ͼ����ı�
	virtual void Update2DTransformMatrix();

private:

	// �ù�����Ψһ�ģ�Ψһ����
	static ASPipelineCrossLine2D* ms_SelfPointer;

	// ���߽ṹ
	vtkSmartPointer<vtkPoints>					m_pCrossLinePoints[6];
	vtkSmartPointer<vtkCellArray>				m_pCrossLineCells[6];
	vtkSmartPointer<vtkActor>					m_pCrossLineActor[6];
	vtkSmartPointer<vtkPolyData>				m_pCrossLineData[6];
	vtkSmartPointer<vtkTransform>				m_pCrossLineTransform[6];
	vtkSmartPointer<vtkTransformPolyDataFilter>	m_pCrossLineTransformPolyDataFilter[6];
	vtkSmartPointer<vtkProperty>				m_pCrossLineProperty[3];
	vtkSmartPointer<vtkPolyDataMapper>			m_pCrosslineMapper[6];

	// ��ʾ����
	bool m_isShown = false;
	
};

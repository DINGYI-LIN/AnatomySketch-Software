#pragma once
#include "ASPipelineBase.h"
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPlane.h>
#include <vtkCleanPolyData.h>
#include <vtkCutter.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <QColor>

#define LineWidth_Nomal		2
#define LineWidth_Bold		3

class ASPipelinePolyImage : public ASPipelineBase
{
public:
	ASPipelinePolyImage(const int c_ID);
	~ASPipelinePolyImage();

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type);
	virtual bool isTypeAbsolute(const int c_Type);

	// ������������
	void SetInputData(vtkPolyData* InputData);
	// ������ʾ����
	virtual void SetShown(const bool c_Shown); // �Ƿ���ʾ
	void SetColor(const QColor c_Color);
	void SetLineWidth(const double c_Width);
	void SetOpacity(const double c_Opacity); // ������ά��ʾ��͸���ȣ�0��1
	void SetContourLineWidth(const double c_Width = 2);
	void SetContourLinePickable(const bool c_Pickable);
	// Actor
	void GetActor2D(vtkActor** ppActor);
	// �����������ݱ仯��ˢ�¹���
	void UpdataInput();

	// �麯��
	virtual void DeleteNode();	// ���ô˺������ͷŹ���
	virtual void Update2DTransformMatrix(); // ��ͼ����ı�

private:

	// ���߽ṹ
	// 2D
	vtkSmartPointer<vtkPlane>					m_pPlane2D[3];
	vtkSmartPointer<vtkCleanPolyData>			m_pCleanPolyData2D;
	vtkSmartPointer<vtkCutter>					m_pCutter2D[3];
	vtkSmartPointer<vtkTransform>				m_pTransform2D[3];
	vtkSmartPointer<vtkTransformPolyDataFilter>	m_pTransformPolyDataFilter2D[3];
	vtkSmartPointer<vtkPolyDataMapper>			m_pPolyDataMapper[3];
	vtkSmartPointer<vtkActor>					m_pActor2D[3];
	vtkSmartPointer<vtkRenderer>				m_pRenderer2D[3];
	// 3D
	vtkSmartPointer<vtkPolyDataMapper>			m_pPolyDataMapper3D;
	vtkSmartPointer<vtkActor>					m_pActor3D;
	vtkSmartPointer<vtkRenderer>				m_pRenderer3D;

	// ��Ӧ����
	vtkSmartPointer<vtkPolyData> m_InputData;

	// ��ʾ����
	bool m_isShown = false;
	QColor m_Color;
	double m_LineWidth;
	double m_Opacity; // ��ά��ʾ��͸����
	double m_ContourLineWidth;
	bool m_ContourLinePickable;

	//����Ĭ����������ķ������ڼ���������ʱ�趨���淽��
	double m_cPlaneNormal[3][3] = { { 1,0,0 },{ 0,1,0 },{ 0,0,1 } };

	
};

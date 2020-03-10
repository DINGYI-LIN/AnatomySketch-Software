#pragma once
#include "ASPipelineBase.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkImageStack.h>
#include <vtkMatrix4x4.h>

class ASPipelineSeeds : public ASPipelineBase
{
public:
	ASPipelineSeeds(const int c_ID);
	~ASPipelineSeeds();

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type);
	virtual bool isTypeAbsolute(const int c_Type);

	// �麯��
	virtual void DeleteNode();	// ���ô˺������ͷŹ���
	virtual void Update2DTransformMatrix();	// ��ͼ����ı�
	virtual void SetShown(const bool c_Shown); // �Ƿ���ʾ

	// �ڻ���ʱ������һ���������ʾ
	void AddOnePointDisplay(double* pPositon);

private:
	// �ù�����Ψһ�ģ�Ψһ����
	static ASPipelineSeeds* ms_PipelineSeeds;

	// �Ƿ���ʾ
	bool m_isShown = false;

	// ����Ԫ��
	vtkSmartPointer<vtkImageData>	m_ImageData[3];
	vtkSmartPointer<vtkImageActor>	m_ImageActor[3];
	vtkSmartPointer<vtkImageStack>	m_pImageStack2D[3];
	vtkSmartPointer<vtkImageStack>	m_pImageStack3D[3];

	// ��ʾ��������
	double m_ImageExtent[6];
	double m_ImageSpacing[3];
	double m_ImagePosition[3];
	int m_ExtentofPixelInPainting[3];
	vtkSmartPointer<vtkMatrix4x4> m_pMatrix[3];
	vtkSmartPointer<vtkMatrix4x4> m_pMatrixToZero[3];
	vtkSmartPointer<vtkMatrix4x4> m_pMatrixToOne[3];

	// ��ǰ״̬��ÿ�������Ƿ������ӵ�
	bool m_bHaveObj[3] = { false, false, false };

	// ����ĳ��ͼ����ʾ
	void UpdataDisplayPosition(const int c_ViewLabel);
	// ��ʼ��ĳ�����vtkImageData
	void InitImageData(const int c_ViewLabel);
};

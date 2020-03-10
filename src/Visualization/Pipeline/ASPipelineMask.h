#pragma once
#include "ASPipelineBase.h"
#include <vtkSmartPointer.h>
#include <vtkImageReslice.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkImageStack.h>

class ASPipelineMask : public ASPipelineBase
{
public:
	ASPipelineMask(const int c_ID);
	~ASPipelineMask();

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type);
	virtual bool isTypeAbsolute(const int c_Type);

	// ������ʾ����
	virtual void SetShown(const bool c_Shown);
	// ������������
	void SetMaskImageData(vtkImageData* InputData);
	// ����
	void Update();

	// �麯������ͼ����ı�
	virtual void Update2DTransformMatrix();

private:

	// �ù�����Ψһ�ģ�Ψһ����
	static ASPipelineMask* ms_PipelineMask;
	// ��ʾ����
	bool m_isShown = false;
	// ��Ӧ��������
	vtkSmartPointer<vtkImageData> m_InputData;
	// ���߽ṹ
	vtkSmartPointer<vtkImageReslice>	m_ImageReslice[3];
	vtkSmartPointer<vtkImageData>		m_ImageMapped[3];
	vtkSmartPointer<vtkImageActor>		m_ImageActor[3];
	vtkSmartPointer<vtkImageStack>		m_pImageStack2D[3];
	vtkSmartPointer<vtkImageStack>		m_pImageStack3D[3];

	// ����m_ImageMapped
	void UpdateImageMapped();
};

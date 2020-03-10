#pragma once
#include "ASPipelineBase.h"
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkImageExtractComponents.h>
#include <vtkImageReslice.h>
#include <vtkImageMapToColors.h>
#include <vtkImageActor.h>
#include <vtkImageStack.h>

class ASArrayImageData;

class ASPipelineArrayImage : public ASPipelineBase
{
public:
	ASPipelineArrayImage(const int c_ID);
	~ASPipelineArrayImage();

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type);
	virtual bool isTypeAbsolute(const int c_Type);

	// ������������
	void SetInputData(vtkImageData* InputData);
	// �������ݱ仯��ˢ�¹���
	void UpdataInputData(const int c_Frame);
	// ������ʾ����	
	void SetFrame(const int c_Frame);
	void SetColorMapping(const int c_ColorMap, const double c_ColorWindow, const double c_ColorLevel);
	void SetLayer(const int c_Layer);
	void SetOpacity(const double c_Opacity); // ������ά��ʾ��͸���ȣ�0��1
	// ��ʼ������
	void ArrayPipeInit(ASArrayImageData* arrayImage);

	// �麯��
	virtual void DeleteNode();	// ���ô˺������ͷŹ���
	virtual void Update2DTransformMatrix(); // ��ͼ����ı�
	virtual void SetShown(const bool c_Shown); // �Ƿ���ʾ
	virtual void ReinitDisplay(); // ������ʾ

private:

	// ���߽ṹ
	vtkSmartPointer<vtkImageExtractComponents>		m_pImageExtractComponents;
	vtkSmartPointer<vtkImageReslice>				m_pImageReslice[3];
	vtkSmartPointer<vtkImageMapToColors>			m_pImageMapToColors[3];
	vtkSmartPointer<vtkImageActor>					m_pImageActor[3];
	vtkSmartPointer<vtkImageStack>					m_pImageStack2D[3];
	vtkSmartPointer<vtkImageStack>					m_pImageStack3D[3];

	// ��Ӧ����
	vtkSmartPointer<vtkImageData> m_InputData;

	// ��ʾ����
	bool m_isShown = false;
	int m_Frame = 0;
	int m_ColorMap;
	int m_Layer;
	double m_ColorWindow;
	double m_ColorLevel;
	double m_Opacity = 1; // ��ά��ʾ��͸����

	// ������ɫ����λ�������ImageMapToColors
	void UpdateImageMapToColors();
	
};

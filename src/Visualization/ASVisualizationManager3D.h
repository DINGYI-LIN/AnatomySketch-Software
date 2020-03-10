#pragma once
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkImageStack.h>

class ASQVTKWidget;

class ASVisualizationManager3D
{
public:
	ASVisualizationManager3D();
	~ASVisualizationManager3D();

	// �趨��ʾQVTKWidgetָ��
	void SetQVTKWidget(ASQVTKWidget* pQVTKWidget);
	// ����ImageStack�ı任����
	void UpdateImageStack3DTransform();
	// �������
	void ResetCamera();
	// �л�3D��ͼ2D�����Ƿ���ʾ�������л����Ƿ���ʾ
	static bool Switch3DImageStackShown();

	// ImageStack
	static void GetImageStack3D(vtkSmartPointer<vtkImageStack>* ImageStack);
	// Renderer
	static void GetRenderer3D(vtkSmartPointer<vtkRenderer>* Renderer);

	// ��Ⱦ
	static void Render();
	 

private:

	bool m_ImageStack3DShown = true; // ImageStack3D�Ƿ���ʾ

	// ����Ԫ��
	ASQVTKWidget* m_QVTKWidget;	// ��ʾQVTKWidgetָ��
	vtkSmartPointer<vtkRenderer> m_Renderer3D;
	vtkSmartPointer<vtkImageStack> m_ImageStack3D[3];
	// ��ά��ʾ��ʼ��
	void DisplayInit3D();

	// Ψһ�����ָ��
	static ASVisualizationManager3D* ms_SelfPointer;

};

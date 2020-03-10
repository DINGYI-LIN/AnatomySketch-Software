#pragma once
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkImageStack.h>
#include <vtkMatrix4x4.h>
#include <QString>

class ASQVTKWidget;

/*
ȫ�ֵõ��任����
vtkSmartPointer<vtkMatrix4x4> pMatrix[3];
vtkSmartPointer<vtkMatrix4x4> pMatrixToZero[3];
vtkSmartPointer<vtkMatrix4x4> pMatrixToOne[3];
ASVisualizationManager2D::GetTransformMatrix4x4(pMatrix, pMatrixToZero, pMatrixToOne);
*/

class ASVisualizationManager2D
{
public:
	ASVisualizationManager2D();
	~ASVisualizationManager2D();

	// �趨��ʾQVTKWidgetָ��
	void SetQVTKWidget(ASQVTKWidget** pQVTKWidget);
	// ��ʾ�����趨
	void setImagePosition(double* ImagePosition);
	// Matrix4x4
	static void GetTransformMatrix4x4(vtkSmartPointer<vtkMatrix4x4>* Matrix4x4, 
		vtkSmartPointer<vtkMatrix4x4>* Matrix4x4InvertToZero, 
		vtkSmartPointer<vtkMatrix4x4>* Matrix4x4InvertToOne);
	// ImageStack
	static void GetImageStack2D(vtkSmartPointer<vtkImageStack>* ImageStack);
	// Renderer
	static void GetRenderer2D(vtkSmartPointer<vtkRenderer>* Renderer);
	// ���������Ұ��Χ
	static double GetViewableRange(const int c_ViewLabel);
	// �������Ƿ����ʰȡ
	static void SetContoursPickable(const bool c_pickable);
	static bool GetContoursPickable();

	// ���ݵ�ǰ����ˢ�±任����
	void UpdateTransformMatrix();
	// �������
	void ResetCamera();

	// ��Ⱦ
	static void Render();
	static void Render(const int c_ViewLabel);

private:

	// ����Ԫ��
	ASQVTKWidget* m_QVTKWidget[3];	// ��ʾQVTKWidgetָ��
	vtkSmartPointer<vtkRenderer> m_Renderer2D[3];
	vtkSmartPointer<vtkImageStack> m_ImageStack2D[3];

	// Ψһ�����ָ��
	static ASVisualizationManager2D* ms_SelfPointer;

	double* m_ImagePosition;			// ���㣬��������ϵ��ASVisualizationManager�е�����

	//�������桢ʸ״�桢��״��任��������ת������
	const double m_constDirectionCosines[3][9] = { { 0, 1, 0, 0, 0, 1, 1, 0, 0 },{ 1, 0, 0, 0, 0, 1, 0, -1, 0 },{ 1, 0, 0, 0, -1, 0, 0, 0, -1 } };
	//�任����
	vtkSmartPointer<vtkMatrix4x4> m_pMatrix4x4[3];				//����ʾ����ϵ����������ϵ�ı任����
	vtkSmartPointer<vtkMatrix4x4> m_pMatrix4x4InvertToZero[3];	//����������ϵ����ʾ����ϵ�ı任���󣬽����Z����Ϊ0
	vtkSmartPointer<vtkMatrix4x4> m_pMatrix4x4InvertToOne[3];	//����������ϵ����ʾ����ϵ�ı任���󣬽����Z����Ϊ1

	// �������Ƿ����ʰȡ
	bool m_ContoursPickable = false;

	// ��ά��ʾ��ʼ��
	void DisplayInit2D();
};

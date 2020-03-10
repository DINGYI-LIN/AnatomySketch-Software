#include "ASVisualizationManager3D.h"
#include "ASVisualizationManager2D.h"
#include "ASQVTKWidget.h"
#include "ASPipelineManager.h"
#include "ASPipelineBase.h"
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <vtkBMPReader.h>
#include <vtkTexture.h>

// Ψһ�����ָ��
ASVisualizationManager3D* ASVisualizationManager3D::ms_SelfPointer = nullptr;

ASVisualizationManager3D::ASVisualizationManager3D()
{
	ms_SelfPointer = this;
}

ASVisualizationManager3D::~ASVisualizationManager3D()
{

}

// �趨��ʾQVTKWidgetָ��
void ASVisualizationManager3D::SetQVTKWidget(ASQVTKWidget* pQVTKWidget)
{
	this->m_QVTKWidget = pQVTKWidget;

	this->DisplayInit3D();
}
// ����ImageStack�ı任����
void ASVisualizationManager3D::UpdateImageStack3DTransform()
{
	vtkSmartPointer<vtkMatrix4x4> pMatrix[3];
	vtkSmartPointer<vtkMatrix4x4> pMatrixToZero[3];
	vtkSmartPointer<vtkMatrix4x4> pMatrixToOne[3];
	ASVisualizationManager2D::GetTransformMatrix4x4(pMatrix, pMatrixToZero, pMatrixToOne);
	for (int ViewLabel = 0; ViewLabel < 3; ViewLabel++)
	{
		m_ImageStack3D[ViewLabel]->SetUserMatrix(pMatrix[ViewLabel]);
	}
}
// �������
void ASVisualizationManager3D::ResetCamera()
{
	m_Renderer3D->ResetCamera();
}
// �л�3D��ͼ2D�����Ƿ���ʾ�������л����Ƿ���ʾ
bool ASVisualizationManager3D::Switch3DImageStackShown()
{
	if (ms_SelfPointer->m_ImageStack3DShown)
	{
		// ��Ϊ����ʾ
		ms_SelfPointer->m_ImageStack3DShown = false;
		ms_SelfPointer->m_Renderer3D->RemoveActor(ms_SelfPointer->m_ImageStack3D[0]);
		ms_SelfPointer->m_Renderer3D->RemoveActor(ms_SelfPointer->m_ImageStack3D[1]);
		ms_SelfPointer->m_Renderer3D->RemoveActor(ms_SelfPointer->m_ImageStack3D[2]);
		return false;
	} 
	else
	{
		// ��Ϊ��ʾ
		ms_SelfPointer->m_ImageStack3DShown = true;
		ms_SelfPointer->m_Renderer3D->AddActor(ms_SelfPointer->m_ImageStack3D[0]);
		ms_SelfPointer->m_Renderer3D->AddActor(ms_SelfPointer->m_ImageStack3D[1]);
		ms_SelfPointer->m_Renderer3D->AddActor(ms_SelfPointer->m_ImageStack3D[2]);
		return true;
	}
}
// ImageStack
void ASVisualizationManager3D::GetImageStack3D(vtkSmartPointer<vtkImageStack>* ImageStack)
{
	ImageStack[0] = ms_SelfPointer->m_ImageStack3D[0];
	ImageStack[1] = ms_SelfPointer->m_ImageStack3D[1];
	ImageStack[2] = ms_SelfPointer->m_ImageStack3D[2];
}
// Renderer
void ASVisualizationManager3D::GetRenderer3D(vtkSmartPointer<vtkRenderer>* Renderer)
{
	*Renderer = ms_SelfPointer->m_Renderer3D;
}

// ��Ⱦ
void ASVisualizationManager3D::Render()
{
	ms_SelfPointer->m_QVTKWidget->GetRenderWindow()->Render();
}

// ��ά��ʾ��ʼ��
void ASVisualizationManager3D::DisplayInit3D()
{
	for (int crntViewLabel = 0; crntViewLabel < 3; crntViewLabel++)
	{
		//vtkImageStack
		m_ImageStack3D[crntViewLabel] = vtkSmartPointer<vtkImageStack>::New();
		m_ImageStack3D[crntViewLabel]->SetPickable(false);
	}
	// vtkRenderer
	m_Renderer3D = vtkSmartPointer<vtkRenderer>::New();
	m_Renderer3D->AddActor(m_ImageStack3D[0]);
	m_Renderer3D->AddActor(m_ImageStack3D[1]);
	m_Renderer3D->AddActor(m_ImageStack3D[2]);
	m_QVTKWidget->GetRenderWindow()->AddRenderer(m_Renderer3D);
	// ���ñ���
	vtkSmartPointer<vtkBMPReader> BackgroundBMPReader = vtkSmartPointer<vtkBMPReader>::New();
	BackgroundBMPReader->SetFileName("background3D.bmp");
	BackgroundBMPReader->Update();
	vtkSmartPointer<vtkTexture> BackgroundTexture = vtkSmartPointer<vtkTexture>::New();
	BackgroundTexture->SetInputConnection(BackgroundBMPReader->GetOutputPort());
	BackgroundTexture->Update();
	m_Renderer3D->TexturedBackgroundOn();
	m_Renderer3D->SetBackgroundTexture(BackgroundTexture);
	// ���ʮ���߹���
	ASPipelineManager::AddPipeline(PipeLineType_OuterBorder3D);
}

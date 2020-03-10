#include "ASInteractorStyle2DGeneral.h"
#include "ASTransGeneralInteractor.h"
#include "ASVisualizationManager2D.h"
#include "ASPipelineBase.h"
#include "ASVisualizationManager.h"
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCallbackCommand.h>
#include <vtkObjectFactory.h>   //ʰȡ�й�
#include <vtkPropPicker.h>
#include <ASArrayImageData.h>
#include <vtkCamera.h>
#include <vtkCoordinate.h>

vtkStandardNewMacro(ASInteractorStyle2DGeneral);


ASInteractorStyle2DGeneral::ASInteractorStyle2DGeneral()
{
	m_picker = vtkSmartPointer<vtkPointPicker>::New();
	m_picker->SetTolerance(0.0); // ����ʰȡ��Χ/ʰȡ�뾶
}

ASInteractorStyle2DGeneral::~ASInteractorStyle2DGeneral()
{

}

//����ƶ�
void ASInteractorStyle2DGeneral::OnMouseMove()
{
	if (ASPipelineBase::GetNumOfShowingObj2D() <= 0)
	{
		return;
	}
	int x = this->Interactor->GetEventPosition()[0];
	int y = this->Interactor->GetEventPosition()[1];

	this->HoverDetection(x, y);

	// ����״̬
	if (m_IsWinlev)
	{
		this->WinLevContinue();
	}
	else if (m_isLeftButtonDown)
	{
		m_picker->Pick(x, y, 0, this->GetDefaultRenderer());
		double posfinal[4];

		//cout << x << " - " << y << endl;
		//cout << m_picker->GetPickPosition()[0] << " - " << m_picker->GetPickPosition()[1] <<
		//	" - " << m_picker->GetPickPosition()[2] << endl;

		getPickPosFinal(posfinal, m_picker->GetPickPosition());
		ASTransGeneralInteractor::SetVisualizationPosition(posfinal[0], posfinal[1], posfinal[2]);
	}
	else if (m_isMiddleButtonDown)
	{
		this->Move_Panning(x, y);
	}
	else if (m_isRightButtonDown)
	{
		this->Move_Zooming(x, y);
	}
}

//����������
void ASInteractorStyle2DGeneral::OnLeftButtonDown()
{
	m_isLeftButtonDown = true;

	if (ASPipelineBase::GetNumOfShowingObj2D() <= 0)
	{
		return;
	}

	if (this->Interactor->GetAltKey())
	{
		// Alt���´�λ����
		this->WinLevStart();
	}
	else
	{
		int x = this->Interactor->GetEventPosition()[0];
		int y = this->Interactor->GetEventPosition()[1];

		m_picker->Pick(x, y, 0, this->GetDefaultRenderer());
		double posfinal[4];

		//cout << x << " - " << y << endl;
		//cout << m_picker->GetPickPosition()[0] << " - " << m_picker->GetPickPosition()[1] <<
		//	" - " << m_picker->GetPickPosition()[2] << endl;

		getPickPosFinal(posfinal, m_picker->GetPickPosition());
		ASTransGeneralInteractor::SetVisualizationPosition(posfinal[0], posfinal[1], posfinal[2]);
	}
}

//������̧��
void ASInteractorStyle2DGeneral::OnLeftButtonUp()
{
	m_isLeftButtonDown = false;
	m_IsWinlev = false;
	if (ASPipelineBase::GetNumOfShowingObj2D() <= 0)
	{
		return;
	}
}

//����м�����
void ASInteractorStyle2DGeneral::OnMiddleButtonDown()
{
	m_isMiddleButtonDown = true;
	if (ASPipelineBase::GetNumOfShowingObj2D() <= 0)
	{
		return;
	}
	this->GrabFocus(this->EventCallbackCommand);
	this->StartPan();
}

//����м�̧��
void ASInteractorStyle2DGeneral::OnMiddleButtonUp()
{
	m_isMiddleButtonDown = false;
	if (ASPipelineBase::GetNumOfShowingObj2D() <= 0)
	{
		return;
	}
	this->EndPan();
	if (this->Interactor)
	{
		this->ReleaseFocus();
	}
}

//����Ҽ�����
void ASInteractorStyle2DGeneral::OnRightButtonDown()
{
	m_isRightButtonDown = true;
	if (ASPipelineBase::GetNumOfShowingObj2D() <= 0)
	{
		return;
	}
	this->GrabFocus(this->EventCallbackCommand);
	this->StartDolly();
}

//����Ҽ�̧��
void ASInteractorStyle2DGeneral::OnRightButtonUp()
{
	m_isRightButtonDown = false;
	if (ASPipelineBase::GetNumOfShowingObj2D() <= 0)
	{
		return;
	}
	this->EndDolly();
	if (this->Interactor)
	{
		this->ReleaseFocus();
	}
}

//���������Ϲ���
void ASInteractorStyle2DGeneral::OnMouseWheelForward()
{

	if (ASPipelineBase::GetNumOfShowingObj2D() <= 0 || m_isMiddleButtonDown || m_isLeftButtonDown || m_isRightButtonDown)
	{
		return;
	}

	// Ĭ�ϲ��� �л�����
	double Posfinal[3];
	double Spaing[3];
	ASVisualizationManager::GetDisplayPosition(Posfinal);
	ASVisualizationManager::GetDisplaySpacing(Spaing);
	Posfinal[m_ViewLabel] += Spaing[m_ViewLabel];
	ASTransGeneralInteractor::SetVisualizationPosition(Posfinal[0], Posfinal[1], Posfinal[2]);
}

//���������¹���
void ASInteractorStyle2DGeneral::OnMouseWheelBackward()
{
	if (ASPipelineBase::GetNumOfShowingObj2D() <= 0 || m_isMiddleButtonDown || m_isLeftButtonDown || m_isRightButtonDown)
	{
		return;
	}

	// Ĭ�ϲ��� �л�����
	double Posfinal[3];
	double Spaing[3];
	ASVisualizationManager::GetDisplayPosition(Posfinal);
	ASVisualizationManager::GetDisplaySpacing(Spaing);
	Posfinal[m_ViewLabel] -= Spaing[m_ViewLabel];
	ASTransGeneralInteractor::SetVisualizationPosition(Posfinal[0], Posfinal[1], Posfinal[2]);
}

//������ͼ
void ASInteractorStyle2DGeneral::setViewLabel(int ViewLabel)
{
	m_ViewLabel = ViewLabel;
}

// ����ƽ��
void ASInteractorStyle2DGeneral::TouchPan(double* pos)
{
	vtkSmartPointer<vtkRenderer> renderer[3];
	ASVisualizationManager2D::GetRenderer2D(renderer);

	double viewFocus[4], viewPoint[3];
	double motionVector[4] = {0,0,0,0};

	// Calculate the focal depth since we'll be using it a lot

	vtkCamera *camera = renderer[m_ViewLabel]->GetActiveCamera();
	camera->GetFocalPoint(viewFocus);
	this->ComputeWorldToDisplay(viewFocus[0], viewFocus[1], viewFocus[2],
		viewFocus);

	vtkSmartPointer<vtkCoordinate> Coordinate = vtkSmartPointer<vtkCoordinate>::New();
	Coordinate->SetCoordinateSystemToDisplay();
	Coordinate->SetValue(pos[0], pos[1], 0);
	double* mvector1 = Coordinate->GetComputedWorldValue(renderer[m_ViewLabel]);
	double a[3];
	a[0] = mvector1[0];
	a[1] = mvector1[1];
	Coordinate->SetValue(pos[2], pos[3], 0);
	double* mvector2 = Coordinate->GetComputedWorldValue(renderer[m_ViewLabel]);
	motionVector[0] = mvector2[0] - a[0];
	motionVector[1] = a[1] - mvector2[1];
	motionVector[2] = 0;

	camera->GetFocalPoint(viewFocus);
	camera->GetPosition(viewPoint);
	camera->SetFocalPoint(motionVector[0] + viewFocus[0],
		motionVector[1] + viewFocus[1],
		motionVector[2] + viewFocus[2]);

	camera->SetPosition(motionVector[0] + viewPoint[0],
		motionVector[1] + viewPoint[1],
		motionVector[2] + viewPoint[2]);

	if (this->Interactor->GetLightFollowCamera())
	{
		renderer[m_ViewLabel]->UpdateLightsGeometryToFollowCamera();
	}

	this->Interactor->Render();
}
// ��������
void ASInteractorStyle2DGeneral::TouchZoom(double factor)
{
	vtkSmartPointer<vtkRenderer> renderer[3];
	ASVisualizationManager2D::GetRenderer2D(renderer);	
	vtkCamera* camera = renderer[m_ViewLabel]->GetActiveCamera();
	if (camera->GetParallelProjection())
	{
		camera->SetParallelScale(camera->GetParallelScale() / factor);
	}
	else
	{
		camera->Dolly(factor);
		if (this->AutoAdjustCameraClippingRange)
		{
			renderer[m_ViewLabel]->ResetCameraClippingRange();
		}
	}
	if (this->Interactor->GetLightFollowCamera())
	{
		renderer[m_ViewLabel]->UpdateLightsGeometryToFollowCamera();
	}
	this->Interactor->Render();
	// ����ʱ��Ҫˢ�����������ߵĿ��Ƶ�뾶
	ASTransGeneralInteractor::GenerateViewZoom(m_ViewLabel);
}
// �����в�
void ASInteractorStyle2DGeneral::TouchWheel(double dis)
{
	if (dis > 0)
	{		
		this->OnMouseWheelForward();
	}
	else
	{
		this->OnMouseWheelBackward();
	}
}

//��vtkPointPicker�õ��������z����0��������ΪvtkImageReslice��ͼ��ı任����Ҫ���ݱ任������л��㡣
void ASInteractorStyle2DGeneral::getPickPosFinal(double* posfinal, double* PointPickerOutput)
{
	double input[4];
	input[0] = PointPickerOutput[0];
	input[1] = PointPickerOutput[1];
	input[2] = 0;						//��ֹʰȡ��Z����Ϊ1�ĵ�---------------------------------------------------------------------------------��Ҫ
	input[3] = 1;

	vtkSmartPointer<vtkMatrix4x4> pMatrix[3];
	vtkSmartPointer<vtkMatrix4x4> pMatrixToZero[3];
	vtkSmartPointer<vtkMatrix4x4> pMatrixToOne[3];
	ASVisualizationManager2D::GetTransformMatrix4x4(pMatrix, pMatrixToZero, pMatrixToOne);
	pMatrix[m_ViewLabel]->MultiplyPoint(input, posfinal);
}

// ��ͣ���
void ASInteractorStyle2DGeneral::HoverDetection(const int c_x, const int c_y)
{
	//ʰȡ
	vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
	picker->Pick(c_x, c_y, 0, this->GetDefaultRenderer());
	vtkActor* pickedActor = picker->GetActor();
	ASTransGeneralInteractor::HoverActorPicked(pickedActor, c_x, c_y, m_ViewLabel);
}
// �����ı䴰λ����
void ASInteractorStyle2DGeneral::WinLevStart()
{
	m_IsWinlev = true;
	m_crntTopData = ASVisualizationManager::GetToplayerData();
	if (m_crntTopData == nullptr)
	{
		return;
	}
	m_LevelWindowInitial[0] = m_crntTopData->getWindowLevel()[1];
	m_LevelWindowInitial[1] = m_crntTopData->getWindowLevel()[0];

	vtkRenderWindowInteractor *rwi = this->Interactor;

	this->m_LevelWindowStartPosition[0] = rwi->GetEventPosition()[0];
	this->m_LevelWindowStartPosition[1] = rwi->GetEventPosition()[1];
}
void ASInteractorStyle2DGeneral::WinLevContinue()
{
	vtkRenderWindowInteractor *rwi = this->Interactor;
	this->m_LevelWindowCurrentPosition[0] = rwi->GetEventPosition()[0];
	this->m_LevelWindowCurrentPosition[1] = rwi->GetEventPosition()[1];
	int *size = this->DefaultRenderer->GetSize();
	double window = this->m_LevelWindowInitial[1];
	double level = this->m_LevelWindowInitial[0];
	// Compute normalized delta
	double dx = (this->m_LevelWindowCurrentPosition[0] -
		this->m_LevelWindowStartPosition[0]) / size[0];
	double dy = (this->m_LevelWindowStartPosition[1] -
		this->m_LevelWindowCurrentPosition[1]) / size[1];
	// Scale by current values
	double* ScalarRange = m_crntTopData->getArrayImageData()->GetScalarRange();
	dy = dy * (ScalarRange[1] - ScalarRange[0]) / 20;
	if (fabs(window) > 0.01)
	{
		dx = dx * window;
	}
	else
	{
		dx = dx * (window < 0 ? -0.01 : 0.01);
	}
	//if (fabs(level) > 0.01)
	//{
	//	dy = dy * level;
	//}
	//else
	//{
	//	dy = dy * (level < 0 ? -0.01 : 0.01);
	//}
	// Abs so that direction does not flip
	if (window < 0.0)
	{
		dx = -1 * dx;
	}
	//if (level < 0.0)
	//{
	//	dy = -1 * dy;
	//}
	// Compute new window level
	double newWindowLevel[2];
	newWindowLevel[0] = dx + window;
	newWindowLevel[1] = level - dy;
	if (newWindowLevel[0] < 0.01)
	{
		newWindowLevel[0] = 0.01;
	}
	ASTransGeneralInteractor::SetArrayDataWindowLevel(m_crntTopData, newWindowLevel);
}

// ��Ӧ
void ASInteractorStyle2DGeneral::Move_Panning(const int c_x, const int c_y)
{
	this->FindPokedRenderer(c_x, c_y);
	this->Pan();
	this->InvokeEvent(vtkCommand::InteractionEvent, NULL);
}
void ASInteractorStyle2DGeneral::Move_Zooming(const int c_x, const int c_y)
{
	this->FindPokedRenderer(c_x, c_y);
	this->Dolly();
	this->InvokeEvent(vtkCommand::InteractionEvent, NULL);
	// ����ʱ��Ҫˢ�����������ߵĿ��Ƶ�뾶
	ASTransGeneralInteractor::GenerateViewZoom(m_ViewLabel);
}

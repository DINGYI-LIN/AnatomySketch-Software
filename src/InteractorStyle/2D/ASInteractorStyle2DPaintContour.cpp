#include "ASInteractorStyle2DPaintContour.h"
#include "ASTransGeneralInteractor.h"
#include "ASPipelineBase.h"
#include "ASVisualizationManager.h"
#include "ASFModelContour.h"
#include "ASTransContour.h"
#include "ASVisualizationManager.h"
#include <vtkPropPicker.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkObjectFactory.h>   //ʰȡ�й�
#include <math.h>

vtkStandardNewMacro(ASInteractorStyle2DPaintContour);

ASInteractorStyle2DPaintContour::ASInteractorStyle2DPaintContour()
{

}

ASInteractorStyle2DPaintContour::~ASInteractorStyle2DPaintContour()
{

}

//����ƶ�
void ASInteractorStyle2DPaintContour::OnMouseMove()
{
	if (ASPipelineBase::GetNumOfShowingObj2D() <= 0)
	{
		return;
	}
	int x = this->Interactor->GetEventPosition()[0];
	int y = this->Interactor->GetEventPosition()[1];
	this->HoverDetection(x, y);

	if (m_MoveState == 1 || m_MoveState == 4 || m_MoveState == 5)
	{
		m_picker->Pick(x, y, 0, this->GetDefaultRenderer());
		double posfinal[4];
		getPickPosFinal(posfinal, m_picker->GetPickPosition());
		//ʰȡ
		vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
		picker->Pick(x, y, 0, this->GetDefaultRenderer());
		vtkActor* pickedActor = picker->GetActor();
		if (pickedActor && ASTransContour::CheckFirstCtrlPoint(pickedActor, m_ViewLabel))
		{
			if (m_MoveState == 1)
			{
				// �ǵ�һ��
				ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Closetemp, pickedActor);
				m_MoveState = 4;
			}
			else if (m_MoveState == 5)
			{
				if (ASFModelContour::GetInterfaceModel() == 2 && m_isLeftButtonDown ||
					ASFModelContour::GetInterfaceModel() == 1)
				{
					ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Closetemp, pickedActor);
					m_MoveState = 4;
				}
			}
		}
		else
		{
			if (m_MoveState == 1)
			{
				ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Movetemp);
			}
			else if (m_MoveState == 5)
			{
				if (ASFModelContour::GetInterfaceModel() == 2 && m_isLeftButtonDown || 
					ASFModelContour::GetInterfaceModel() == 1)
				{
					double dis = sqrt(pow(m_TouchLastCtr[0] - posfinal[0], 2) + pow(m_TouchLastCtr[1] - posfinal[1], 2)
						+ pow(m_TouchLastCtr[2] - posfinal[2], 2));
					double Threshold = ASVisualizationManager::GetZoomPara(m_ViewLabel) / TouchThresholdCoeff;
					if (dis > Threshold)
					{
						m_TouchLastCtr[0] = posfinal[0];
						m_TouchLastCtr[1] = posfinal[1];
						m_TouchLastCtr[2] = posfinal[2];
						ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Add);
					}
					ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Movetemp);
					return;
				}
			}
			else
			{
				ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_ClosetempStop);
				if (ASFModelContour::GetInterfaceModel() == 0)
				{
					// ʹ�������ӿ��Ƶ�
					m_MoveState = 1;
				}
				else if (ASFModelContour::GetInterfaceModel() == 1)
				{
					// ʹ�������������
					m_MoveState = 5;
				}
				else if (ASFModelContour::GetInterfaceModel() == 2)
				{
					// ʹ�ô��ر���������
					if (m_isLeftButtonDown)
					{
						m_MoveState = 5;
					}
				}
			}			
		}
	}
	if (m_IsWinlev)
	{
		this->WinLevContinue();
	}
	else if (m_isLeftButtonDown)
	{
		m_picker->Pick(x, y, 0, this->GetDefaultRenderer());
		double posfinal[4];
		getPickPosFinal(posfinal, m_picker->GetPickPosition());
		switch (m_MoveState)
		{
		case -1:
			ASTransGeneralInteractor::SetVisualizationPosition(posfinal[0], posfinal[1], posfinal[2]);
			break;
		case 2:
			ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Moving);
			break;
		case 3:
			ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_InsertContinue);
			break;
		default:
			break;
		}
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
void ASInteractorStyle2DPaintContour::OnLeftButtonDown()
{
	m_isLeftButtonDown = true;

	if (ASPipelineBase::GetNumOfShowingObj2D() <= 0)
	{
		m_MoveState = 0;
		return;
	}

	int x = this->Interactor->GetEventPosition()[0];
	int y = this->Interactor->GetEventPosition()[1];
	m_picker->Pick(x, y, 0, this->GetDefaultRenderer());
	double posfinal[4];
	getPickPosFinal(posfinal, m_picker->GetPickPosition());
	
	if (this->Interactor->GetAltKey())
	{
		// Alt���´�λ����
		this->WinLevStart();
	}
	else if (this->Interactor->GetControlKey() && ASFModelContour::GetContourModleEnabled())
	{
		if (!ASTransContour::GetCurrentContourData())
		{
			return;
		}
		if (m_MoveState == 1)
		{
			// ��ӿ��Ƶ�
			ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Add);
		}
		else if (m_MoveState == 4)
		{
			// �պ�����
			ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Close);
			m_MoveState = 1;
		}
		else if (m_MoveState == -1 || ASFModelContour::GetInterfaceModel() == 2)
		{
			m_TouchLastCtr[0] = posfinal[0];
			m_TouchLastCtr[1] = posfinal[1];
			m_TouchLastCtr[2] = posfinal[2];
			ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Addtemp);
			ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Add);
			m_MoveState = 5;
		}
	}
	else if (this->Interactor->GetShiftKey() && ASFModelContour::GetContourModleEnabled())
	{
		// shift������ƽ�ƿ��Ƶ�
		//ʰȡ
		vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
		picker->Pick(x, y, 0, this->GetDefaultRenderer());
		vtkActor* pickedActor = picker->GetActor();
		if (pickedActor)
		{
			ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_MoveChoose, pickedActor);
			m_MoveState = 2;
		}
		else
		{
			m_MoveState = 0;
		}
	}
	else if (m_isKey_d_down == true && ASFModelContour::GetContourModleEnabled())
	{
		// d������ɾ�����Ƶ�
		//ʰȡ
		vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
		picker->Pick(x, y, 0, this->GetDefaultRenderer());
		vtkActor* pickedActor = picker->GetActor();
		if (pickedActor)
		{
			ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Delete, pickedActor);
		}
		m_MoveState = 0;
	}
	else if (m_isKey_a_down == true && ASFModelContour::GetContourModleEnabled())
	{
		// a�����ڲ�����Ƶ�
		ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_InsertStart);
		m_MoveState = 3;
	}
	else if (m_isKey_q_down == true && ASFModelContour::GetContourModleEnabled())
	{
		// q������ɾ����������
		//ʰȡ
		vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
		picker->Pick(x, y, 0, this->GetDefaultRenderer());
		vtkActor* pickedActor = picker->GetActor();
		if (pickedActor)
		{
			ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_DeleteWhole, pickedActor);
		}
		m_MoveState = 0;
	}
	else
	{
		m_MoveState = -1;
		// ��ͨ�������л�����
		ASTransGeneralInteractor::SetVisualizationPosition(posfinal[0], posfinal[1], posfinal[2]);
	}	
}
//������̧��
void ASInteractorStyle2DPaintContour::OnLeftButtonUp()
{
	m_isLeftButtonDown = false;
	m_IsWinlev = false;
	if (ASPipelineBase::GetNumOfShowingObj2D() <= 0)
	{
		return;
	}
	if (ASFModelContour::GetInterfaceModel() == 2)
	{
		if (m_MoveState == 5)
		{
			int x = this->Interactor->GetEventPosition()[0];
			int y = this->Interactor->GetEventPosition()[1];
			m_picker->Pick(x, y, 0, this->GetDefaultRenderer());
			double posfinal[4];
			getPickPosFinal(posfinal, m_picker->GetPickPosition());
			m_MoveState = -1;
			ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Deletetemp, nullptr);
		}
		else if (m_MoveState == 4)
		{
			int x = this->Interactor->GetEventPosition()[0];
			int y = this->Interactor->GetEventPosition()[1];
			m_picker->Pick(x, y, 0, this->GetDefaultRenderer());
			double posfinal[4];
			getPickPosFinal(posfinal, m_picker->GetPickPosition());
			// ����ģʽ
			ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Close);
			ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Deletetemp, nullptr);
			m_MoveState = -1;
		}
	}
}
void ASInteractorStyle2DPaintContour::OnMouseWheelForward()
{
	if (ASPipelineBase::GetNumOfShowingObj2D() <= 0 || m_isMiddleButtonDown || m_isLeftButtonDown || m_isRightButtonDown)
	{
		return;
	}
	if (m_MoveState == 1)
	{
		m_MoveState = -1;
		int x = this->Interactor->GetEventPosition()[0];
		int y = this->Interactor->GetEventPosition()[1];
		m_picker->Pick(x, y, 0, this->GetDefaultRenderer());
		double posfinal[4];
		getPickPosFinal(posfinal, m_picker->GetPickPosition());
		ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Deletetemp, nullptr);
	}
	// Ĭ�ϲ��� �л�����
	double Posfinal[3];
	double Spaing[3];
	ASVisualizationManager::GetDisplayPosition(Posfinal);
	ASVisualizationManager::GetDisplaySpacing(Spaing);
	Posfinal[m_ViewLabel] += Spaing[m_ViewLabel];
	ASTransGeneralInteractor::SetVisualizationPosition(Posfinal[0], Posfinal[1], Posfinal[2]);
}
void ASInteractorStyle2DPaintContour::OnMouseWheelBackward()
{
	if (ASPipelineBase::GetNumOfShowingObj2D() <= 0 || m_isMiddleButtonDown || m_isLeftButtonDown || m_isRightButtonDown)
	{
		return;
	}
	if (m_MoveState == 1)
	{
		m_MoveState = -1;
		int x = this->Interactor->GetEventPosition()[0];
		int y = this->Interactor->GetEventPosition()[1];
		m_picker->Pick(x, y, 0, this->GetDefaultRenderer());
		double posfinal[4];
		getPickPosFinal(posfinal, m_picker->GetPickPosition());
		ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Deletetemp, nullptr);
	}
	// Ĭ�ϲ��� �л�����
	double Posfinal[3];
	double Spaing[3];
	ASVisualizationManager::GetDisplayPosition(Posfinal);
	ASVisualizationManager::GetDisplaySpacing(Spaing);
	Posfinal[m_ViewLabel] -= Spaing[m_ViewLabel];
	ASTransGeneralInteractor::SetVisualizationPosition(Posfinal[0], Posfinal[1], Posfinal[2]);
}
// ����
void ASInteractorStyle2DPaintContour::OnKeyPress()
{
	// Get the keypress
	vtkRenderWindowInteractor *rwi = this->Interactor;
	std::string key = rwi->GetKeySym();
	if (key == "a" || key == "A")
	{
		m_isKey_a_down = true;
	}
	if (key == "d" || key == "D")
	{
		m_isKey_d_down = true;
	}
	if (key == "q" || key == "Q")
	{
		m_isKey_q_down = true;
	}
	if (key == "Control_L" || key == "Control_R")
	{
		m_isKey_Ctrl_down = true;
		if (ASFModelContour::GetContourModleEnabled() == false)
		{
			return;
		}
		int x = this->Interactor->GetEventPosition()[0];
		int y = this->Interactor->GetEventPosition()[1];
		m_picker->Pick(x, y, 0, this->GetDefaultRenderer());
		double posfinal[4];
		getPickPosFinal(posfinal, m_picker->GetPickPosition());
		if (ASFModelContour::GetInterfaceModel() == 2 && m_isLeftButtonDown ||
			ASFModelContour::GetInterfaceModel() == 1)
		{
			// ����ģʽ
			m_TouchLastCtr[0] = posfinal[0];
			m_TouchLastCtr[1] = posfinal[1];
			m_TouchLastCtr[2] = posfinal[2];
			ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Addtemp);
			ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Add);
			m_MoveState = 5;
		}
		else if (ASFModelContour::GetInterfaceModel() == 0)
		{
			// �Ǵ���ģʽ
			ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Addtemp);
			m_MoveState = 1;
		}
	}
}
void ASInteractorStyle2DPaintContour::OnKeyRelease()
{
	// Get the keypress
	vtkRenderWindowInteractor *rwi = this->Interactor;
	std::string key = rwi->GetKeySym();
	if (key == "a" || key == "A")
	{
		m_isKey_a_down = false;
	}
	if (key == "d" || key == "D")
	{
		m_isKey_d_down = false;
	}
	if (key == "q" || key == "Q")
	{
		m_isKey_q_down = false;
	}
	if (key == "Control_L" || key == "Control_R")
	{
		m_isKey_Ctrl_down = false;
		if (m_MoveState == 1 || m_MoveState == 5)
		{
			int x = this->Interactor->GetEventPosition()[0];
			int y = this->Interactor->GetEventPosition()[1];
			m_picker->Pick(x, y, 0, this->GetDefaultRenderer());
			double posfinal[4];
			getPickPosFinal(posfinal, m_picker->GetPickPosition());
			m_MoveState = -1;
			ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Deletetemp, nullptr);
		}
		if (m_MoveState == 4 && ASFModelContour::GetInterfaceModel())
		{
			int x = this->Interactor->GetEventPosition()[0];
			int y = this->Interactor->GetEventPosition()[1];
			m_picker->Pick(x, y, 0, this->GetDefaultRenderer());
			double posfinal[4];
			getPickPosFinal(posfinal, m_picker->GetPickPosition());
			// ����ģʽ
			ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Close);
			ASTransContour::SplineContourOperation(posfinal, m_ViewLabel, CtrOpe_Deletetemp, nullptr);
			m_MoveState = -1;
		}
	}
}
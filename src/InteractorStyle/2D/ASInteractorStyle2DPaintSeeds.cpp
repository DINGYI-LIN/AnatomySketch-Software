#include "ASInteractorStyle2DPaintSeeds.h"
#include "ASTransGeneralInteractor.h"
#include "ASPipelineBase.h"
#include "ASVisualizationManager.h"
#include "ASFModelSeeds.h"
#include "ASTransSeeds.h"
#include "ASTransContour.h"
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkObjectFactory.h>   //ʰȡ�й�

vtkStandardNewMacro(ASInteractorStyle2DPaintSeeds);

ASInteractorStyle2DPaintSeeds::ASInteractorStyle2DPaintSeeds()
{

}

ASInteractorStyle2DPaintSeeds::~ASInteractorStyle2DPaintSeeds()
{

}

//����ƶ�
void ASInteractorStyle2DPaintSeeds::OnMouseMove()
{
	if (ASPipelineBase::GetNumOfShowingObj2D() <= 0)
	{
		return;
	}
	int x = this->Interactor->GetEventPosition()[0];
	int y = this->Interactor->GetEventPosition()[1];
	this->HoverDetection(x, y);
	if (m_IsWinlev)
	{
		this->WinLevContinue();
	}
	else if (m_isLeftButtonDown)
	{
		if (m_isPaintingSeeds)
		{
			// Ctrl���£������ӵ�
			m_picker->Pick(x, y, 0, this->GetDefaultRenderer());
			double posfinal[4];
			getPickPosFinal(posfinal, m_picker->GetPickPosition());
			ASTransSeeds::ContinuePaintSeeds(posfinal, m_ViewLabel);
		}
		else
		{
			// ��ͨ�������л�����
			if (m_isLeftButtonDown)
			{
				m_picker->Pick(x, y, 0, this->GetDefaultRenderer());
				double posfinal[4];
				getPickPosFinal(posfinal, m_picker->GetPickPosition());
				ASTransGeneralInteractor::SetVisualizationPosition(posfinal[0], posfinal[1], posfinal[2]);
			}
			else if (m_isMiddleButtonDown)
			{
				this->FindPokedRenderer(x, y);
				this->Pan();
				this->InvokeEvent(vtkCommand::InteractionEvent, NULL);
			}
			else if (m_isRightButtonDown)
			{
				this->FindPokedRenderer(x, y);
				this->Dolly();
				this->InvokeEvent(vtkCommand::InteractionEvent, NULL);
			}
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
void ASInteractorStyle2DPaintSeeds::OnLeftButtonDown()
{
	m_isLeftButtonDown = true;

	if (ASPipelineBase::GetNumOfShowingObj2D() <= 0)
	{
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
	else if(this->Interactor->GetControlKey() && ASFModelSeeds::GetSeedsModleEnabled())
	{
		if (ASTransSeeds::GetCurrentSeedData() == nullptr)
		{
			return;
		}
		if (ASTransSeeds::GetCrntSeedsID() < 0)
		{
			return;
		}
		// Ctrl���£������ӵ�
		m_isPaintingSeeds = true;

		int x = this->Interactor->GetEventPosition()[0];
		int y = this->Interactor->GetEventPosition()[1];
		m_picker->Pick(x, y, 0, this->GetDefaultRenderer());
		double posfinal[4];
		getPickPosFinal(posfinal, m_picker->GetPickPosition());
		ASTransSeeds::StartPaintSeeds(posfinal, m_ViewLabel);
	}
	else
	{
		// ��ͨ�������л�����
		m_isPaintingSeeds = false;
		ASTransGeneralInteractor::SetVisualizationPosition(posfinal[0], posfinal[1], posfinal[2]);
	}	
}
//������̧��
void ASInteractorStyle2DPaintSeeds::OnLeftButtonUp()
{
	m_isLeftButtonDown = false;
	m_IsWinlev = false;
	if (m_isPaintingSeeds)
	{
		ASTransSeeds::EndPaintSeeds();
		m_isPaintingSeeds = false;
	}
	if (ASPipelineBase::GetNumOfShowingObj2D() <= 0)
	{
		return;
	}
}
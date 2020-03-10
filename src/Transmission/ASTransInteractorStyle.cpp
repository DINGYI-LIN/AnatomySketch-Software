#include "ASTransInteractorStyle.h"
#include "ASInteractorStyleManager.h"
#include "ASInteractorStyle2DGeneral.h"
#include "ASInteractorStyle3DGeneral.h"

ASTransInteractorStyle* ASTransInteractorStyle::ms_GeneralInteractor = nullptr;

ASTransInteractorStyle::ASTransInteractorStyle(QObject *parent)
	: ASTransmissionBase(parent)
{
	ms_GeneralInteractor = this;
}

ASTransInteractorStyle::~ASTransInteractorStyle()
{

}

// Ψһ����
ASTransInteractorStyle* ASTransInteractorStyle::GetSelfPointer()
{
	return ms_GeneralInteractor;
}
// ���õ�ǰ2D������ʽ��InteractorStyle2D_
void ASTransInteractorStyle::SetInteratorStyle2D(const int c_Interactor)
{
	ASInteractorStyleManager::setInteractorStyle2D(c_Interactor);
	ms_GeneralInteractor->signalInteractorStyle2DChanged(c_Interactor);
}
// ����˫ָƽ������
void ASTransInteractorStyle::TouchPan(const int c_ViewLabel, double* pos)
{
	if (c_ViewLabel < 3)
	{
		// 2D
		ASInteractorStyle2DGeneral* interactor = ASInteractorStyleManager::GetInteractorStyle2D(c_ViewLabel);
		interactor->TouchPan(pos);
	}
	else if (c_ViewLabel == 3)
	{
		// 3D
		ASInteractorStyle3DGeneral* interactor = ASInteractorStyleManager::GetInteractorStyle3D();
		interactor->TouchPan(pos);
	}
}
void ASTransInteractorStyle::TouchZoom(const int c_ViewLabel, const double c_Factor)
{
	if (c_ViewLabel < 3)
	{
		// 2D
		ASInteractorStyle2DGeneral* interactor = ASInteractorStyleManager::GetInteractorStyle2D(c_ViewLabel);
		interactor->TouchZoom(c_Factor);
	}
	else if (c_ViewLabel == 3)
	{
		// 3D
		ASInteractorStyle3DGeneral* interactor = ASInteractorStyleManager::GetInteractorStyle3D();
		interactor->TouchZoom(c_Factor);
	}
}
void ASTransInteractorStyle::TouchWheel(const int c_ViewLabel, const double c_dis)
{
	if (c_ViewLabel < 3)
	{
		// 2D
		ASInteractorStyle2DGeneral* interactor = ASInteractorStyleManager::GetInteractorStyle2D(c_ViewLabel);
		interactor->TouchWheel(c_dis);
	}
}

#include "ASPaintingLandmarkWidget.h"
#include "ASTransLandmark.h"
#include "ASLandMarkItemWidget.h"
#include "ASDataStructureWalker.h"
#include "ASAbstractData.h"
#include "ASLandmarkData.h"
#include "ASInteractorStyleManager.h"
#include "ASTransInteractorStyle.h"
#include "ASTransGlobalKeyBoard.h"
#include "ASTransGeneralInteractor.h"
#include <QVBoxLayout>

ASPaintingLandmarkWidget::ASPaintingLandmarkWidget(QWidget *parent)
	: ASWidgetInSideBarBase(parent)
{
	this->UIInit();
	this->setStyleSheet("padding: 2px;");

	// ����transmission�ź�
	connect(ASTransInteractorStyle::GetSelfPointer(), SIGNAL(signalInteractorStyle2DChanged(int)), 
		this, SLOT(slotInteractorStyle2DChanged(int)));
}

ASPaintingLandmarkWidget::~ASPaintingLandmarkWidget()
{

}

void ASPaintingLandmarkWidget::SetEnabled(const bool c_bEnabled)
{
	if (c_bEnabled == ASFModelLandmark::GetLandmarkModleEnabled())
	{
		return;
	}
	ASTransLandmark::SetModelEnabled(c_bEnabled);
}

// �����ʼ��
void ASPaintingLandmarkWidget::UIInit()
{

}
// �����ǰ������ʽ�ı�
void ASPaintingLandmarkWidget::slotInteractorStyle2DChanged(int interactor)
{
	if (interactor == InterStyle2D_PaintingLandmarks)
	{
		this->SetEnabled(true);
	}
	else
	{
		this->SetEnabled(false);
	}
}
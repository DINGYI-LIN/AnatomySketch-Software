#include "ASWidgetInSideBarBase.h"

ASWidgetInSideBarBase::ASWidgetInSideBarBase(QWidget *parent)
	: QWidget(parent)
{
	//�����û�е���Ǹ�������ƶ������ڴ��ڱ߽�����
	setMouseTracking(true);
}

ASWidgetInSideBarBase::~ASWidgetInSideBarBase()
{
}

void ASWidgetInSideBarBase::SetEnabled(const bool c_bEnabled)
{

}
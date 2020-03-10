#pragma once

#include "ASWidgetInSideBarBase.h"
#include <QPushButton>
#include <QListWidget>
#include <QMenu>
#include <QAction>

class ASLandMarkItemWidget;

class ASPaintingLandmarkWidget : public ASWidgetInSideBarBase
{
	Q_OBJECT

public:
	ASPaintingLandmarkWidget(QWidget *parent);
	~ASPaintingLandmarkWidget();

	virtual void SetEnabled(const bool c_bEnabled);

private:

	// �����ʼ��
	void UIInit();

signals:

private slots :

	// �����ǰ������ʽ�ı�
	void slotInteractorStyle2DChanged(int interactor);
};

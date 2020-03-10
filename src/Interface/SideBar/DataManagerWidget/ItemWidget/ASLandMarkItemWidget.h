#pragma once

#include "ASMarkEleItemWidget.h"
#include <QString>
#include <QColor>
#include <QCheckBox>
#include <QLabel>
#include <QListWidgetItem>

class ASLandMarkItemWidget : public ASMarkEleItemWidget
{
	Q_OBJECT

public:
	ASLandMarkItemWidget(QWidget *parent);
	~ASLandMarkItemWidget();

	// ID
	virtual int getMarkEleID();
	// Focus
	virtual void SetFocus(const bool c_f);
	// ����
	void SetLandmarkID(const int c_ID);
	int GetLandmarkID();
	void SetColor(const QColor c_Color);

private:

	int m_LandmarkID;
	// ����Ԫ��
	//QLabel* m_LabelLabel; // ռλ
	//QLabel* m_LabelColor;

	void UIInit();

protected slots:

	virtual void slotCheckboxStateChanged(int state);
};

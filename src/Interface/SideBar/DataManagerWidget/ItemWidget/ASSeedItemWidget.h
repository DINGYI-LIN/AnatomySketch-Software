#pragma once

#include "ASMarkEleItemWidget.h"
#include <QString>
#include <QColor>
#include <QCheckBox>
#include <QLabel>
#include <QListWidgetItem>

class ASSeedItemWidget : public ASMarkEleItemWidget
{
	Q_OBJECT

public:
	ASSeedItemWidget(QWidget *parent);
	~ASSeedItemWidget();

	// ID
	virtual int getMarkEleID();
	// Focus
	virtual void SetFocus(const bool c_f);
	// ����
	void SetSeedID(const int c_ID);
	int GetSeedID();
	void SetLabel(const int c_Label);
	void SetColor(const QColor c_Color);

private:

	int m_SeedID;
	// ����Ԫ��
	//QLabel* m_LabelLabel;
	//QLabel* m_LabelColor;

	void UIInit();

private slots:

	virtual void slotCheckboxStateChanged(int state);

};

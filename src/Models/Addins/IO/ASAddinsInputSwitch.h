#pragma once

#include "ASAddinsInputBase.h"
#include <QComboBox>

class ASAddinsInputSwitch : public ASAddinsInputBase
{
public:
	ASAddinsInputSwitch(ASAddinsBase* parent);
	~ASAddinsInputSwitch();

	// Value
	virtual void SetValue(const QStringList c_value);
	// QComboBox
	QComboBox* GetComboBox();
	// �õ���ָ�룬����argc��sΪ����
	virtual void* GetVoidPoint(const QString s);

private:

	QComboBox* m_ComboBox = nullptr;
	int m_dPara;


};

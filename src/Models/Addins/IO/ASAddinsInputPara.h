#pragma once

#include "ASAddinsInputBase.h"
#include <QDoubleSpinBox>

class ASAddinsInputPara : public ASAddinsInputBase
{
public:
	ASAddinsInputPara(ASAddinsBase* parent);
	~ASAddinsInputPara();

	// Value
	virtual void SetValue(const QStringList c_value);
	// QDoubleSpinBox
	QDoubleSpinBox* GetDouSpinBox();
	// �õ���ָ�룬����argc��sΪ����
	virtual void* GetVoidPoint(const QString s);
	// �������뵽Python�����е���ʱ�ļ�.1�ɹ���-1ʧ��
	virtual int PythonInputGenerate();
	// Para
	void SetParaValue(const double c_value);

private:
	
	QDoubleSpinBox* m_DouSpinBox = nullptr;
	double m_dPara;

};

#pragma once

#include "ASAddinsOutputNode.h"
#include <QLineEdit>

class ASAddinsOutputParameter : public ASAddinsOutputNode
{
public:
	ASAddinsOutputParameter(ASAddinsBase* parent);
	~ASAddinsOutputParameter();

	// �õ���ָ�룬����argc��sΪ����
	virtual void* GetVoidPoint(const QString s);
	virtual void GenerateFinished(const int InterfaceType = 0);
	// QLineEdit
	QLineEdit* GetLineEdit();

private:

	QLineEdit* m_LineEdit = nullptr;
	double m_dPara;

};

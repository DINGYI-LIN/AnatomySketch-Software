#pragma once

#include "ASAbstractData.h"
#include <QColor>

class ASMarkData : public ASAbstractData
{
public:
	ASMarkData();
	~ASMarkData();
	virtual void DeleteNode();	// ���ô˺������ͷŽڵ�

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type); // �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
	virtual bool isTypeAbsolute(const int c_Type);
	static bool isTypeInheritedStatic(const int c_Type);

	// ��ɫ
	void setColor(const QColor c_Color);
	QColor getColor();

protected:
	QColor m_Color;

};

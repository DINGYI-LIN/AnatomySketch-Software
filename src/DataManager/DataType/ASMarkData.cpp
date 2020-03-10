#include "ASMarkData.h"

// �̳�ʱ��Ҫ�ڹ��캯�����趨 m_Datatype�� ����дwalkerCheck����

ASMarkData::ASMarkData()
{
	m_Datatype = DataType_MarkData;
}

ASMarkData::~ASMarkData()
{
}

// ���ô˺������ͷŽڵ�
void ASMarkData::DeleteNode()
{
	delete this;
}

// ���������ж�
// �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
bool ASMarkData::isTypeInherited(const int c_Type)
{
	if (c_Type == DataType_MarkData || ASAbstractData::isTypeInherited(c_Type))
	{
		return true;
	}
	return false;
}
bool ASMarkData::isTypeAbsolute(const int c_Type)
{
	if (c_Type == DataType_MarkData)
	{
		return true;
	}
	return false;
}
bool ASMarkData::isTypeInheritedStatic(const int c_Type)
{
	if (c_Type == DataType_MarkData || ASAbstractData::isTypeInheritedStatic(c_Type))
	{
		return true;
	}
	return false;
}

// ��ɫ
void ASMarkData::setColor(const QColor c_Color)
{
	m_Color = c_Color;
}
QColor ASMarkData::getColor()
{
	return m_Color;
}

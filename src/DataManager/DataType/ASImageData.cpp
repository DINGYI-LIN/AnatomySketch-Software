#include "ASImageData.h"

ASImageData::ASImageData()
{
	m_Datatype = DataType_ImageData;
}

ASImageData::~ASImageData()
{
}

// ���ô˺������ͷŽڵ�
void ASImageData::DeleteNode()
{
	delete this;
}
// ���������ж�
// �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
bool ASImageData::isTypeInherited(const int c_Type)
{
	if (c_Type == DataType_ImageData || ASAbstractData::isTypeInherited(c_Type))
	{
		return true;
	}
	return false;
}
bool ASImageData::isTypeAbsolute(const int c_Type)
{
	if (c_Type == DataType_ImageData)
	{
		return true;
	}
	return false;
}
bool ASImageData::isTypeInheritedStatic(const int c_Type)
{
	if (c_Type == DataType_ImageData || ASAbstractData::isTypeInheritedStatic(c_Type))
	{
		return true;
	}
	return false;
}
#include "ASAnnotation.h"

// �̳�ʱ��Ҫ�ڹ��캯�����趨 m_Datatype�� ����дwalkerCheck����

ASAnnotation::ASAnnotation()
{
	m_Datatype = DataType_Annotation;
}

ASAnnotation::~ASAnnotation()
{
}

// ���ô˺������ͷŽڵ�
void ASAnnotation::DeleteNode()
{
	delete this;
}

// ���������ж�
// �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
bool ASAnnotation::isTypeInherited(const int c_Type)
{
	if (c_Type == DataType_Annotation || ASAbstractData::isTypeInherited(c_Type))
	{
		return true;
	}
	return false;
}
bool ASAnnotation::isTypeAbsolute(const int c_Type)
{
	if (c_Type == DataType_Annotation)
	{
		return true;
	}
	return false;
}
bool ASAnnotation::isTypeInheritedStatic(const int c_Type)
{
	if (c_Type == DataType_Annotation || ASAbstractData::isTypeInheritedStatic(c_Type))
	{
		return true;
	}
	return false;
}

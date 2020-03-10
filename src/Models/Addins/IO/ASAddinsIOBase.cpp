#include "ASAddinsIOBase.h"

ASAddinsIOBase::ASAddinsIOBase(ASAddinsBase* parent)
{
	m_Parent = parent;
}

ASAddinsIOBase::~ASAddinsIOBase()
{

}

// Type
int ASAddinsIOBase::GetType()
{
	return m_Type;
}
bool ASAddinsIOBase::isInput()
{
	return true;
}
// Name
void ASAddinsIOBase::SetName(const QString c_name)
{
	this->m_Name = c_name;
}
QString ASAddinsIOBase::GetName()
{
	return m_Name;
}
// �õ���ָ�룬����argc��sΪ����
void* ASAddinsIOBase::GetVoidPoint(const QString s)
{
	return nullptr;
}
// �������뵽Python�����е���ʱ�ļ�
int ASAddinsIOBase::PythonInputGenerate()
{
	return -1;
}
// ������ͷ�����
void ASAddinsIOBase::FreeMemory()
{

}
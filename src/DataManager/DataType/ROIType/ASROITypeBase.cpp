#include "ASROITypeBase.h"

// �̳�ʱ��Ҫ�ڹ��캯�����趨 m_Datatype�� ����дwalkerCheck����

ASROITypeBase::ASROITypeBase()
{
	m_ROIType = ROIType_Base;
}

ASROITypeBase::~ASROITypeBase()
{
}

// ���ô˺������ͷŽڵ�
void ASROITypeBase::DeleteNode()
{
	delete this;
}

// ���������ж�
// �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
bool ASROITypeBase::isTypeInherited(const int c_Type)
{
	if (c_Type == ROIType_Base)
	{
		return true;
	}
	return false;
}
bool ASROITypeBase::isTypeAbsolute(const int c_Type)
{
	if (c_Type == ROIType_Base)
	{
		return true;
	}
	return false;
}
bool ASROITypeBase::isTypeInheritedStatic(const int c_Type)
{
	if (c_Type == ROIType_Base)
	{
		return true;
	}
	return false;
}
int ASROITypeBase::GetROIType()
{
	return m_ROIType;
}

void ASROITypeBase::GetCenter(double* center)
{

}

// ROIID
void ASROITypeBase::SetROIID(const int c_nID)
{
	m_ROIID = c_nID;
}
int ASROITypeBase::GetROIID()
{
	return m_ROIID;
}
// Name
void ASROITypeBase::SetName(const QString c_Name)
{
	m_Name = c_Name;
}
QString ASROITypeBase::GetName()
{
	return m_Name;
}
// Shown
void ASROITypeBase::SetShown(const bool c_shown)
{
	m_isShown = c_shown;
}
bool ASROITypeBase::isShown()
{
	return m_isShown;
}
// Color
void ASROITypeBase::SetColor(QColor color)
{
	m_Color = color;
}
QColor ASROITypeBase::GetColor()
{
	return m_Color;
}
#include "ASPipelineBase.h"

int ASPipelineBase::ms_NumOfShowingObj2D = 0;
int ASPipelineBase::ms_NumOfObj2D = 0;

ASPipelineBase::ASPipelineBase(const int c_ID)
{
	m_IDOfPipeline = c_ID;
	m_PipelineType = PipeLineType_Base;
}

ASPipelineBase::~ASPipelineBase()
{

}

// ���������ж�
bool ASPipelineBase::isTypeInherited(const int c_Type)
{
	if (c_Type == PipeLineType_Base)
	{
		return true;
	}
	return false;
}
bool ASPipelineBase::isTypeAbsolute(const int c_Type)
{
	if (c_Type == PipeLineType_Base)
	{
		return true;
	}
	return false;
}

// ID
int ASPipelineBase::getIDOfPipeline()
{
	return m_IDOfPipeline;
}
int ASPipelineBase::getIDOfData()
{
	return m_IDOfData;
}
// Type
int ASPipelineBase::GetPipeLineType()
{
	return this->m_PipelineType;
}

// �麯��
// ���ô˺������ͷŹ���
void ASPipelineBase::DeleteNode()
{
	delete this;
}
// ���ö�Ӧ���ݵ�ID
void ASPipelineBase::SetDataID(const int c_DataID)
{
	this->m_IDOfData = c_DataID;
}
// ��ͼ����ı�
void ASPipelineBase::Update2DTransformMatrix()
{

}
// �Ƿ���ʾ
void ASPipelineBase::SetShown(const bool c_Shown)
{

}
// ������ʾ
void ASPipelineBase::ReinitDisplay()
{

}

// �õ���ǰ��ά������ʾ�����Ķ�����Ŀ
int ASPipelineBase::GetNumOfShowingObj2D()
{
	return ms_NumOfShowingObj2D;
}
// �õ���ǰ��ά�������еĶ�����Ŀ
int ASPipelineBase::GetNumOfObj2D()
{
	return ms_NumOfObj2D;
}

#pragma once

// ����
#define PipeLineType_Base			0
#define PipeLineType_ArrayImage		1
#define PipeLineType_PolyImage		2
#define PipeLineType_CrossLine2D	3
#define PipeLineType_OuterBorder3D	4
#define PipeLineType_Mask			5
#define PipeLineType_Seeds			6
#define PipeLineType_Contour		7
#define PipeLineType_Landmark		8
#define PipeLineType_Text			9
#define PipeLineType_ROICube		10

class ASPipelineBase
{
public:
	ASPipelineBase(const int c_ID);
	~ASPipelineBase();

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type); 
	virtual bool isTypeAbsolute(const int c_Type);

	// ID
	int getIDOfPipeline();
	int getIDOfData();
	// Type
	int GetPipeLineType();

	// �麯��
	virtual void DeleteNode();	// ���ô˺������ͷŹ���
	virtual void SetDataID(const int c_DataID); // ���ö�Ӧ���ݵ�ID
	virtual void Update2DTransformMatrix(); // ��ͼ����ı�
	virtual void SetShown(const bool c_Shown); // �Ƿ���ʾ
	virtual void ReinitDisplay(); // ������ʾ

	
	static int GetNumOfShowingObj2D();	// �õ���ǰ��ά������ʾ�����Ķ�����Ŀ
	static int GetNumOfObj2D();	// �õ���ǰ��ά�������еĶ�����Ŀ

protected:
	int m_PipelineType = -1;	// ��Ⱦ��������
	int m_IDOfPipeline = -1;	// ��Ⱦ���ߵ�ID
	int m_IDOfData = -1;		// ��Ӧ�����ݵ�ID��

	static int ms_NumOfShowingObj2D;
	static int ms_NumOfObj2D;

private:


};

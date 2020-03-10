#pragma once
#include <QList>

class ASPipelineBase;

// �������ݴ洢�ṹ�ı���
// ���� for (ASPipelineBase* item = ASPipelineManager::bigen_single(PipeLineType_ArrayImage); item != nullptr; item = ASPipelineManager::next_single(PipeLineType_ArrayImage)){}
//      for (ASPipelineBase* item = ASPipelineManager::bigen_inherit(PipeLineType_ArrayImage); item != nullptr; item = ASPipelineManager::next_inherit(PipeLineType_ArrayImage)){}

// ���ҹ���
// QList<ASPipelineBase*>* listPipe = new QList<ASPipelineBase*>;
// ASPipelineManager::GetPipelineForDataID(listPipe, ID);

class ASPipelineManager
{
public:
	ASPipelineManager();
	~ASPipelineManager();

	// �½����Ƴ�����
	static ASPipelineBase* AddPipeline(const int c_TypeOfPipeline); // �½����ߣ����ع���ָ��
	static void RemovePipeline(ASPipelineBase* pPipeline);
	// �������й��ߵ�Update2DTransformMatrix���������½���
	static void UpdatePipeline2DTransformMatrix();
	// ������ID���ҹ��ߣ�һ�����ݿ��ܶ�Ӧ�������
	static void GetPipelineForDataID(QList<ASPipelineBase*>* pList, const int c_DataID);

	// ��Ⱦ���ߵı���
	static ASPipelineBase* bigen_inherit(int type);
	static ASPipelineBase* bigen_single(int type);
	static ASPipelineBase* next_inherit(int type);
	static ASPipelineBase* next_single(int type);

private:

	// Ψһ����
	static ASPipelineManager* m_PipelineManager;
	// �洢���ߵ��б�
	QList<ASPipelineBase*>* m_listPipeline;
	// ���ڹ��߱������������λ��
	static int m_PosTraversing;

};

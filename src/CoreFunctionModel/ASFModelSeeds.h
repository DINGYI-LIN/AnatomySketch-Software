#pragma once
#include "ASFunctionModelBase.h"

class ASPipelineSeeds;

class ASFModelSeeds : public ASFunctionModelBase
{
	Q_OBJECT

public:
	ASFModelSeeds(QObject *parent = 0);
	~ASFModelSeeds();

	// ��ǰ���Ƶ����ӵ��ID
	void SetIDOfPaintingData(const int c_ID);
	static int GetIDOfPaintingData();
	// ģ��ʹ��״̬
	void SetSeedsModleEnabled(const bool c_enabled);
	static bool GetSeedsModleEnabled();
	// û�������߾ͽ�������
	void InitSeedsPipeline();
	// �������ӵ�
	void StartPaintingData(double* pPosition);
	void ContinuePaintingData(double* pPosition);
	// ɾ�����ӵ�
	void DeleteSeeds(const int c_DataID, const int c_SeedID);
	// ˢ�����ӵ���ʾ
	void RefreshSeedsDisplay();
	// ���ӵ�����Ƿ���ʾ��û��2D����ʱ����ʾ���ӵ�
	void SetSeedShown(const bool c_Shown);
	// ���ӵ����ݷ����仯ʱ��������Ҫ���������б�����˵ɾ�����ӵ��ļ�ʱ���������б��еĶ�ӦID �޳�
	void AdjustUndoList();

	// ��ȡ���ӵ�����
	void LoadSeedData(const QString c_FileName);

private:
	// Ψһ����
	static ASFModelSeeds* ms_FModelSeeds;

	// ��ǰ���Ƶ����ӵ��ID
	int m_IDOfPaintingData = -1;
	// ģ��ʹ��״̬
	bool m_SeedModelEnabled = false;
	// ���ӵ�ģ���Ƿ���ʾ
	bool m_SeedsShown = false;

	// ���ӵ���ʾ����
	ASPipelineSeeds* m_SeedPipeLine = nullptr;

	// �������˳��
	QList<int>* m_OperationSequence;

private slots:
	

};

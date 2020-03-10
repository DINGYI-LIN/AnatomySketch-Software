#pragma once
#include "ASTransmissionBase.h"

class ASAbstractData;
class ASFModelSeeds;
class ASSeedData;

class ASTransSeeds : public ASTransmissionBase
{
	Q_OBJECT

public:
	ASTransSeeds(QObject *parent = 0);
	~ASTransSeeds();

	// Ψһ����
	static ASTransSeeds* GetSelfPointer();
	//��ǰSeedsID
	static void SetCrntSeedsID(const int c_id);
	static int GetCrntSeedsID();
	// �õ���ǰ���ӵ��ļ�
	static ASSeedData* GetCurrentSeedData();
	// �½����ӵ��ļ�
	static void NewSeedsData(ASAbstractData* pParent);
	static void NewSeedsData(ASAbstractData* pParent, QString name, int label, QColor color);
	// ˢ�����ӵ�����б�
	static void UpdateListsOfSeedData();
	// ����ģ���Ƿ�ʹ��
	static void SetModelEnabled(const bool c_enable);
	// ˢ�����ӵ��б�
	static void RefreshSeedsList();
	// ���õ�ǰ���ڻ��Ƶ����ӵ����ݵ�ID
	//static void SetPaintingSeedsID(const int c_ID);
	// �������ӵ�
	static void StartPaintSeeds(double* pPosition, const int c_ViewLabel);
	static void ContinuePaintSeeds(double* pPosition, const int c_ViewLabel);
	static void EndPaintSeeds();
	// ˢ�����ӵ���ʾ
	static void RefreshSeedsDisplay();
	// ���ӵ��Ƿ���ʾ
	static void SetSeedShown(const bool c_Shown);
	// ����һ��
	static void UndoPaintingSedds();
	// ���ӵ����ݷ����仯ʱ��������Ҫ���������б�����˵ɾ�����ӵ��ļ�ʱ���������б��еĶ�ӦID �޳�
	static void AdjustUndoList();
	// ��Ӳ�̶��ļ�
	static void LoadseedDataFromDisk(const QStringList c_FileNameList);
	// �Ƴ�������
	static void RemoveSeeds(const int c_SeedDataID, const int c_SeedID);

private:
	// Ψһ����
	static ASTransSeeds* ms_SelfPointer;
	// ���ӵ�ģ��
	ASFModelSeeds* m_FModelSeeds;
	// �����еĽڵ�
	ASSeedData* m_WorkingSeedData = nullptr;
	// ��ǰSeedID
	int m_CurrentSeedID = -1;

	//void fNewSeedData(QString name, int label, QColor color);

signals :

	// ���ý����ģ��ʹ��״̬
	void signalSetModelEnabled(bool enabled);
};

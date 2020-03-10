#pragma once
#include "ASTransmissionBase.h"
#include <QStringList>
#include <QMessageBox>
#include <QAbstractButton>

class ASFModelImportDataFromDisk;
class ASFModelExportDataToDisk;
class ASAbstractData;
class ASArrayImageData;

class ASTransAddDeleteData : public ASTransmissionBase
{
	Q_OBJECT

public:
	ASTransAddDeleteData(QObject *parent = 0);
	~ASTransAddDeleteData();

	// Ψһ����
	static ASTransAddDeleteData* GetSelfPointer();

	// ��Ӳ�̶�ȡ����
	static void LoadDataFromDisk(const QStringList c_FileNameList); // ��ʼ��ȡ
	static void LoadDataFromDiskFinished(ASAbstractData* NewDataNode, int Type); // ���һ��																				 
	static void LoadDataStopManualyFinished(); // ��Ӳ�̶�ȡ���ݹ����б�ȡ�����߳��˳����
	static void AddLoadWaitingArea(const QStringList c_strlist, const int c_type);
	// �������ݵ�Ӳ��
	static void SaveOneDataToDisk(ASAbstractData* SaveDataNode);
	static void SaveAllPolyDataToDisk();
	static void StartSaveDataToDisk();
	static void SaveDataToDiskFinished(); // �������
	static void SaveDataStopManualyFinished(); // �������ݹ����б�ȡ�����߳��˳����
	// �Ƴ�����
	static void RemoveDataNode(ASAbstractData* RemoveDataNode);
	static void RemoveAllDataNode();
	// �����������ƶ�����
	// ���뱻�ƶ������ݣ������Ի���ѡ����λ��
	static void MoveDataNode(ASAbstractData* DataNode);
	// 1 startID ���ƶ��ڵ��ID 
	// 2 FaterID �ƶ���λ�õĸ��ڵ��ID��-1Ϊ���ڵ�
	// 3 endPos  �ƶ���λ��Ϊ���ڵ�ĵڼ������ӣ������Ϊԭ�ڵ�ɾ��֮ǰ�����
	static void MoveDataNode(const int startID, const int FaterID, const int endPos);
	// �����¹���
	static void AddNewPipeline(ASAbstractData* NewDataNode, int Type);
	// �ļ����������ˢ����ʾ
	static void UpdateDispleyAfterAddDelete(const bool c_bResetCamera = true);
	// �ļ��������������Ϊ�����仯�����ͣ�������������Ͷ���Ӱ��������DataType_AbstractData���Դ�����
	static void UpdateListsAfterAddDelete(const int c_AffectType);
	
private:
	// Ψһ����
	static ASTransAddDeleteData* ms_SelfPointer;

	// 0 ��Ӳ�̶�������
	// �������·���б�
	static QStringList* m_FileListToLoad;
	// ���ݶ�ȡģ��
	static ASFModelImportDataFromDisk* m_FModelImportDataFromDisk;
	// �����ݽ��ȶԻ���
	QMessageBox* m_MessageBoxImportDataFromDisk = nullptr;
	// ����ȴ���������ط�д��̫��������ʱ��Ҫ�ġ�
	QStringList* m_LoadWaitingSeed;
	QStringList* m_LoadWaitingCtr;
	QStringList* m_LoadWaitingLdm;
	QStringList* m_LoadWaitingRoi;
	// 1 ��Ӳ����д������
	// ��д�����ݽڵ��б��·���б�
	QList<ASAbstractData*> m_NodeListToWrite;
	QStringList m_PathListToWrite;
	// ����д��ģ��
	static ASFModelExportDataToDisk* m_FModelExportDataToDisk;
	// д���ݽ��ȶԻ���
	QMessageBox* m_MessageBoxExportDataToDisk = nullptr;

	// 2 �Ƴ�����
	// �ݹ麯�����Ƴ�������
	void RemoveDataNodeAndChildren(ASAbstractData* DataNode);

	// �������ݲ���ʱ�Ƿ�Ҫ�������
	static bool ms_bResetCarmera;

private slots:

	// ��Ӳ�̶�ȡ���ݹ����б�ȡ��
	void slotLoadDataStopManualy(QAbstractButton* button);
	// ��Ӳ��д���ݹ����б�ȡ��
	void slotWriteDataStopManualy(QAbstractButton* button);

signals:

	// �Ƴ����ݺ������ݴ洢����ɾ���ڵ�
	int signalRemoveNode(ASAbstractData* DataNode);
	// ˢ�������б�
	void signalUpdateDataNodeLists(int Type);
};

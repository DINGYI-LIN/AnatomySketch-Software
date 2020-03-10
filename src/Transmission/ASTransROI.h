#pragma once
#include "ASTransmissionBase.h"
#include <QString>

class ASROIData;
class ASROITypeBase;
class ASFModelROI;
class ASAbstractData;

class ASTransROI : public ASTransmissionBase
{
	Q_OBJECT

public:
	ASTransROI(QObject *parent = 0);
	~ASTransROI();

	// Ψһ����
	static ASTransROI* GetSelfPointer();
	//��ǰROIID
	static void SetCrntROIID(const int c_id);
	static int GetCrntROIID();
	// �õ���ǰROI�ļ�
	static ASROIData* GetCurrentROIData();
	// ˢ������������б�
	static void UpdateListsOfROIData();
	// �½�ROI����
	static void NewROIData(ASAbstractData* pParent);
	static void NewROIData(ASAbstractData* pParent, QString name, int label, QColor color);
	// ��ȡROI����
	static void LoadROIDataFromDisk(const QStringList c_FileNameList);
	// �½�ROI
	static ASROITypeBase* NewROI(const int c_ROIId, const QString c_Name, const int c_Type);
	// �Ƴ�ROI
	static void RemoveROI(const int c_ROIDataId, const int c_ROIId);
	// ˢ��ROI�б�
	static void RefreshROIList();
	// ��������Cube��Χ
	static void SetROICubeRange(const int c_Index, const double c_Value);
	// ˢ��ROICube��ʾ
	static void RefreshROICubeDisplay();

private:

	// Ψһ����
	static ASTransROI* ms_SelfPointer;
	// ģ��
	ASFModelROI* m_FModelROI;
	// ��ǰROIID
	int m_CurrentROIID = -1;

	//void fNewROIData(QString name, int label, QColor color);

signals:

	// ˢ��Cube Roi�������
	void signalRefreshROICube();
	// ˢ��ROI�б�
	void signalRefreshList();
};

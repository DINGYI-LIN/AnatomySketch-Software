#pragma once

#include "ASMarkData.h"
#include <QList>

class ASROITypeBase;

// �̳�ʱ��Ҫ�ڹ��캯�����趨 m_Datatype�� ����дwalkerCheck����

class ASROIData : public ASMarkData
{
public:
	ASROIData();
	~ASROIData();
	virtual void DeleteNode();	// ���ô˺������ͷŽڵ�

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type); // �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
	virtual bool isTypeAbsolute(const int c_Type);
	static bool isTypeInheritedStatic(const int c_Type);
	
	// �½�ROI
	ASROITypeBase* NewROI(const QString c_Name, const int c_Type);
	void RemoveROI(const int c_ROIId);
	// ROI����
	int GetNumOfROIs();
	ASROITypeBase* GetROIAt(const int c_index);
	ASROITypeBase* GetROIWithID(const int c_ROIID);

protected:

	// �洢ROI
	QList<ASROITypeBase*>* m_plistROIs;

private:

};

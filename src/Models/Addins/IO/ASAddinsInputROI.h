#pragma once

#include "ASAddinsInputNode.h"
#include <QComboBox>

class ASROIData;
class ASAddinsComboBox;

typedef struct structInputROI
{
	QString Name;
	int Label;
	QColor Color;
	bool autoROI; // �Ƿ�֧���Զ�����ROI
	ASAddinsComboBox* ComboBox;
}structInputROI;

class ASAddinsInputROI : public ASAddinsInputNode
{
public:
	ASAddinsInputROI(ASAddinsBase* parent);
	~ASAddinsInputROI();

	// Value
	virtual void SetValue(const QStringList c_value);
	// DataNode
	void SetROIData(ASROIData* datanode);
	// �õ���ָ�룬����argc��sΪ����
	virtual void* GetVoidPoint(const QString s);
	// �������뵽Python�����е���ʱ�ļ�.1�ɹ���-1ʧ��
	virtual int PythonInputGenerate();
	// ������ͷ�����
	virtual void FreeMemory();
	// InputLandMark
	int GetNumOfInputROI();
	structInputROI* GetInputROIAt(const int c_index);
	virtual void RefreshCombo(int datatype);
	// ComboBox�ص�����
	void ComboBoxCallBack(ASAddinsComboBox* sender);

private:
	
	ASROIData* m_ROIData = nullptr;
	float* m_Data = nullptr;
	int m_CubeSize = 0;

	QList<structInputROI*>* m_listInputROI;
};

#pragma once

#include "ASAddinsInputNode.h"
#include <QComboBox>

class ASLandmarkData;
class ASAddinsComboBox;

typedef struct structInputLandMark
{
	QString Name;
	int Label;
	QColor Color;
	ASAddinsComboBox* ComboBox;
}structInputLandMark;

class ASAddinsInputLandmark : public ASAddinsInputNode
{
public:
	ASAddinsInputLandmark(ASAddinsBase* parent);
	~ASAddinsInputLandmark();

	// Value
	virtual void SetValue(const QStringList c_value);
	// DataNode
	void SetLandmarkData(ASLandmarkData* datanode);
	// �õ���ָ�룬����argc��sΪ����
	virtual void* GetVoidPoint(const QString s);
	// �������뵽Python�����е���ʱ�ļ�.1�ɹ���-1ʧ��
	virtual int PythonInputGenerate();
	// ������ͷ�����
	virtual void FreeMemory();
	// InputContours
	int GetNumOfInputLandMark();
	structInputLandMark* GetInputLandMarkAt(const int c_index);
	virtual void RefreshCombo(int datatype);
	// ComboBox�ص�����
	void ComboBoxCallBack(ASAddinsComboBox* sender);

private:
	
	ASLandmarkData* m_LandmarkData = nullptr;	
	QList<structInputLandMark*>* m_listInputLandMark;
	// ����DLL������
	float* m_Data = nullptr;
	int m_Size = 0;

};

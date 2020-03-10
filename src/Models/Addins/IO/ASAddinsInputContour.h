#pragma once

#include "ASAddinsInputNode.h"
#include <QComboBox>

class ASContourData;
class ASAddinsComboBox;

typedef struct structInputContour
{
	QString Name;
	int Label;
	QColor Color;
	ASAddinsComboBox* ComboBox;
}structInputContour;

class ASAddinsInputContour : public ASAddinsInputNode
{
public:
	ASAddinsInputContour(ASAddinsBase* parent);
	~ASAddinsInputContour();

	// Value
	virtual void SetValue(const QStringList c_value);
	// DataNode
	void SetContourData(ASContourData* datanode);
	// �õ���ָ�룬����argc��sΪ����
	virtual void* GetVoidPoint(const QString s);
	// �������뵽Python�����е���ʱ�ļ�.1�ɹ���-1ʧ��
	virtual int PythonInputGenerate();
	// ������ͷ�����
	virtual void FreeMemory();
	// InputContours
	int GetNumOfInputContour();
	structInputContour* GetInputContourAt(const int c_index);
	virtual void RefreshCombo(int datatype);
	// ComboBox�ص�����
	void ComboBoxCallBack(ASAddinsComboBox* sender);

private:
	
	ASContourData* m_ContourData = nullptr;
	// ����DLL������
	float* m_Data = nullptr;
	int m_Size = 0;
	QList<structInputContour*>* m_listInputContour;

};

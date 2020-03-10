#pragma once

#include "ASAddinsInputNode.h"
#include <QComboBox>
#include <QString>
#include <QColor>

class ASSeedData;
class ASAddinsComboBox;

typedef struct structInputSeed
{
	QString Name;
	int Label;
	QColor Color;
	ASAddinsComboBox* ComboBox;
}structInputSeed;

class ASAddinsInputSeed : public ASAddinsInputNode
{
public:
	ASAddinsInputSeed(ASAddinsBase* parent);
	~ASAddinsInputSeed();

	// Value
	virtual void SetValue(const QStringList c_value);
	// DataNode
	void SetSeedData(ASSeedData* datanode);
	// �õ���ָ�룬����argc��sΪ����
	virtual void* GetVoidPoint(const QString s);
	// �������뵽Python�����е���ʱ�ļ�.1�ɹ���-1ʧ��
	virtual int PythonInputGenerate();
	// ������ͷ�����
	virtual void FreeMemory();
	// InputSeeds
	int GetNumOfInputSeed();
	structInputSeed* GetInputSeedAt(const int c_index);
	virtual void RefreshCombo(int datatype);
	// ComboBox�ص�����
	void ComboBoxCallBack(ASAddinsComboBox* sender);

private:
	
	ASSeedData* m_SeedData = nullptr;
	int m_Size = 0;
	float* m_Data = nullptr;

	QList<structInputSeed*>* m_listInputSeed;

	int UpdatemData();
};

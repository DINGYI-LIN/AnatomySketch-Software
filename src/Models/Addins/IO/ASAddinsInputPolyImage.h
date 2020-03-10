#pragma once

#include "ASAddinsInputNode.h"
#include <QComboBox>
#include <vtkImageData.h>

class ASPolyImageData;

class ASAddinsInputPolyImage : public ASAddinsInputNode
{
public:
	ASAddinsInputPolyImage(ASAddinsBase* parent);
	~ASAddinsInputPolyImage();

	// DataNode
	void SetPolyData(ASPolyImageData* data);
	// Combobox
	QComboBox* GetCombobox();
	// ImageData
	ASPolyImageData* GetPolyData();
	// �õ���ָ�룬����argc��sΪ����
	virtual void* GetVoidPoint(const QString s);
	// �������뵽Python�����е���ʱ�ļ�.1�ɹ���-1ʧ��
	virtual int PythonInputGenerate();
	// ������ͷ�����
	virtual void FreeMemory();

	virtual void RefreshCombo(int datatype);

private:
	
	QComboBox* m_Combobox = nullptr;
	ASPolyImageData* m_PolyData = nullptr;

	float* m_PointsArray = nullptr;
	int m_PointsSize;
	int* m_Edges = nullptr;
	int* m_EdgesGroup = nullptr;
	int m_EdgesGroupSize;


};

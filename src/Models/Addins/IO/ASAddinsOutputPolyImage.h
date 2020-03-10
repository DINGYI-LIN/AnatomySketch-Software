#pragma once

#include "ASAddinsOutputNode.h"

class ASAddinsOutputPolyImage : public ASAddinsOutputNode
{
public:
	ASAddinsOutputPolyImage(ASAddinsBase* parent);
	~ASAddinsOutputPolyImage();

	// �õ���ָ�룬����argc��sΪ����
	virtual void* GetVoidPoint(const QString s);
	virtual void GenerateFinished(const int InterfaceType = 0);
	// ������ͷ�����
	virtual void FreeMemory();

private:
	
	float** m_pPoints = nullptr;
	int** m_pEdges = nullptr;
	int** m_pGroupEdges = nullptr;
	int m_NumOfPoints = -1;
	int m_NumOfEdges = -1;
	int m_NumOfGroup = -1;
};

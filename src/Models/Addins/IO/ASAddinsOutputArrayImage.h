#pragma once

#include "ASAddinsOutputNode.h"

class ASAddinsOutputArrayImage : public ASAddinsOutputNode
{
public:
	ASAddinsOutputArrayImage(ASAddinsBase* parent);
	~ASAddinsOutputArrayImage();

	// �õ���ָ�룬����argc��sΪ����
	virtual void* GetVoidPoint(const QString s);
	virtual void GenerateFinished(const int InterfaceType = 0);

	// ������ͷ�����
	virtual void FreeMemory();

	float* GetArray();
	int* GetDim();
	double* GetSpacing();
	double* GetOrigin();

private:
	
	float** m_pArray = nullptr;
	int* m_Dim = nullptr;
	double* m_Spacing = nullptr;
	double* m_Origin = nullptr;

};

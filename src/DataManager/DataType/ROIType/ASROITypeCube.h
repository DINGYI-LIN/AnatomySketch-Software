#pragma once

#include "ASROITypeBase.h"

// �̳�ʱ��Ҫ�ڹ��캯�����趨 m_Datatype�� ����дwalkerCheck����

class ASROITypeCube : public ASROITypeBase
{
public:
	ASROITypeCube();
	~ASROITypeCube();
	virtual void DeleteNode();	// ���ô˺������ͷŽڵ�

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type); // �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
	virtual bool isTypeAbsolute(const int c_Type);
	static bool isTypeInheritedStatic(const int c_Type);

	virtual void GetCenter(double* center);
	// ��Χ
	void SetRange(double xmin, double xmax, double ymin, 
		double ymax, double zmin, double zmax);
	void SetRange(double* range);
	void SetRange(const int c_Index, const double c_Value);
	double* GetRange();
	void GetRange(double* range);

protected:

	double m_Range[6];

private:

};

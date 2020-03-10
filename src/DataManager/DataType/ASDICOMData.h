#pragma once

#include "ASArrayImageData.h"
#include <vtkDICOMDirectory.h>
#include <vtkDICOMItem.h>

// �̳�ʱ��Ҫ�ڹ��캯�����趨 m_Datatype�� ����дwalkerCheck����

class ASDICOMData : public ASArrayImageData
{
public:
	ASDICOMData();
	~ASDICOMData();
	virtual void DeleteNode();	// ���ô˺������ͷŽڵ�

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type); // �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
	virtual bool isTypeAbsolute(const int c_Type);
	static bool isTypeInheritedStatic(const int c_Type);

	// ��ǩ��Ϣ
	void SetPatientItem(const vtkDICOMItem c_item);
	void SetStudyItem(const vtkDICOMItem c_item);
	void SetSeriesItem(const vtkDICOMItem c_item);
	vtkDICOMItem GetPatientItem(void);
	vtkDICOMItem GetStudyItem(void);
	vtkDICOMItem GetSeriesItem(void);

private:
	int m_nSeriesID;
	vtkDICOMItem m_PatientItem;
	vtkDICOMItem m_StudyItem;
	vtkDICOMItem m_SeriesItem;
};

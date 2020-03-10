#pragma once

#include "ASImageData.h"
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <QColor>

// �̳�ʱ��Ҫ�ڹ��캯�����趨 m_Datatype�� ����дwalkerCheck����

class ASPolyImageData : public ASImageData
{
public:
	ASPolyImageData();
	~ASPolyImageData();
	virtual void DeleteNode();	// ���ô˺������ͷŽڵ�

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type); // �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
	virtual bool isTypeAbsolute(const int c_Type);
	static bool isTypeInheritedStatic(const int c_Type);

	// �õ�ͼ������
	QColor getColor();
	void setColor(const QColor c_Color); // ������ɫ
	int getOpacity();
	void setOpacity(const int opacity);
	vtkPolyData* getPolyImageData();
	void setPolyData(vtkPolyData* pPolyData);
	// �������ݺ�����ݳ�ʼ��
	void DataInitAfterLoad();

	//// �����α�ģ��
	//void setPolyDeformationChoosen(const bool isChoosen);
	//bool isPolyDeformationChoosen();

protected:

	QColor m_Color; 
	int	m_nOpacity; // ��͸����,0~100
	vtkSmartPointer<vtkPolyData> m_PolyData = nullptr; // ����������

private:

	// �����α书�ܳ�Ա
	bool m_isPolyDeformationChoosen = false;


};

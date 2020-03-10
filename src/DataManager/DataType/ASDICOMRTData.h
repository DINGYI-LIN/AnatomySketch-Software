#pragma once

#include "ASMarkData.h"
#include <QList>

// �̳�ʱ��Ҫ�ڹ��캯�����趨 m_Datatype�� ����дwalkerCheck����

typedef struct structDICOMRTDataSlice {
	double layer;
	QList<double> points;
	double LayerDataBounds[4]; //��Ϊ���ݶ��Ǻ�����ϵģ�����Ϊ�������һ��ı߽硣xmin,xmax,ymin,ymax��
}structDICOMRTDataSlice;

class ASDICOMRTData : public ASMarkData
{
public:
	ASDICOMRTData();
	~ASDICOMRTData();
	virtual void DeleteNode();	// ���ô˺������ͷŽڵ�

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type); // �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
	virtual bool isTypeAbsolute(const int c_Type);
	static bool isTypeInheritedStatic(const int c_Type);

	// ���һ���պ�����
	void appendSlice(const double* c_pdPoints, const int c_nNumOfPoints);
	// slice����
	int getNumOfSlice();
	// ��ȡSlice
	structDICOMRTDataSlice* getSliceAt(int index);

	// ��̬����
	static int getNumOfDICOMRTData();

	// ��̬����
	// �õ�����DICOM-RT���ݵķ�Χ������0�ɹ�������-1��ʾû��RT���ݻ�ֻ�п�����
	static int getDICOMRTDataBounds(double* pdBounds);

private:
	// ������պ�����
	QList<structDICOMRTDataSlice*>* m_ListRTDataSlice;

	static int ms_nNumOfDICOMRTData;				// ��ǰ�򿪵�RT���ݵ�����

};

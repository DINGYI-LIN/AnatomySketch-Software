#pragma once

#include "ASMarkData.h"
#include <QColor>

// �̳�ʱ��Ҫ�ڹ��캯�����趨 m_Datatype�� ����дwalkerCheck����

typedef struct structLandmark
{
	double dPosition[3];
	QString qsName;
	int LandmarkID; // ÿ��landmark����ΨһID
	QColor color;
}structLandmark;

class ASLandmarkData : public ASMarkData
{
public:
	ASLandmarkData();
	~ASLandmarkData();
	virtual void DeleteNode();	// ���ô˺������ͷŽڵ�

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type); // �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
	virtual bool isTypeAbsolute(const int c_Type);
	static bool isTypeInheritedStatic(const int c_Type);

	// �궨����������
	static int GetNumOfLandmarkData();
	// ���ʱ궨��
	int GetNumberOfLandmark();
	structLandmark* GetLandmarkAt(const int c_Landmark);
	structLandmark* GetLandmarkWithID(const int c_id);
	void AppandLandmark(structLandmark* NewLandmark);
	// �����߲���
	void AddLandMark(double* pPosition, QString qsname);
	void MoveLandMark(double* pPos, const int c_PointID);
	void DeleteLandMark(const int c_PointID);

	// ����
	virtual double* getDataExtent(); // �õ����ݷ�Χ��double[6]
	
protected:

	QList<structLandmark*>* m_listLandmarks;

private:

	static int ms_nNumOfLandmarkData;				// ��ǰ�򿪵ı궨�����ݵ�����
};

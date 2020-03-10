#pragma once

#include "ASMarkData.h"
#include "GlobelDeclaration.h"

// �̳�ʱ��Ҫ�ڹ��캯�����趨 m_Datatype�� ����дwalkerCheck����

typedef struct structCurve {
	QList<structPoint*> pvectorPoint;
	int ViewLabel; //0:sagittal  1 : coronal   2 : axial DimensionsOfImage
	double dLayer;
	bool isClosure; // �Ƿ�պ�
	bool haveTemporary = false;
}structCurve;
typedef struct structContour {
	int contourID;
	bool isShown;
	QColor color;
	QString name;
	int label;
	QList<structCurve*>* pListCurves;
}structContour;

class ASContourData : public ASMarkData
{
public:
	ASContourData();
	~ASContourData();
	virtual void DeleteNode();	// ���ô˺������ͷŽڵ�

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type); // �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
	virtual bool isTypeAbsolute(const int c_Type);
	static bool isTypeInheritedStatic(const int c_Type);
	// �½�������
	int NewContour(const QString c_name, const int c_lable, const QColor c_color);
	// ��������������
	static int GetNumOfContourData();
	// ��ǩֵ
	int getLabel();
	void setLabel(const int label);
	// ����������
	int GetNumberOfContour();
	structContour* GetContourAt(const int c_Contour);
	structContour* GetContourFromID(const int c_ContourID);
	void AppandContour(structContour* NewContour);
	// ����
	virtual double* getDataExtent(); // �õ����ݷ�Χ��double[6]

	// �����߲���
	void AddContrlPointsTemp(double* pPosition, const int ViewLabel, 
		double* pSpacing, const int c_ContourID);
	void AddContrlPoints(double* pPosition, const int ViewLabel, double* pSpacing, const int c_ContourID);
	void MoveContrlPoints(double* pPosition, const int c_ViewLabel, double* pSpacing, const int c_ContourID,
		const int c_IndexOfContour = -1, const int c_IndexOfHandle = -1);
	void DeleteContrlPointsTemp(double* pPosition, const int c_ViewLabel, double* pSpacing, 
		const int c_ContourID);
	void SetContourClosed(const int c_viewlabel, const int c_indexOfContour, const int c_indexOfHandle, 
		const bool c_Closed, const int c_ContourID);
	void DeleteContrlPoints(const int c_ViewLabel, double* pSpacing, const int c_ContourID, 
		const int c_IndexOfContour, const int c_IndexOfHandle);
	void InsertContrlPoints(double* pPosition, const int c_ViewLabel, double* pSpacing, 
		const int c_ContourID, const int c_IndexOfContour, const int c_IndexOfHandle);
	void DeleteContour(const int c_viewlabel, const int c_indexOfContour, const int c_indexOfHandle,
		const int c_ContourID);
	void DeleteWholeContour(const int c_ContourID);

protected:

	int m_nLabel; // ��ǩֵ

private:

	QList<structContour*>* m_listContours;

	static int ms_nNumOfContourData;				// ��ǰ�򿪵����������ݵ�����

	// �õ�һ���µĲ��ظ�ID
	int GetNewContourID();
};

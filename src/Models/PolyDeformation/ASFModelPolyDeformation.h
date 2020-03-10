#pragma once
#include "ASFunctionModelBase.h"
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <QList>

#define PolyDeformation_Panning		0
#define PolyDeformation_Rotation	1
#define PolyDeformation_Zooming		2
#define PolyDeformation_FFD			3
#define PolyDeformation_None		4

#define  MaximumWithdrawalSteps		7		//���������

// --------------------- �������ݣ����ڳ��� ---------------------
typedef struct structTemporaryPolyDataSet
{
	int ID;
	vtkSmartPointer<vtkPolyData> pPolyData;
}structTemporaryPolyDataSet;

typedef struct structPolyDeformationTemporaryData
{
	int		DeformaitonType;
	QList<structTemporaryPolyDataSet*>* pTemporaryDataSet;
}structPolyDeformationTemporaryData;

class ASFModelPolyDeformation : public ASFunctionModelBase
{
	Q_OBJECT

public:
	ASFModelPolyDeformation(QObject *parent = 0);
	~ASFModelPolyDeformation();

	// ѡ��
	void SetDataNodeChoosen(const int c_ID, const bool c_Choosen);
	void ResetDataNodeChoosen(QList<int> choosenID);
	static bool IsPolyChoosen(const int c_ID);
	// ��ǰ�任
	int GetCurrentTransType();

	// ��ʼ�任
	void StartPolyDeformation(double* Pos, const int c_Type, double ViewRange);
	// �����任
	int ContinuePolyDeformation(double* Pos, const int c_Viewlabel, const int c_Type);
	// ����
	void ContinueZoom(const double c_mX, const double c_mY, const double c_mZ);
	// ��ת
	void ContinueRotation(const double angle, const int viewlabel);
	// �ı�FFDӰ��뾶
	int FFDRadiusChange(int ZoominOrZoomout);
	// ����
	int UndoDef();


private:
	// Ψһ����
	static ASFModelPolyDeformation* ms_SelfPointer;
	// ��ǰѡ������ID�б�
	QList<int> m_listChoosenID;

	// �任������Ϣ
	double m_adPolyDeformationPos[6];
	// ��ǰ��ͼ��Χ
	double m_dViewRange = 0;
	// FFD��ǰ���ð뾶
	double m_FFDRadius = 0;
	// ������ת�����ŵ�����
	double m_PolyDeformationDataCenter[3];
	// ��ǰ�任
	int m_CurrentTransType = PolyDeformation_None;
	// �������ݴ洢����
	QList<structPolyDeformationTemporaryData*>* m_listPolyDeformationTemporaryData;

	// ����ƽ�Ʊ任
	int PanningDeformation();
	// ������ת�任����꽻��
	int RotationDeformation(int viewlabel);
	// ����FFD�任
	int FFDDeformation();

private slots:
	

};

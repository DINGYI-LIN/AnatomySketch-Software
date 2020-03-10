#pragma once
#include "ASTransmissionBase.h"
#include <QProgressDialog>

class ASAbstractData;
class ASArrayImageData;
class ASFModelGraphCut;

class ASTransGraphCut : public ASTransmissionBase
{
	Q_OBJECT

public:
	ASTransGraphCut(QObject *parent = 0);
	~ASTransGraphCut();

	// Ψһ����
	static ASTransGraphCut* GetSelfPointer();

	// Marching cubs
	static void SetMarchingCubs(const bool c_Marching, const int c_SmoothIterations);
	// ����Graph Cut����
	static void GraphCutGenerate(const int c_ImageDataID, const QList<int> SeedsID, 
		const QString c_OutputName, const double c_Lambda, const double c_Delta, 
		const int c_nNeighbor, const QString c_PostProcessing, const bool c_bQuery);
	// �������
	static void GraphCutsFinished(ASArrayImageData* DataNode);

private:
	// Ψһ����
	static ASTransGraphCut* ms_Selfpointer;
	// �����ݽ��ȶԻ���
	QProgressDialog* m_ProgressDialog = nullptr;
	// ����ģ��
	ASFModelGraphCut* m_FModelGraphCut;
	// Marching Cubs
	bool m_NeedMarchingCubs = false;
	int m_SmoothIterations = 0;

	QList<int> m_SeedsID;

signals:


};

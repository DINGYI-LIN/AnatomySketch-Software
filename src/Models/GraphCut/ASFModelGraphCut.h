#pragma once
#include "ASFunctionModelBase.h"
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <QList>

class ASArrayImageData;
class ASPolyImageData;
class ASThreadGraphCut;

#define NoMask_GraphCut	99998
#define MaskModeID_GraphCut	99999

class ASFModelGraphCut : public ASFunctionModelBase
{
	Q_OBJECT

public:
	ASFModelGraphCut(QObject *parent = 0);
	~ASFModelGraphCut();

	// Graph cuts
	void SetInputData(ASArrayImageData* input);
	void SetSeedsID(QList<int> SeedsID);
	void SetOutputImage(ASArrayImageData* output);
	void SetParameter(const double c_Lambda, const double c_Delta, const int c_Neighbor);
	void SetPostProcessing(const QString c_PostProcessing);
	// ��ʼ����
	void GraphCutsStart();

	// Marching cubs
	void MarchingCubs(ASArrayImageData* MarInput, QList<ASPolyImageData*>* listMarOutput, QList<int> SeedsID, const int c_SmoothIterations);


private:
	
	ASArrayImageData* m_InputImage;
	QList<int> m_listSeedsID;
	ASArrayImageData* m_OutputData;
	double m_Lambda;
	double m_Delta;
	int m_nNeighbor;
	QString m_PostProcessing;

	// �����߳�
	ASThreadGraphCut* m_ThreadGraphCut = nullptr;

private slots:

	// ����ɹ�
	void signalDataLoadFinished();

};

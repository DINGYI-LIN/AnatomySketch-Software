#pragma once
#include "ASPipelineBase.h"
#include <vtkSmartPointer.h>
#include <vtkSphereHandleRepresentation.h>
#include <vtkRenderer.h>
#include <QList>
#include <QColor>

#define	LANDMARKRADIUS				10		// �궨��뾶

// �궨����ʾ���߽ṹ��
typedef struct structLandmarkPipeline
{
	int LandmarkDataID;
	int LandmarkPointID;
	int ViewLabel;
	QString qsName;
	QColor qColor;
	vtkSmartPointer<vtkSphereHandleRepresentation> SphereHandleRep;
}structLandmarkPipeline;

class ASPipelineLandmark : public ASPipelineBase
{
public:
	ASPipelineLandmark(const int c_ID);
	~ASPipelineLandmark();

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type);
	virtual bool isTypeAbsolute(const int c_Type);

	// �麯��
	virtual void DeleteNode();	// ���ô˺������ͷŹ���
	virtual void Update2DTransformMatrix(); // ��ͼ����ı�
	virtual void SetShown(const bool c_Shown); // �Ƿ���ʾ

	// ˢ��������������ʾ
	void RefreshLandmarkDisplay(const int c_ViewLabel);
	// ���ÿ��Ƶ�ֱ��
	void ReSetCtrlRadius(const int c_ViewLabel);
	// ����actor��ַ��ѯ���Ƶ���Ϣ
	bool ReserchLanmark(vtkActor* pActor, int* LandmarkDataID, int* ViewLabel, int* LandmarkPointID);

private:

	bool m_isShown = false;
	vtkSmartPointer<vtkRenderer> m_pRenderer2D[3];
	QList<structLandmarkPipeline*>* m_plistLandmarkPipelines;
	double m_HandleRadius[3] = { 1, 1, 1 };
	// ���Ƶ�뾶
	double GetCtrlPointRadiusSplineContour(const int c_viewLabel);
};

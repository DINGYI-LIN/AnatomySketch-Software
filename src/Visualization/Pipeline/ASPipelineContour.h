#pragma once
#include "ASPipelineBase.h"
#include <QList>
#include <QColor>
#include <vtkSphereHandleRepresentation.h>
#include <vtkParametricSpline.h>
#include <vtkParametricFunctionSource.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkTransform.h>
#include <vtkProperty.h>
#include <vtkActor.h>

#define	CTRLPOINTRADIUS				10		// ���������߿��Ƶ�뾶

//��������ʾ���߽ṹ�壬CTRS��ContourSplin
typedef struct structCTRSPipe {
	int											ID;
	int											ContourID;
	int											ViewLabel;
	int											ItemOfContour; // �������������е����
	QList<vtkSphereHandleRepresentation*>*		plistContourSplinSphereHandle;
	vtkSmartPointer<vtkPoints>					pCTRSPoints;
	vtkSmartPointer<vtkParametricSpline>		pCTRSParaSpline;
	vtkSmartPointer<vtkParametricFunctionSource> pCTRSParaFuncSource;
	vtkSmartPointer<vtkPolyData>				pCTRSPolyData;
	vtkSmartPointer<vtkTransform>				pCTRSTransform;
	vtkSmartPointer<vtkTransformPolyDataFilter>	pCTRSTransPolyDataFilter;
	vtkSmartPointer<vtkPolyDataMapper>			pCTRSPolyDataMapper;
	vtkSmartPointer<vtkProperty>				pCTRSProperty;
	vtkSmartPointer<vtkActor>					pCTRSActor;
}structCTRSPipe;

class ASPipelineContour : public ASPipelineBase
{
public:
	ASPipelineContour(const int c_ID);
	~ASPipelineContour();

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type);
	virtual bool isTypeAbsolute(const int c_Type);

	// �麯��
	virtual void DeleteNode();	// ���ô˺������ͷŹ���
	virtual void Update2DTransformMatrix(); // ��ͼ����ı�
	virtual void SetShown(const bool c_Shown); // �Ƿ���ʾ

	// �Ƿ����ʰȡ
	void SetPickable(const bool c_isPickable);
	// ˢ��������������ʾ
	void RefreshSplineContourDisplay(const int c_ViewLabel);
	// ���ÿ��Ƶ�ֱ��
	void ReSetCtrlRadius(const int c_ViewLabel);
	// ����actor��ַ��ѯ���Ƶ���Ϣ
	bool reserchHandleSplineContour(vtkActor* pActor, int* ID, int* ContourID, int* ViewLabel, 
		int* ItemOfContour, int* ItemOfHandle);
	// ������Ƶ�ʱ���������жϿ��Ƶ�λ��
	bool getInsertHandleIndex(double* pos, const int c_viewLabel, int* ID, int* ItemOfContour, int* ItemOfHandle);

private:

	bool m_isShown = false;
	bool m_Pickable = true;
	vtkSmartPointer<vtkRenderer>				m_pRenderer2D[3];
	QList<structCTRSPipe*>* m_plistContourSplinePipeline;
	double m_HandleRadius[3] = { 1, 1, 1 };
	
	// ���Ƶ�뾶
	double GetCtrlPointRadiusSplineContour(const int c_viewLabel);
};

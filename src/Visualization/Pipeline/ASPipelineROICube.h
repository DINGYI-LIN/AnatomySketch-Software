#pragma once
#include "ASPipelineBase.h"
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <QList>

typedef struct structCubePipe
{
	int ROIDataID;
	int ROIID;
	int ViewLabel;
	vtkSmartPointer<vtkPoints>					pPoints;
	vtkSmartPointer<vtkCellArray>				pCells;
	vtkSmartPointer<vtkActor>					pActor;
	vtkSmartPointer<vtkPolyData>				pData;
	vtkSmartPointer<vtkTransform>				pTransform;
	vtkSmartPointer<vtkTransformPolyDataFilter>	pTransPolyDataFilter;
	vtkSmartPointer<vtkProperty>				pProperty;
	vtkSmartPointer<vtkPolyDataMapper>			pMapper;
}structCubePipe;

class ASPipelineROICube : public ASPipelineBase
{
public:
	ASPipelineROICube(const int c_ID);
	~ASPipelineROICube();

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type);
	virtual bool isTypeAbsolute(const int c_Type);
	virtual void DeleteNode();	// ���ô˺������ͷŹ���

	// �麯������ͼ����ı�
	virtual void Update2DTransformMatrix();

private:

	// �ù�����Ψһ�ģ�Ψһ����
	static ASPipelineROICube* ms_SelfPointer;

	// ���߽ṹ
	QList<structCubePipe*>* m_listCubePipes;

	
};

#pragma once
#include "ASFunctionModelBase.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>

class ASPipelineMask;

class ASFModelMask : public ASFunctionModelBase
{
	Q_OBJECT

public:
	ASFModelMask(QObject *parent = 0);
	~ASFModelMask();

	// ��ǰ����ģ��ʹ��״̬
	static bool IsMaskEnable();
	void SetMaskEnable(const bool c_enable);
	// ����ͼ��ID
	void SetMaskImageID(const int c_ID);
	// ��������
	static vtkImageData* GetMaskImageData();
	// �������ֲ���
	void SetMaskParameter(double* Extent, double* ScaleRange);
	static double* GetMaskExtent();
	static double* GetMaskScaleRange();
	static double* GetMDataScaleRange();
	// ������������ͼ��
	void SetMaskModel(const int c_model);
	int GetMaskModel();
	void SetMDataID(const int c_ID);

private:
	// Ψһ����
	static ASFModelMask* ms_FModelMask;
	// ���ֶ���ID
	int m_WorkingDataID = -1;
	int m_maskMoudle = 0;
	int m_MDataID = -1;
	// ���ֲ���
	double m_MaskExtentOri[6];
	int m_MaskExtent[6];
	double m_ScaleRange[2];
	double m_ScaleRangeMData[2];
	// ����ģ��ʹ��״̬
	static bool ms_isEnable;
	// �洢���ֵ�ImageData
	vtkSmartPointer<vtkImageData> m_pMaskImageData = nullptr;
	// ������ʾ����
	ASPipelineMask* m_MaskPipeLine = nullptr;

private slots:
	

};

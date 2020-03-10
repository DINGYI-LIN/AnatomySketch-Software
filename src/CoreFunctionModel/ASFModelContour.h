#pragma once
#include "ASFunctionModelBase.h"
#include <vtkActor.h>

class ASPipelineContour;

class ASFModelContour : public ASFunctionModelBase
{
	Q_OBJECT

public:
	ASFModelContour(QObject *parent = 0);
	~ASFModelContour();

	// ��ǰ���Ƶ����ӵ��ID
	void SetIDOfPaintingData(const int c_ID);
	static int GetIDOfPaintingData();
	// ��ǰ�������ݽڵ��������ߵ����
	void SetCurrentContourID(const int c_ID);
	static int GetCurrentContourID();
	// ģ��ʹ��״̬
	void SetContourModleEnabled(const bool c_enabled);
	static bool GetContourModleEnabled();
	// û�������߾ͽ�������
	void InitContourPipeline();
	// �����߹����Ƿ���ʾ��û��2D����ʱ����ʾ���ӵ�
	void SetContourShown(const bool c_Shown);
	// ����ģʽ��0, ��ͨ; 1, ����
	void SetInterfaceModel(const int c_model);
	static int GetInterfaceModel();

	// �����߲���
	// �����ʱ���Ƶ�
	void AddContrlPointsTemp(double* pPosition, const int ViewLabel, double* pSpacing);
	// ��ӿ��Ƶ�
	void AddContrlPoints(double* pPosition, const int ViewLabel, double* pSpacing);
	// �ƶ����Ƶ�
	void MoveContrlPoints(double* pPosition, const int c_ViewLabel, double* pSpacing, const int c_ID = -1, 
		const int c_ContourID = -1, const int c_IndexOfContour = -1, const int c_IndexOfHandle = -1);
	// �պ�������
	void SetContourClosed(const int c_id, const int c_viewlabel, const int c_indexOfContour, const int c_indexOfHandle, const bool c_Closed);
	// ɾ�����Ƶ�
	void DeleteContrlPoints(const int c_ViewLabel, double* pSpacing, const int c_ID, const int c_ContourID,
		const int c_IndexOfContour, const int c_IndexOfHandle);
	// ɾ�����һ�����Ƶ�
	void DeleteContrlPointsTemp(double* pPosition, const int c_ViewLabel, double* pSpacing);	
	// ������Ƶ�
	void InsertContrlPoints(double* pPosition, const int c_ViewLabel, double* pSpacing, const int c_ID, const int c_IndexOfContour, const int c_IndexOfHandle);
	// ɾ������
	void DeleteContour(const int c_id, const int c_ContourID, const int c_viewlabel, 
		const int c_indexOfContour, const int c_indexOfHandle);
	// ɾ��������������
	void DeleteWholeContour(const int c_DataID, const int c_ContourID);
	// ���ÿ��Ƶ�ֱ��
	void ReSetCtrlRadius(const int c_ViewLabel);
	// ��ʾ
	void RefreshSplineContourDisplay(const int c_ViewLabel);
	// ����actor��ַ��ѯ���Ƶ���Ϣ
	bool ReserchHandleSplineContour(vtkActor* pActor, int* ID, int* ContourID, int* ViewLabel, 
		int* ItemOfContour, int* ItemOfHandle);
	// ������Ƶ�ʱ���������жϿ��Ƶ�λ��
	bool GetInsertHandleIndex(double* pos, const int c_viewLabel, int* ID, int* ItemOfContour, int* ItemOfHandle);

	// ��ȡ����������
	void LoadContourData(const QString c_FileName);

private:
	// Ψһ����
	static ASFModelContour* ms_SelfPointer;

	// ��ǰ�������������ݽڵ��ID
	int m_IDOfPaintingData = -1;
	// ��ǰ�������ݽڵ��������ߵ����
	int m_CurrentContourID = -1;
	// ģ��ʹ��״̬
	bool m_ContourModelEnabled = false;
	// ������ģ���Ƿ���ʾ
	bool m_ContourShown = false;
	// ����ģʽ��0, ��ͨ; 1, ����
	int m_InterfaceModel = 0;

	// ����
	ASPipelineContour* m_PipelineContour = nullptr;

private slots:
	

};

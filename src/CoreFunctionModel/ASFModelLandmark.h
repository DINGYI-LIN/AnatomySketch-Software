#pragma once
#include "ASFunctionModelBase.h"
#include <vtkActor.h>

class ASPipelineLandmark;

class ASFModelLandmark : public ASFunctionModelBase
{
	Q_OBJECT

public:
	ASFModelLandmark(QObject *parent = 0);
	~ASFModelLandmark();

	//// ��ǰ���Ƶı궨���ID
	//void SetIDOfPaintingData(const int c_ID);
	//static int GetIDOfPaintingData();
	// ģ��ʹ��״̬
	void SetLandmarkModleEnabled(const bool c_enabled);
	static bool GetLandmarkModleEnabled();
	// û�������߾ͽ�������
	void InitLandmarkPipeline();
	// �����߹����Ƿ���ʾ��û��2D����ʱ����ʾ���ӵ�
	void SetLandmarkShown(const bool c_Shown);

	// �궨�����
	// ��ӱ궨��
	void AddLandmark(double* pPosition, QString qsname);
	// �ƶ��궨��
	void MoveLandmark(double* pPos, const int c_DataID, const int c_ViewLabel, const int c_PointID);
	// ɾ���궨��
	void DeleteLandmark(const int c_DataID, const int c_PointID);

	// ���ÿ��Ƶ�ֱ��
	void ReSetCtrlRadius(const int c_ViewLabel);
	// ��ʾ
	void RefreshLMDisplay(const int c_ViewLabel);
	// ����actor��ַ��ѯ���Ƶ���Ϣ
	bool ReserchLanmark(vtkActor* pActor, int* LandmarkDataID, int* ViewLabel, int* LandmarkPointID);

	// ��ȡ���ӵ�����
	void LoadLandmarkData(const QString c_FileName);

private:
	// Ψһ����
	static ASFModelLandmark* ms_SelfPointer;

	// ģ��ʹ��״̬
	bool m_LandmarkModelEnabled = false;
	// �궨��ģ���Ƿ���ʾ
	bool m_LandmarkShown = false;

	// ����
	ASPipelineLandmark* m_PipelineLandmark = nullptr;

private slots:
	

};

#pragma once
#include "ASTransmissionBase.h"
#include "ASFModelLandmark.h"
#include <vtkActor.h>

class ASLandmarkData;
class ASAbstractData;

#define CtrOpe_AddLandM			0
#define CtrOpe_MoveChooseLandM	1
#define CtrOpe_MovingLandM		2
#define CtrOpe_DeleteLandM		3
#define CtrOpe_ZoomLandM		4

class ASTransLandmark : public ASTransmissionBase
{
	Q_OBJECT

public:
	ASTransLandmark(QObject *parent = 0);
	~ASTransLandmark();

	// Ψһ����
	static ASTransLandmark* GetSelfPointer();

	// �õ���ǰ�궨��
	static ASLandmarkData* GetCurrentLMData();
	// �½��������ļ�
	static void NewLandmarkData(ASAbstractData* pParent);
	// ��ʼ�������߹���
	static void InitLandmarkPipeline();
	// ����ģ���Ƿ�ʹ��
	static void SetModelEnabled(const bool c_enable);
	// �궨���Ƿ���ʾ
	static void SetLandmarksShown(const bool c_Shown);
	// �궨�����
	static void LandmarkOperation(double* pos, int viewlabel, int operate, vtkActor* actor);
	// ˢ��
	static void RefreshLandMDisplay();
	// ��Ӳ�̶��ļ�
	static void LoadLandMDataFromDisk(const QStringList c_FileNameList);
	// �Ƴ��궨��
	static void RemoveLandMark(const int c_LMDataNodeID, const int c_LMID);

private:

	// Ψһ����
	static ASTransLandmark* ms_SelfPointer;
	// �궨��ģ��
	ASFModelLandmark* m_FModelLandmark;

signals :

	// ���ý����ģ��ʹ��״̬
	void signalSetModelEnabled(bool enabled);

};

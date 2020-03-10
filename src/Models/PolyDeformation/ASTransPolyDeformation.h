#pragma once
#include "ASTransmissionBase.h"
#include <vtkActor.h>

class ASPolyImageData;
class ASFModelPolyDeformation;

class ASTransPolyDeformation : public ASTransmissionBase
{
	Q_OBJECT

public:
	ASTransPolyDeformation(QObject *parent = 0);
	~ASTransPolyDeformation();

	// Ψһ����
	static ASTransPolyDeformation* GetSelfPointer();
	// �����Ƿ�ѡ��
	static void ResetPolyDataChoosen(QList<int> listChoosenID);
	static void SetPolyDataChoosen(const int c_DataNodeID, const bool c_Choosen);
	static bool ConourPicked(vtkActor* ActorPicked); // ͨ������ʰȡ����������
	// ʹ��
	static void SetEnabled(const bool c_enable);
	static bool GetEnabled();

	// ����;)
	static void PolyDefStart(double* Pos, const int c_ViewLabel, const int c_TransType);
	static void PolyDefContinue(double* Pos, const int c_ViewLabel, const int c_TransType);
	static void PolyDefZoom(int InOrOut); 	//�������š� 0: zoom in 1: zoom out
	static void PolyDefRotate(int ClockwiseOrCounter, int viewlabel); //������ת
	static void PolyDefWheelFFD(int ForwardOrBackward); 	//PolyDeformation, FFD�� 0:Forward 1:Backward
	static void PolyDefUndo();

private:

	// PolyDeformationģ��
	ASFModelPolyDeformation* m_FModelPoly;
	// Ψһ����
	static ASTransPolyDeformation* ms_SelfPointer;
	static bool ms_Enabled;

signals:

	// ����ѡ��״̬�ı�
	void signalChoosnChanged(int ID);

};

#pragma once
#include "ASTransmissionBase.h"
#include <vtkActor.h>

class ASAbstractData;
class ASArrayImageData;
class ASPolyImageData;
class ASFModelGeneralInteractor;

class ASTransGeneralInteractor : public ASTransmissionBase
{
	Q_OBJECT

public:
	ASTransGeneralInteractor(QObject *parent = 0);
	~ASTransGeneralInteractor();

	// Ψһ����
	static ASTransGeneralInteractor* GetSelfPointer();
	// �л�3D��ͼ2D�����Ƿ���ʾ�������л����Ƿ���ʾ
	static bool Switch3DImageStackShown();
	// ������ʾ���㣬��Ⱦ
	static void SetVisualizationPosition(const double c_x, const double c_y, const double c_z);
	// ���õ�ǰ֡
	static void SetVisualizationFrame(const int c_frame);
	// ���õ�ǰͼ��λ����
	static void SetVisualizationLevelWindow(const double c_level, const double c_window);
	// ����ĳ�����Ƿ���ʾ
	static void SetDateShown(const int c_ID, const bool c_isShown);
	// ��������
	static void ReinitDataNode(ASAbstractData* DataNode);
	// ���������ݵ���ɫ��
	static void SetArrayDataColorMap(ASArrayImageData* DataNode, const int c_ColorMap);
	// ���������ݴ�λ����
	static void SetArrayDataWindowLevel(ASArrayImageData* DataNode, double* WindowLevel);
	// ���������ݲ�͸����
	static void SetPolyDataOpacity(ASAbstractData* DataNode, const int c_Opacity);
	// ������������ɫ
	static void SetPolyDataColor(ASPolyImageData* DataNode, const QColor c_Color);
	// ��ͼ����
	static void GenerateViewZoom(const int c_view);

	// ������ʾ���㣬����Ⱦ
	static void fSetVisualizationPosition(const double c_x, const double c_y, const double c_z);

	// ��ͣ��Ϣ
	static void HoverActorPicked(vtkActor* actor, const int c_x, const int c_y, const int c_ViewLabel);
	static void AddHoverInfor(vtkActor* actor, QString infor);
	static void DeleteHoverInfor(vtkActor* actor);
	static int ShowHoverText(const int c_ViewLabel, const QString c_text, double* pos1, double* pos2);
	static void DeleteHoverText(const int c_TextID, const int c_ViewLabel);

	static void SetWindow(double m_Window);
	static void SetLevel(double m_Level);

	static double GetWindow();
	static double GetLevel();

private:
	// ��λ����
	double WindowLevel[2];

	// Ψһ����
	static ASTransGeneralInteractor* ms_SelfPointer;

	// ����ģ��
	ASFModelGeneralInteractor* m_FModelGenInter;

	// �����Ƿ���ʾ
	void fSetDataShown(ASAbstractData* DataNode, const bool c_isShown);

signals:

	// �����Ƿ���ʾ�ı�
	void signalDataShownChanged(ASAbstractData* DataNode);
};

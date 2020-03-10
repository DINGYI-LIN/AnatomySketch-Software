#pragma once
#include "ASTransmissionBase.h"
#include "ASAbstractData.h"
#include <QKeyEvent>
#include <QColor>

class ASFModelMask;

#define SIDEBAR_IMAGENAVIGATOR		0	// �������ImageNavigator
#define SIDEBAR_Mask				1	// �������Mask
#define SIDEBAR_PaintingSeeds		2	// ��������������ӵ�
#define SIDEBAR_PaintingContour		3	// �����������������
#define SIDEBAR_PaintingLandmark	4	// ����������Ʊ궨��
#define SIDEBAR_PolyDeformation		5	// �������PolyDeformation
#define SIDEBAR_GraphCuts			6	// �������GraphCuts��ͼ���㷨
#define SIDEBAR_Operation			7	// ����������
#define SIDEBAR_ROI					8	// �������ROI

class ASTransSidebarGeneral : public ASTransmissionBase
{
	Q_OBJECT

public:
	ASTransSidebarGeneral(QObject *parent = 0);
	~ASTransSidebarGeneral();

	// Ψһ����
	static ASTransSidebarGeneral* GetSelfPointer();

	// ���ò�����·�widget�Ƿ���ʾ
	static void SetSidebarBelowWidget(const int c_WidgetType, const bool c_isShown);

	// ˢ�²�����ļ�����ѡ��
	static void RefreshDataComboBox(const int c_AffectType);

	// 0 ��ǰѡ�е����ݽڵ�
	static void SetCrntDataNode(ASAbstractData* datanode);
	static ASAbstractData* GetCrntDataNode();

	// 1 ImageNavigator
	// ���õ�ǰ����
	static void SetDisplayPosition(const double c_x, const double c_y, const double c_z);
	// ���õ�ǰ֡
	static void SetDisplayFrame(const int c_Frame);
	// �������سߴ�
	static void SetImageSpacing(double* Spacing);
	// ����ͼ��Χ��֡��Χ
	static void SetDisplayExtent(double* Extent, const int c_NumOfFrames);
	// ���ô�λ����
	static void SetWindowLevel(double* WindowLevel);

	// 2 Mask
	// ��������ʹ��״̬
	static void SetMaskModleEnabled(const bool c_Enable);
	// ���ò���ͼ��ID
	static void SetMaskWorkingImageID(const int c_ID);
	// �������ֲ���
	static void SetMaskParameter(double* Extent, double* ScaleRange);
	// ��������ģʽ
	static void SetMaskModel(const int c_model); // 0: ��ͨģʽ, 1: ������������ͼ��ģʽ
	static int GetMaskModel(); // 0: ��ͨģʽ, 1: ������������ͼ��ģʽ
	// ������������λ��
	static void SetMaskInteractorly(const double c_x, const double c_y, const double c_z);
	// ������������ͼ���ID
	static void SetMaskMData(const int c_ID);

	// 3 Addins
	static void NewFromAddin(const int c_Type, QString name, int label, QColor color);

	static void BtnRst();

private:
	// Ψһ����
	static ASTransSidebarGeneral* ms_SelfPointer;

	// ��ǰѡ�е����ݽڵ㣬ѡ��ͬ�����ݽڵ���Ľ�����ʽ�����ݽ����ھ���ı�ǩ�����ݽڵ㱾���¼.
	static ASAbstractData* ms_crntDataNode;

	// ����ģ��
	ASFModelMask* m_FModelMask;

signals:
	
	void signalSetSideBarBelowWidget(int IDOfWidget, bool isShown); // ���ò�����·�widget�Ƿ���ʾ
	void signalRefreshDataComboBox(int c_AffectType);
	// 1 ImageNavigator
	void signalSetDisplayPosition(double PosX, double PosY, double PosZ);
	void signalSetDisplayFrame(int Frame);
	void signalSetImageSpacing(double* Spacing);
	void signalSetDisplayExtent(double* Extent, const int c_NumOfFrames);
	void signalSetWindowLevel(double window, double level);
	// 2 Mask
	void signalMaskEnabledChanged(); // ����ģ��ʹ��״̬�л�
	void signalSetMaskInteractorly(double x, double y, double z);

	void signalBtnRst();
};

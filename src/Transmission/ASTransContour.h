#pragma once
#include "ASTransmissionBase.h"
#include <vtkActor.h>

#define CtrOpe_Addtemp			0
#define CtrOpe_Movetemp			1
#define CtrOpe_Deletetemp		2
#define CtrOpe_Closetemp		3
#define CtrOpe_ClosetempStop	4
#define CtrOpe_Add				5
#define CtrOpe_Close			6

#define CtrOpe_MoveChoose		7 
#define CtrOpe_Moving			8 
#define CtrOpe_Delete			9 
#define CtrOpe_InsertStart		10 
#define CtrOpe_InsertContinue	11
#define CtrOpe_Refresh			12
#define CtrOpe_DeleteWhole		13

class ASAbstractData;
class ASFModelContour;
class ASContourData;

class ASTransContour : public ASTransmissionBase
{
	Q_OBJECT

public:
	ASTransContour(QObject *parent = 0);
	~ASTransContour();

	// Ψһ����
	static ASTransContour* GetSelfPointer();
	//��ǰContourID
	static void SetCrntContourID(const int c_id);
	static int GetCrntContourID();
	// �õ���ǰContour����
	static ASContourData* GetCurrentContourData();
	// �½��������ļ�
	static void NewContourData(ASAbstractData* pParent);
	static void NewContourData(ASAbstractData* pParent, QString name, int label, QColor color);
	// ˢ������������б�
	static void UpdateListsOfContourData();
	// ��ʼ�������߹���
	static void InitContourPipeline();
	// ����ģ���Ƿ�ʹ��
	static void SetModelEnabled(const bool c_enable);
	// �������Ƿ���ʾ
	static void SetContourShown(const bool c_Shown);
	// ���ý�����ʽ��0, ��ͨ; 1, ����
	static void SetInterfaceModel(const int c_model);
	static int GetInterfaceModel();
	// ˢ���������б�
	static void RefreshContourList();
	// ���õ�ǰ���ڻ��Ƶ����������ݵ�ID
	static void SetPaintingContourID(const int c_ID);
	// ����������
	static void SplineContourOperation(double* pos, int viewlabel, int operate, vtkActor* actor = nullptr);
	// �ж��Ƿ�Ϊ��һ�����Ƶ�
	static bool CheckFirstCtrlPoint(vtkActor* pActor, int viewlabel);
	// ˢ��
	static void RefreshContourDisplay();
	// ��Ӳ�̶��ļ�
	static void LoadContourDataFromDisk(const QStringList c_FileNameList);
	// ��ͼ����
	static void ViewZoom(const int c_view);
	// �Ƴ�������
	static void RemoveContour(const int c_ContourDataNodeID, const int c_ContourID);

private:

	// Ψһ����
	static ASTransContour* ms_SelfPointer;
	// ���ӵ�ģ��
	ASFModelContour* m_FModelContour;

	int ID_Closetemp = -1;
	int ContourID_Closetemp = -1;
	int viewLabel_Closetemp = -1;
	int indexOfContour_Closetemp = -1;
	int indexOfHandle_Closetemp = -1;
	bool Closetemp = false;

signals :

	// ���ý����ģ��ʹ��״̬
	void signalSetModelEnabled(bool enabled);

};

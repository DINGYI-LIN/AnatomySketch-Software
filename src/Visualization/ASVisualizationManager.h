#pragma once

class ASVisualizationManager2D;
class ASVisualizationManager3D;
class ASPipelineManager;
class ASAbstractData;
class ASArrayImageData;
class ASColorMap;

#define Layer_MaskModel			1000
#define Layer_SeedsModel		1001

#define ZoomPara 50

class ASVisualizationManager
{
public:
	ASVisualizationManager();
	~ASVisualizationManager();

	// ��õ�ǰ��ʾ����
	static void GetDisplayPosition(double* position);
	static void GetDisplayExtent(double* extent);
	static void GetDisplaySpacing(double* spacing);
	static ASArrayImageData* GetToplayerData();
	static int GetDisplayFrame();

	// ��Ⱦ
	static void Render();
	// ���ݵ�ǰ�����ߵ��������ĸ�����ʾԪ��
	static void UpdateAuxiliaryPipeline();
	// ������ʾ��Χ
	static void ResetDisplayExtent();
	// �����ж϶���������
	static void ResetTopArrayImage();
	// �������
	static void ResetCamera();
	// ���ý���
	static void SetDisplayPostion(const double c_x, const double c_y, const double c_z);
	// ����֡
	static void SetDisplayFrame(const int c_Frame);
	// ����ָ��
	static void RefreshZoomPara(const int c_View);
	static double GetZoomPara(const int c_View);

private:
	// ��ʾ����
	double m_ImagePosition[3];			// ���㣬��������ϵ
	double m_ImageExtent[6];			// ��Χ����������ϵ
	int m_ImageFrame;					// ��ǰ��ʾʱ��
	int m_ImageNumOfFrame;				// ͼ����ʾ֡��Χ
	double m_ImageSpacing[3];			// ���سߴ�
	double m_ZoomPara[3];				// ����ָ��
	ASArrayImageData* m_TopLayerData = nullptr;	// ����������
	// ��ǰ���ڵĶ���������������ʾ��û��ʾ��������ʮ���ߵȸ�����ʾ��
	int m_NumberOfObject = 0;
	// ��ģ��
	ASVisualizationManager2D* m_VisualizationManager2D;
	ASVisualizationManager3D* m_VisualizationManager3D;
	ASPipelineManager* m_PipeLineManager;
	ASColorMap* m_ColorMap;

	// Ψһ����
	static ASVisualizationManager* ms_SelfPointer;
};

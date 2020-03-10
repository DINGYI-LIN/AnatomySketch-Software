#pragma once

#include "ASImageData.h"
#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>
#include <vtkImageData.h>

// �̳�ʱ��Ҫ�ڹ��캯�����趨 m_Datatype�� ����дwalkerCheck����

#define ColorMode_Grayscale	0
#define ColorMode_RGB		1

class ASArrayImageData : public ASImageData
{
public:
	ASArrayImageData();
	~ASArrayImageData();
	virtual void DeleteNode();	// ���ô˺������ͷŽڵ�

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type); // �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
	virtual bool isTypeAbsolute(const int c_Type);
	static bool isTypeInheritedStatic(const int c_Type);

	// �õ�ͼ����Ϣ
	int getColorMap();
	void setColorMap(const int colormap); // ������ɫ�� �궨��:ColorMap_
	int getLayer();
	void setLayer(const int c_Layer);
	// ��λ����
	double* getWindowLevel();
	void setWindowLevel(); // �޲�����ʾ����ΪĬ��ֵ
	void setWindowLevel(const double window, const double level);
	double* getImageExtent();
	// ��͸����
	int getOpacity();
	void setOpacity(const int opacity);
	// ͼ������
	vtkImageData* getArrayImageData(); // ������һ�����ݵ�ͼ��
	void copyArrayImageDataFrom(const int c_ID);
	// �Ҷ�ͼ�ͱ�ǩͼ
	enumArrayImageDataType getArrayImageDataType();
	void setArrayImageDataType(const enumArrayImageDataType type);
	// ɫ��ģʽ
	void SetColorMode(const int c_mode);
	int GetColorMode();

	// ��������
	void setArrayImageData(vtkImageData* ImageData);
	// �������ݺ�����ݳ�ʼ��
	void DataInitAfterLoad();


	// �麯��
	// 1 ���ݶ�ȡ
	//virtual int LoadData(QString filename);
	// 2 �����Ƿ���ʾ����д���麯������ΪҪͳ�Ƶ�ǰ��ʾ�������ݵ�����
	virtual void setShown(const bool shown);

	// ---------------------- ��̬���� ----------------------
	// �õ���ǰ�Ѿ�������������
	static int getNumOfArrayImageData();
	// �õ���ǰ�Ѿ���ʾ����������
	static int getNumberOfArrayImageDataShown();
	// �õ���ǰ������ʾ�����ݣ�û�з���nullptr
	static ASArrayImageData* getTopLayerDisplayingArrayImageData();

private:

	static int ms_nNumOfArrayImageData;				// ��ǰ�򿪵������ݵ�����
	static int ms_nNumberOfArrayImageDataShown;		// ��ǰ��ʾ�������ݵ�����

protected:

	int			m_ColorMode;			// ɫ��ģʽ���궨��:ColorMode_
	int			m_nColorMap;			// �궨��:ColorMap_
	int			m_nLayer;				// ����ʾʱ�Ĳ㼶��ϵ���������ظ������������
	double		m_adWindowLevel[2];		// [0]��color window [1]��color level
	int	m_nOpacity = 100; // ��͸����,0~100
	enumArrayImageDataType			m_ArrayImageDataType;	// ͼ�����͡�0��ͼ���ļ���1����ǩͼ�ļ�
	vtkSmartPointer<vtkMatrix4x4>	m_pTransform;			// ͼ��任����
	vtkSmartPointer<vtkImageData>	m_pImageData;			// ����������

	// �ж�����m_pImageData�ǻҶ�ͼ���Ǳ�ǩͼ������m_ArrayImageDataType��m_nColorMap����ȡ����ʱʹ��
	void checkDataTypeAndColorMap();
	// �������ݷ�Χ������m_adImageExtent����ȡ����ʱʹ��
	void checkDataExtent();
	// �ж�����m_pImageData�Ƿ�ΪCTͼ�񣬸���m_adWindowLevel����ȡ����ʱʹ��
	void checkDataIsCTOrNot();

	// ��̬��Ա�ͳ�Ա����
	

};

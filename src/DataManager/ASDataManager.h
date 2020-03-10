#pragma once

//#include "common.h"
//#include "ASSignalLinker.h"
#include <vtkDICOMDirectory.h>
#include <vtkActor.h>
#include <vtkImageData.h>
#include "QObject"
#include "QString"
#include "QList"

class ASDataTree;
class ASAbstractData;
class ASArrayImageData;
class ASPolyDeformation;
class ASMask;

class ASDataManager : public QObject
{
	Q_OBJECT

public:
	ASDataManager(QObject *parent = 0);
	~ASDataManager();
	
	//�ɸ�����������������ָ��
	//void setSignalLinker(ASSignalLinker* linker);
	//������ʼ���������ʼ�������׶�
	//void Parameterinitialization();

	// ������
	//void LoadData(QString filename);
	// ��ȡDICOM����
	//void LoadDICOMSeries(vtkDICOMDirectory* dir, QList<int>* serieslist);
	// ��������
	//void saveData(ASAbstractData* data);
	// �Ƴ�����
	//void removeData(ASAbstractData* data);
	// �½���ǩ�ļ�������Ϊ���֣���ǩֵ����ɫ
	//void NewLabelData(QString str, int label, int* nColor);
	// �½�������
	//ASArrayImageData* NewArrayImageData(const int c_TemplateID, QString qname);

	//----------------- Mask -----------------------

	//�õ��������������ָ�룬ֻ��
	//unsigned char* GetMaskArrayAddr();
	//�õ�������ʾ��vtkImageData
	//vtkImageData* GetMaskImageData();
	//�趨����ͼ������ݣ���������������Ժ��������飬��Ҫ�������ͼ���ID
	//void setMaskImageData(int ID);

	//----------------- PolyDeformation -----------------------

	//// ��ʼPolyDeformation����
	//void startPolyDeformation(double posx, double posy, double posz, enumPolyDeformaiton type, double ViewRange);
	//// ����PolyDeformation����
	//void PolyDeformationContinue(double posx, double posy, double posz, int viewlabel, enumPolyDeformaiton TransType);
	////����
	//void PolyDeformationUndo();
	////�õ���ǰPolyDeformation����������
	//enumPolyDeformaiton getCurrentPolyDeformationType();
	//// �������ת
	//void RotationChanging(double angle, int viewlabel);
	//// Zoom
	//void ZoomChanging(double multiple_x, double multiple_y, double multiple_z);
	//void ZoomChanging(double multiple);
	//// FFD���ֵ���Ӱ�췶Χ
	//void FFDWheel(int ForwardOrBackward);

private:

	// ���ݴ洢�������ݽṹ
	ASDataTree* m_DataTree;
	// �����ݱ༭ģ��
	//ASPolyDeformation* m_PolyDeformation;
	// ����ģ��
	//ASMask* m_pMask;
	// �����ͨ���ź�������
	//ASSignalLinker* m_SignalLinker;

signals:

	////---------------------------��ʾ����--------------------------------------
	////������ʾ����
	//void signalAddImageDataDisplay(int ID);					//�����������ļ���ʾ
	//void signalAddPolyDataDisplay(int ID);					//�����������ļ���ʾ
	//void signalAddDICOMRTDisplay();							//����DICOM-RT�ļ���ʾ������ͬʱ���˶��RT�ļ�������ֱ�ӽ���RT������ʾ��ˢ�¡�
	//void signalAddSeeds2DDisplay(int ID);					//�������ӵ���ʾ�����½���Ӧ��ǩ�ļ������ӵ���Ⱦ����
	//void signalRemoveDataDisplay(int ID, enumDataType type);// �Ƴ�������ʾ
	//void signalUpdataLayerDisplay();						//�����ݲ���º�ˢ�²㼶����ʾ

	////������ʾ����
	//void signalPolyDeformationRefresh();					//PolyDeformationˢ����ʾ
	////����Ҫ���ݹ�����ָ����෢�͵�ַ���������ʼ���׶Σ����⻥����ã�ʹ�ÿ�ָ��
	//void signalSetDatamanagerAddress(void* p);
	////ˢ���ļ���ʾ�б�
	//void signalRefreshDataManagerWidget();
	////ˢ�������ļ�����ѡ��
	//void signalRefreshFileComboBox();
};

#pragma once
#include "ASTransmissionBase.h"
#include <vtkDICOMDirectory.h>
#include <vtkSmartPointer.h>
#include <QString>
#include <QList>
#include <QMessageBox>

class ASDialogDICOMImporter;
class ASFModelDICOMImporter;
class ASAbstractData;

class ASTransDICOMLoader : public ASTransmissionBase
{
	Q_OBJECT

public:
	ASTransDICOMLoader(QObject *parent = 0);
	~ASTransDICOMLoader();

	// Ψһ����
	static ASTransDICOMLoader* GetSelfPointer();

	// ��DIOCOMɨ�贰��
	static void OpenDICOMScanWidget();
	// ɨ��Ӳ��
	static void ScanDisk(const QString c_path);
	// ɨ�����
	static void ScanningDiskFinished(vtkDICOMDirectory* DICOMDirectory);
	// ɨ������б�ȡ��
	static void ScanningDiskStopManualy();
	// ��ȡDICOM����
	static bool LoadDICOMData(vtkDICOMDirectory* dir, QList<int>* serieslist);
	// DICOM���ж�ȡ��ϣ�NewDataNode = nullptr��ʾ��ȡʧ��
	static void LoadDICOMDataFinished(ASAbstractData* NewDataNode, int Type);

private:
	// Ψһ����
	static ASTransDICOMLoader* mc_TransDICOMLoader;

	// DICOM�ļ�ɨ��ĶԻ���
	ASDialogDICOMImporter* m_DialogDICOMImporter;
	// DICOM�ļ�����ģ�飬��ģ�������ɨ��Ӳ�̵Ĺ��ܣ����Խ���ɨ����ȡ�̡߳�
	ASFModelDICOMImporter* m_FModelDICOMImporter = nullptr;

	// �����ݽ��ȶԻ���
	QMessageBox* m_MessageBoxImportDataFromDisk = nullptr;
	int NumOfSeriesToLoad;
	int crntSeriesToLoad;
	// �����ļ�DIR�����к�
	vtkSmartPointer<vtkDICOMDirectory> m_DICOMDirectory;
	QList<int> m_SeriesList;

private slots:

	// ��Ӳ�̶�ȡ���ݹ����б�ȡ��
	void slotLoadDICOMStopManualy(QAbstractButton* button);

signals:

};

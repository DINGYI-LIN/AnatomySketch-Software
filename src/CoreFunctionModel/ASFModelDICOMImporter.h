#pragma once
#include "ASFunctionModelBase.h"
#include <vtkSmartPointer.h>
#include <vtkDICOMDirectory.h>
#include <QMutex>
#include <QList>

class ASThreadDICOMScanner;
class ASThreadDICOMLoader;
class ASAbstractData;

class ASFModelDICOMImporter : public ASFunctionModelBase
{
	Q_OBJECT

public:
	ASFModelDICOMImporter(QObject *parent = 0);
	~ASFModelDICOMImporter();

	// ����ɨ��·��
	void SetScanningPath(const QString c_ScanPath);
	// ��ʼɨ�裬�����̲߳�������Ϣ
	void StartScanning();
	// ɨ�豻ȡ��������ɨ��
	void CancelScanning();
	// ��ȡDICOM����
	void LoadDICOMData(vtkDICOMDirectory* dir, const int c_Series);
	// ��ȡDICOM���б�ȡ����������ȡ
	void CancelLoadDICOMData();

private:

	// ɨ��·��
	QString m_ScanningPath;
	
	// ��ģ��
	ASThreadDICOMScanner* m_ThreadDICOMScanner = nullptr;
	ASThreadDICOMLoader* m_ThreadDICOMLoader = nullptr;

	// ɨ�����洢
	vtkSmartPointer<vtkDICOMDirectory> m_DICOMDirectory;
	QMutex* m_MutexForDICOMDirectory;

private slots:

	// ɨ�����
	void slotScanningFinished();
	// ���ݶ�ȡ�ɹ���NewDataNode = nullptr��ʾ��ȡʧ��
	void slotDataLoadFinished(ASAbstractData* NewDataNode, int Type);

signals:

	// ɨ�����
	void signalScanningFinished(vtkDICOMDirectory* m_DICOMDirectory);

};

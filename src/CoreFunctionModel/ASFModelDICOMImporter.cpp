#include "ASFModelDICOMImporter.h"
#include "ASThreadDICOMScanner.h"
#include "ASThreadDICOMLoader.h"
#include "ASTransDICOMLoader.h"

ASFModelDICOMImporter::ASFModelDICOMImporter(QObject *parent)
	: ASFunctionModelBase(parent)
{
	m_DICOMDirectory = vtkSmartPointer<vtkDICOMDirectory>::New();

	m_MutexForDICOMDirectory = new QMutex();
}

ASFModelDICOMImporter::~ASFModelDICOMImporter()
{

}

// ����ɨ��·��
void ASFModelDICOMImporter::SetScanningPath(const QString c_ScanPath)
{
	m_ScanningPath = c_ScanPath;
}
// ��ʼɨ�裬�����̲߳�������Ϣ
void ASFModelDICOMImporter::StartScanning()
{
	if (m_ThreadDICOMScanner != nullptr)
	{
		return;
	}	
	m_ThreadDICOMScanner = new ASThreadDICOMScanner(this);
	connect(m_ThreadDICOMScanner, SIGNAL(signalScanningFinished()), this, SLOT(slotScanningFinished()));
	m_ThreadDICOMScanner->SetScanPath(m_ScanningPath);
	m_ThreadDICOMScanner->SetDICOMDirectory(m_DICOMDirectory);
	m_ThreadDICOMScanner->SetMutex(m_MutexForDICOMDirectory);
	m_ThreadDICOMScanner->start();
}
// ɨ�豻ȡ��������ɨ��
void ASFModelDICOMImporter::CancelScanning()
{
	m_ThreadDICOMScanner->terminate();
	m_ThreadDICOMScanner->wait();
	m_MutexForDICOMDirectory->unlock();
	disconnect(m_ThreadDICOMScanner, SIGNAL(signalScanningFinished()), this, SLOT(slotScanningFinished()));
	/*
	Since Qt 4.8, if deleteLater() is called on an object that lives in a thread with no running event loop,
	the object will be destroyed when the thread finishes.
	m_ThreadExportDataToDisk->deleteLater();
	*/
	delete m_ThreadDICOMScanner;
	m_ThreadDICOMScanner = nullptr;
}
// ɨ�����
void ASFModelDICOMImporter::slotScanningFinished()
{
	m_ThreadDICOMScanner->terminate();
	m_ThreadDICOMScanner->wait();
	// �ͷ��߳�
	disconnect(m_ThreadDICOMScanner, SIGNAL(signalScanningFinished()), this, SLOT(slotScanningFinished()));
	delete m_ThreadDICOMScanner;
	m_ThreadDICOMScanner = nullptr;
	// ˢ�´��������б���ʾ
	ASTransDICOMLoader::ScanningDiskFinished(m_DICOMDirectory);
}
// ��ȡDICOM����
void ASFModelDICOMImporter::LoadDICOMData(vtkDICOMDirectory* dir, const int c_Series)
{
	if (m_ThreadDICOMLoader != nullptr)
	{
		return;
	}
	m_ThreadDICOMLoader = new ASThreadDICOMLoader(this);
	connect(m_ThreadDICOMLoader, SIGNAL(signalDataLoadFinished(ASAbstractData*, int)), this, SLOT(slotDataLoadFinished(ASAbstractData*, int)));
	m_ThreadDICOMLoader->SetDICOMDirSeries(dir, c_Series);
	m_ThreadDICOMLoader->start();
}
// ��ȡDICOM���б�ȡ����������ȡ
void ASFModelDICOMImporter::CancelLoadDICOMData()
{
	m_ThreadDICOMLoader->terminate();
	m_ThreadDICOMLoader->wait();
	disconnect(m_ThreadDICOMLoader, SIGNAL(signalDataLoadFinished(ASAbstractData*, int)), this, SLOT(slotDataLoadFinished(ASAbstractData*, int)));
	delete m_ThreadDICOMLoader; // ������ܻ�����ڴ�й©	
	m_ThreadDICOMLoader = nullptr;
}
// ���ݶ�ȡ�ɹ���NewDataNode = nullptr��ʾ��ȡʧ��
void ASFModelDICOMImporter::slotDataLoadFinished(ASAbstractData* NewDataNode, int Type)
{
	disconnect(m_ThreadDICOMLoader, SIGNAL(signalDataLoadFinished(ASAbstractData*, int)), this, SLOT(slotDataLoadFinished(ASAbstractData*, int)));
	delete m_ThreadDICOMLoader;
	m_ThreadDICOMLoader = nullptr;
	ASTransDICOMLoader::LoadDICOMDataFinished(NewDataNode, Type);
}
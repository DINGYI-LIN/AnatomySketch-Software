#include "ASTransDICOMLoader.h"
#include "ASDialogDICOMImporter.h"
#include "ASFModelDICOMImporter.h"
#include "ASTransAddDeleteData.h"
#include "ASAbstractData.h"
#include "ASMainWidget.h"
#include "ASDataTree.h"
#include "ASTransDataGeneral.h"

ASTransDICOMLoader* ASTransDICOMLoader::mc_TransDICOMLoader = nullptr;

ASTransDICOMLoader::ASTransDICOMLoader(QObject *parent)
	: ASTransmissionBase(parent)
{
	mc_TransDICOMLoader = this;

	m_DialogDICOMImporter = new ASDialogDICOMImporter(ASMainWidget::GetMainWidget());
	// ɨ���ȡģ��
	m_FModelDICOMImporter = new ASFModelDICOMImporter(this);
}

ASTransDICOMLoader::~ASTransDICOMLoader()
{

}
// Ψһ����
ASTransDICOMLoader* ASTransDICOMLoader::GetSelfPointer()
{
	return mc_TransDICOMLoader;
}

// ��DIOCOMɨ�贰��
void ASTransDICOMLoader::OpenDICOMScanWidget()
{
	mc_TransDICOMLoader->m_DialogDICOMImporter->show();
	mc_TransDICOMLoader->m_DialogDICOMImporter->CheckVoid();
}
// ɨ��Ӳ��
void ASTransDICOMLoader::ScanDisk(const QString c_path)
{
	mc_TransDICOMLoader->m_FModelDICOMImporter->SetScanningPath(c_path);
	mc_TransDICOMLoader->m_FModelDICOMImporter->StartScanning(); // ��ʼɨ�裬���̣߳����������ᷢsignal����
}
// ɨ�����
void ASTransDICOMLoader::ScanningDiskFinished(vtkDICOMDirectory* DICOMDirectory)
{
	mc_TransDICOMLoader->m_DialogDICOMImporter->DiskScanningFinished(DICOMDirectory);
}
// ɨ������б�ȡ��
void ASTransDICOMLoader::ScanningDiskStopManualy()
{
	mc_TransDICOMLoader->m_FModelDICOMImporter->CancelScanning();
}
// ��ȡDICOM����
bool ASTransDICOMLoader::LoadDICOMData(vtkDICOMDirectory* dir, QList<int>* serieslist)
{
	if (serieslist->size() == 0)
	{
		return false;
	}
	mc_TransDICOMLoader->m_DICOMDirectory = dir;
	mc_TransDICOMLoader->m_SeriesList = *serieslist;
	mc_TransDICOMLoader->NumOfSeriesToLoad = serieslist->size();
	mc_TransDICOMLoader->crntSeriesToLoad = 1;
	// 0 �������ȶԻ���
	mc_TransDICOMLoader->m_MessageBoxImportDataFromDisk = new QMessageBox(QMessageBox::NoIcon, 
		"Anatomy Sketch", 
		tr("Loading the ") + QString::number(mc_TransDICOMLoader->crntSeriesToLoad) + tr("th sequence, ") + QString::number(mc_TransDICOMLoader->NumOfSeriesToLoad) + tr("in total."),
		QMessageBox::Cancel, NULL);
	connect(mc_TransDICOMLoader->m_MessageBoxImportDataFromDisk, SIGNAL(buttonClicked(QAbstractButton*)), mc_TransDICOMLoader, SLOT(slotLoadDICOMStopManualy(QAbstractButton*)));
	mc_TransDICOMLoader->m_MessageBoxImportDataFromDisk->setModal(true);
	mc_TransDICOMLoader->m_MessageBoxImportDataFromDisk->show();
	// 1 ��������
	mc_TransDICOMLoader->m_FModelDICOMImporter->LoadDICOMData(dir, serieslist->first()); // ��ʼ�����ݣ����̣߳����������ᷢsignal����
	return true;
}
// DICOM���ж�ȡ��ϣ�NewDataNode = nullptr��ʾ��ȡʧ��
void ASTransDICOMLoader::LoadDICOMDataFinished(ASAbstractData* NewDataNode, int Type)
{
	if (NewDataNode == nullptr)
	{
		// ��ȡʧ��
		QMessageBox::critical(NULL, "Anatomy Sketch", tr("The") + QString::number(mc_TransDICOMLoader->crntSeriesToLoad) + tr("th sequence failed to load."), QMessageBox::Yes, QMessageBox::Yes);
		mc_TransDICOMLoader->m_SeriesList.removeFirst();
		mc_TransDICOMLoader->crntSeriesToLoad++;
	} 
	else
	{
		mc_TransDICOMLoader->m_SeriesList.removeFirst();
		mc_TransDICOMLoader->crntSeriesToLoad++;
		// 1 ���¶�������ݼ���������
		ASDataTree::NewDataNode(NewDataNode, nullptr);
		// 2 �����¹���
		ASTransAddDeleteData::AddNewPipeline(NewDataNode, Type);
		// 3 ���õ�ǰ����
		if (NewDataNode->isTypeInherited(DataType_ArrayImageData))
		{
			if (ASTransDataGeneral::GetGeneratingData() == nullptr)
			{
				ASTransDataGeneral::SetGeneratingData(NewDataNode);
			}
		}
	}
	// 3 �ж��Ƿ���Ҫ���������
	if (mc_TransDICOMLoader->m_SeriesList.size() == 0)
	{
		// û��Ҫ����������
		disconnect(mc_TransDICOMLoader->m_MessageBoxImportDataFromDisk, SIGNAL(buttonClicked(QAbstractButton*)), mc_TransDICOMLoader, SLOT(slotLoadDICOMStopManualy(QAbstractButton*)));
		delete mc_TransDICOMLoader->m_MessageBoxImportDataFromDisk;
		ASTransAddDeleteData::UpdateDispleyAfterAddDelete();
		ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_ArrayImageData);
	}
	else
	{
		// ����������
		mc_TransDICOMLoader->m_MessageBoxImportDataFromDisk->setText(
			tr("Loading the ") + QString::number(mc_TransDICOMLoader->crntSeriesToLoad) + tr("th sequence, ") + QString::number(mc_TransDICOMLoader->NumOfSeriesToLoad) + tr("in total."));
		mc_TransDICOMLoader->m_FModelDICOMImporter->LoadDICOMData(mc_TransDICOMLoader->m_DICOMDirectory, mc_TransDICOMLoader->m_SeriesList.first()); // ��ʼ�����ݣ����̣߳����������ᷢsignal����
	}
}

// ��Ӳ�̶�ȡ���ݹ����б�ȡ��
void ASTransDICOMLoader::slotLoadDICOMStopManualy(QAbstractButton* button)
{
	m_FModelDICOMImporter->CancelLoadDICOMData();
	// û��Ҫ����������	
	disconnect(mc_TransDICOMLoader->m_MessageBoxImportDataFromDisk, SIGNAL(buttonClicked(QAbstractButton*)), mc_TransDICOMLoader, SLOT(slotLoadDICOMStopManualy(QAbstractButton*)));
	mc_TransDICOMLoader->m_MessageBoxImportDataFromDisk->deleteLater();
	ASTransAddDeleteData::UpdateDispleyAfterAddDelete();
	ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_ArrayImageData);
}
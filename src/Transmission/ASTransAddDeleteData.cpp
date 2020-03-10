#include "ASTransAddDeleteData.h"
#include "ASTransGeneralInteractor.h"
#include "ASFModelImportDataFromDisk.h"
#include "ASFModelExportDataToDisk.h"
#include "ASArrayImageData.h"
#include "ASPolyImageData.h"
#include "ASOperation.h"
#include "ASPipelineManager.h"
#include "ASPipelineArrayImage.h"
#include "ASPipelinePolyImage.h"
#include "ASVisualizationManager.h"
#include "ASVisualizationManager2D.h"
#include "ASDataTree.h"
#include "ASDataStructureWalker.h"
#include "ASTransSidebarGeneral.h"
#include "ASSeedData.h"
#include "ASContourData.h"
#include "ASLandmarkData.h"
#include "ASTransSeeds.h"
#include "ASTransContour.h"
#include "ASTransLandmark.h"
#include "ASTransAddins.h"
#include "ASMainWidget.h"
#include "ASTransDataGeneral.h"
#include "ASROIData.h"
#include "ASTransROI.h"
#include "ASTransSetting.h"
#include <QFileInfo>
#include <QFileDialog>
#include <QInputDialog>
#include <QSettings>

ASTransAddDeleteData* ASTransAddDeleteData::ms_SelfPointer = nullptr;
QStringList* ASTransAddDeleteData::m_FileListToLoad = new QStringList();
ASFModelImportDataFromDisk* ASTransAddDeleteData::m_FModelImportDataFromDisk = nullptr;
ASFModelExportDataToDisk* ASTransAddDeleteData::m_FModelExportDataToDisk = nullptr;
bool ASTransAddDeleteData::ms_bResetCarmera = true;

ASTransAddDeleteData::ASTransAddDeleteData(QObject *parent)
	: ASTransmissionBase(parent)
{
	ms_SelfPointer = this;
	m_LoadWaitingSeed = new QStringList;
	m_LoadWaitingCtr = new QStringList;
	m_LoadWaitingLdm = new QStringList;
	m_LoadWaitingRoi = new QStringList;
}

ASTransAddDeleteData::~ASTransAddDeleteData()
{

}

// Ψһ����
ASTransAddDeleteData* ASTransAddDeleteData::GetSelfPointer()
{
	return ms_SelfPointer;
}

// ��Ӳ�̶�ȡ����
void ASTransAddDeleteData::LoadDataFromDisk(const QStringList c_FileNameList)
{
	ms_bResetCarmera = (ASPipelineBase::GetNumOfObj2D() == 0);
	if (c_FileNameList.size() == 0)
	{
		// ����ȴ�������
		if (ms_SelfPointer->m_LoadWaitingSeed->size() > 0)
		{
			ASTransSeeds::LoadseedDataFromDisk(*ms_SelfPointer->m_LoadWaitingSeed);
			ms_SelfPointer->m_LoadWaitingSeed->clear();
		}
		if (ms_SelfPointer->m_LoadWaitingCtr->size() > 0)
		{
			ASTransContour::LoadContourDataFromDisk(*ms_SelfPointer->m_LoadWaitingCtr);
			ms_SelfPointer->m_LoadWaitingCtr->clear();
		}
		if (ms_SelfPointer->m_LoadWaitingLdm->size() > 0)
		{
			ASTransLandmark::LoadLandMDataFromDisk(*ms_SelfPointer->m_LoadWaitingLdm);
			ms_SelfPointer->m_LoadWaitingLdm->clear();
		}
		if (ms_SelfPointer->m_LoadWaitingRoi->size() > 0)
		{
			ASTransROI::LoadROIDataFromDisk(*ms_SelfPointer->m_LoadWaitingRoi);
			ms_SelfPointer->m_LoadWaitingRoi->clear();
		}
		qDebug("Update Visualization.");
		ASTransAddDeleteData::UpdateDispleyAfterAddDelete();
		qDebug("Update Lists.");
		ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_AbstractData);
		return;
	}
	if (m_FModelImportDataFromDisk == nullptr)
	{
		m_FModelImportDataFromDisk = new ASFModelImportDataFromDisk();
	}

	*m_FileListToLoad = c_FileNameList;

	// 0 �������ȶԻ���
	ms_SelfPointer->m_MessageBoxImportDataFromDisk = new QMessageBox(QMessageBox::NoIcon, 
		"Anatomy Sketch", "Loading " + c_FileNameList.first(), QMessageBox::Cancel, NULL);
	ms_SelfPointer->m_MessageBoxImportDataFromDisk->setModal(true);
	ms_SelfPointer->m_MessageBoxImportDataFromDisk->show();
	connect(ms_SelfPointer->m_MessageBoxImportDataFromDisk, SIGNAL(buttonClicked(QAbstractButton*)), 
		ms_SelfPointer, SLOT(slotLoadDataStopManualy(QAbstractButton*)));

	qDebug(qPrintable("start Loading Data: " + c_FileNameList.first()));

	// �������ݣ����̣߳����������ɹ���ᷢsignal����
	m_FModelImportDataFromDisk->LoadDataFromDisk(c_FileNameList.first());
}
void ASTransAddDeleteData::LoadDataFromDiskFinished(ASAbstractData* NewDataNode, int Type)
{
	m_FileListToLoad->removeFirst();
	// 1 ���¶�������ݼ���������
	ASDataTree::NewDataNode(NewDataNode, nullptr);
	qDebug("Build new data node.");
	if (NewDataNode->isTypeInherited(DataType_ArrayImageData))
	{
		if (ASTransDataGeneral::GetGeneratingData() == nullptr)
		{
			ASTransDataGeneral::SetGeneratingData(NewDataNode);
		}
	}
	// 2 �����¹���
	ASTransAddDeleteData::AddNewPipeline(NewDataNode, Type);
	qDebug("Build new pipeline.");
	// 3 �ж��Ƿ���Ҫ���������
	if (m_FileListToLoad->size() == 0)
	{
		// û��Ҫ����������
		disconnect(ms_SelfPointer->m_MessageBoxImportDataFromDisk, SIGNAL(buttonClicked(QAbstractButton*)), ms_SelfPointer, SLOT(slotLoadDataStopManualy(QAbstractButton*)));
		delete ms_SelfPointer->m_MessageBoxImportDataFromDisk;
		// ����ȴ�������
		if (ms_SelfPointer->m_LoadWaitingSeed->size() > 0)
		{
			ASTransSeeds::LoadseedDataFromDisk(*ms_SelfPointer->m_LoadWaitingSeed);
			ms_SelfPointer->m_LoadWaitingSeed->clear();
		}
		if (ms_SelfPointer->m_LoadWaitingCtr->size() > 0)
		{
			ASTransContour::LoadContourDataFromDisk(*ms_SelfPointer->m_LoadWaitingCtr);
			ms_SelfPointer->m_LoadWaitingCtr->clear();
		}
		if (ms_SelfPointer->m_LoadWaitingLdm->size() > 0)
		{
			ASTransLandmark::LoadLandMDataFromDisk(*ms_SelfPointer->m_LoadWaitingLdm);
			ms_SelfPointer->m_LoadWaitingLdm->clear();
		}
		if (ms_SelfPointer->m_LoadWaitingRoi->size() > 0)
		{
			ASTransROI::LoadROIDataFromDisk(*ms_SelfPointer->m_LoadWaitingRoi);
			ms_SelfPointer->m_LoadWaitingRoi->clear();
		}
		ASTransAddDeleteData::UpdateDispleyAfterAddDelete(ms_bResetCarmera);
		ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_AbstractData);
	}
	else
	{
		// ����������
		ms_SelfPointer->m_MessageBoxImportDataFromDisk->setText(m_FileListToLoad->first());
		m_FModelImportDataFromDisk->LoadDataFromDisk(m_FileListToLoad->first());
	}
}
void ASTransAddDeleteData::LoadDataStopManualyFinished()
{
	m_FileListToLoad->clear();
	// û��Ҫ����������
	disconnect(ms_SelfPointer->m_MessageBoxImportDataFromDisk, SIGNAL(buttonClicked(QAbstractButton*)), ms_SelfPointer, SLOT(slotLoadDataStopManualy(QAbstractButton*)));
	//delete ms_SelfPointer->m_MessageBoxImportDataFromDisk;
	qDebug("Update Visualization.");
	ASTransAddDeleteData::UpdateDispleyAfterAddDelete();
	qDebug("Update Lists.");
	ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_AbstractData);
}
void ASTransAddDeleteData::AddLoadWaitingArea(const QStringList c_strlist, const int c_type)
{
	switch (c_type)
	{
	case 0:
		// seed
		ms_SelfPointer->m_LoadWaitingSeed->append(c_strlist);
		break;
	case 1:
		// ctr
		ms_SelfPointer->m_LoadWaitingCtr->append(c_strlist);
		break;
	case 2:
		// ldm
		ms_SelfPointer->m_LoadWaitingLdm->append(c_strlist);
		break;
	case 3:
		// roi
		ms_SelfPointer->m_LoadWaitingRoi->append(c_strlist);
		break;
	default:
		break;
	}
}
// �������ݵ�Ӳ��
void ASTransAddDeleteData::SaveOneDataToDisk(ASAbstractData* SaveDataNode)
{
	ms_SelfPointer->m_NodeListToWrite.clear();
	ms_SelfPointer->m_PathListToWrite.clear();
	//Ϊ���ܼ�ס�ϴδ򿪵�·��
	QString lastPath = ASTransSetting::GetSetting()->value("LastFilePath").toString();
	// 0 �����ļ���
	QString WritingFileName;
	QFileDialog FileDialog;
	switch (SaveDataNode->getDataType())
	{
	case DataType_ArrayImageData:
	case DataType_DICOMData:
	{
		ASArrayImageData* crntDataNode = (ASArrayImageData*)SaveDataNode;
		QString selectFilter = "mhd(*.mhd)";
		//WritingFileName = FileDialog.getSaveFileName(0, "save", "./" + crntDataNode->getName() + ".mhd", "mhd(*.mhd)", &selectFilter,
		//	QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
		WritingFileName = FileDialog.getSaveFileName(0, "save", lastPath + "/" +
			crntDataNode->getName(), "mhd(*.mhd)", &selectFilter,
			QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
		if (WritingFileName == "")
		{
			return;
		}
		break;
	}
	case DataType_PolyImageData:
	{
		ASPolyImageData* crntDataNode = (ASPolyImageData*)SaveDataNode;
		QString setFilter = "OBJ(*.obj);;STL(*.stl);;PLY(*.ply)";
		QString selectFilter, dirString;
		QString crntFileName = crntDataNode->getFileName();
		if (crntFileName.isEmpty() == false)
		{
			dirString = QFileInfo(crntFileName).filePath();
			if (QFileInfo(crntFileName).suffix() == "stl")
			{
				selectFilter = "STL(*.stl)";
			}
			else if (QFileInfo(crntFileName).suffix() == "obj")
			{
				selectFilter = "OBJ(*.obj)";
			}
			else if (QFileInfo(crntFileName).suffix() == "ply")
			{
				selectFilter = "PLY(*.ply)";
			}
		}
		else
		{
			dirString = "./" + crntDataNode->getName() + ".stl";
			selectFilter = "STL(*.stl)";
		}
		//WritingFileName = FileDialog.getSaveFileName(0, "save", dirString, setFilter, &selectFilter,
		//	QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
		WritingFileName = FileDialog.getSaveFileName(0, "save", lastPath + "/" + crntDataNode->getName(), 
			setFilter, &selectFilter,
			QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
		if (WritingFileName == "")
		{
			return;
		}
		break;
	}
	case DataType_SeedData:
	{
		ASSeedData* crntDataNode = static_cast<ASSeedData*>(SaveDataNode);
		QString selectFilter = "seed(*.seed)";
		QString crntName = "";
		if (crntDataNode->getFather()->getDataNodeID() >= 0)
		{
			crntName = lastPath + "/" + crntDataNode->getFather()->getName();
		}
		WritingFileName = FileDialog.getSaveFileName(0, "save", crntName, "seed(*.seed)", &selectFilter,
			QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
		break;
	}
	case DataType_ContourData:
	{
		ASContourData* crntDataNode = static_cast<ASContourData*>(SaveDataNode);
		QString selectFilter = "ctr(*.ctr)";
		QString crntName = "";
		if (crntDataNode->getFather()->getDataNodeID() >= 0)
		{
			crntName = lastPath + "/" + crntDataNode->getFather()->getName();
		}
		WritingFileName = FileDialog.getSaveFileName(0, "save", crntName, "ctr(*.ctr)", &selectFilter,
			QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
		if (WritingFileName == "")
		{
			return;
		}
		break;
	}
	case DataType_LandmarkData:
	{
		ASLandmarkData* crntDataNode = static_cast<ASLandmarkData*>(SaveDataNode);
		QString selectFilter = "ldm(*.ldm)";
		QString crntName = "";
		if (crntDataNode->getFather()->getDataNodeID() >= 0)
		{
			crntName = lastPath + "/" + crntDataNode->getFather()->getName();
		}
		WritingFileName = FileDialog.getSaveFileName(0, "save", crntName, "ldm(*.ldm)", &selectFilter,
			QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
		if (WritingFileName == "")
		{
			return;
		}
		break;
	}
	case DataType_ROI:
	{
		ASROIData* crntDataNode = static_cast<ASROIData*>(SaveDataNode);
		QString selectFilter = "roi(*.roi)";
		QString crntName = "";
		if (crntDataNode->getFather()->getDataNodeID() >= 0)
		{
			crntName = lastPath + "/" + crntDataNode->getFather()->getName();
		}
		WritingFileName = FileDialog.getSaveFileName(0, "save", crntName, "roi(*.roi)", &selectFilter,
			QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
		if (WritingFileName == "")
		{
			return;
		}
		break;
	}
	default:
		break;
	}
	QFileInfo fi(WritingFileName);
	ASTransSetting::GetSetting()->setValue("LastFilePath", QVariant(fi.path()));
	ms_SelfPointer->m_PathListToWrite.append(WritingFileName);
	ms_SelfPointer->m_NodeListToWrite.append(SaveDataNode);
	ASTransAddDeleteData::StartSaveDataToDisk();
}
void ASTransAddDeleteData::SaveAllPolyDataToDisk()
{
	ms_SelfPointer->m_NodeListToWrite.clear();
	ms_SelfPointer->m_PathListToWrite.clear();
	//���ļ���׼�Ի���
	QString OperatingDirectoryName = QFileDialog::getExistingDirectory(
		0,						// ָ������
		"Directory",				// �ļ��Ի������������
		"");					// ָ�����ļ�Ŀ¼
								//�ж��Ƿ���ļ�
	if (OperatingDirectoryName.size() == 0)
	{
		return;
	}
	// ������������
	for (ASAbstractData* item = ASDataStructureWalker::bigen_inherit(DataType_PolyImageData); item != nullptr; item = ASDataStructureWalker::next_inherit(DataType_PolyImageData))
	{
		ASPolyImageData* crntDataNode = static_cast<ASPolyImageData*>(item);
		QString filename = OperatingDirectoryName + "/" + crntDataNode->getName() + ".stl";
		ms_SelfPointer->m_NodeListToWrite.append(item);
		ms_SelfPointer->m_PathListToWrite.append(filename);
	}
	ASTransAddDeleteData::StartSaveDataToDisk();
}
void ASTransAddDeleteData::StartSaveDataToDisk()
{
	// 1 �������ȶԻ���
	ms_SelfPointer->m_MessageBoxExportDataToDisk = new QMessageBox(QMessageBox::NoIcon, "Anatomy Sketch", "Writing " + QFileInfo(ms_SelfPointer->m_PathListToWrite.first()).baseName(), QMessageBox::Cancel, NULL);
	ms_SelfPointer->m_MessageBoxExportDataToDisk->setModal(true);
	ms_SelfPointer->m_MessageBoxExportDataToDisk->show();
	connect(ms_SelfPointer->m_MessageBoxExportDataToDisk, SIGNAL(buttonClicked(QAbstractButton*)), ms_SelfPointer, SLOT(slotWriteDataStopManualy(QAbstractButton*)));

	// 2 ʵ��һ�����ݱ���ģ��
	m_FModelExportDataToDisk = new ASFModelExportDataToDisk();
	// �������ݣ����̣߳����������ɹ���ᷢsignal����
	m_FModelExportDataToDisk->WriteDataToDisk(ms_SelfPointer->m_PathListToWrite.first(), 
		ms_SelfPointer->m_NodeListToWrite.first());
}
void ASTransAddDeleteData::SaveDataToDiskFinished()
{
	ms_SelfPointer->m_PathListToWrite.removeFirst();
	ms_SelfPointer->m_NodeListToWrite.removeFirst();
	// �ж��Ƿ���Ҫд������
	if (ms_SelfPointer->m_NodeListToWrite.size() == 0)
	{
		// û��Ҫд��������
		disconnect(ms_SelfPointer->m_MessageBoxExportDataToDisk, SIGNAL(buttonClicked(QAbstractButton*)), 
			ms_SelfPointer, SLOT(slotWriteDataStopManualy(QAbstractButton*)));
		delete ms_SelfPointer->m_MessageBoxExportDataToDisk;
		delete m_FModelExportDataToDisk;
		m_FModelExportDataToDisk = nullptr;
	} 
	else
	{
		// ����д����
		ms_SelfPointer->m_MessageBoxExportDataToDisk->setText("Writing " + QFileInfo(ms_SelfPointer->m_PathListToWrite.first()).baseName());
		m_FModelExportDataToDisk->WriteDataToDisk(ms_SelfPointer->m_PathListToWrite.first(), ms_SelfPointer->m_NodeListToWrite.first());
	}
}
void ASTransAddDeleteData::SaveDataStopManualyFinished()
{
	delete m_FModelExportDataToDisk;
	m_FModelExportDataToDisk = nullptr;
}

// �Ƴ�����
void ASTransAddDeleteData::RemoveDataNode(ASAbstractData* RemoveDataNode)
{
	//ѯ���Ƿ�ر��ļ�
	QMessageBox message(QMessageBox::Warning, "Anatomy Sketch", tr("Remove this and its child data?"), QMessageBox::Yes | QMessageBox::No, NULL);
	if (message.exec() == QMessageBox::No)
	{
		return;
	}
	int DataType = RemoveDataNode->getDataType();
	qDebug(qPrintable("start removing Data: " + RemoveDataNode->getName()));
	ms_SelfPointer->RemoveDataNodeAndChildren(RemoveDataNode);
	ms_bResetCarmera = (ASPipelineBase::GetNumOfObj2D() == 0);
	ASTransAddDeleteData::UpdateDispleyAfterAddDelete(ms_bResetCarmera);
	ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_AbstractData);
}
void ASTransAddDeleteData::RemoveAllDataNode()
{
	//ѯ���Ƿ�ر��ļ�
	QMessageBox::StandardButton rb = QMessageBox::question(NULL, "Anatomy Sketch", tr("Close all data?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	if (rb == QMessageBox::No)
	{
		return;
	}
	// �Ƴ�����
	ms_SelfPointer->RemoveDataNodeAndChildren(ASDataTree::getRootDataNote());
	// ˢ����ʾ
	ASTransAddDeleteData::UpdateDispleyAfterAddDelete();
	ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_AbstractData);
}
// �����������ƶ�����
// ���뱻�ƶ������ݣ������Ի���ѡ����λ��
void ASTransAddDeleteData::MoveDataNode(ASAbstractData* DataNode)
{
	int crntID = DataNode->getDataNodeID();
	// 0 �����Ի���ѡ���µĸ��׽ڵ�
	bool ok;
	QStringList items;
	QList<int> ListID;
	for (ASAbstractData* item = ASDataStructureWalker::bigen_inherit(DataType_AbstractData); 
		item != nullptr; 
		item = ASDataStructureWalker::next_inherit(DataType_AbstractData))
	{
		bool a = true;
		if (item->getDataNodeID() != crntID && DataNode->getFather() != item)
		{
			ASAbstractData* f = item->getFather();
			while (f != nullptr)
			{
				if (f->getDataNodeID() == crntID)
				{
					a = false;
					break;
				}
				f = f->getFather();
			}
		}
		else
		{
			a = false;
		}
		if (a)
		{
			items << item->getName();
			ListID << item->getDataNodeID();
		}
	}
	
	QString item = QInputDialog::getItem(ASMainWidget::GetMainWidget(), "Input Item Dialog",
		"please choose a item:", items, 0, true, &ok);
	if (ok)
	{
		int index = items.indexOf(item);
		// 0 �����������ƶ��ڵ�
		ASAbstractData* FatherDataNode = ASAbstractData::getDataNodeFromID(ListID.at(index));
		ASAbstractData* startIDDataNode = DataNode;
		startIDDataNode->getFather()->removeChild(startIDDataNode);
		int numOfChild = FatherDataNode->getChild()->size();
		FatherDataNode->addChild(startIDDataNode, numOfChild);
		startIDDataNode->setFather(FatherDataNode);
		// 1 ���¼������ݵĲ㼶
		ASDataTree::RefreshArrayDataLayer();
		// 2 ˢ�¹��߲㼶
		for (ASAbstractData* item = ASDataStructureWalker::bigen_inherit(DataType_ArrayImageData); item != nullptr; item = ASDataStructureWalker::next_inherit(DataType_ArrayImageData))
		{
			ASArrayImageData* CrntDataNode = (ASArrayImageData*)item;
			QList<ASPipelineBase*>* listPipeline = new QList<ASPipelineBase*>;
			ASPipelineManager::GetPipelineForDataID(listPipeline, CrntDataNode->getDataNodeID());
			for (int ncrntPipe = 0; ncrntPipe < listPipeline->size(); ncrntPipe++)
			{
				if (listPipeline->at(ncrntPipe)->GetPipeLineType() == PipeLineType_ArrayImage)
				{
					((ASPipelineArrayImage*)listPipeline->at(ncrntPipe))->SetLayer(CrntDataNode->getLayer());
				}
			}
		}
		// 3 ���¼��㶥�������ݺ����سߴ�
		ASVisualizationManager::ResetTopArrayImage();
		// 4 ��Ⱦ
		ASVisualizationManager::Render();
		// 5 �����������
		ASTransDataGeneral::ResetGeneratingData();
		// 6 ˢ�²�����ļ��б���ʾ���������ͱ仯����Ҫˢ��
		emit ms_SelfPointer->signalUpdateDataNodeLists(DataType_AbstractData);
	}
}
// 1 startID ���ƶ��ڵ��ID 
// 2 FaterID �ƶ���λ�õĸ��ڵ��ID��-1Ϊ���ڵ�
// 3 endPos  �ƶ���λ��Ϊ���ڵ�ĵڼ������ӣ������Ϊԭ�ڵ�ɾ��֮ǰ�����
void ASTransAddDeleteData::MoveDataNode(const int startID, const int FaterID, const int endPos)
{
	// 0 �����������ƶ��ڵ�
	int orderToInsert = endPos;
	ASAbstractData* FatherDataNode = ASAbstractData::getDataNodeFromID(FaterID);
	ASAbstractData* startIDDataNode = ASAbstractData::getDataNodeFromID(startID);
	if (startIDDataNode->getFather() == FatherDataNode)
	{
		// ����ͬ���ڵ����ƶ�
		if (startIDDataNode->getFather()->getOrderInBrother(startIDDataNode) < endPos)
		{
			// �����ƶ�
			orderToInsert -= 1;
		}
	}
	startIDDataNode->getFather()->removeChild(startIDDataNode);
	FatherDataNode->addChild(startIDDataNode, orderToInsert);
	startIDDataNode->setFather(FatherDataNode);
	// 1 ���¼������ݵĲ㼶
	ASDataTree::RefreshArrayDataLayer();
	// 2 ˢ�¹��߲㼶
	for (ASAbstractData* item = ASDataStructureWalker::bigen_inherit(DataType_ArrayImageData); item != nullptr; item = ASDataStructureWalker::next_inherit(DataType_ArrayImageData))
	{
		ASArrayImageData* CrntDataNode = (ASArrayImageData*)item;
		QList<ASPipelineBase*>* listPipeline = new QList<ASPipelineBase*>;
		ASPipelineManager::GetPipelineForDataID(listPipeline, CrntDataNode->getDataNodeID());
		for (int ncrntPipe = 0; ncrntPipe < listPipeline->size(); ncrntPipe++)
		{
			if (listPipeline->at(ncrntPipe)->GetPipeLineType() == PipeLineType_ArrayImage)
			{
				((ASPipelineArrayImage*)listPipeline->at(ncrntPipe))->SetLayer(CrntDataNode->getLayer());
			}
		}
	}
	// 3 ���¼��㶥�������ݺ����سߴ�
	ASVisualizationManager::ResetTopArrayImage();
	// 4 ��Ⱦ
	ASVisualizationManager::Render();
}
// �����¹���
void ASTransAddDeleteData::AddNewPipeline(ASAbstractData* NewDataNode, int Type)
{
	switch (Type)
	{
	case DataType_ArrayImageData:
	case DataType_DICOMData:
	{
		ASArrayImageData* crntDataNode = (ASArrayImageData*)NewDataNode;
		ASPipelineArrayImage* newPipeLine = (ASPipelineArrayImage*)ASPipelineManager::AddPipeline(PipeLineType_ArrayImage);
		newPipeLine->SetInputData(crntDataNode->getArrayImageData());
		newPipeLine->SetDataID(NewDataNode->getDataNodeID());
		newPipeLine->ArrayPipeInit(crntDataNode);
		break;
	}
	case DataType_PolyImageData:
	{
		ASPolyImageData* crntDataNode = (ASPolyImageData*)NewDataNode;
		ASPipelinePolyImage* newPipeLine = (ASPipelinePolyImage*)ASPipelineManager::AddPipeline(PipeLineType_PolyImage);
		newPipeLine->SetInputData(crntDataNode->getPolyImageData());
		newPipeLine->SetDataID(NewDataNode->getDataNodeID());
		newPipeLine->SetShown(true);
		newPipeLine->SetColor(crntDataNode->getColor());
		newPipeLine->SetOpacity(1);
		newPipeLine->SetContourLineWidth();
		newPipeLine->SetContourLinePickable(ASVisualizationManager2D::GetContoursPickable());
		break;
	}
	default:
		break;
	}
}
// �ļ����������ˢ����ʾ
void ASTransAddDeleteData::UpdateDispleyAfterAddDelete(const bool c_bResetCamera)
{
	// �������ݷ�Χ	
	ASVisualizationManager::ResetDisplayExtent();
	// ���ݵ�ǰ�����ߵ��������ĸ�����ʾԪ��
	ASVisualizationManager::UpdateAuxiliaryPipeline(); // ��ResetDisplayExtent()֮��ˢ�����ӵ���Ҫ�õ���
	// ���¼��㶥�������ݺ����سߴ�
	ASVisualizationManager::ResetTopArrayImage();
	if (c_bResetCamera)
	{
		// ���ý���
		double Extent[6];
		ASVisualizationManager::GetDisplayExtent(Extent);
		ASTransGeneralInteractor::fSetVisualizationPosition((Extent[0] + Extent[1]) / 2, (Extent[2] + Extent[3]) / 2, (Extent[4] + Extent[5]) / 2);
		// �������
		ASVisualizationManager::ResetCamera();
	}
	// ��Ⱦ
	ASVisualizationManager::Render();
}
// �ļ��������
void ASTransAddDeleteData::UpdateListsAfterAddDelete(const int c_AffectType)
{
	// ˢ�²�����ļ��б���ʾ���������ͱ仯����Ҫˢ��
	emit ms_SelfPointer->signalUpdateDataNodeLists(c_AffectType);
	// ˢ�²�����ļ�����ѡ��
	ASTransSidebarGeneral::RefreshDataComboBox(c_AffectType); 
	// ��������ӵ�����ˢ�����ӵ��б�
	if (ASSeedData::isTypeInheritedStatic(c_AffectType))
	{
		ASTransSeeds::RefreshSeedsList();
		ASTransSeeds::AdjustUndoList();
	}
	// ���������������ˢ�����ӵ��б�	
	if (ASContourData::isTypeInheritedStatic(c_AffectType))
	{
		ASTransContour::RefreshContourList();
	}
	// �����ROI
	if (ASROIData::isTypeInheritedStatic(c_AffectType))
	{
		ASTransROI::RefreshROIList();
	}
}
// �ݹ麯�����Ƴ�������
void ASTransAddDeleteData::RemoveDataNodeAndChildren(ASAbstractData* DataNode)
{	
	// 0 �ͷ��ӽڵ�
	QList<ASAbstractData*>* listChildren = DataNode->getChild();
	for (int ncrntChild = listChildren->size() - 1; ncrntChild >= 0; ncrntChild--)
	{
		RemoveDataNodeAndChildren(listChildren->at(ncrntChild));
	}
	// 1 ��¼����ID���������ͣ����ͷ�����
	if (DataNode == ASDataTree::getRootDataNote())
	{
		return;
	}
	if (DataNode->getDataType() == DataType_Operation)
	{
		ASTransAddins::DataRemoved(DataNode);
	}
	int nID = DataNode->getDataNodeID();
	// 3 ��ǰ����
	if (DataNode == ASTransDataGeneral::GetGeneratingData())
	{
		ASTransDataGeneral::SetGeneratingData(nullptr);
	}
	emit ms_SelfPointer->signalRemoveNode(DataNode);
	// 2 ��ɾ����ʾ
	QList<ASPipelineBase*>* crntListPipeline = new QList<ASPipelineBase*>;
	ASPipelineManager::GetPipelineForDataID(crntListPipeline, nID);
	for (int crntPipe = 0; crntPipe < crntListPipeline->size(); crntPipe++)
	{
		if (crntListPipeline->at(crntPipe)->isTypeInherited(PipeLineType_ArrayImage)
			|| crntListPipeline->at(crntPipe)->isTypeInherited(PipeLineType_PolyImage))
		{
			ASPipelineManager::RemovePipeline(crntListPipeline->at(crntPipe));
		}		
	}
}
void ASTransAddDeleteData::slotLoadDataStopManualy(QAbstractButton* button)
{
	m_FModelImportDataFromDisk->CancelLoadData();
}
// ��Ӳ��д���ݹ����б�ȡ��
void ASTransAddDeleteData::slotWriteDataStopManualy(QAbstractButton* button)
{
	m_FModelExportDataToDisk->CancelWriteData();
	disconnect(ms_SelfPointer->m_MessageBoxExportDataToDisk, SIGNAL(buttonClicked(QAbstractButton*)), ms_SelfPointer, SLOT(slotWriteDataStopManualy(QAbstractButton*)));
	delete ms_SelfPointer->m_MessageBoxExportDataToDisk;
}
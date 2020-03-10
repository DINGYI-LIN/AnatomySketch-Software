#include "ASDataManager.h"
#include "ASDataTree.h"
#include "ASDataStructureWalker.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QStringList>
#include <QInputDialog>
#include <QFileDialog>

#include "ASAbstractData.h"
#include "ASArrayImageData.h"
#include "ASSeedData.h"
#include "ASDICOMData.h"
//#include "ASDICOMRTLoader.h"
//#include "ASPolyDeformation.h"
//#include "ASMask.h"


ASDataManager::ASDataManager(QObject *parent)
	: QObject(parent)
{
	// ���ݴ洢�������ݽṹ
	m_DataTree = new ASDataTree(this);
	//// �����ݱ༭ģ��
	//m_PolyDeformation = new ASPolyDeformation();
	//// ����ģ��
	//m_pMask = new ASMask();
}

ASDataManager::~ASDataManager()
{

}

////�ɸ�����������������ָ��
//void ASDataManager::setSignalLinker(ASSignalLinker* linker)
//{
//	m_SignalLinker = linker;
//
//	//��������ص��źŲ�
//	connect(this, SIGNAL(signalSetDatamanagerAddress(void*)), m_SignalLinker, SIGNAL(signalSetDatamanagerAddress(void*)));
//	connect(this, SIGNAL(signalRefreshDataManagerWidget()), m_SignalLinker, SIGNAL(signalRefreshDataManagerWidget()));
//	connect(this, SIGNAL(signalAddImageDataDisplay(int)), m_SignalLinker, SIGNAL(signalAddImageDataDisplay(int)));						//������������ʾ
//	connect(this, SIGNAL(signalAddPolyDataDisplay(int)), m_SignalLinker, SIGNAL(signalAddPolyDataDisplay(int)));						//������������ʾ
//	connect(this, SIGNAL(signalAddDICOMRTDisplay()), m_SignalLinker, SIGNAL(signalAddDICOMRTDisplay()));								//����DICOM-RT�ļ���ʾ������ͬʱ���˶��RT�ļ�������ֱ�ӽ���RT������ʾ��ˢ�¡�
//	connect(this, SIGNAL(signalAddSeeds2DDisplay(int)), m_SignalLinker, SIGNAL(signalAddSeeds2DDisplay(int)));							//�������ӵ���ʾ�����½���Ӧ��ǩ�ļ������ӵ���Ⱦ����
//	
//	connect(this, SIGNAL(signalRemoveDataDisplay(int, enumDataType)), m_SignalLinker, SIGNAL(signalRemoveDataDisplay(int, enumDataType)));// �Ƴ�������ʾ
//
//	connect(this, SIGNAL(signalUpdataLayerDisplay()), m_SignalLinker, SIGNAL(signalUpdataLayerDisplay()));								//�����ݲ���º�ˢ�²㼶����ʾ
//	connect(this, SIGNAL(signalRefreshFileComboBox()), m_SignalLinker, SIGNAL(signalRefreshFileComboBox()));							//ˢ�������ļ�����ѡ��
//	connect(this, SIGNAL(signalPolyDeformationRefresh()), m_SignalLinker, SIGNAL(signalPolyDeformationRefresh()));						//FFD���������У�generate֮ǰ��ˢ����ʾ
//}

////������ʼ���������ʼ�������׶�
//void ASDataManager::Parameterinitialization()
//{
//	emit signalSetDatamanagerAddress(this);
//}

//// ������
//void ASDataManager::LoadData(QString filename)
//{
//	// ��ȡ�ļ���׺�������ж��ļ�����
//	QFileInfo pFileInfo = QFileInfo(filename);
//	QString qstrSuffix = pFileInfo.suffix();
//
//	//�ж��ļ�����
//	if (strcmp(qstrSuffix.toStdString().c_str(), "mhd") == 0 || strcmp(qstrSuffix.toStdString().c_str(), "nii") == 0)
//	{
//		// ������
//		int newID = m_DataTree->LoadData(filename, EMArrayImageData);
//		if (newID >= 0)
//		{
//			//��ȡ�ɹ������½������ʾ
//			emit signalAddImageDataDisplay(newID);
//		}
//	}
//	else if (strcmp(qstrSuffix.toStdString().c_str(), "stl") == 0 || strcmp(qstrSuffix.toStdString().c_str(), "ply") == 0 || strcmp(qstrSuffix.toStdString().c_str(), "obj") == 0)
//	{
//		// ������
//		int newID = m_DataTree->LoadData(filename, EMPolyImageData);
//		if (newID >= 0)
//		{
//			//��ȡ�ɹ������½������ʾ
//			emit signalAddPolyDataDisplay(newID);
//		}
//	}
//	else if (strcmp(qstrSuffix.toStdString().c_str(), "dcm") == 0)
//	{
//		//DICOM-RT����
//		QString fileName = QFileInfo(filename).fileName();
//		if (fileName.at(0) != 'R' || fileName.at(1) != 'S' || fileName.at(2) != '.')	//	����ļ�����ǰ׺�Ƿ�Ϊ"RS."
//		{
//			//��ǰ׺������"RS."
//			int ret = QMessageBox::question(0, tr("message"), tr("The file name does not meet the DICOM-RT requirements. Whether to continue?"), QMessageBox::Yes, QMessageBox::Cancel);
//			if (ret == QMessageBox::Cancel)
//			{
//				return;
//			}
//		}
//		//����һ����������ȷ��RT��ԭ��ߴ�������Ϣ
//		QStringList lst;
//		QList<int> IDofLst;
//		for (ASAbstractData* item = ASDataStructureWalker::bigen_inherit(EMArrayImageData); item != nullptr; item = ASDataStructureWalker::next_inherit(EMArrayImageData))
//		{
//			lst << item->getName();
//			IDofLst << item->getDataNodeID();
//		}
//		//����ѯ�ʶԻ���
//		bool ok = false;
//		QString rtnstring = QInputDialog::getItem(0, tr("message"), tr("Choose an array image data to set coordinate information: "), lst, 0, true, &ok);
//		if (ok)
//		{
//			vtkImageData* crntImageData = ((ASArrayImageData*)ASAbstractData::getDataNodeFromID(IDofLst.at(lst.indexOf(rtnstring))))->getArrayImageData();
//			ASDICOMRTLoader Loader;
//			Loader.setDataTree(m_DataTree);
//			Loader.setFatherID(IDofLst.at(lst.indexOf(rtnstring)));
//			Loader.setFileName(filename);
//			if (Loader.update())
//			{
//				emit signalAddDICOMRTDisplay();
//			}
//		}
//	}
//
//	emit signalRefreshDataManagerWidget();
//	emit signalRefreshFileComboBox();		//ˢ���ļ�����ѡ��
//}
//// ��ȡDICOM����
//void ASDataManager::LoadDICOMSeries(vtkDICOMDirectory* dir, QList<int>* serieslist)
//{
//	int numOfSeries = serieslist->size();
//	for (int it = 0; it < numOfSeries; it++)
//	{
//		int crntSeries = serieslist->at(it);
//
//		ASDICOMData* crntDataNode = (ASDICOMData*)m_DataTree->NewDataNode(EMDICOMData, nullptr);
//		crntDataNode->LoadDICOMDeries(dir, crntSeries);
//		emit signalAddImageDataDisplay(crntDataNode->getDataNodeID());
//	}
//	emit signalRefreshDataManagerWidget();
//	emit signalRefreshFileComboBox();		//ˢ���ļ�����ѡ��
//}
//// ��������
//void ASDataManager::saveData(ASAbstractData* data)
//{
//	// ��ʱֻ֧��polydata
//	QFileDialog FileDialog;
//
//	QString setFilter = "OBJ(*.obj);;STL(*.stl);;PLY(*.ply)";
//	QString selectFilter, dirString;
//	QString crntFileName = data->getFileName();
//	if (crntFileName.isEmpty() == false)
//	{
//		dirString = QFileInfo(crntFileName).filePath();
//		if (QFileInfo(crntFileName).suffix() == "stl")
//		{
//			selectFilter = "STL(*." + QFileInfo(crntFileName).suffix() + ")";
//		}
//		else if (QFileInfo(crntFileName).suffix() == "obj")
//		{
//			selectFilter = "OBJ(*." + QFileInfo(crntFileName).suffix() + ")";
//		}
//		else if (QFileInfo(crntFileName).suffix() == "ply")
//		{
//			selectFilter = "PLY(*." + QFileInfo(crntFileName).suffix() + ")";
//		}
//	}
//	else
//	{
//		dirString = "./" + data->getName() + ".stl";
//		selectFilter = "PLY(*." + QFileInfo(crntFileName).suffix() + ")";
//	}
//	QString saveFileName = FileDialog.getSaveFileName(0, "save", dirString, setFilter, &selectFilter,
//		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
//	if (data->getFileName() != saveFileName)
//	{
//		data->setFileName(saveFileName);
//	}
//	if (data->getName() != QFileInfo(saveFileName).baseName())
//	{
//		data->setName(QFileInfo(saveFileName).baseName());
//		emit signalRefreshDataManagerWidget();
//		emit signalRefreshFileComboBox();		//ˢ���ļ�����ѡ��
//	}
//	data->SaveData(saveFileName);
//}
//// �Ƴ�����
//void ASDataManager::removeData(ASAbstractData* data)
//{
//	if (data->isBeingProcess())
//	{
//		return;
//	}
//	if (data->isChildrenBeingProcess())
//	{
//		return;
//	}
//	//ѯ���Ƿ�ر��ļ�
//	QMessageBox message(QMessageBox::Warning, "Information", "Really to remove data?", QMessageBox::Yes | QMessageBox::No, NULL);
//	if (message.exec() == QMessageBox::No)
//	{
//		return;
//	}
//
//	// �ȼ�¼����ID���������ͣ����ͷ�����
//	int id = data->getDataNodeID();
//	enumDataType type = data->getDataType();
//	ASDataTree::RemoveNode(data);
//	// ��ɾ����ʾ
//	signalRemoveDataDisplay(id, type);
//
//	// ˢ�½���
//	emit signalRefreshDataManagerWidget();
//	emit signalRefreshFileComboBox();		//ˢ���ļ�����ѡ��
//}
//// �½���ǩ�ļ�������Ϊ���֣���ǩֵ����ɫ
//void ASDataManager::NewLabelData(QString str, int label, int* nColor)
//{
//	ASSeedData* crntDataNode = (ASSeedData*)m_DataTree->NewDataNode(EMSeedData, nullptr);
//	crntDataNode->setBeingProcess(false);
//	crntDataNode->setName(str);
//	crntDataNode->setLabel(label);
//	crntDataNode->setColor(nColor[0], nColor[1], nColor[2]);
//	
//	emit signalAddSeeds2DDisplay(crntDataNode->getDataNodeID());
//	emit signalRefreshDataManagerWidget();
//	emit signalRefreshFileComboBox();		//ˢ���ļ�����ѡ��
//}
//// �½�������
//ASArrayImageData* ASDataManager::NewArrayImageData(const int c_TemplateID, QString qname)
//{
//	ASArrayImageData* pTemplateData = (ASArrayImageData*)ASAbstractData::getDataNodeFromID(c_TemplateID);
//	ASArrayImageData* pNewData = (ASArrayImageData*)m_DataTree->NewDataNode(EMArrayImageData, pTemplateData);
//	pNewData->copyArrayImageDataFrom(c_TemplateID);
//	pNewData->setName(qname);
//	return pNewData;
//}

//----------------- Mask -----------------------
//
////�õ��������������ָ�룬ֻ��
//unsigned char* ASDataManager::GetMaskArrayAddr()
//{
//	return m_pMask->GetMaskArrayAddr();
//}
////�õ�������ʾ��vtkImageData
//vtkImageData* ASDataManager::GetMaskImageData()
//{
//	return m_pMask->GetMaskImageData();
//}
////�趨����ͼ������ݣ���������������Ժ��������飬��Ҫ�������ͼ���ID
//void ASDataManager::setMaskImageData(int ID)
//{
//	m_pMask->setMaskImageData(ID);
//}

//----------------- PolyDeformation -----------------------
//void ASDataManager::startPolyDeformation(double posx, double posy, double posz, enumPolyDeformaiton type, double ViewRange)
//{
//	m_PolyDeformation->startPolyDeformation(posx, posy, posz, type, ViewRange);
//}
//// ����PolyDeformation����
//void ASDataManager::PolyDeformationContinue(double posx, double posy, double posz, int viewlabel, enumPolyDeformaiton TransType)
//{
//	if (m_PolyDeformation->continuePolyDeformation(posx, posy, posz, viewlabel, TransType) == 0)
//	{
//		//ˢ����ʾ
//		emit signalPolyDeformationRefresh();
//	}
//}
////�����������ת
//void ASDataManager::RotationChanging(double angle, int viewlabel)
//{
//	if (m_PolyDeformation->RotationDeformation(angle, viewlabel) == 0)
//	{
//		//ˢ����ʾ
//		emit signalPolyDeformationRefresh();
//	}
//}
////Zoom
//void ASDataManager::ZoomChanging(double multiple_x, double multiple_y, double multiple_z)
//{
//	m_PolyDeformation->setZoomMultiple(multiple_x, multiple_y, multiple_z);
//	if (m_PolyDeformation->ZoomDeformation() == 0)
//	{
//		//ˢ����ʾ
//		emit signalPolyDeformationRefresh();
//	}
//}
//void ASDataManager::ZoomChanging(double multiple)
//{
//	double* crntMultiple = m_PolyDeformation->getZoomMultiple();
//	for (int i = 0; i < 3; i++)
//	{
//		crntMultiple[i] *= multiple;
//	}
//	m_PolyDeformation->setZoomMultiple(crntMultiple[0], crntMultiple[1], crntMultiple[2]);
//	if (m_PolyDeformation->ZoomDeformation() == 0)
//	{
//		//ˢ����ʾ
//		emit signalPolyDeformationRefresh();
//	}
//}
//
////����
//void ASDataManager::PolyDeformationUndo()
//{
//	if (m_PolyDeformation->UndoDeformation() == 0)
//	{
//		emit signalPolyDeformationRefresh();
//	}
//}
////�õ���ǰPolyDeformation����������
//enumPolyDeformaiton ASDataManager::getCurrentPolyDeformationType()
//{
//	return m_PolyDeformation->getCurrentPolyDeformaitonType();
//}
////���ֵ���Ӱ�췶Χ
//void ASDataManager::FFDWheel(int ForwardOrBackward)
//{
//	// �ı�Ӱ��뾶
//	if (m_PolyDeformation->FFDRadiusChange(ForwardOrBackward) == 0)
//	{
//		// ˢ����ʾ
//		emit signalPolyDeformationRefresh();
//	}
//}


#include "ASTransROI.h"
#include "ASTransDataGeneral.h"
#include "ASTransAddDeleteData.h"
#include "ASROIData.h"
#include "ASMainWidget.h"
#include "ASDataTree.h"
#include "ASDataStructureWalker.h"
#include "ASROITypeBase.h"
#include "ASROITypeCube.h"
#include "ASFModelROI.h"
#include "ASDialogNewElement.h"
#include "ASAbstractData.h"
#include "ASArrayImageData.h"
#include "ASTransCompleter.h"
#include "ASInteractorStyleManager.h"
#include "ASTransInteractorStyle.h"
#include "ASTransSidebarGeneral.h"
#include "ASVisualizationManager.h"

ASTransROI* ASTransROI::ms_SelfPointer = nullptr;

ASTransROI::ASTransROI(QObject *parent)
	: ASTransmissionBase(parent)
{
	ms_SelfPointer = this;
	m_FModelROI = new ASFModelROI();
}

ASTransROI::~ASTransROI()
{

}
// Ψһ����
ASTransROI* ASTransROI::GetSelfPointer()
{
	return ms_SelfPointer;
}
//��ǰROIID
void ASTransROI::SetCrntROIID(const int c_id)
{
	ms_SelfPointer->m_CurrentROIID = c_id;
}
int ASTransROI::GetCrntROIID()
{
	return ms_SelfPointer->m_CurrentROIID;
}
// �õ���ǰROI�ļ�
ASROIData* ASTransROI::GetCurrentROIData()
{
	ASAbstractData* CrntDataNode = ASTransSidebarGeneral::GetCrntDataNode();
	if (CrntDataNode && CrntDataNode->isTypeInherited(DataType_ROI))
	{
		return static_cast<ASROIData*>(CrntDataNode);
	}
	return nullptr;
}
// ˢ������������б�
void ASTransROI::UpdateListsOfROIData()
{
	ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_ROI);
}
// �½�ROI����
void ASTransROI::NewROIData(ASAbstractData* pParent)
{	
	// 1 ����궨������
	ASDialogNewElement* dia = new ASDialogNewElement(ASMainWidget::GetMainWidget(), enROI);
	dia->exec();
	if (dia->m_result.size() == 0)
	{
		return;
	}
	QList<structCompleterItem*>* pList = ASTransCompleter::GetStructureList();
	QString NewName = dia->m_result;
	//bool bbb = false;
	//for (int index = 0; index < pList->size(); index++)
	//{
	//	if (pList->at(index)->name == NewName)
	//	{
	//		bbb = true;
	//		break;
	//	}
	//}
	//if (bbb == false)
	//{
	//	return;
	//}

	if (NewName.size() == 0)
	{
		return;
	}
	QColor c(Qt::red);
	for (int index = 0; index < pList->size(); index++)
	{
		if (pList->at(index)->name == NewName)
		{
			c = pList->at(index)->color;
			break;
		}
	}

	ASArrayImageData* GenData = static_cast<ASArrayImageData*>(
		ASTransDataGeneral::GetGeneratingData());
	// 1 �ж��Ƿ���Ҫ�½�ROI�ļ�
	ASROIData* ROIData;
	if (pParent->isTypeInherited(DataType_ROI))
	{
		ROIData = static_cast<ASROIData*>(pParent);
	}
	else
	{
		ROIData = static_cast<ASROIData*>(pParent->getChild(DataType_ROI));
	}
	if (!ROIData)
	{
		ROIData = new ASROIData();
		ROIData->setName("Bounding box data");
		ROIData->setShown(true);
		ASDataTree::NewDataNode(ROIData, pParent);
		ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_ROI);
		if (!ROIData)
		{
			qDebug("Error: Null pointer of current ROIData. From ASROIWidget(2).");
			return;
		}
	}

	// 2 �½�CubeROI
	ASROITypeBase* roi = ASTransROI::NewROI(ROIData->getDataNodeID(), NewName, ROIType_Cube);
	if (roi->GetROIType() != ROIType_Cube)
	{
		qDebug("Error: Wrong ROI type.");
		return;
	}
	ASROITypeCube* cube = static_cast<ASROITypeCube*>(roi);
	cube->SetRange(GenData->getImageExtent());

	QStringList StrList;
	cube->SetColor(c);
	// ����ROI�ĳ�ʼ��ΧΪȫͼ
	ASTransSidebarGeneral::SetCrntDataNode(ROIData);
	ASTransROI::SetCrntROIID(cube->GetROIID());
	ASTransROI::RefreshROICubeDisplay();
	ASTransROI::UpdateListsOfROIData();
	// ʹ��
	if (ASInteractorStyleManager::GetInteractorStyle2D() != InterStyle2D_ROICube)
	{
		ASTransInteractorStyle::SetInteratorStyle2D(InterStyle2D_ROICube);
	}

}
void ASTransROI::ASTransROI::NewROIData(ASAbstractData* pParent, QString name, int label, QColor color)
{
	ASArrayImageData* GenData = static_cast<ASArrayImageData*>(
		ASTransDataGeneral::GetGeneratingData());
	// 1 �ж��Ƿ���Ҫ�½�ROI�ļ�
	ASROIData* ROIData = static_cast<ASROIData*>(pParent->getChild(DataType_ROI));
	if (!ROIData)
	{
		ROIData = new ASROIData();
		ROIData->setName(tr("ROI data"));
		ROIData->setShown(true);
		ASDataTree::NewDataNode(ROIData, pParent);
		ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_ROI);
		if (!ROIData)
		{
			qDebug("Error: Null pointer of current ROIData. From ASROIWidget(2).");
			return;
		}
	}

	// 2 �½�CubeROI
	ASROITypeBase* roi = ASTransROI::NewROI(ROIData->getDataNodeID(), name, ROIType_Cube);
	if (roi->GetROIType() != ROIType_Cube)
	{
		qDebug("Error: Wrong ROI type.");
		return;
	}
	ASROITypeCube* cube = static_cast<ASROITypeCube*>(roi);
	cube->SetRange(GenData->getImageExtent());

	QStringList StrList;
	cube->SetColor(color);
	// ����ROI�ĳ�ʼ��ΧΪȫͼ
	ASTransSidebarGeneral::SetCrntDataNode(ROIData);
	ASTransROI::SetCrntROIID(cube->GetROIID());
	ASTransROI::RefreshROICubeDisplay();
	ASTransROI::UpdateListsOfROIData();
	// ʹ��
	if (ASInteractorStyleManager::GetInteractorStyle2D() != InterStyle2D_ROICube)
	{
		ASTransInteractorStyle::SetInteratorStyle2D(InterStyle2D_ROICube);
	}
}
// ��ȡROI����
void ASTransROI::LoadROIDataFromDisk(const QStringList c_FileNameList)
{
	ms_SelfPointer->m_FModelROI->InitROICubePipeline();
	for (int nit = 0; nit < c_FileNameList.size(); nit++)
	{
		ms_SelfPointer->m_FModelROI->LoadROIData(c_FileNameList.at(nit));
	}
}
// �½�Cube Roi
ASROITypeBase* ASTransROI::NewROI(const int c_ROIId, const QString c_Name, const int c_Type)
{
	ASROIData* crntData = static_cast<ASROIData*>(ASAbstractData::getDataNodeFromID(c_ROIId));
	return crntData->NewROI(c_Name, c_Type);
}
// �Ƴ�ROI
void ASTransROI::RemoveROI(const int c_ROIDataId, const int c_ROIId)
{
	ASROIData* crntData = static_cast<ASROIData*>(ASAbstractData::getDataNodeFromID(c_ROIDataId));
	crntData->RemoveROI(c_ROIId);
	// ˢ����ʾ
	ASTransROI::RefreshROICubeDisplay();
	// ˢ�������б�
	ASTransROI::UpdateListsOfROIData();
}
// ˢ��ROI�б�
void ASTransROI::RefreshROIList()
{
	emit ms_SelfPointer->signalRefreshList();
}
// ��������Cube��Χ
void ASTransROI::SetROICubeRange(const int c_Index, const double c_Value)
{
	ASROIData* CrntROIData = ASTransROI::GetCurrentROIData();
	if (!CrntROIData)
	{
		qDebug("Error: Null pointer of current ROIData. From ASTrsnsROI.");
		return;
	}
	int crntROIId = ASTransROI::GetCrntROIID();
	ASROITypeBase* roi = CrntROIData->GetROIWithID(crntROIId);
	if (!roi)
	{
		qDebug("Error: Null pointer of current ROI. From ASTrsnsROI.");
		return;
	}
	if (roi->GetROIType() != ROIType_Cube)
	{
		qDebug("Error: Wrong ROI type. From ASTrsnsROI.");
		return;
	}
	ASROITypeCube* crntROI = static_cast<ASROITypeCube*>(roi);
	double crntRange[6];
	crntROI->GetRange(crntRange);
	if (c_Index % 2)
	{
		// �������ֵ
		if (c_Value < crntRange[c_Index - 1])
		{
			return;
		}
	}
	else
	{
		// ż����Сֵ
		if (c_Value > crntRange[c_Index + 1])
		{
			return;
		}
	}
	crntROI->SetRange(c_Index, c_Value);
	emit ms_SelfPointer->signalRefreshROICube();
	ms_SelfPointer->m_FModelROI->RefreshROICubeDisplay();
}
// ˢ��ROICube��ʾ
void ASTransROI::RefreshROICubeDisplay()
{
	ms_SelfPointer->m_FModelROI->RefreshROICubeDisplay();
}

//void ASTransROI::fNewROIData(QString name, int label, QColor color)
//{
//	ASArrayImageData* GenData = static_cast<ASArrayImageData*>(
//		ASTransDataGeneral::GetGeneratingData());
//	// 1 �ж��Ƿ���Ҫ�½�ROI�ļ�
//	ASROIData* ROIData = ASTransROI::GetCurrentROIData();
//	if (!ROIData)
//	{
//		ROIData = new ASROIData();
//		ROIData->setName(tr("ROI data"));
//		ROIData->setShown(true);
//		ASDataTree::NewDataNode(ROIData, ASTransDataGeneral::GetGeneratingData());
//		ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_ROI);
//		if (!ROIData)
//		{
//			qDebug("Error: Null pointer of current ROIData. From ASROIWidget(2).");
//			return;
//		}
//	}
//
//	// 2 �½�CubeROI
//	ASROITypeBase* roi = ASTransROI::NewROI(ROIData->getDataNodeID(), name, ROIType_Cube);
//	if (roi->GetROIType() != ROIType_Cube)
//	{
//		qDebug("Error: Wrong ROI type.");
//		return;
//	}
//	ASROITypeCube* cube = static_cast<ASROITypeCube*>(roi);
//	cube->SetRange(GenData->getImageExtent());
//
//	QStringList StrList;
//	cube->SetColor(color);
//	// ����ROI�ĳ�ʼ��ΧΪȫͼ
//	ASTransROI::SetCrntROIID(cube->GetROIID());
//	ASTransROI::RefreshROICubeDisplay();
//	ASTransROI::UpdateListsOfROIData();
//	// ʹ��
//	if (ASInteractorStyleManager::GetInteractorStyle2D() != InterStyle2D_ROICube)
//	{
//		ASTransInteractorStyle::SetInteratorStyle2D(InterStyle2D_ROICube);
//	}
//}
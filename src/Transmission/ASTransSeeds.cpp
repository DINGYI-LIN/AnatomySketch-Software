#include "ASTransSeeds.h"
#include "ASDialogNewSeedsFile.h"
#include "ASMainWidget.h"
#include "ASTransAddDeleteData.h"
#include "ASAbstractData.h"
#include "ASSeedData.h"
#include "ASFModelSeeds.h"
#include "ASInteractorStyleManager.h"
#include "ASTransInteractorStyle.h"
#include "ASVisualizationManager.h"
#include "ASDataTree.h"
#include "ASTransDataGeneral.h"
#include "ASDataStructureWalker.h"
#include "ASArrayImageData.h"
#include "ASDialogNewElement.h"
#include "ASTransCompleter.h"
#include "ASTransSidebarGeneral.h"

ASTransSeeds* ASTransSeeds::ms_SelfPointer = nullptr;

ASTransSeeds::ASTransSeeds(QObject *parent)
	: ASTransmissionBase(parent)
{
	ms_SelfPointer = this;
	m_FModelSeeds = new ASFModelSeeds();
}

ASTransSeeds::~ASTransSeeds()
{

}

// Ψһ����
ASTransSeeds* ASTransSeeds::GetSelfPointer()
{
	return ms_SelfPointer;
}
//��ǰSeedsID
void ASTransSeeds::SetCrntSeedsID(const int c_id)
{
	ms_SelfPointer->m_CurrentSeedID = c_id;
	//if (c_id >= 0)
	//{
	//	ms_SelfPointer->m_FModelSeeds->SetSeedsModleEnabled(true);
	//}
	//else
	//{
	//	ms_SelfPointer->m_FModelSeeds->SetSeedsModleEnabled(false);
	//}
}
int ASTransSeeds::GetCrntSeedsID()
{
	return ms_SelfPointer->m_CurrentSeedID;
}
// �õ���ǰ���ӵ��ļ�
ASSeedData* ASTransSeeds::GetCurrentSeedData()
{
	ASAbstractData* CrntDataNode = ASTransSidebarGeneral::GetCrntDataNode();
	if (CrntDataNode && CrntDataNode->isTypeInherited(DataType_SeedData))
	{
		return static_cast<ASSeedData*>(CrntDataNode);
	}
	return nullptr;
}
// �½����ӵ��ļ�
void ASTransSeeds::NewSeedsData(ASAbstractData* pParent)
{
	// 1 ����궨������
	ASDialogNewElement* dia = new ASDialogNewElement(ASMainWidget::GetMainWidget(), enSeed);
	dia->exec();
	if (dia->m_result.size() == 0)
	{
		return;
	}
	QString NewName = dia->m_result;
	if (NewName.size() == 0)
	{
		return;
	}
	QList<structCompleterItem*>* pList = ASTransCompleter::GetStructureList();
	int seedid = -1;
	QColor c(Qt::red);
	for (int index = 0; index < pList->size(); index++)
	{
		if (pList->at(index)->name == NewName)
		{
			seedid = pList->at(index)->id;
			c = pList->at(index)->color;
			break;
		}
	}
	// �ж��Ƿ���Ҫ�½����ӵ��ļ�
	ASSeedData* SeedData;
	if (pParent->isTypeInherited(DataType_SeedData))
	{
		SeedData = static_cast<ASSeedData*>(pParent);
	}
	else
	{
		SeedData = static_cast<ASSeedData*>(pParent->getChild(DataType_SeedData));
	}
	if (!SeedData)
	{
		SeedData = new ASSeedData();
		SeedData->setName(tr("Seed data"));
		SeedData->setShown(true);
		ASDataTree::NewDataNode(SeedData, pParent);
		if (!SeedData)
		{
			qDebug("Error: Null pointer of current SeedsData. From ASPaintingSeedsWidget.");
			return;
		}
	}
	int id = SeedData->NewSeed(NewName, seedid, c);
	if (id == -1)
	{
		qDebug("error: Bad new seed id in ASPaintingSeedsWidget.cpp");
		return;
	}
	ASTransSidebarGeneral::SetCrntDataNode(SeedData);
	ASTransSeeds::SetCrntSeedsID(id);
	// ˢ��
	ASTransSeeds::UpdateListsOfSeedData();
	// ʹ��
	ASTransSeeds::SetModelEnabled(true);
}
void ASTransSeeds::NewSeedsData(ASAbstractData* pParent, QString name, int label, QColor color)
{
	// �ж��Ƿ���Ҫ�½����ӵ��ļ�
	ASSeedData* SeedData = static_cast<ASSeedData*>(pParent->getChild(DataType_SeedData));
	if (!SeedData)
	{
		SeedData = new ASSeedData();
		SeedData->setName(tr("Seed data"));
		SeedData->setShown(true);
		ASDataTree::NewDataNode(SeedData, pParent);
		if (!SeedData)
		{
			qDebug("Error: Null pointer of current SeedsData. From ASPaintingSeedsWidget.");
			return;
		}
	}
	int id = SeedData->NewSeed(name, label, color);
	if (id == -1)
	{
		qDebug("error: Bad new seed id in ASPaintingSeedsWidget.cpp");
		return;
	}
	ASTransSidebarGeneral::SetCrntDataNode(SeedData);
	ASTransSeeds::SetCrntSeedsID(id);
	// ˢ��
	ASTransSeeds::UpdateListsOfSeedData();
	// ʹ��
	ASTransSeeds::SetModelEnabled(true);
}
// ˢ�����ӵ�����б�
void ASTransSeeds::UpdateListsOfSeedData()
{
	ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_SeedData);
}
// ����ģ���Ƿ�ʹ��
void ASTransSeeds::SetModelEnabled(const bool c_enable)
{
	ms_SelfPointer->m_FModelSeeds->SetSeedsModleEnabled(c_enable);
	emit ms_SelfPointer->signalSetModelEnabled(c_enable);
	if (c_enable)
	{
		if (ASInteractorStyleManager::GetInteractorStyle2D() != InterStyle2D_PaintingSeeds)
		{
			ASTransInteractorStyle::SetInteratorStyle2D(InterStyle2D_PaintingSeeds);
		}
	}
	else
	{
		if (ASInteractorStyleManager::GetInteractorStyle2D() == InterStyle2D_PaintingSeeds)
		{
			ASTransInteractorStyle::SetInteratorStyle2D(InterStyle2D_General);
		}
	}
}
// ˢ�����ӵ��б�
void ASTransSeeds::RefreshSeedsList()
{
	ms_SelfPointer->m_FModelSeeds->SetIDOfPaintingData(-1);
	// ��һ���������ӵ��ļ���Ҫ�������ӵ���ʾ�Ĺ���
	if (ASSeedData::GetNumOfSeedsData() > 0)
	{
		ms_SelfPointer->m_FModelSeeds->InitSeedsPipeline();
	}
}
// ���õ�ǰ���ڻ��Ƶ����ӵ����ݵ�ID
//void ASTransSeeds::SetPaintingSeedsID(const int c_ID)
//{
//	ms_SelfPointer->m_FModelSeeds->SetIDOfPaintingData(c_ID);
//}
// �������ӵ�
void ASTransSeeds::StartPaintSeeds(double* pPosition, const int c_ViewLabel)
{
	double Extent[6];
	ASVisualizationManager::GetDisplayExtent(Extent);
	if (pPosition[0] < Extent[0] || pPosition[0] > Extent[1])
	{
		return;
	}
	if (pPosition[1] < Extent[2] || pPosition[1] > Extent[3])
	{
		return;
	}
	if (pPosition[2] < Extent[4] || pPosition[2] > Extent[5])
	{
		return;
	}
	// ��������
	ms_SelfPointer->m_WorkingSeedData = ASTransSeeds::GetCurrentSeedData();
	ms_SelfPointer->m_WorkingSeedData->AddOperaSequence(ms_SelfPointer->m_CurrentSeedID);

	ms_SelfPointer->m_WorkingSeedData->StartPaintingSeeds(pPosition, c_ViewLabel, ms_SelfPointer->m_CurrentSeedID);
	// ˢ����ʾ
	ms_SelfPointer->m_FModelSeeds->StartPaintingData(pPosition);
	// ��Ⱦ
	ASVisualizationManager::Render();
}
void ASTransSeeds::ContinuePaintSeeds(double* pPosition, const int c_ViewLabel)
{
	double Extent[6];
	ASVisualizationManager::GetDisplayExtent(Extent);
	if (pPosition[0] < Extent[0] || pPosition[0] > Extent[1])
	{
		return;
	}
	if (pPosition[1] < Extent[2] || pPosition[1] > Extent[3])
	{
		return;
	}
	if (pPosition[2] < Extent[4] || pPosition[2] > Extent[5])
	{
		return;
	}
	// ��������
	ms_SelfPointer->m_WorkingSeedData->ContinuePaintingSeeds(pPosition, c_ViewLabel);
	// ˢ����ʾ
	ms_SelfPointer->m_FModelSeeds->ContinuePaintingData(pPosition);
	// ��Ⱦ
	ASVisualizationManager::Render();
}
void ASTransSeeds::EndPaintSeeds()
{
	ms_SelfPointer->m_WorkingSeedData->EndPaintingSeeds();
	ms_SelfPointer->m_WorkingSeedData = nullptr;
}
// ˢ�����ӵ���ʾ
void ASTransSeeds::RefreshSeedsDisplay()
{
	ms_SelfPointer->m_FModelSeeds->RefreshSeedsDisplay();
	// ��Ⱦ
	ASVisualizationManager::Render();
}
// ���ӵ��Ƿ���ʾ
void ASTransSeeds::SetSeedShown(const bool c_Shown)
{
	ms_SelfPointer->m_FModelSeeds->SetSeedShown(c_Shown);
}
// ����һ��
void ASTransSeeds::UndoPaintingSedds()
{
	bool b = ASTransSeeds::GetCurrentSeedData()->UndoALine();
	if (b)
	{
		// ˢ������
		ms_SelfPointer->m_FModelSeeds->RefreshSeedsDisplay();
		// ��Ⱦ
		ASVisualizationManager::Render();
	}
}
// ���ӵ����ݷ����仯ʱ��������Ҫ���������б�����˵ɾ�����ӵ��ļ�ʱ���������б��еĶ�ӦID �޳�
void ASTransSeeds::AdjustUndoList()
{
	ms_SelfPointer->m_FModelSeeds->AdjustUndoList();
}
// ��Ӳ�̶��ļ�
void ASTransSeeds::LoadseedDataFromDisk(const QStringList c_FileNameList)
{
	ms_SelfPointer->m_FModelSeeds->InitSeedsPipeline();
	for (int nit = 0; nit < c_FileNameList.size(); nit++)
	{
		ms_SelfPointer->m_FModelSeeds->LoadSeedData(c_FileNameList.at(nit));
	}
}
// �Ƴ�������
void ASTransSeeds::RemoveSeeds(const int c_SeedDataID, const int c_SeedID)
{
	// �Ƴ����ӵ�
	ms_SelfPointer->m_FModelSeeds->DeleteSeeds(c_SeedDataID, c_SeedID);
	// ˢ����ʾ
	ms_SelfPointer->m_FModelSeeds->RefreshSeedsDisplay();
	// ��Ⱦ
	ASVisualizationManager::Render();
	// ˢ�������б�
	ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_SeedData);
}

//void ASTransSeeds::fNewSeedData(QString name, int label, QColor color)
//{
//	// �ж��Ƿ���Ҫ�½����ӵ��ļ�
//	ASSeedData* SeedData = ASTransSeeds::GetCurrentSeedData();
//	if (!SeedData)
//	{
//		SeedData = new ASSeedData();
//		SeedData->setName(tr("Seed data"));
//		SeedData->setShown(true);
//		ASDataTree::NewDataNode(SeedData, ASTransDataGeneral::GetGeneratingData());
//		if (!SeedData)
//		{
//			qDebug("Error: Null pointer of current SeedsData. From ASPaintingSeedsWidget.");
//			return;
//		}
//	}
//	int id = SeedData->NewSeed(name, label, color);
//	if (id == -1)
//	{
//		qDebug("error: Bad new seed id in ASPaintingSeedsWidget.cpp");
//		return;
//	}
//
//	ASTransSeeds::SetCrntSeedsID(id);
//	// ˢ��
//	ASTransSeeds::UpdateListsOfSeedData();
//	// ʹ��
//	ASTransSeeds::SetModelEnabled(true);
//}
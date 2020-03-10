#include "ASTransContour.h"
#include "ASMainWidget.h"
#include "ASDialogNewSeedsFile.h"
#include "ASContourData.h"
#include "ASTransAddDeleteData.h"
#include "ASFModelContour.h"
#include "ASInteractorStyleManager.h"
#include "ASTransInteractorStyle.h"
#include "ASVisualizationManager2D.h"
#include "ASVisualizationManager.h"
#include "ASPipelineContour.h"
#include "ASPipelineManager.h"
#include "ASDataTree.h"
#include "ASTransDataGeneral.h"
#include "ASDataStructureWalker.h"
#include "ASArrayImageData.h"
#include "ASDialogNewElement.h"
#include "ASTransCompleter.h"
#include "ASTransSidebarGeneral.h"
#include "ASAnnotation.h"

ASTransContour* ASTransContour::ms_SelfPointer = nullptr;

ASTransContour::ASTransContour(QObject *parent)
	: ASTransmissionBase(parent)
{
	ms_SelfPointer = this;
	m_FModelContour = new ASFModelContour();
}

ASTransContour::~ASTransContour()
{

}
// Ψһ����
ASTransContour* ASTransContour::GetSelfPointer()
{
	return ms_SelfPointer;
}
//��ǰSeedsID
void ASTransContour::SetCrntContourID(const int c_id)
{
	ms_SelfPointer->m_FModelContour->SetCurrentContourID(c_id);
	//if (c_id >= 0)
	//{
	//	ms_SelfPointer->m_FModelContour->SetContourModleEnabled(true);
	//}
	//else
	//{
	//	ms_SelfPointer->m_FModelContour->SetContourModleEnabled(false);
	//}
}
int ASTransContour::GetCrntContourID()
{
	return ms_SelfPointer->m_FModelContour->GetCurrentContourID();
}
// �õ���ǰContour����
ASContourData* ASTransContour::GetCurrentContourData()
{
	ASAbstractData* CrntDataNode = ASTransSidebarGeneral::GetCrntDataNode();
	if (CrntDataNode && CrntDataNode->isTypeInherited(DataType_ContourData))
	{
		return static_cast<ASContourData*>(CrntDataNode);
	}
	return nullptr;
}
// �½��������ļ�
void ASTransContour::NewContourData(ASAbstractData* pParent)
{
	// 1 ����궨������
	//ASDialogNewElement* dia = new ASDialogNewElement(ASMainWidget::GetMainWidget(), enContour);
	//dia->exec();
	//if (dia->m_result.size() == 0)
	//{
	//	return;
	//}
	//QString NewName = dia->m_result;
	//if (NewName.size() == 0)
	//{
	//	return;
	//}
	QString NewName = "Contour";
	QList<structCompleterItem*>* pList = ASTransCompleter::GetStructureList();
	int contourid = -1;
	QColor c(Qt::red);
	for (int index = 0; index < pList->size(); index++)
	{
		if (pList->at(index)->name == NewName)
		{
			contourid = pList->at(index)->id;
			c = pList->at(index)->color;
			break;
		}
	}

	ASContourData* ContourData;
	if (pParent->isTypeInherited(DataType_ContourData))
	{
		ContourData = static_cast<ASContourData*>(pParent);
	}
	else
	{
		ContourData = static_cast<ASContourData*>(pParent->getChild(DataType_ContourData));
	}	
	if (!ContourData)
	{
		ContourData = new ASContourData();
		ContourData->setName(tr("Contour data"));
		ContourData->setShown(true);
		ASDataTree::NewDataNode(ContourData, pParent);
		if (!ContourData)
		{
			qDebug("Error: Null pointer of current ContourData. From ASPaintingContourWidget.");
			return;
		}
	}
	int id = ContourData->NewContour(NewName, contourid, c);
	if (id == -1)
	{
		qDebug("error: Bad new seed id in ASPaintingSeedsWidget.cpp");
		return;
	}
	ASTransSidebarGeneral::SetCrntDataNode(ContourData);
	ASTransContour::SetCrntContourID(id);
	// ˢ��
	ASTransContour::UpdateListsOfContourData();
	// ʹ��
	ASTransContour::SetModelEnabled(true);
	
}
void ASTransContour::NewContourData(ASAbstractData* pParent, QString name, int label, QColor color)
{
	// �ж��Ƿ���Ҫ�½��������ļ�
	ASContourData* ContourData = static_cast<ASContourData*>(pParent->getChild(DataType_ContourData));
	if (!ContourData)
	{
		ContourData = new ASContourData();
		ContourData->setName(tr("Contour data"));
		ContourData->setShown(true);
		ASDataTree::NewDataNode(ContourData, pParent);
		if (!ContourData)
		{
			qDebug("Error: Null pointer of current ContourData. From ASPaintingContourWidget.");
			return;
		}
	}
	int id = ContourData->NewContour(name, label, color);
	if (id == -1)
	{
		qDebug("error: Bad new seed id in ASPaintingSeedsWidget.cpp");
		return;
	}
	ASTransSidebarGeneral::SetCrntDataNode(ContourData);
	ASTransContour::SetCrntContourID(id);
	// ˢ��
	ASTransContour::UpdateListsOfContourData();
	// ʹ��
	ASTransContour::SetModelEnabled(true);
}
// ˢ������������б�
void ASTransContour::UpdateListsOfContourData()
{
	ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_ContourData);
}
// ��ʼ�������߹���
void ASTransContour::InitContourPipeline()
{
	ms_SelfPointer->m_FModelContour->InitContourPipeline();
	ms_SelfPointer->m_FModelContour->ReSetCtrlRadius(0);
	ms_SelfPointer->m_FModelContour->ReSetCtrlRadius(1);
	ms_SelfPointer->m_FModelContour->ReSetCtrlRadius(2);
}
// ����ģ���Ƿ�ʹ��
void ASTransContour::SetModelEnabled(const bool c_enable)
{
	ms_SelfPointer->m_FModelContour->SetContourModleEnabled(c_enable);
	emit ms_SelfPointer->signalSetModelEnabled(c_enable);
	if (c_enable)
	{
		if (ASInteractorStyleManager::GetInteractorStyle2D() != InterStyle2D_PaintingContour)
		{
			ASTransInteractorStyle::SetInteratorStyle2D(InterStyle2D_PaintingContour);
		}
	}
	else
	{
		if (ASInteractorStyleManager::GetInteractorStyle2D() == InterStyle2D_PaintingContour)
		{
			ASTransInteractorStyle::SetInteratorStyle2D(InterStyle2D_General);
		}
	}
}
// �������Ƿ���ʾ
void ASTransContour::SetContourShown(const bool c_Shown)
{
	ms_SelfPointer->m_FModelContour->SetContourShown(c_Shown);
}
// ���ý�����ʽ��0, ��ͨ; 1, ����
void ASTransContour::SetInterfaceModel(const int c_model)
{
	ms_SelfPointer->m_FModelContour->SetInterfaceModel(c_model);
}
int ASTransContour::GetInterfaceModel()
{
	return ms_SelfPointer->m_FModelContour->GetInterfaceModel();
}
// ˢ���������б�
void ASTransContour::RefreshContourList()
{
	ms_SelfPointer->m_FModelContour->SetIDOfPaintingData(-1);
}
// ���õ�ǰ���ڻ��Ƶ����������ݵ�ID
void ASTransContour::SetPaintingContourID(const int c_ID)
{
	ms_SelfPointer->m_FModelContour->SetIDOfPaintingData(c_ID);
}
// ����������operate: 0-2����ӣ����£��ƶ����պϣ�; 3-4: �ƶ������£��ƶ���; 5: ɾ��; 6-7: ���루���£��ƶ���; 8: ˢ��(����ʱ) ; 9: ɾ����������
void ASTransContour::SplineContourOperation(double* pos, int viewlabel, int operate, vtkActor* actor)
{
	static int s_GeneratingID = -1;
	static int s_GeneratingContourID = -1;
	static int s_GeneratingViewLabel = -1;
	static int s_GeneratingIndexOfContour = -1;
	static int s_GeneratingIndexOfHandle = -1;

	double ImageSpacing[3];
	ASVisualizationManager::GetDisplaySpacing(ImageSpacing);
	switch (operate)
	{
	case CtrOpe_Addtemp:
	{
		// �����ʱ���Ƶ�
		ms_SelfPointer->m_FModelContour->AddContrlPointsTemp(pos, viewlabel, ImageSpacing);
		// ˢ������
		ms_SelfPointer->m_FModelContour->RefreshSplineContourDisplay(viewlabel);
		// ��Ⱦ
		ASVisualizationManager2D::Render(viewlabel);
		break;
	}
	case CtrOpe_Movetemp:
	{
		// ��ӿ��Ƶ�Ĺ�����ƽ�����һ�����Ƶ�
		ms_SelfPointer->m_FModelContour->MoveContrlPoints(pos, viewlabel, ImageSpacing);
		// ˢ������
		ms_SelfPointer->m_FModelContour->RefreshSplineContourDisplay(viewlabel);
		// ��Ⱦ
		ASVisualizationManager2D::Render(viewlabel);
		break;
	}
	case CtrOpe_Deletetemp:
	{
		// ��ӿ��Ƶ�Ĺ�����ɾ�����һ�����Ƶ�
		ms_SelfPointer->m_FModelContour->DeleteContrlPointsTemp(pos, viewlabel, ImageSpacing);
		// ˢ������
		ms_SelfPointer->m_FModelContour->RefreshSplineContourDisplay(viewlabel);
		// ��Ⱦ
		ASVisualizationManager2D::Render(viewlabel);
		break;
	}
	case CtrOpe_Closetemp:
	{
		// ��ͼ�պ�����������������δ�պ������ĵ�һ�����Ƶ�����Գɹ��պ�
		if (ms_SelfPointer->m_FModelContour->ReserchHandleSplineContour(
			actor, &(ms_SelfPointer->ID_Closetemp), &(ms_SelfPointer->ContourID_Closetemp), 
			&(ms_SelfPointer->viewLabel_Closetemp),
			&(ms_SelfPointer->indexOfContour_Closetemp), &(ms_SelfPointer->indexOfHandle_Closetemp)))
		{
			if (ms_SelfPointer->viewLabel_Closetemp != viewlabel)
			{
				return;
			}
			// ��ӿ��Ƶ�Ĺ�����ɾ�����һ�����Ƶ�
			ms_SelfPointer->m_FModelContour->DeleteContrlPointsTemp(pos, viewlabel, ImageSpacing);
			// �պ�������
			ms_SelfPointer->m_FModelContour->SetContourClosed(ms_SelfPointer->ID_Closetemp, ms_SelfPointer->viewLabel_Closetemp, ms_SelfPointer->indexOfContour_Closetemp, ms_SelfPointer->indexOfHandle_Closetemp, true);
			// ˢ������
			ms_SelfPointer->m_FModelContour->RefreshSplineContourDisplay(viewlabel);
			// ��Ⱦ
			ASVisualizationManager2D::Render(viewlabel);
			ms_SelfPointer->Closetemp = true;
		}
		break;
	}
	case CtrOpe_ClosetempStop:
	{
		if (ms_SelfPointer->Closetemp == false)
		{
			return;
		}
		// ȡ���պ�������
		ms_SelfPointer->m_FModelContour->SetContourClosed(ms_SelfPointer->ID_Closetemp, ms_SelfPointer->viewLabel_Closetemp, ms_SelfPointer->indexOfContour_Closetemp, ms_SelfPointer->indexOfHandle_Closetemp, false);
		// �����ʱ���Ƶ�
		ms_SelfPointer->m_FModelContour->AddContrlPointsTemp(pos, viewlabel, ImageSpacing);
		// ˢ������
		ms_SelfPointer->m_FModelContour->RefreshSplineContourDisplay(viewlabel);
		// ��Ⱦ
		ASVisualizationManager2D::Render(viewlabel);
		ms_SelfPointer->Closetemp = false;
		break;
	}
	case CtrOpe_Add:
	{
		// ��ӿ��Ƶ�
		ms_SelfPointer->m_FModelContour->AddContrlPoints(pos, viewlabel, ImageSpacing);
		// ˢ������
		ms_SelfPointer->m_FModelContour->RefreshSplineContourDisplay(viewlabel);
		// ��Ⱦ
		ASVisualizationManager2D::Render(viewlabel);
		break;
	}
	case CtrOpe_Close:
	{
		if (ms_SelfPointer->Closetemp == false)
		{
			return;
		}
		// �����ʱ���Ƶ�
		ms_SelfPointer->m_FModelContour->AddContrlPointsTemp(pos, viewlabel, ImageSpacing);
		// ˢ������
		ms_SelfPointer->m_FModelContour->RefreshSplineContourDisplay(viewlabel);
		// ��Ⱦ
		ASVisualizationManager2D::Render(viewlabel);
		ms_SelfPointer->Closetemp = false;
		ms_SelfPointer->ID_Closetemp = -1;
		ms_SelfPointer->indexOfContour_Closetemp = -1;
		break;
	}
	case CtrOpe_MoveChoose:
	{
		// ׼��ƽ�ƿ��Ƶ�
		ms_SelfPointer->m_FModelContour->ReserchHandleSplineContour(actor, &s_GeneratingID, 
			&s_GeneratingContourID, &s_GeneratingViewLabel, &s_GeneratingIndexOfContour, 
			&s_GeneratingIndexOfHandle);
		break;
	}
	case CtrOpe_Moving:
	{
		// ƽ�ƿ��Ƶ�
		ms_SelfPointer->m_FModelContour->MoveContrlPoints(pos, viewlabel, ImageSpacing, s_GeneratingID, 
			s_GeneratingContourID, s_GeneratingIndexOfContour, s_GeneratingIndexOfHandle);
		// ˢ������
		ms_SelfPointer->m_FModelContour->RefreshSplineContourDisplay(viewlabel);
		// ��Ⱦ
		ASVisualizationManager2D::Render(viewlabel);
		break;
	}
	case CtrOpe_Delete:
	{
		// ɾ�����Ƶ�
		int ID;
		int ContourID;
		int viewLabel;
		int indexOfContour;
		int indexOfHandle;
		if (ms_SelfPointer->m_FModelContour->ReserchHandleSplineContour(actor, &ID, &ContourID, &viewLabel, &indexOfContour, &indexOfHandle))
		{
			if (viewLabel != viewlabel)
			{
				return;
			}
			// ɾ�����Ƶ�
			ms_SelfPointer->m_FModelContour->DeleteContrlPoints(viewlabel, ImageSpacing, ID, ContourID, 
				indexOfContour, indexOfHandle);
			// ˢ������
			ms_SelfPointer->m_FModelContour->RefreshSplineContourDisplay(viewlabel);
			// ��Ⱦ
			ASVisualizationManager2D::Render(viewlabel);
		}
		break;
	}
	case CtrOpe_InsertStart:
	{
		// ������Ƶ㣬����
		ms_SelfPointer->m_FModelContour->GetInsertHandleIndex(
			pos, viewlabel, &s_GeneratingID, &s_GeneratingIndexOfContour, &s_GeneratingIndexOfHandle);
		// ������Ƶ�
		ms_SelfPointer->m_FModelContour->InsertContrlPoints(
			pos, viewlabel, ImageSpacing, s_GeneratingID, s_GeneratingIndexOfContour, s_GeneratingIndexOfHandle);
		// ˢ������
		ms_SelfPointer->m_FModelContour->RefreshSplineContourDisplay(viewlabel);
		// ��Ⱦ
		ASVisualizationManager2D::Render(viewlabel);
		break;
	}
	case CtrOpe_InsertContinue:
	{
		// ������Ƶ㣬�ƶ�
		// ɾ�����Ƶ�
		ms_SelfPointer->m_FModelContour->DeleteContrlPoints(viewlabel, ImageSpacing, s_GeneratingID, 
			s_GeneratingContourID, s_GeneratingIndexOfContour, s_GeneratingIndexOfHandle + 1);
		// ������Ƶ�
		ms_SelfPointer->m_FModelContour->InsertContrlPoints(pos, viewlabel, ImageSpacing, s_GeneratingID, s_GeneratingIndexOfContour, s_GeneratingIndexOfHandle);
		// ˢ������
		ms_SelfPointer->m_FModelContour->RefreshSplineContourDisplay(viewlabel);
		// ��Ⱦ
		ASVisualizationManager2D::Render(viewlabel);
		break;
	}
	case CtrOpe_Refresh:
	{
		// ˢ������
		ms_SelfPointer->m_FModelContour->ReSetCtrlRadius(viewlabel);
		// ��Ⱦ
		ASVisualizationManager2D::Render(viewlabel);
		break;
	}
	case CtrOpe_DeleteWhole:
	{
		int ID;
		int ContourID;
		int viewLabel;
		int indexOfContour;
		int indexOfHandle;
		if (ms_SelfPointer->m_FModelContour->ReserchHandleSplineContour(actor, &ID, &ContourID, &viewLabel, 
			&indexOfContour, &indexOfHandle))
		{
			if (viewLabel != viewlabel)
			{
				return;
			}
			// �պ�������
			ms_SelfPointer->m_FModelContour->DeleteContour(ID, ContourID, viewLabel, indexOfContour, indexOfHandle);
			// ˢ������
			ms_SelfPointer->m_FModelContour->RefreshSplineContourDisplay(viewlabel);
			// ��Ⱦ
			ASVisualizationManager2D::Render(viewlabel);
		}
		break;
	}
	default:
		break;
	}
}
// �ж��Ƿ�Ϊ��һ�����Ƶ�
bool ASTransContour::CheckFirstCtrlPoint(vtkActor* pActor, int viewlabel)
{
	int ID;
	int ContourID;
	int viewLabel;
	int indexOfContour;
	int indexOfHandle;
	if (ms_SelfPointer->m_FModelContour->ReserchHandleSplineContour(pActor, &ID, &ContourID, &viewLabel, 
		&indexOfContour, &indexOfHandle))
	{
		if (viewLabel == viewlabel && indexOfHandle == 0)
		{
			ASContourData* crntData = static_cast<ASContourData*>(ASAbstractData::getDataNodeFromID(ID));
			structContour* crntContour = crntData->GetContourFromID(ContourID);
			structCurve* crntCurve = crntContour->pListCurves->at(indexOfContour);

			if (crntCurve->isClosure == false)
			{
				return true;			
			}
			else
			{
				if (ID == ms_SelfPointer->ID_Closetemp && indexOfContour == ms_SelfPointer->indexOfContour_Closetemp)
				{
					return true;
				}
			}
		}
	}
	return false;
}
// ˢ��
void ASTransContour::RefreshContourDisplay()
{
	ms_SelfPointer->m_FModelContour->RefreshSplineContourDisplay(0);
	ms_SelfPointer->m_FModelContour->RefreshSplineContourDisplay(1);
	ms_SelfPointer->m_FModelContour->RefreshSplineContourDisplay(2);
	ASVisualizationManager2D::Render();
}
// ��Ӳ�̶��ļ�
void ASTransContour::LoadContourDataFromDisk(const QStringList c_FileNameList)
{
	for (int nit = 0; nit < c_FileNameList.size(); nit++)
	{
		ms_SelfPointer->m_FModelContour->LoadContourData(c_FileNameList.at(nit));
	}
}
// ��ͼ����
void ASTransContour::ViewZoom(const int c_view)
{
	SplineContourOperation(nullptr, c_view, CtrOpe_Refresh);
}
// �Ƴ�������
void ASTransContour::RemoveContour(const int c_ContourDataNodeID, const int c_ContourID)
{
	// ɾ��������
	ms_SelfPointer->m_FModelContour->DeleteWholeContour(c_ContourDataNodeID, c_ContourID);
	// ˢ����ʾ
	ms_SelfPointer->m_FModelContour->RefreshSplineContourDisplay(0);
	ms_SelfPointer->m_FModelContour->RefreshSplineContourDisplay(1);
	ms_SelfPointer->m_FModelContour->RefreshSplineContourDisplay(2);
	// ��Ⱦ
	ASVisualizationManager2D::Render();
	// ˢ�������б�
	ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_ContourData);
}
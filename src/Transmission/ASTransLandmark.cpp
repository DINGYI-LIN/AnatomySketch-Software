#include "ASTransLandmark.h"
#include "ASMainWidget.h"
#include "ASLandmarkData.h"
#include "ASDataTree.h"
#include "ASTransAddDeleteData.h"
#include "ASInteractorStyleManager.h"
#include "ASTransInteractorStyle.h"
#include "ASVisualizationManager2D.h"
#include "ASVisualizationManager.h"
#include "ASTransDataGeneral.h"
#include "ASDataStructureWalker.h"
#include "ASDialogNewLM.h"
#include "ASTransSidebarGeneral.h"
#include <QInputDialog>

ASTransLandmark* ASTransLandmark::ms_SelfPointer = nullptr;

ASTransLandmark::ASTransLandmark(QObject *parent)
	: ASTransmissionBase(parent)
{
	ms_SelfPointer = this;
	m_FModelLandmark = new ASFModelLandmark();
}

ASTransLandmark::~ASTransLandmark()
{

}
// Ψһ����
ASTransLandmark* ASTransLandmark::GetSelfPointer()
{
	return ms_SelfPointer;
}

// �õ���ǰROI�ļ�
ASLandmarkData* ASTransLandmark::GetCurrentLMData()
{
	ASAbstractData* CrntDataNode = ASTransSidebarGeneral::GetCrntDataNode();
	if (CrntDataNode && CrntDataNode->isTypeInherited(DataType_LandmarkData))
	{
		return static_cast<ASLandmarkData*>(CrntDataNode);
	}
	return nullptr;
}
// �½��������ļ�
void ASTransLandmark::NewLandmarkData(ASAbstractData* pParent)
{
	ASLandmarkData* LMdata;
	if (pParent->isTypeInherited(DataType_LandmarkData))
	{
		LMdata = static_cast<ASLandmarkData*>(pParent);
	}
	else
	{
		LMdata = static_cast<ASLandmarkData*>(pParent->getChild(DataType_LandmarkData));
	}
	if (!LMdata)
	{
		LMdata = new ASLandmarkData();
		LMdata->setBeingProcess(false);
		LMdata->setName(tr("Landmark data"));
		LMdata->setShown(true);
		ASDataTree::NewDataNode(LMdata, pParent);
		if (!LMdata)
		{
			return;
		}
	}

	// ������������ӽڵ�	
	ASTransSidebarGeneral::SetCrntDataNode(LMdata);
	// �����б���ʾ
	ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_LandmarkData);
	// ʹ��
	ASTransLandmark::SetModelEnabled(true);
}
// ��ʼ�������߹���
void ASTransLandmark::InitLandmarkPipeline()
{
	ms_SelfPointer->m_FModelLandmark->InitLandmarkPipeline();
	ms_SelfPointer->m_FModelLandmark->ReSetCtrlRadius(0);
	ms_SelfPointer->m_FModelLandmark->ReSetCtrlRadius(1);
	ms_SelfPointer->m_FModelLandmark->ReSetCtrlRadius(2);
}
// ����ģ���Ƿ�ʹ��
void ASTransLandmark::SetModelEnabled(const bool c_enable)
{
	ms_SelfPointer->m_FModelLandmark->SetLandmarkModleEnabled(c_enable);
	emit ms_SelfPointer->signalSetModelEnabled(c_enable);
	if (c_enable)
	{
		if (ASInteractorStyleManager::GetInteractorStyle2D() != InterStyle2D_PaintingLandmarks)
		{
			ASTransInteractorStyle::SetInteratorStyle2D(InterStyle2D_PaintingLandmarks);
		}
	}
	else
	{
		if (ASInteractorStyleManager::GetInteractorStyle2D() == InterStyle2D_PaintingLandmarks)
		{
			ASTransInteractorStyle::SetInteratorStyle2D(InterStyle2D_General);
		}
	}
}
// �궨���Ƿ���ʾ
void ASTransLandmark::SetLandmarksShown(const bool c_Shown)
{
	ms_SelfPointer->m_FModelLandmark->SetLandmarkShown(c_Shown);
}
// ��ӱ궨��
void ASTransLandmark::LandmarkOperation(double* pos, int viewlabel, int operate, vtkActor* actor)
{
	static int s_crntDataID = -1;
	static int s_crntViewLabel = -1;
	static int s_crntPointID = -1;

	double ImageSpacing[3];
	ASVisualizationManager::GetDisplaySpacing(ImageSpacing);
	switch (operate)
	{
	case CtrOpe_AddLandM:
	{
		// 1 ��ӱ궨��
		// 1.1�����Ի����趨�궨������
		ASDialogNewLM* dia = new ASDialogNewLM(ASMainWidget::GetMainWidget());
		dia->exec();
		if (dia->m_result.size() > 0)
		{
			// 1.2 ��ӱ궨��
			ms_SelfPointer->m_FModelLandmark->AddLandmark(pos, dia->m_result);
			// 1.3 ˢ����ʾ
			ms_SelfPointer->m_FModelLandmark->RefreshLMDisplay(viewlabel);
			// 1.4 ��Ⱦ
			ASVisualizationManager2D::Render(viewlabel);
		}
		ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_LandmarkData);
		break;
	}
	case CtrOpe_MoveChooseLandM:
	{
		// 2 ׼��ƽ�Ʊ궨��
		ms_SelfPointer->m_FModelLandmark->ReserchLanmark(actor, &s_crntDataID, &s_crntViewLabel, &s_crntPointID);
		break;
	}
	case CtrOpe_MovingLandM:
	{
		// 3 ����ƽ�Ʊ궨��
		// 3.1 ƽ�Ʊ궨��
		ms_SelfPointer->m_FModelLandmark->MoveLandmark(pos, s_crntDataID, s_crntViewLabel, s_crntPointID);
		// 3.2 ˢ����ʾ
		ms_SelfPointer->m_FModelLandmark->RefreshLMDisplay(0);
		ms_SelfPointer->m_FModelLandmark->RefreshLMDisplay(1);
		ms_SelfPointer->m_FModelLandmark->RefreshLMDisplay(2);
		// 3.3 ��Ⱦ
		ASVisualizationManager2D::Render();
		break;
	}
	case CtrOpe_DeleteLandM:
	{
		// 4 ɾ���궨��
		// 4.1 Ѱ�ұ궨��
		ms_SelfPointer->m_FModelLandmark->ReserchLanmark(actor, &s_crntDataID, &s_crntViewLabel, &s_crntPointID);
		// 4.2 ɾ���궨��
		ms_SelfPointer->m_FModelLandmark->DeleteLandmark(s_crntDataID, s_crntPointID);
		// 4.3 ˢ����ʾ
		ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_LandmarkData);
		ms_SelfPointer->m_FModelLandmark->RefreshLMDisplay(0);
		ms_SelfPointer->m_FModelLandmark->RefreshLMDisplay(1);
		ms_SelfPointer->m_FModelLandmark->RefreshLMDisplay(2);
		// 4.4 ��Ⱦ
		ASVisualizationManager2D::Render();
		break;
	}
	case CtrOpe_ZoomLandM:
	{
		// 5 ͼ������ʱ��֤���Ƶ㲻����
		// ˢ������
		ms_SelfPointer->m_FModelLandmark->ReSetCtrlRadius(viewlabel);
		// ��Ⱦ
		ASVisualizationManager2D::Render(viewlabel);
		break;
	}
	default:
		break;
	}
}
// ˢ��
void ASTransLandmark::RefreshLandMDisplay()
{
	ms_SelfPointer->m_FModelLandmark->RefreshLMDisplay(0);
	ms_SelfPointer->m_FModelLandmark->RefreshLMDisplay(1);
	ms_SelfPointer->m_FModelLandmark->RefreshLMDisplay(2);
}
// ��Ӳ�̶��ļ�
void ASTransLandmark::LoadLandMDataFromDisk(const QStringList c_FileNameList)
{
	ms_SelfPointer->m_FModelLandmark->InitLandmarkPipeline();
	for (int nit = 0; nit < c_FileNameList.size(); nit++)
	{
		ms_SelfPointer->m_FModelLandmark->LoadLandmarkData(c_FileNameList.at(nit));
	}
}
// �Ƴ��궨��
void ASTransLandmark::RemoveLandMark(const int c_LMDataNodeID, const int c_LMID)
{
	// 4.2 ɾ���궨��
	ms_SelfPointer->m_FModelLandmark->DeleteLandmark(c_LMDataNodeID, c_LMID);
	// 4.3 ˢ����ʾ
	ms_SelfPointer->m_FModelLandmark->RefreshLMDisplay(0);
	ms_SelfPointer->m_FModelLandmark->RefreshLMDisplay(1);
	ms_SelfPointer->m_FModelLandmark->RefreshLMDisplay(2);
	// 4.4 ��Ⱦ
	ASVisualizationManager2D::Render();
	// ˢ�������б�
	ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_LandmarkData);
}

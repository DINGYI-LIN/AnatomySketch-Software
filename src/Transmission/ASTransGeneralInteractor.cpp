#include "ASTransGeneralInteractor.h"
#include "ASTransSidebarGeneral.h"
#include "ASTransStatusBarGeneral.h"
#include "ASVisualizationManager.h"
#include "ASVisualizationManager2D.h"
#include "ASVisualizationManager3D.h"
#include "ASAbstractData.h"
#include "ASArrayImageData.h"
#include "ASPolyImageData.h"
#include "ASPipelineBase.h"
#include "ASPipelineManager.h"
#include "ASPipelineArrayImage.h"
#include "ASPipelinePolyImage.h"
#include "ASPipelineOuterBorder3D.h"
#include "ASTransContour.h"
#include "ASTransLandmark.h"
#include "ASTransROI.h"
#include "ASFModelGeneralInteractor.h"
#include "ASPipelineText.h"
#include <QList>

ASTransGeneralInteractor* ASTransGeneralInteractor::ms_SelfPointer = nullptr;

ASTransGeneralInteractor::ASTransGeneralInteractor(QObject *parent)
	: ASTransmissionBase(parent)
{
	ms_SelfPointer = this;

	// ����ģ��
	m_FModelGenInter = new ASFModelGeneralInteractor();
}

ASTransGeneralInteractor::~ASTransGeneralInteractor()
{

}

// Ψһ����
ASTransGeneralInteractor* ASTransGeneralInteractor::GetSelfPointer()
{
	return ms_SelfPointer;
}
// ������ʾ����
void ASTransGeneralInteractor::SetVisualizationPosition(const double c_x, const double c_y, const double c_z)
{
	ASTransGeneralInteractor::fSetVisualizationPosition(c_x, c_y, c_z);
	ASVisualizationManager::Render();
}
// �л�3D��ͼ2D�����Ƿ���ʾ�������л����Ƿ���ʾ
bool ASTransGeneralInteractor::Switch3DImageStackShown()
{
	bool shown = ASVisualizationManager3D::Switch3DImageStackShown();
	ASPipelineOuterBorder3D::setCrossShairShown(shown);
	ASVisualizationManager3D::Render();
	return shown;
}
// ���õ�ǰ֡
void ASTransGeneralInteractor::SetVisualizationFrame(const int c_frame)
{
	ASVisualizationManager::SetDisplayFrame(c_frame);
	// ���������ݹ���
	for (ASPipelineBase* item = ASPipelineManager::bigen_inherit(PipeLineType_ArrayImage); item != nullptr; item = ASPipelineManager::next_inherit(PipeLineType_ArrayImage))
	{
		ASPipelineArrayImage* CrntPipeline = (ASPipelineArrayImage*)item;
		CrntPipeline->SetFrame(c_frame);
	}
	// ��Ⱦ
	ASVisualizationManager::Render();
	// �����
	ASTransSidebarGeneral::SetDisplayFrame(c_frame);
	// ����״̬������������Ϣ
	ASTransStatusBarGeneral::RefreshStatusBarFocusInfo();
}
// ���õ�ǰͼ��λ����
void ASTransGeneralInteractor::SetVisualizationLevelWindow(const double c_level, const double c_window)
{
	ASArrayImageData* crntTopData = ASVisualizationManager::GetToplayerData();
	double windowleble[2];
	windowleble[0] = c_window;
	windowleble[1] = c_level;
	SetArrayDataWindowLevel(crntTopData, windowleble);
}
// ����ĳ�����Ƿ���ʾ
void ASTransGeneralInteractor::SetDateShown(const int c_ID, const bool c_isShown)
{
	ASAbstractData* crntDataNode = ASAbstractData::getDataNodeFromID(c_ID);
	if (c_isShown != crntDataNode->isShown())
	{		
		ms_SelfPointer->fSetDataShown(crntDataNode, c_isShown);
		emit ms_SelfPointer->signalDataShownChanged(crntDataNode);
		// ��Ⱦ
		ASVisualizationManager::Render();
	}
}
// ��������
void ASTransGeneralInteractor::ReinitDataNode(ASAbstractData* DataNode)
{
	// 0 ������ظ�Ϊ��ʾ
	if (DataNode->isShown() == false)
	{
		ms_SelfPointer->fSetDataShown(DataNode, true);
		emit ms_SelfPointer->signalDataShownChanged(DataNode);
	}
	// 1 ���Ϊ�����ݣ����ô�λ����
	if (DataNode->isTypeInherited(DataType_ArrayImageData))
	{
		ASArrayImageData* crntDataNode = (ASArrayImageData*)DataNode;
		crntDataNode->setWindowLevel();
		QList<ASPipelineBase*>* crntListPipeline = new QList<ASPipelineBase*>;
		ASPipelineManager::GetPipelineForDataID(crntListPipeline, DataNode->getDataNodeID());
		for (int crntPipe = 0; crntPipe < crntListPipeline->size(); crntPipe++)
		{
			if (crntListPipeline->at(crntPipe)->GetPipeLineType() == PipeLineType_ArrayImage)
			{
				ASPipelineArrayImage* crntPipeline = (ASPipelineArrayImage*)crntListPipeline->at(crntPipe);
				crntPipeline->SetColorMapping(crntDataNode->getColorMap(), crntDataNode->getWindowLevel()[0], crntDataNode->getWindowLevel()[1]);
			}
		}
	}
	// 2 ��������Ϊ��������
	// ���½�����ʾ
	double* aExtent = DataNode->getDataExtent();
	ASVisualizationManager::SetDisplayPostion((aExtent[0] + aExtent[1]) / 2, (aExtent[2] + aExtent[3]) / 2, (aExtent[4] + aExtent[5]) / 2);
	ASTransStatusBarGeneral::RefreshStatusBarFocusInfo();
	// �������
	ASVisualizationManager::ResetCamera();
	// 3 ��Ⱦ
	ASVisualizationManager::Render();
}
// ���������ݵ���ɫ��
void ASTransGeneralInteractor::SetArrayDataColorMap(ASArrayImageData* DataNode, const int c_ColorMap)
{
	if (DataNode->getColorMap() == c_ColorMap)
	{
		return;
	}
	DataNode->setColorMap(c_ColorMap);
	QList<ASPipelineBase*>* crntListPipeline = new QList<ASPipelineBase*>;
	ASPipelineManager::GetPipelineForDataID(crntListPipeline, DataNode->getDataNodeID());
	for (int crntPipe = 0; crntPipe < crntListPipeline->size(); crntPipe++)
	{
		if (crntListPipeline->at(crntPipe)->GetPipeLineType() == PipeLineType_ArrayImage)
		{
			((ASPipelineArrayImage*)crntListPipeline->at(crntPipe))->SetColorMapping(c_ColorMap, DataNode->getWindowLevel()[0], DataNode->getWindowLevel()[1]);
			
		}
	}
	ASVisualizationManager::Render();
}
// ���������ݴ�λ����
void ASTransGeneralInteractor::SetArrayDataWindowLevel(ASArrayImageData* DataNode, double* WindowLevel)
{
	// 0 �������ݵĴ�λ�������
	DataNode->setWindowLevel(WindowLevel[0], WindowLevel[1]);
	// 1 ���¹���
	QList<ASPipelineBase*>* listPipe = new QList<ASPipelineBase*>;
	ASPipelineManager::GetPipelineForDataID(listPipe, DataNode->getDataNodeID());
	for (int ncrntPipe = 0; ncrntPipe < listPipe->size(); ncrntPipe++)
	{
		if (listPipe->at(ncrntPipe)->GetPipeLineType() == PipeLineType_ArrayImage)
		{
			((ASPipelineArrayImage*)listPipe->at(ncrntPipe))->SetColorMapping(DataNode->getColorMap(), DataNode->getWindowLevel()[0], DataNode->getWindowLevel()[1]);
		}
	}
	// 2 ��Ⱦ
	ASVisualizationManager::Render();
	// 3 ���²�����ʾ
	ASTransStatusBarGeneral::RefreshStatusBarFocusInfo();
	ASTransSidebarGeneral::SetWindowLevel(WindowLevel);
}
// ���������ݲ�͸����
void ASTransGeneralInteractor::SetPolyDataOpacity(ASAbstractData* DataNode, const int c_Opacity)
{
	if (DataNode->isTypeInherited(DataType_PolyImageData))
	{
		ASPolyImageData* PolyData = static_cast<ASPolyImageData*>(DataNode);
		PolyData->setOpacity(c_Opacity);
		QList<ASPipelineBase*>* crntListPipeline = new QList<ASPipelineBase*>;
		ASPipelineManager::GetPipelineForDataID(crntListPipeline, PolyData->getDataNodeID());
		for (int crntPipe = 0; crntPipe < crntListPipeline->size(); crntPipe++)
		{
			if (crntListPipeline->at(crntPipe)->GetPipeLineType() == PipeLineType_PolyImage)
			{
				((ASPipelinePolyImage*)crntListPipeline->at(crntPipe))->SetOpacity(((double)c_Opacity) / 100);
			}
		}
		ASVisualizationManager3D::Render();
	}
	if (DataNode->isTypeInherited(DataType_ArrayImageData))
	{
		ASArrayImageData* ArrayData = static_cast<ASArrayImageData*>(DataNode);
		ArrayData->setOpacity(c_Opacity);
		QList<ASPipelineBase*>* crntListPipeline = new QList<ASPipelineBase*>;
		ASPipelineManager::GetPipelineForDataID(crntListPipeline, ArrayData->getDataNodeID());
		for (int crntPipe = 0; crntPipe < crntListPipeline->size(); crntPipe++)
		{
			if (crntListPipeline->at(crntPipe)->GetPipeLineType() == PipeLineType_ArrayImage)
			{
				((ASPipelineArrayImage*)crntListPipeline->at(crntPipe))->SetOpacity(((double)c_Opacity) / 100);
			}
		}
		ASVisualizationManager::Render();
	}

}
// ������������ɫ
void ASTransGeneralInteractor::SetPolyDataColor(ASPolyImageData* DataNode, const QColor c_Color)
{
	DataNode->setColor(c_Color);
	QList<ASPipelineBase*>* crntListPipeline = new QList<ASPipelineBase*>;
	ASPipelineManager::GetPipelineForDataID(crntListPipeline, DataNode->getDataNodeID());
	for (int crntPipe = 0; crntPipe < crntListPipeline->size(); crntPipe++)
	{
		if (crntListPipeline->at(crntPipe)->GetPipeLineType() == PipeLineType_PolyImage)
		{
			((ASPipelinePolyImage*)crntListPipeline->at(crntPipe))->SetColor(c_Color);
		}
	}
	ASVisualizationManager::Render();
}
// ��ͼ����
void ASTransGeneralInteractor::GenerateViewZoom(const int c_view)
{
	ASVisualizationManager::RefreshZoomPara(c_view);
	ASTransContour::ViewZoom(c_view);
	ASTransLandmark::LandmarkOperation(nullptr, c_view, CtrOpe_ZoomLandM, nullptr);
}

// �����Ƿ���ʾ
void ASTransGeneralInteractor::fSetDataShown(ASAbstractData* DataNode, const bool c_isShown)
{
	DataNode->setShown(c_isShown);
	bool flagResetSpacing = false;
	QList<ASPipelineBase*>* crntListPipeline = new QList<ASPipelineBase*>;
	ASPipelineManager::GetPipelineForDataID(crntListPipeline, DataNode->getDataNodeID());
	for (int crntPipe = 0; crntPipe < crntListPipeline->size(); crntPipe++)
	{
		crntListPipeline->at(crntPipe)->SetShown(c_isShown);
		if (crntListPipeline->at(crntPipe)->GetPipeLineType() == PipeLineType_ArrayImage)
		{
			flagResetSpacing = true;
		}
	}
	if (DataNode->isTypeInherited(DataType_ContourData))
	{
		ASTransContour::RefreshContourDisplay();
	}
	if (DataNode->isTypeInherited(DataType_LandmarkData))
	{
		ASTransLandmark::RefreshLandMDisplay();
	}
	if (DataNode->isTypeInherited(DataType_ROI))
	{
		ASTransROI::RefreshROICubeDisplay();
	}
	// ���ݵ�ǰ�����ߵ��������ĸ�����ʾԪ��
	ASVisualizationManager::UpdateAuxiliaryPipeline();
	// ���¼��㶥�������ݺ����سߴ�
	if (flagResetSpacing)
	{
		ASVisualizationManager::ResetTopArrayImage();
	}	
}

// ������ʾ���㣬����Ⱦ
void ASTransGeneralInteractor::fSetVisualizationPosition(const double c_x, const double c_y, const double c_z)
{
	// ������ʾ����
	ASVisualizationManager::SetDisplayPostion(c_x, c_y, c_z);
	// ���ò���������������
	ASTransSidebarGeneral::SetDisplayPosition(c_x, c_y, c_z);
	// ����״̬������������Ϣ
	ASTransStatusBarGeneral::RefreshStatusBarFocusInfo();
}

// ��ͣ��Ϣ
void ASTransGeneralInteractor::HoverActorPicked(vtkActor* actor, const int c_x, const int c_y, const int c_ViewLabel)
{
	 ms_SelfPointer->m_FModelGenInter->HoverActorPicked(actor, c_x, c_y, c_ViewLabel);
}
void ASTransGeneralInteractor::AddHoverInfor(vtkActor* actor, QString infor)
{
	ms_SelfPointer->m_FModelGenInter->AddHoverInfor(actor, infor);
}
void ASTransGeneralInteractor::DeleteHoverInfor(vtkActor* actor)
{
	ms_SelfPointer->m_FModelGenInter->DeleteHoverInfor(actor);
}
int ASTransGeneralInteractor::ShowHoverText(const int c_ViewLabel, const QString c_text, double* pos1, double* pos2)
{
	int n = ASPipelineText::ShowText(c_ViewLabel, c_text, pos1, pos2);
	ASVisualizationManager2D::Render(c_ViewLabel);
	return n;
}
void ASTransGeneralInteractor::DeleteHoverText(const int c_TextID, const int c_ViewLabel)
{
	ASPipelineText::DeleteText(c_TextID);
	ASVisualizationManager2D::Render(c_ViewLabel);
}

void ASTransGeneralInteractor::SetLevel(double m_Level)
{
	ms_SelfPointer->WindowLevel[1] = m_Level;	
}

void ASTransGeneralInteractor::SetWindow(double m_Window)
{
	ms_SelfPointer->WindowLevel[0] = m_Window;
}

double ASTransGeneralInteractor::GetLevel()
{
	return ms_SelfPointer->WindowLevel[1];
}

double ASTransGeneralInteractor::GetWindow()
{
	return ms_SelfPointer->WindowLevel[0];
}





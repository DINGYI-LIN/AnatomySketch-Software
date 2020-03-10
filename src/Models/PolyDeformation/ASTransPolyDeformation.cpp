#include "ASTransPolyDeformation.h"
#include "ASPolyImageData.h"
#include "ASFModelPolyDeformation.h"
#include "ASPipelineManager.h"
#include "ASPipelineBase.h"
#include "ASPipelinePolyImage.h"
#include "ASVisualizationManager2D.h"
#include "ASVisualizationManager.h"

ASTransPolyDeformation* ASTransPolyDeformation::ms_SelfPointer = nullptr;
bool ASTransPolyDeformation::ms_Enabled = false;

ASTransPolyDeformation::ASTransPolyDeformation(QObject *parent)
	: ASTransmissionBase(parent)
{
	ms_SelfPointer = this;
	m_FModelPoly = new ASFModelPolyDeformation();
}

ASTransPolyDeformation::~ASTransPolyDeformation()
{

}
// Ψһ����
ASTransPolyDeformation* ASTransPolyDeformation::GetSelfPointer()
{
	return ms_SelfPointer;
}
// ���������Ƿ�ѡ��
void ASTransPolyDeformation::ResetPolyDataChoosen(QList<int> listChoosenID)
{
	ms_SelfPointer->m_FModelPoly->ResetDataNodeChoosen(listChoosenID);
}
void ASTransPolyDeformation::SetPolyDataChoosen(const int c_DataNodeID, const bool c_Choosen)
{
	// ���������Ƿ�ѡ��
	ms_SelfPointer->m_FModelPoly->SetDataNodeChoosen(c_DataNodeID, c_Choosen);
	// ˢ�¸����ݼӴ���ʾ
	double LineWidth;
	if (c_Choosen)
	{
		LineWidth = LineWidth_Bold;
	} 
	else
	{
		LineWidth = LineWidth_Nomal;
	}
	QList<ASPipelineBase*>* listPipe = new QList<ASPipelineBase*>;
	ASPipelineManager::GetPipelineForDataID(listPipe, c_DataNodeID);
	for (int ncrntPipe = 0; ncrntPipe < listPipe->size(); ncrntPipe++)
	{
		ASPipelineBase* crntPipeLine = listPipe->at(ncrntPipe);
		if (crntPipeLine->isTypeInherited(PipeLineType_PolyImage))
		{
			((ASPipelinePolyImage*)crntPipeLine)->SetLineWidth(LineWidth);
		}
	}
	// ��Ⱦ
	ASVisualizationManager2D::Render();
}
bool ASTransPolyDeformation::ConourPicked(vtkActor* ActorPicked)
{
	// ���������߹���
	for (ASPipelineBase* item = ASPipelineManager::bigen_inherit(PipeLineType_PolyImage); item != nullptr; item = ASPipelineManager::next_inherit(PipeLineType_PolyImage))
	{
		ASPipelinePolyImage* crntPipeline = (ASPipelinePolyImage*)item;
		vtkActor* actor[3];
		crntPipeline->GetActor2D(actor);
		for (int ViewLabel = 0; ViewLabel < 3; ViewLabel++)
		{
			if (actor[ViewLabel] == ActorPicked)
			{
				SetPolyDataChoosen(crntPipeline->getIDOfData(), !ASFModelPolyDeformation::IsPolyChoosen(crntPipeline->getIDOfData()));
				emit ms_SelfPointer->signalChoosnChanged(crntPipeline->getIDOfData());
				return true;
			}
		}
	}
	return false;
}
// ʹ��
void ASTransPolyDeformation::SetEnabled(const bool c_enable)
{
	ms_Enabled = c_enable;
	ASVisualizationManager2D::SetContoursPickable(c_enable);
}
bool ASTransPolyDeformation::GetEnabled()
{
	return ms_Enabled;
}

// ����;)
void ASTransPolyDeformation::PolyDefStart(double* Pos, const int c_ViewLabel, const int c_TransType)
{
	if (c_TransType == PolyDeformation_FFD)
	{
		ms_SelfPointer->m_FModelPoly->StartPolyDeformation(Pos, c_TransType, ASVisualizationManager2D::GetViewableRange(c_ViewLabel));
	}
	else
	{
		ms_SelfPointer->m_FModelPoly->StartPolyDeformation(Pos, c_TransType, 0);
	}
}
void ASTransPolyDeformation::PolyDefContinue(double* Pos, const int c_ViewLabel, const int c_TransType)
{
	// ����任
	ms_SelfPointer->m_FModelPoly->ContinuePolyDeformation(Pos, c_ViewLabel, c_TransType);
	// ���¹���
	// ���������߹���
	for (ASPipelineBase* item = ASPipelineManager::bigen_inherit(PipeLineType_PolyImage); item != nullptr; item = ASPipelineManager::next_inherit(PipeLineType_PolyImage))
	{
		ASPipelinePolyImage* crntPipeline = (ASPipelinePolyImage*)item;
		if (ASFModelPolyDeformation::IsPolyChoosen(crntPipeline->getIDOfData()))
		{
			crntPipeline->UpdataInput();
		}
	}	
	// ��Ⱦ
	ASVisualizationManager::Render();
}
void ASTransPolyDeformation::PolyDefZoom(int InOrOut)
{
	if (InOrOut == 0)
	{
		ms_SelfPointer->m_FModelPoly->StartPolyDeformation(nullptr, PolyDeformation_Zooming, 0);
		ms_SelfPointer->m_FModelPoly->ContinueZoom(1.01, 1.01, 1.01);
	}
	else
	{
		ms_SelfPointer->m_FModelPoly->StartPolyDeformation(nullptr, PolyDeformation_Zooming, 0);
		ms_SelfPointer->m_FModelPoly->ContinueZoom(0.99, 0.99, 0.99);
	}
	// ���¹���
	// ���������߹���
	for (ASPipelineBase* item = ASPipelineManager::bigen_inherit(PipeLineType_PolyImage); item != nullptr; item = ASPipelineManager::next_inherit(PipeLineType_PolyImage))
	{
		ASPipelinePolyImage* crntPipeline = (ASPipelinePolyImage*)item;
		if (ASFModelPolyDeformation::IsPolyChoosen(crntPipeline->getIDOfData()))
		{
			crntPipeline->UpdataInput();
		}
	}
	// ��Ⱦ
	ASVisualizationManager::Render();
}
void ASTransPolyDeformation::PolyDefRotate(int ClockwiseOrCounter, int viewlabel)
{
	if (ClockwiseOrCounter == 1)
	{
		ms_SelfPointer->m_FModelPoly->StartPolyDeformation(nullptr, PolyDeformation_Rotation, 1);
		ms_SelfPointer->m_FModelPoly->ContinueRotation(0.01, viewlabel);
	}
	else
	{
		ms_SelfPointer->m_FModelPoly->StartPolyDeformation(nullptr, PolyDeformation_Rotation, 1);
		ms_SelfPointer->m_FModelPoly->ContinueRotation(-0.01, viewlabel);
	}
	// ���¹���
	// ���������߹���
	for (ASPipelineBase* item = ASPipelineManager::bigen_inherit(PipeLineType_PolyImage); item != nullptr; item = ASPipelineManager::next_inherit(PipeLineType_PolyImage))
	{
		ASPipelinePolyImage* crntPipeline = (ASPipelinePolyImage*)item;
		if (ASFModelPolyDeformation::IsPolyChoosen(crntPipeline->getIDOfData()))
		{
			crntPipeline->UpdataInput();
		}
	}
	// ��Ⱦ
	ASVisualizationManager::Render();
}
void ASTransPolyDeformation::PolyDefWheelFFD(int ForwardOrBackward)
{
	if (ms_SelfPointer->m_FModelPoly->GetCurrentTransType() != PolyDeformation_FFD)
	{
		return;
	}

	ms_SelfPointer->m_FModelPoly->FFDRadiusChange(ForwardOrBackward);
	// ���¹���
	// ���������߹���
	for (ASPipelineBase* item = ASPipelineManager::bigen_inherit(PipeLineType_PolyImage); item != nullptr; item = ASPipelineManager::next_inherit(PipeLineType_PolyImage))
	{
		ASPipelinePolyImage* crntPipeline = (ASPipelinePolyImage*)item;
		if (ASFModelPolyDeformation::IsPolyChoosen(crntPipeline->getIDOfData()))
		{
			crntPipeline->UpdataInput();
		}
	}
	// ��Ⱦ
	ASVisualizationManager::Render();
}
void ASTransPolyDeformation::PolyDefUndo()
{
	ms_SelfPointer->m_FModelPoly->UndoDef();
	// ���¹���
	// ���������߹���
	for (ASPipelineBase* item = ASPipelineManager::bigen_inherit(PipeLineType_PolyImage); item != nullptr; item = ASPipelineManager::next_inherit(PipeLineType_PolyImage))
	{
		ASPipelinePolyImage* crntPipeline = (ASPipelinePolyImage*)item;
		if (ASFModelPolyDeformation::IsPolyChoosen(crntPipeline->getIDOfData()))
		{
			crntPipeline->UpdataInput();
		}
	}
	// ��Ⱦ
	ASVisualizationManager::Render();
}
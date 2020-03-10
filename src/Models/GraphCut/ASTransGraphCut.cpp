#include "ASTransGraphCut.h"
#include "ASArrayImageData.h"
#include "ASPolyImageData.h"
#include "ASAbstractData.h"
#include "ASSeedData.h"
#include "ASFModelGraphCut.h"
#include "ASFModelMask.h"
#include "ASDataStructureWalker.h"
#include "ASTransAddDeleteData.h"
#include "ASMainWidget.h"
#include "ASFModelGraphCut.h"
#include "ASPipelineBase.h"
#include "ASPipelineManager.h"
#include "ASPipelineArrayImage.h"
#include "ASPipelinePolyImage.h"
#include "ASVisualizationManager.h"
#include "ASDataTree.h"
#include <vtkImageData.h>
#include <QMessageBox>

ASTransGraphCut* ASTransGraphCut::ms_Selfpointer = nullptr;

ASTransGraphCut::ASTransGraphCut(QObject *parent)
	: ASTransmissionBase(parent)
{
	ms_Selfpointer = this;
	m_FModelGraphCut = new ASFModelGraphCut();
}

ASTransGraphCut::~ASTransGraphCut()
{

}

// Ψһ����
ASTransGraphCut* ASTransGraphCut::GetSelfPointer()
{
	return ms_Selfpointer;
}
// Marching cubs
void ASTransGraphCut::SetMarchingCubs(const bool c_Marching, int c_SmoothIterations)
{
	ms_Selfpointer->m_NeedMarchingCubs = c_Marching;
	ms_Selfpointer->m_SmoothIterations = c_SmoothIterations;
}
// ����Graph Cut����
void ASTransGraphCut::GraphCutGenerate(const int c_ImageDataID, const QList<int> SeedsID,
	const QString c_OutputName, const double c_Lambda, const double c_Delta,
	const int c_nNeighbor, const QString c_PostProcessing, const bool c_bQuery)
{
	ms_Selfpointer->m_SeedsID = SeedsID;
	// 1 ����ͼ��
	ASAbstractData* InputImageDataNode = ASAbstractData::getDataNodeFromID(c_ImageDataID);
	if (InputImageDataNode->isTypeInherited(DataType_ArrayImageData) == false)
	{
		return;
	}
	// 2 ���ӵ�
	int numOfSeeds = SeedsID.size();
	for (int i = 0; i < numOfSeeds; i++)
	{
		ASAbstractData* InputSeed = ASAbstractData::getDataNodeFromID(SeedsID.at(i));
		if (InputSeed->isTypeInherited(DataType_SeedData) == false)
		{
			return;
		}
	}
	// 3 ���
	ASArrayImageData* OutputDataNode;
	int OutputDataID = -1;
	for (ASAbstractData* item = ASDataStructureWalker::bigen_inherit(DataType_ArrayImageData); item != nullptr; item = ASDataStructureWalker::next_inherit(DataType_ArrayImageData))
	{
		ASArrayImageData* crntDataNode = (ASArrayImageData*)item;
		if (crntDataNode->getName() == c_OutputName)
		{
			OutputDataID = crntDataNode->getDataNodeID();
		}
	}
	if (OutputDataID == -1)
	{
		// �½�����
		QMessageBox message(QMessageBox::NoIcon, "Anatomy Sketch", tr("Create new file?"), QMessageBox::Yes | QMessageBox::No, NULL);
		if (message.exec() == QMessageBox::No)
		{
			return;
		}
		OutputDataNode = new ASArrayImageData();
		OutputDataNode->setName(c_OutputName);
		OutputDataNode->setShown(true);
		OutputDataNode->setVoidNode(true);
		ASDataTree::NewDataNode(OutputDataNode, ASAbstractData::getDataNodeFromID(c_ImageDataID)); // �����ݼ���������
		ASTransAddDeleteData::UpdateListsAfterAddDelete(DataType_AbstractData);
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
	} 
	else
	{
		OutputDataNode = (ASArrayImageData*)ASAbstractData::getDataNodeFromID(OutputDataID);
		if (OutputDataNode->isTypeInherited(DataType_ArrayImageData) == false)
		{
			return;
		}
		// ��������
		if (c_bQuery == false)
		{
			QMessageBox message(QMessageBox::NoIcon, "Anatomy Sketch", tr("Overwrite the file?"), QMessageBox::Yes | QMessageBox::No, NULL);
			if (message.exec() == QMessageBox::No)
			{
				return;
			}
		}
	}

	// 5 ʵ������ģ�鿪ʼ����
	// 5.1 �������ȶԻ���
	ms_Selfpointer->m_ProgressDialog = new QProgressDialog(tr("Calculating..."), tr("Cancel"), 0, 100, ASMainWidget::GetMainWidget());
	ms_Selfpointer->m_ProgressDialog->setWindowTitle("Anatomy Sketch");
	ms_Selfpointer->m_ProgressDialog->setWindowModality(Qt::WindowModal); // ģ̬�Ի���
	ms_Selfpointer->m_ProgressDialog->show();
	//connect(ms_Selfpointer->m_ProgressDialog, SIGNAL(buttonClicked(QAbstractButton*)), ms_Selfpointer, SLOT(slotLoadDataStopManualy(QAbstractButton*)));

	// 5.2 ����ģ��
	ms_Selfpointer->m_FModelGraphCut->SetInputData((ASArrayImageData*)InputImageDataNode);
	ms_Selfpointer->m_FModelGraphCut->SetSeedsID(SeedsID);
	ms_Selfpointer->m_FModelGraphCut->SetOutputImage(OutputDataNode);
	ms_Selfpointer->m_FModelGraphCut->SetParameter(c_Lambda, c_Delta, c_nNeighbor);
	ms_Selfpointer->m_FModelGraphCut->SetPostProcessing(c_PostProcessing);
	ms_Selfpointer->m_FModelGraphCut->GraphCutsStart();
}
// Graph cuts �������
void ASTransGraphCut::GraphCutsFinished(ASArrayImageData* DataNode)
{
	// 1 ����GraphCuts��ʾ
	if (DataNode->isVoidNode())
	{
		DataNode->DataInitAfterLoad();
		ASVisualizationManager::ResetDisplayExtent();
		ASVisualizationManager::ResetTopArrayImage();
		// 2 �����¹���
		ASTransAddDeleteData::AddNewPipeline(DataNode, DataType_ArrayImageData);
		DataNode->setVoidNode(false);
	}
	else
	{
		ASVisualizationManager::ResetDisplayExtent();
		ASVisualizationManager::ResetTopArrayImage();
		QList<ASPipelineBase*>* listPipe = new QList<ASPipelineBase*>;
		ASPipelineManager::GetPipelineForDataID(listPipe, DataNode->getDataNodeID());
		for (int ncrntPipe = 0; ncrntPipe < listPipe->size(); ncrntPipe++)
		{
			if (listPipe->at(ncrntPipe)->isTypeInherited(PipeLineType_ArrayImage))
			{
				ASPipelineArrayImage* crntPipe = static_cast<ASPipelineArrayImage*>(listPipe->at(ncrntPipe));
				crntPipe->SetInputData(DataNode->getArrayImageData());
				crntPipe->UpdataInputData(ASVisualizationManager::GetDisplayFrame());
			}
		}
	}
	// 2 Marching cubs
	if (ms_Selfpointer->m_NeedMarchingCubs)
	{
		QList<ASPolyImageData*>* listMarchingOutput = new QList<ASPolyImageData*>;
		ms_Selfpointer->m_FModelGraphCut->MarchingCubs(DataNode, listMarchingOutput, 
			ms_Selfpointer->m_SeedsID, ms_Selfpointer->m_SmoothIterations);
		for (int ncrntPoly = 0; ncrntPoly < listMarchingOutput->size(); ncrntPoly++)
		{
			ASPolyImageData* crntPoly = listMarchingOutput->at(ncrntPoly);
			if (crntPoly->isVoidNode())
			{
				crntPoly->DataInitAfterLoad();
				ASVisualizationManager::ResetDisplayExtent();
				// �����¹���
				ASTransAddDeleteData::AddNewPipeline(crntPoly, DataType_PolyImageData);
				crntPoly->setVoidNode(false);
			} 
			else
			{
				ASVisualizationManager::ResetDisplayExtent();
				QList<ASPipelineBase*>* listPipe = new QList<ASPipelineBase*>;
				ASPipelineManager::GetPipelineForDataID(listPipe, crntPoly->getDataNodeID());
				for (int ncrntPipe = 0; ncrntPipe < listPipe->size(); ncrntPipe++)
				{
					if (listPipe->at(ncrntPipe)->isTypeInherited(PipeLineType_PolyImage))
					{
						ASPipelinePolyImage* crntPipe = static_cast<ASPipelinePolyImage*>(listPipe->at(ncrntPipe));
						crntPipe->SetInputData(crntPoly->getPolyImageData());
						crntPipe->UpdataInput();
					}
				}
			}
		}
		delete listMarchingOutput;
	}
	ASVisualizationManager::Render();
	delete ms_Selfpointer->m_ProgressDialog;
	ms_Selfpointer->m_ProgressDialog = nullptr;

}
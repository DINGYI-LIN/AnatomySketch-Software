#include "ASPipelineLandmark.h"
#include "ASVisualizationManager2D.h"
#include "ASVisualizationManager.h"
#include "ASDataStructureWalker.h"
#include "ASLandmarkData.h"
#include "ASTransGeneralInteractor.h"
#include "vtkProperty.h"
#include <vtkProp.h>
#include <vtkCoordinate.h>

ASPipelineLandmark::ASPipelineLandmark(const int c_ID) : ASPipelineBase(c_ID)
{
	m_PipelineType = PipeLineType_Landmark;
	m_plistLandmarkPipelines = new QList<structLandmarkPipeline*>;
	// Renderer
	ASVisualizationManager2D::GetRenderer2D(m_pRenderer2D);
}

ASPipelineLandmark::~ASPipelineLandmark()
{

}

// ���������ж�
bool ASPipelineLandmark::isTypeInherited(const int c_Type)
{
	if (c_Type == PipeLineType_Landmark || ASPipelineBase::isTypeInherited(c_Type))
	{
		return true;
	}
	return false;
}
bool ASPipelineLandmark::isTypeAbsolute(const int c_Type)
{
	if (c_Type == PipeLineType_Landmark)
	{
		return true;
	}
	return false;
}

// �麯��
// ���ô˺������ͷŹ���
void ASPipelineLandmark::DeleteNode()
{

}
// ��ͼ����ı�
void ASPipelineLandmark::Update2DTransformMatrix()
{
	RefreshLandmarkDisplay(0);
	RefreshLandmarkDisplay(1);
	RefreshLandmarkDisplay(2);
}
void ASPipelineLandmark::SetShown(const bool c_Shown)
{
	m_isShown = c_Shown;
	RefreshLandmarkDisplay(0);
	RefreshLandmarkDisplay(1);
	RefreshLandmarkDisplay(2);
}

// ˢ��������������ʾ
void ASPipelineLandmark::RefreshLandmarkDisplay(const int c_ViewLabel)
{
	// ��ո÷����ԭ��������ʾ
	for (int ncrntLandmark = 0; ncrntLandmark < m_plistLandmarkPipelines->size();)
	{
		structLandmarkPipeline* crntPipeline = m_plistLandmarkPipelines->at(ncrntLandmark);
		if (crntPipeline->ViewLabel == c_ViewLabel)
		{
			vtkSmartPointer<vtkPropCollection> PropCollection = vtkSmartPointer<vtkPropCollection>::New();
			crntPipeline->SphereHandleRep->GetActors(PropCollection);
			PropCollection->InitTraversal();
			vtkProp* prop = PropCollection->GetNextProp();
			m_pRenderer2D[crntPipeline->ViewLabel]->RemoveActor(prop);
			ASTransGeneralInteractor::DeleteHoverInfor(static_cast<vtkActor*>(prop));
			crntPipeline->SphereHandleRep->Delete();

			m_plistLandmarkPipelines->removeOne(crntPipeline);
			delete(crntPipeline);
		}
		else
		{
			ncrntLandmark++;
		}
	}
	if (m_isShown == false)
	{
		return;
	}

	//���㵱ǰ��ķ�Χ���Ը÷�Χ�����ݽ�����ʾ
	double ImagePosition[3];
	ASVisualizationManager::GetDisplayPosition(ImagePosition);
	double ImageSpacing[3];
	ASVisualizationManager::GetDisplaySpacing(ImageSpacing);
	double layermin = ImagePosition[c_ViewLabel] - 0.5 * ImageSpacing[c_ViewLabel];
	double layermax = ImagePosition[c_ViewLabel] + 0.5 * ImageSpacing[c_ViewLabel];
	vtkSmartPointer<vtkMatrix4x4> pMatrix[3];
	vtkSmartPointer<vtkMatrix4x4> pMatrixToZero[3];
	vtkSmartPointer<vtkMatrix4x4> pMatrixToOne[3];
	ASVisualizationManager2D::GetTransformMatrix4x4(pMatrix, pMatrixToZero, pMatrixToOne);

	// �������б궨������
	for (ASAbstractData* item = ASDataStructureWalker::bigen_inherit(DataType_LandmarkData); 
		item != nullptr; item = ASDataStructureWalker::next_inherit(DataType_LandmarkData))
	{
		ASLandmarkData* crntDataNode = static_cast<ASLandmarkData*>(item);
		// �����궨��
		int NumOfLandmark = crntDataNode->GetNumberOfLandmark();
		for (int ncrntLandmark = 0; ncrntLandmark < NumOfLandmark; ncrntLandmark++)
		{
			structLandmark* crntLandmark = crntDataNode->GetLandmarkAt(ncrntLandmark);
			// �жϸñ궨���Ƿ��ڵ�ǰ����
			if (crntLandmark->dPosition[c_ViewLabel] >= layermin && crntLandmark->dPosition[c_ViewLabel] < layermax)
			{
				// �����¹���
				structLandmarkPipeline* crntPipeline = new structLandmarkPipeline;
				crntPipeline->LandmarkDataID = crntDataNode->getDataNodeID();
				crntPipeline->LandmarkPointID = crntLandmark->LandmarkID;
				crntPipeline->qsName = crntLandmark->qsName;
				crntPipeline->ViewLabel = c_ViewLabel;
				crntPipeline->qColor = crntLandmark->color;
				// �任����
				vtkSmartPointer<vtkMatrix4x4> pactMatrixToOne = vtkSmartPointer<vtkMatrix4x4>::New();
				pactMatrixToOne->DeepCopy(pMatrixToOne[c_ViewLabel]);
				
				crntPipeline->SphereHandleRep = vtkSphereHandleRepresentation::New();
				double posTransInput[4];
				posTransInput[0] = crntLandmark->dPosition[0];
				posTransInput[1] = crntLandmark->dPosition[1];
				posTransInput[2] = crntLandmark->dPosition[2];
				posTransInput[3] = 1;
				double posDisplay[4];
				pactMatrixToOne->MultiplyPoint(posTransInput, posDisplay);
				crntPipeline->SphereHandleRep->SetWorldPosition(posDisplay);
				crntPipeline->SphereHandleRep->SetSphereRadius(m_HandleRadius[c_ViewLabel]);
				crntPipeline->SphereHandleRep->SetPickable(true);
				// vtkActor
				vtkSmartPointer<vtkPropCollection> PropCollection = vtkSmartPointer<vtkPropCollection>::New();
				crntPipeline->SphereHandleRep->GetActors(PropCollection);
				PropCollection->InitTraversal();
				vtkActor* actor = (vtkActor*)(PropCollection->GetNextProp());
				if (crntDataNode->isShown())
				{
					m_pRenderer2D[crntPipeline->ViewLabel]->AddActor(actor);
					ASTransGeneralInteractor::AddHoverInfor(actor, crntLandmark->qsName);
					actor->SetPickable(true);
					double color[3];
					color[0] = ((double)crntPipeline->qColor.red()) / 255;
					color[1] = ((double)crntPipeline->qColor.green()) / 255;
					color[2] = ((double)crntPipeline->qColor.blue()) / 255;
					actor->GetProperty()->SetColor(color);
				}
				m_plistLandmarkPipelines->append(crntPipeline);
			}
		}
	}
}

// ���ÿ��Ƶ�ֱ��
void ASPipelineLandmark::ReSetCtrlRadius(const int c_ViewLabel)
{
	m_HandleRadius[c_ViewLabel] = this->GetCtrlPointRadiusSplineContour(c_ViewLabel);
	if (m_HandleRadius[c_ViewLabel] > 0)
	{
		for (int ncrntPipeline = 0; ncrntPipeline < m_plistLandmarkPipelines->size(); ncrntPipeline++)
		{
			structLandmarkPipeline* crntPipeline = m_plistLandmarkPipelines->at(ncrntPipeline);
			if (crntPipeline->ViewLabel == c_ViewLabel)
			{
				crntPipeline->SphereHandleRep->SetSphereRadius(m_HandleRadius[c_ViewLabel]);
			}
		}
	}
	else
	{
		m_HandleRadius[c_ViewLabel] = 1;
	}
}
// ����actor��ַ��ѯ���Ƶ���Ϣ
bool ASPipelineLandmark::ReserchLanmark(vtkActor* pActor, int* LandmarkDataID, int* ViewLabel, int* LandmarkPointID)
{
	// ����landmark
	for (int ncrntLandmark = 0; ncrntLandmark < m_plistLandmarkPipelines->size(); ncrntLandmark++)
	{
		structLandmarkPipeline* crntPipeline = m_plistLandmarkPipelines->at(ncrntLandmark);
		vtkSmartPointer<vtkPropCollection> PropCollection = vtkSmartPointer<vtkPropCollection>::New();
		crntPipeline->SphereHandleRep->GetActors(PropCollection);
		PropCollection->InitTraversal();
		vtkActor* actor = (vtkActor*)(PropCollection->GetNextProp());
		if (actor == pActor)
		{
			*LandmarkDataID = crntPipeline->LandmarkDataID;
			*ViewLabel = crntPipeline->ViewLabel;
			*LandmarkPointID = crntPipeline->LandmarkPointID;
			return true;
		}
	}
	return false;
}
// ���Ƶ�뾶
double ASPipelineLandmark::GetCtrlPointRadiusSplineContour(const int c_viewLabel)
{
	return ASVisualizationManager::GetZoomPara(c_viewLabel) / LANDMARKRADIUS;
}
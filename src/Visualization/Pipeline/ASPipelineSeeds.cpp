#include "ASPipelineSeeds.h"
#include "ASVisualizationManager2D.h"
#include "ASVisualizationManager3D.h"
#include "ASVisualizationManager.h"
#include "ASDataStructureWalker.h"
#include "ASAbstractData.h"
#include "ASSeedData.h"
#include "GlobelDeclaration.h"
#include "ASFModelSeeds.h"
#include "ASTransSeeds.h"
#include <QColor>
#include <vtkImageProperty.h>
#include <vtkImageIterator.h>

ASPipelineSeeds* ASPipelineSeeds::ms_PipelineSeeds = nullptr;

ASPipelineSeeds::ASPipelineSeeds(const int c_ID) : ASPipelineBase(c_ID)
{
	m_PipelineType = PipeLineType_Seeds;
	ms_PipelineSeeds = this;

	// ���߳�ʼ��
	for (int ViewLabel = 0; ViewLabel < 3; ViewLabel++)
	{
		// vtkImageData
		m_ImageData[ViewLabel] = vtkSmartPointer<vtkImageData>::New();
		//vtkImageActor
		m_ImageActor[ViewLabel] = vtkSmartPointer<vtkImageActor>::New();
		m_ImageActor[ViewLabel]->SetInputData(m_ImageData[ViewLabel]);
		m_ImageActor[ViewLabel]->GetProperty()->SetLayerNumber(Layer_SeedsModel);
	}
	//ImageStack
	ASVisualizationManager2D::GetImageStack2D(m_pImageStack2D);
	ASVisualizationManager3D::GetImageStack3D(m_pImageStack3D);

	this->Update2DTransformMatrix();
}

ASPipelineSeeds::~ASPipelineSeeds()
{

}

// ���������ж�
bool ASPipelineSeeds::isTypeInherited(const int c_Type)
{
	if (c_Type == PipeLineType_Seeds || ASPipelineBase::isTypeInherited(c_Type))
	{
		return true;
	}
	return false;
}
bool ASPipelineSeeds::isTypeAbsolute(const int c_Type)
{
	if (c_Type == PipeLineType_Seeds)
	{
		return true;
	}
	return false;
}

// �麯������ͼ����ı�
void ASPipelineSeeds::DeleteNode()
{
	// �ͷ�����ʱ�����ͷ������߹���
	// delete this;	
}
void ASPipelineSeeds::Update2DTransformMatrix()
{
	if (m_isShown == false)
	{
		return;
	}
	// ��ʾ������Ϣ
	ASVisualizationManager::GetDisplayExtent(m_ImageExtent);	
	ASVisualizationManager::GetDisplaySpacing(m_ImageSpacing);	
	ASVisualizationManager::GetDisplayPosition(m_ImagePosition);
	//ͼ����������ϵ�ߴ�
	m_ExtentofPixelInPainting[0] = (m_ImageExtent[1] - m_ImageExtent[0]) / m_ImageSpacing[0];
	m_ExtentofPixelInPainting[1] = (m_ImageExtent[3] - m_ImageExtent[2]) / m_ImageSpacing[1];
	m_ExtentofPixelInPainting[2] = (m_ImageExtent[5] - m_ImageExtent[4]) / m_ImageSpacing[2];
	// �任����
	ASVisualizationManager2D::GetTransformMatrix4x4(m_pMatrix, m_pMatrixToZero, m_pMatrixToOne);
	// ���¹���
	this->UpdataDisplayPosition(ViewLabel_Sagittal);
	this->UpdataDisplayPosition(ViewLabel_Coronal);
	this->UpdataDisplayPosition(ViewLabel_Axial);
}
// �Ƿ���ʾ
void ASPipelineSeeds::SetShown(const bool c_Shown)
{
	m_isShown = c_Shown;
	if (m_isShown)
	{
		Update2DTransformMatrix();
	} 
	else
	{
		for (int ViewLabel = 0; ViewLabel < 3; ViewLabel++)
		{
			// ��ƽ����û�����ӵ���Ҫ��ʾ
			m_pImageStack2D[ViewLabel]->RemoveImage(m_ImageActor[ViewLabel]);
			m_pImageStack3D[ViewLabel]->RemoveImage(m_ImageActor[ViewLabel]);
		}
	}
}
// �ڻ���ʱ������һ���������ʾ
void ASPipelineSeeds::AddOnePointDisplay(double* pPositon)
{
	if (m_isShown == false)
	{
		return;
	}
	ASSeedData* crntData = ASTransSeeds::GetCurrentSeedData();
	int crntSeedsID = ASTransSeeds::GetCrntSeedsID();
	structSeeds* crntSeeds = crntData->getSeedsFromID(crntSeedsID);	
	unsigned char r = crntSeeds->color.red();
	unsigned char g = crntSeeds->color.green();
	unsigned char b = crntSeeds->color.blue();
	for (int ViewLabel = 0; ViewLabel < 3; ViewLabel++)
	{
		int* crntExtent = m_ImageData[ViewLabel]->GetExtent();
		// 0 �жϲ��淶Χ
		double min = m_ImagePosition[ViewLabel] - (0.5 * m_ImageSpacing[ViewLabel]);
		double max = m_ImagePosition[ViewLabel] + (0.5 * m_ImageSpacing[ViewLabel]);
		if (pPositon[ViewLabel] >= min && pPositon[ViewLabel] < max)
		{
			//�ҵ���Ҫ��ʾ�ıʻ�
			if (m_bHaveObj[ViewLabel] == false)
			{
				m_bHaveObj[ViewLabel] = true;
				this->InitImageData(ViewLabel);
			}
			double input[4];
			double output[4];
			input[0] = pPositon[0];
			input[1] = pPositon[1];
			input[2] = pPositon[2];
			input[3] = 1;
			m_pMatrixToZero[ViewLabel]->MultiplyPoint(input, output);
			int x, y;
			switch (ViewLabel)
			{
			case ViewLabel_Sagittal:
			{
				x = (output[0] - m_ImageExtent[2]) / m_ImageSpacing[1];
				y = (output[1] - m_ImageExtent[4]) / m_ImageSpacing[2];
				break;
			}
			case ViewLabel_Coronal:
			{
				x = (output[0] - m_ImageExtent[0]) / m_ImageSpacing[0];
				y = (output[1] - m_ImageExtent[4]) / m_ImageSpacing[2];
				break;
			}
			case ViewLabel_Axial:
			{
				x = (output[0] - m_ImageExtent[0]) / m_ImageSpacing[0];
				y = (output[1] + m_ImageExtent[3]) / m_ImageSpacing[1];		// !!!������������任����//	�����������y��
				break;
			}
			default:
				break;
			}
			if (x < crntExtent[0] || x > crntExtent[1] || y < crntExtent[2] || y > crntExtent[3])
			{
				continue;
			}
			m_ImageData[ViewLabel]->SetScalarComponentFromDouble(x, y, 0, 0, r);
			m_ImageData[ViewLabel]->SetScalarComponentFromDouble(x, y, 0, 1, g);
			m_ImageData[ViewLabel]->SetScalarComponentFromDouble(x, y, 0, 2, b);
			m_ImageData[ViewLabel]->SetScalarComponentFromDouble(x, y, 0, 3, 255);
			m_ImageData[ViewLabel]->Modified();
			m_ImageActor[ViewLabel]->Update();
		}
		if (m_bHaveObj[ViewLabel])
		{
			// ��ƽ���������ӵ���Ҫ��ʾ
			m_pImageStack2D[ViewLabel]->AddImage(m_ImageActor[ViewLabel]);
			m_pImageStack3D[ViewLabel]->AddImage(m_ImageActor[ViewLabel]);
		}
		else
		{
			// ��ƽ����û�����ӵ���Ҫ��ʾ
			m_pImageStack2D[ViewLabel]->RemoveImage(m_ImageActor[ViewLabel]);
			m_pImageStack3D[ViewLabel]->RemoveImage(m_ImageActor[ViewLabel]);
		}
	}
}
// ����ĳ��ͼ����ʾ
void ASPipelineSeeds::UpdataDisplayPosition(const int c_ViewLabel)
{
	// 0 �жϲ��淶Χ
	double min = m_ImagePosition[c_ViewLabel] - (0.5 * m_ImageSpacing[c_ViewLabel]);
	double max = m_ImagePosition[c_ViewLabel] + (0.5 * m_ImageSpacing[c_ViewLabel]);
	// 1 �ò��Ƿ������ӵ�
	m_bHaveObj[c_ViewLabel] = false;
	// 2 �������ӵ�����ASSeedsData
	for (ASAbstractData* item = ASDataStructureWalker::bigen_single(DataType_SeedData); item != nullptr; item = ASDataStructureWalker::next_single(DataType_SeedData))
	{
		ASSeedData* crntDataNode = (ASSeedData*)item;
		int* crntExtent = m_ImageData[c_ViewLabel]->GetExtent();
		if (crntDataNode->isShown() == false)
		{
			continue;
		}
		int numOfSeeds = crntDataNode->getNumberOfSeeds();
		for (int ncrntSeed = 0; ncrntSeed < numOfSeeds; ncrntSeed++)
		{
			structSeeds* cnrtSeed = crntDataNode->getSeedsAt(ncrntSeed);
			if (cnrtSeed->isShown == false)
			{
				continue;
			}
			int label = cnrtSeed->label;
			unsigned char r = cnrtSeed->color.red();
			unsigned char g = cnrtSeed->color.green();
			unsigned char b = cnrtSeed->color.blue();
			// �ʻ�����
			int numOfLines = cnrtSeed->pListSeedsData->size();
			for (int ncrntLine = 0; ncrntLine < numOfLines; ncrntLine++)
			{
				structLine* crntLine = cnrtSeed->pListSeedsData->at(ncrntLine);
				if (crntLine->ViewLabel == c_ViewLabel)	//ƽ���ڵ�ǰ����
				{
					if (crntLine->dLayer >= min && crntLine->dLayer < max)
					{
						//�ҵ���Ҫ��ʾ�ıʻ�
						if (m_bHaveObj[c_ViewLabel] == false)
						{
							m_bHaveObj[c_ViewLabel] = true;
							this->InitImageData(c_ViewLabel);
						}
						int numOfPoints = crntLine->pvectorPoint.size();
						//����ĳһ�������ϵ����е�
						for (int ncrntPoint = 0; ncrntPoint < numOfPoints; ncrntPoint++)
						{
							structPoint* crntpoint = crntLine->pvectorPoint.at(ncrntPoint);
							double input[4];
							double output[4];
							input[0] = crntpoint->dX;
							input[1] = crntpoint->dY;
							input[2] = crntpoint->dZ;
							input[3] = 1;
							m_pMatrixToZero[c_ViewLabel]->MultiplyPoint(input, output);
							int x, y;
							switch (c_ViewLabel)
							{
							case ViewLabel_Sagittal:
							{
								x = (output[0] - m_ImageExtent[2]) / m_ImageSpacing[1];
								y = (output[1] - m_ImageExtent[4]) / m_ImageSpacing[2];
								break;
							}
							case ViewLabel_Coronal:
							{
								x = (output[0] - m_ImageExtent[0]) / m_ImageSpacing[0];
								y = (output[1] - m_ImageExtent[4]) / m_ImageSpacing[2];
								break;
							}
							case ViewLabel_Axial:
							{
								x = (output[0] - m_ImageExtent[0]) / m_ImageSpacing[0];
								y = (output[1] + m_ImageExtent[3]) / m_ImageSpacing[1];		// !!!������������任����//	�����������y��
								break;
							}
							default:
								break;
							}
							if (x < crntExtent[0] || x > crntExtent[1] || y < crntExtent[2] || y > crntExtent[3])
							{
								continue;
							}
							m_ImageData[c_ViewLabel]->SetScalarComponentFromDouble(x, y, 0, 0, r);
							m_ImageData[c_ViewLabel]->SetScalarComponentFromDouble(x, y, 0, 1, g);
							m_ImageData[c_ViewLabel]->SetScalarComponentFromDouble(x, y, 0, 2, b);
							m_ImageData[c_ViewLabel]->SetScalarComponentFromDouble(x, y, 0, 3, 255);
						}
					}
				}
				else									//��ֱ�ڵ�ǰ����
				{
					int numOfPoints = crntLine->pvectorPoint.size();
					//�����õ����ϵ����е�
					for (int ncrntPoint = 0; ncrntPoint < numOfPoints; ncrntPoint++)
					{
						structPoint* crntpoint = crntLine->pvectorPoint.at(ncrntPoint);
						double input[4];
						input[0] = crntpoint->dX;
						input[1] = crntpoint->dY;
						input[2] = crntpoint->dZ;
						input[3] = 1;
						if (input[c_ViewLabel] >= min && input[c_ViewLabel] < max)
						{
							//�ҵ���Ҫ��ʾ�ıʻ�
							if (m_bHaveObj[c_ViewLabel] == false)
							{
								m_bHaveObj[c_ViewLabel] = true;
								this->InitImageData(c_ViewLabel);
							}
							//�ҵ�ǡ���ڸ�ƽ��ĵ㣬��Ҫ��ʾ
							double output[4];
							m_pMatrixToZero[c_ViewLabel]->MultiplyPoint(input, output);
							int x, y;
							switch (c_ViewLabel)
							{
							case ViewLabel_Sagittal:
							{
								x = (output[0] - m_ImageExtent[2]) / m_ImageSpacing[1];
								y = (output[1] - m_ImageExtent[4]) / m_ImageSpacing[2];
								break;
							}
							case ViewLabel_Coronal:
							{
								x = (output[0] - m_ImageExtent[0]) / m_ImageSpacing[0];
								y = (output[1] - m_ImageExtent[4]) / m_ImageSpacing[2];
								break;
							}
							case ViewLabel_Axial:
							{
								x = (output[0] - m_ImageExtent[0]) / m_ImageSpacing[0];
								y = (output[1] + m_ImageExtent[3]) / m_ImageSpacing[1];		// !!!������������任����//	�����������y��
								break;
							}
							default:
								break;
							}
							if (x < crntExtent[0] || x > crntExtent[1] || y < crntExtent[2] || y > crntExtent[3])
							{
								continue;
							}
							m_ImageData[c_ViewLabel]->SetScalarComponentFromDouble(x, y, 0, 0, r);
							m_ImageData[c_ViewLabel]->SetScalarComponentFromDouble(x, y, 0, 1, g);
							m_ImageData[c_ViewLabel]->SetScalarComponentFromDouble(x, y, 0, 2, b);
							m_ImageData[c_ViewLabel]->SetScalarComponentFromDouble(x, y, 0, 3, 255);
						}
					}
				}
			}
		}
	}

	if (m_bHaveObj[c_ViewLabel])
	{
		// ��ƽ���������ӵ���Ҫ��ʾ
		m_pImageStack2D[c_ViewLabel]->AddImage(m_ImageActor[c_ViewLabel]);
		m_pImageStack3D[c_ViewLabel]->AddImage(m_ImageActor[c_ViewLabel]);
	} 
	else
	{
		// ��ƽ����û�����ӵ���Ҫ��ʾ
		m_pImageStack2D[c_ViewLabel]->RemoveImage(m_ImageActor[c_ViewLabel]);
		m_pImageStack3D[c_ViewLabel]->RemoveImage(m_ImageActor[c_ViewLabel]);
	}
}
// ��ʼ��ĳ�����vtkImageData
void ASPipelineSeeds::InitImageData(const int c_ViewLabel)
{
	switch (c_ViewLabel)
	{
	case ViewLabel_Sagittal:
		m_ImageData[c_ViewLabel]->SetExtent(0, m_ExtentofPixelInPainting[1], 0, m_ExtentofPixelInPainting[2], 0, 0);
		m_ImageData[c_ViewLabel]->SetSpacing(m_ImageSpacing[1], m_ImageSpacing[2], 1);
		m_ImageData[c_ViewLabel]->SetOrigin(m_ImageExtent[2] + 1, m_ImageExtent[4], 0);
		break;
	case ViewLabel_Coronal:
		m_ImageData[c_ViewLabel]->SetExtent(0, m_ExtentofPixelInPainting[0], 0, m_ExtentofPixelInPainting[2], 0, 0);
		m_ImageData[c_ViewLabel]->SetSpacing(m_ImageSpacing[0], m_ImageSpacing[2], 1);
		m_ImageData[c_ViewLabel]->SetOrigin(m_ImageExtent[0], m_ImageExtent[4], 0);
		break;
	case ViewLabel_Axial:
		m_ImageData[c_ViewLabel]->SetExtent(0, m_ExtentofPixelInPainting[0], 0, m_ExtentofPixelInPainting[1], 0, 0);
		m_ImageData[c_ViewLabel]->SetSpacing(m_ImageSpacing[0], m_ImageSpacing[1], 1);
		m_ImageData[c_ViewLabel]->SetOrigin(m_ImageExtent[0], -m_ImageExtent[3] + 1, 0);
		break;
	default:
		break;
	}
	m_ImageData[c_ViewLabel]->AllocateScalars(VTK_UNSIGNED_CHAR, 4);
	// ʹ�õ�������Ԫ�����ʼ��Ϊ1
	vtkImageIterator<unsigned char> it(m_ImageData[c_ViewLabel], m_ImageData[c_ViewLabel]->GetExtent());
	while (!it.IsAtEnd())
	{
		unsigned char *inSI = it.BeginSpan();
		unsigned char *inSIEnd = it.EndSpan();
		while (inSI != inSIEnd)
		{
			*inSI = 0;
			++inSI;
		}
		it.NextSpan();
	}
}
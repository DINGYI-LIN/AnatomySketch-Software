#include "ASFModelSeeds.h"
#include "ASPipelineSeeds.h"
#include "ASPipelineManager.h"
#include "ASAbstractData.h"
#include "ASSeedData.h"
#include "ASDataTree.h"
#include "ASTransDataGeneral.h"
#include "ASArrayImageData.h"
#include "ASTransSeeds.h"
#include "ASMainWidget.h"
#include "ASAnnotation.h"
#include "ASAbstractData.h"
#include <QMessageBox>
#include <QSet>

ASFModelSeeds* ASFModelSeeds::ms_FModelSeeds = nullptr;

ASFModelSeeds::ASFModelSeeds(QObject *parent)
	: ASFunctionModelBase(parent)
{
	ms_FModelSeeds = this;
	m_SeedModelEnabled = false;

	m_OperationSequence = new QList<int>;
}

ASFModelSeeds::~ASFModelSeeds()
{

}

// ��ǰ���Ƶ����ӵ��ID
void ASFModelSeeds::SetIDOfPaintingData(const int c_ID)
{
	ms_FModelSeeds->m_IDOfPaintingData = c_ID;
}
int ASFModelSeeds::GetIDOfPaintingData()
{
	return ms_FModelSeeds->m_IDOfPaintingData;
}
// ģ��ʹ��״̬
void ASFModelSeeds::SetSeedsModleEnabled(const bool c_enabled)
{
	if (this->m_SeedModelEnabled == c_enabled)
	{
		return;
	}
	this->m_SeedModelEnabled = c_enabled;
}
bool ASFModelSeeds::GetSeedsModleEnabled()
{
	return ms_FModelSeeds->m_SeedModelEnabled;
}
// û�������߾ͽ�������
void ASFModelSeeds::InitSeedsPipeline()
{
	if (m_SeedPipeLine == nullptr)
	{
		m_SeedPipeLine = (ASPipelineSeeds*)ASPipelineManager::AddPipeline(PipeLineType_Seeds);
		m_SeedPipeLine->SetShown(m_SeedsShown);
	}
}
// �������ӵ�
void ASFModelSeeds::StartPaintingData(double* pPosition)
{
	m_SeedPipeLine->AddOnePointDisplay(pPosition);
}
void ASFModelSeeds::ContinuePaintingData(double* pPosition)
{
	m_SeedPipeLine->AddOnePointDisplay(pPosition);
}
// ɾ�����ӵ�
void ASFModelSeeds::DeleteSeeds(const int c_DataID, const int c_SeedID)
{
	ASAbstractData* crntData = ASAbstractData::getDataNodeFromID(c_DataID);
	if (crntData->isTypeInherited(DataType_SeedData))
	{
		ASSeedData* crntSeed = static_cast<ASSeedData*>(crntData);
		crntSeed->DeleteWholeSeeds(c_SeedID);
	}
	//ASSeedData* crntData = ASTransSeeds::GetCurrentSeedData();
	//if (crntData != nullptr && crntData->getDataNodeID() == c_DataID)
	//{
	//	crntData->DeleteWholeSeeds(c_SeedID);
	//}
}
// ˢ�����ӵ���ʾ
void ASFModelSeeds::RefreshSeedsDisplay()
{
	if (m_SeedPipeLine != nullptr)
	{
		m_SeedPipeLine->Update2DTransformMatrix();
	}
}
// ���ӵ�����Ƿ���ʾ��û��2D����ʱ����ʾ���ӵ�
void ASFModelSeeds::SetSeedShown(const bool c_Shown)
{
	m_SeedsShown = c_Shown;
	if (m_SeedPipeLine != nullptr)
	{
		m_SeedPipeLine->SetShown(m_SeedsShown);
	}
}
// ���ӵ����ݷ����仯ʱ��������Ҫ���������б�����˵ɾ�����ӵ��ļ�ʱ���������б��еĶ�ӦID �޳�
void ASFModelSeeds::AdjustUndoList()
{
	QSet<int> Set = m_OperationSequence->toSet();
	auto b_set = Set.begin();
	for (int crntit = 0; crntit < Set.size(); crntit++)
	{
		int crntID = *b_set++;
		ASAbstractData* crntData = ASAbstractData::getDataNodeFromID(crntID);
		if (crntData == nullptr || crntData->isTypeInherited(DataType_SeedData) == false)
		{
			m_OperationSequence->removeAll(crntID);
		}
	}
}
// ��ȡ���ӵ�����
void ASFModelSeeds::LoadSeedData(const QString c_FileName)
{
	ASArrayImageData* GenData = static_cast<ASArrayImageData*>(
		ASTransDataGeneral::GetGeneratingData());
	if (!GenData)
	{
		// �޵�ǰ���ݣ��½�ʧ��
		QMessageBox::information(ASMainWidget::GetMainWidget(), tr("New Seed Point"),
			tr("Please set current greyscale data."), QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	// �ж��Ƿ���Ҫ�½�����ļ�
	ASAnnotation* AnnotationData = static_cast<ASAnnotation*>(
		ASTransDataGeneral::GetGeneratingData()->getChild(DataType_Annotation));
	if (!AnnotationData)
	{
		// �½�Annotation
		AnnotationData = ASTransDataGeneral::NewAnnotationData(ASTransDataGeneral::GetGeneratingData());
	}
	// �ж��Ƿ���Ҫ�½����ӵ��ļ�
	ASSeedData* SeedData = static_cast<ASSeedData*>(AnnotationData->getChild(DataType_SeedData));
	if (!SeedData)
	{
		SeedData = new ASSeedData();
		SeedData->setName(tr("Seed data"));
		SeedData->setShown(true);
		ASDataTree::NewDataNode(SeedData, AnnotationData);
		if (!SeedData)
		{
			qDebug("Error: Null pointer of current SeedsData. From ASPaintingSeedsWidget.");
			return;
		}
	}
	
	QStringList StringList;
	QFile file(c_FileName);
	QStringList list;
	QStringList list2;
	if (file.open(QIODevice::ReadOnly))
	{
		while (!file.atEnd())
			StringList << file.readLine();

		file.close();
	}
	int ncrntLine = 0;
	// 0 ����ļ�ͷ
	if (StringList.at(ncrntLine++) != QString("#Anatomy Sketch Seed File\n"))
	{
		return;
	}
	// 1 ���ӵ���������
	if (StringList.at(ncrntLine++) != QString("#NUMBER OF DATA:\n"))
	{
		return;
	}
	int NumOfSeedData = StringList.at(ncrntLine++).toInt();
	// 2 DATALIST
	if (StringList.at(ncrntLine++) != QString("#DATA LIST DEFINITION:\n"))
	{
		return;
	}
	for (int ncrntSeedData = 0; ncrntSeedData < NumOfSeedData; ncrntSeedData++)
	{
		// 2.1 DATA LIST NUMBER
		if (StringList.at(ncrntLine++) != QString("#DATA LIST NUMBER ") + 
			QString::number(ncrntSeedData) + QString(" DEFINITION:\n"))
		{
			return;
		}
		// 2.2 data_list_index
		list = StringList.at(ncrntLine++).split(" # ");
		if (list.at(1) != QString("data_list_index\n"))
		{
			return;
		}
		if (list.at(0).toInt() != ncrntSeedData)
		{
			return;
		}
		// 2.3 data_name
		list = StringList.at(ncrntLine++).split(" # ");
		if (list.at(1) != QString("data_name\n"))
		{
			return;
		}
		QString name = list.at(0);
		// 2.4 Color
		list = StringList.at(ncrntLine++).split(" # ");
		if (list.at(1) != QString("r_color g_color b_color\n"))
		{
			return;
		}
		list2 = list.at(0).split(" ");
		QColor color(list2.at(0).toInt(), list2.at(1).toInt(), list2.at(2).toInt());
		// 2.5 Label
		list = StringList.at(ncrntLine++).split(" # ");
		if (list.at(1) != QString("data_label\n"))
		{
			return;
		}
		int label = list.at(0).toInt();
		// 2.6 number_of_Seed
		list = StringList.at(ncrntLine++).split(" # ");
		if (list.at(1) != QString("number_of_Line\n"))
		{
			return;
		}
		int id = SeedData->NewSeed(name, label, color);
		if (id < 0)
		{
			qDebug("error: Bad new seed id. From ASFModelSeeds");
			continue;
		}
		int NumOfLine = list.at(0).toInt();
		structSeeds* crntSeeds = SeedData->getSeedsFromID(id);
		for (int ncrntSeedLine = 0; ncrntSeedLine < NumOfLine; ncrntSeedLine++)
		{
			structLine* crntLine = new structLine;
			if (StringList.at(ncrntLine++) != QString("#Line LIST NUMBER ") + 
				QString::number(ncrntSeedLine) + QString(" DEFINITION:\n"))
			{
				return;
			}
			// 2.6.1 line_index
			list = StringList.at(ncrntLine++).split(" # ");
			if (list.at(1) != QString("line_index\n"))
			{
				return;
			}
			if (list.at(0).toInt() != ncrntSeedLine)
			{
				return;
			}
			// 2.6.2 line_ViewLabel
			list = StringList.at(ncrntLine++).split(" # ");
			if (list.at(1) != QString("line_ViewLabel\n"))
			{
				return;
			}
			crntLine->ViewLabel = list.at(0).toInt();
			// 2.6.3 line_dLayer
			list = StringList.at(ncrntLine++).split(" # ");
			if (list.at(1) != QString("line_dLayer\n"))
			{
				return;
			}
			crntLine->dLayer = list.at(0).toDouble();
			// 2.6.4 line_nSerial
			list = StringList.at(ncrntLine++).split(" # ");
			if (list.at(1) != QString("line_nSerial\n"))
			{
				return;
			}
			crntLine->nSerial = list.at(0).toInt();
			// 2.6.5 Points
			if (StringList.at(ncrntLine++) != QString("#START_POINTS_POS\n"))
			{
				return;
			}
			while (true)
			{
				list = StringList.at(ncrntLine++).split(" ");
				if (list.size() != 3)
				{
					break;
				}
				structPoint* ncrntPoint = new structPoint;
				ncrntPoint->dX = list.at(0).toDouble();
				ncrntPoint->dY = list.at(1).toDouble();
				ncrntPoint->dZ = list.at(2).toDouble();
				crntLine->pvectorPoint.append(ncrntPoint);
			}
			
			crntSeeds->pListSeedsData->append(crntLine);
		}
	}
}


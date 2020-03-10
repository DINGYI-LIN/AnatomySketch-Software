#include "ASCustomizeDataWriter.h"
#include "ASSeedData.h"
#include "ASContourData.h"
#include "ASLandmarkData.h"
#include "ASROIData.h"
#include "ASROITypeBase.h"
#include "ASROITypeCube.h"
#include "ASDataStructureWalker.h"
#include <QFileInfo>
#include <QTextStream>

ASCustomizeDataWriter::ASCustomizeDataWriter()
{

}

ASCustomizeDataWriter::~ASCustomizeDataWriter()
{

}

void ASCustomizeDataWriter::WriteSeedData(ASSeedData* DataNode, QString FilePath)
{
	QFileInfo fileInfo(FilePath);
	QFile data(FilePath);
	if (data.open(QFile::WriteOnly | QIODevice::Truncate))
	{
		QTextStream out(&data);
		// 1 �ļ�ͷ
		// 1.1 �汾
		out << "#Anatomy Sketch Seed File" << endl;

		// 1.2  ���ӵ�����
		out << "#NUMBER OF DATA:" << endl;
		int numOfSeeds = DataNode->getNumberOfSeeds();
		out << numOfSeeds << endl;
		out << "#DATA LIST DEFINITION:" << endl;
		// 2 ����������ӵ��ļ�
		// 2.1 �������ӵ㣬���α���

		for (int crntSeedDataNo = 0; crntSeedDataNo < numOfSeeds; crntSeedDataNo++)
		{
			// 2.1.0 ��ǰ���ӵ�
			structSeeds* crntSeeds = DataNode->getSeedsAt(crntSeedDataNo);
			// 2.1.1 �ļ�ͷ
			out << "#DATA LIST NUMBER " << crntSeedDataNo << " DEFINITION:" << endl;
			out << crntSeedDataNo << " # data_list_index" << endl;
			out << crntSeeds->name << " # data_name" << endl;
			out << crntSeeds->color.red() << " " << crntSeeds->color.green() <<
				" " << crntSeeds->color.blue() << " # r_color g_color b_color" << endl;
			out << crntSeeds->label << " # data_label" << endl;

			// 2.1.2 number_of_rois
			int NumOfLines = crntSeeds->pListSeedsData->size();
			out << NumOfLines << " # number_of_Line" << endl;

			// 2.1.3 �������������α���
			for (int ncrntLine = 0; ncrntLine < NumOfLines; ncrntLine++)
			{
				structLine* crntLine = crntSeeds->pListSeedsData->at(ncrntLine);
				// ����Ľ�����Ϣ
				out << "#Line LIST NUMBER " << ncrntLine << " DEFINITION:" << endl;
				// д��ǰLine
				out << ncrntLine << " # line_index" << endl;
				out << crntLine->ViewLabel << " # line_ViewLabel" << endl;
				out << crntLine->dLayer << " # line_dLayer" << endl;
				out << crntLine->nSerial << " # line_nSerial" << endl;

				QList<structPoint*> listPoints = crntLine->pvectorPoint;
				out << "#START_POINTS_POS" << endl;
				for (int nCrntPoints = 0; nCrntPoints < listPoints.size(); nCrntPoints++)
				{
					out << listPoints.at(nCrntPoints)->dX << " " << listPoints.at(nCrntPoints)->dY
						<< " " << listPoints.at(nCrntPoints)->dZ << endl;
				}
				out << "#END_POINTS_POS" << endl;
			}
		}
		// 3 д�ļ�β
		out << "#" << endl;
		out << "#END OF LINES DEFINITION" << endl;
	}
}
void ASCustomizeDataWriter::WriteContourData(ASContourData* DataNode, QString FilePath)
{
	QFileInfo fileInfo(FilePath);
	QFile data(FilePath);
	if (data.open(QFile::WriteOnly | QIODevice::Truncate))
	{
		QTextStream out(&data);

		// 1 �ļ�ͷ
		// 1.1 �汾
		out << "#Anatomy Sketch Contour File" << endl;

		// 1.2 ����������
		out << "#NUMBER OF DATA:" << endl;
		int numOfContour = DataNode->GetNumberOfContour();
		out << numOfContour << endl;
		out << "#DATA LIST DEFINITION:" << endl;

		// 2 ��������������ļ�
		int crntPolyDataNo = 0;
		// 2.1 �������棬���α���		
		for (int crntContourDataNo = 0; crntContourDataNo < numOfContour; crntContourDataNo++)
		{
			// 2.1.0 ��ǰ����
			structContour* crntContour = DataNode->GetContourAt(crntContourDataNo);
			// 2.1.1 �ļ�ͷ
			out << "#DATA LIST NUMBER " << crntPolyDataNo << " DEFINITION:" << endl;
			out << crntPolyDataNo << " # data_list_index" << endl;
			out << crntContour->name << " # data_name" << endl;
			out << crntContour->color.red() << " " << crntContour->color.green() << " "
				<< crntContour->color.blue() << " # r_color g_color b_color" << endl;
			out << crntContour->label << " # data_label" << endl;

			// 2.1.2 number_of_rois
			int NumOfCurves = crntContour->pListCurves->size();
			out << NumOfCurves << " # number_of_contours" << endl;

			// 2.1.3 �������������α���
			for (int ncrntCurves = 0; ncrntCurves < NumOfCurves; ncrntCurves++)
			{
				structCurve* crntCurve = crntContour->pListCurves->at(ncrntCurves);

				// ����Ľ�����Ϣ
				out << "#CONTOUR LIST NUMBER " << ncrntCurves << " DEFINITION:" << endl;
				// д��ǰContour
				out << ncrntCurves << " # contour_index" << endl;
				out << crntCurve->ViewLabel << " # contour_ViewLabel" << endl;
				if (crntCurve->isClosure)
				{
					out << "true # contour_isClosure" << endl;
				}
				else
				{
					out << "false # contour_isClosure" << endl;
				}
				out << crntCurve->dLayer << " # contour_dLayer" << endl;
				QList<structPoint*> listPoints = crntCurve->pvectorPoint;
				out << "#START_POINTS_POS" << endl;
				for (int nCrntPoints = 0; nCrntPoints < listPoints.size(); nCrntPoints++)
				{
					out << listPoints.at(nCrntPoints)->dX << " " << listPoints.at(nCrntPoints)->dY << " " << listPoints.at(nCrntPoints)->dZ << endl;
				}
				out << "#END_POINTS_POS" << endl;
			}
			crntPolyDataNo += 1;
		}
		// 3 д�ļ�β
		out << "#" << endl;
		out << "#END OF CONTOURS DEFINITION" << endl;
	}
}
void ASCustomizeDataWriter::WriteLandmarkData(ASLandmarkData* DataNode, QString FilePath)
{
	QFileInfo fileInfo(FilePath);
	QFile data(FilePath);
	if (data.open(QFile::WriteOnly | QIODevice::Truncate))
	{
		QTextStream out(&data);
		// 1 �ļ�ͷ
		// 1.1 �汾
		out << "#Anatomy Sketch Landmark File" << endl;

		// 1.2  �궨������
		out << "#NUMBER OF DATA:" << endl;
		int numOfLandMData = ASLandmarkData::GetNumOfLandmarkData();
		out << numOfLandMData << endl;
		out << "#DATA LIST DEFINITION:" << endl;

		// 2 ����������ӵ��ļ�
		int crntLandMDataNo = 0;
		// 2.1 �������ӵ㣬���α���	
		for (ASAbstractData* item = ASDataStructureWalker::bigen_inherit(DataType_LandmarkData);
			item != nullptr; item = ASDataStructureWalker::next_inherit(DataType_LandmarkData))
		{
			// 2.1.0 ��ǰ���ӵ�
			ASLandmarkData* crntLandMData = static_cast<ASLandmarkData*>(item);

			// 2.1.1 �ļ�ͷ
			out << "#DATA LIST NUMBER " << crntLandMDataNo << " DEFINITION:" << endl;
			out << crntLandMDataNo << " # data_list_index" << endl;
			out << crntLandMData->getName() << " # data_name" << endl;

			// 2.1.2 number_of_landmarks
			int NumOfLandM = crntLandMData->GetNumberOfLandmark();
			out << NumOfLandM << " # number_of_landmarks" << endl;

			// 2.1.3 �����궨�㣬���α���
			for (int ncrntLandM = 0; ncrntLandM < NumOfLandM; ncrntLandM++)
			{
				structLandmark* crntLandM = crntLandMData->GetLandmarkAt(ncrntLandM);

				// ����Ľ�����Ϣ
				out << "#LANDMARK LIST NUMBER " << ncrntLandM << " DEFINITION:" << endl;
				// д��ǰLine
				out << ncrntLandM << " # landmark_index" << endl;
				out << crntLandM->qsName << " # landmark_name" << endl;
				out << crntLandM->LandmarkID << " # landmark_ID" << endl;
				out << crntLandM->color.red() << " " << crntLandM->color.green() << " " <<
					crntLandM->color.blue() << " # r_color g_color b_color" << endl;
				out << "#POINT_POS" << endl;
				out << crntLandM->dPosition[0] << " " << crntLandM->dPosition[1]
					<< " " << crntLandM->dPosition[2] << endl;
				out << "#END_POINT_POS" << endl;
			}
			crntLandMDataNo += 1;
		}
		// 3 д�ļ�β
		out << "#" << endl;
		out << "#END OF LANDMARKS DEFINITION" << endl;
	}
}
void ASCustomizeDataWriter::WriteROIData(ASROIData* DataNode, QString FilePath)
{
	QFileInfo fileInfo(FilePath);
	QFile data(FilePath);
	if (data.open(QFile::WriteOnly | QIODevice::Truncate))
	{
		QTextStream out(&data);
		// 1 �ļ�ͷ
		// 1.1 �汾
		out << "#Anatomy Sketch ROI File" << endl;
		// 1.2 ROI����
		int NumOfROIs = DataNode->GetNumOfROIs();
		out << "#NUMBER OF ROIs:" << endl;
		out << NumOfROIs << endl;
		out << "#ROI LIST DEFINITION:" << endl;

		// 2 �������ROI�ļ�
		for (int nCrntROI = 0; nCrntROI < NumOfROIs; nCrntROI++)
		{
			ASROITypeBase* roi = DataNode->GetROIAt(nCrntROI);
			// 2.1.1 �ļ�ͷ
			out << "#ROI LIST NUMBER " << nCrntROI << " DEFINITION:" << endl;
			out << nCrntROI << " # data_list_index" << endl;
			out << roi->GetName() << " # roi_name" << endl;
			out << roi->GetColor().red() << " " << roi->GetColor().green() << " " <<
				roi->GetColor().blue() << " # r_color g_color b_color" << endl;
			out << roi->GetROIType() << " # roi_type" << endl;
			// 2.1.2 ���ౣ��
			switch (roi->GetROIType())
			{
			case ROIType_Cube:
			{
				ASROITypeCube* cube = static_cast<ASROITypeCube*>(roi);
				out << "#ROI Cube DEFINITION:" << endl;
				double* range = cube->GetRange();
				out << range[0] << " " << range[1] << " " << range[2] << " " <<
					range[3] << " " << range[4] << " " << range[5] << " # Range" << endl;
				out << "#ROI Cube END:" << endl;
				break;
			}
			default:
				break;
			}
		}
		// 3 д�ļ�β
		out << "#" << endl;
		out << "#END OF ROI DEFINITION" << endl;
	}
}

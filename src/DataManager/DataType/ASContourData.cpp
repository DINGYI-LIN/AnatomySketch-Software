#include "ASContourData.h"
#include "ASTransContour.h"

int ASContourData::ms_nNumOfContourData = 0;

ASContourData::ASContourData()
{
	m_Datatype = DataType_ContourData;

	if (ASContourData::ms_nNumOfContourData == 0)
	{
		// ������������ʾ����
		ASTransContour::InitContourPipeline();
	}
	ASContourData::ms_nNumOfContourData += 1;

	m_listContours = new QList<structContour*>;
}

ASContourData::~ASContourData()
{
	ASContourData::ms_nNumOfContourData -= 1;

	while (m_listContours->size())
	{
		structContour* crntContour = m_listContours->first();
		m_listContours->removeFirst();
		while (crntContour->pListCurves->size())
		{
			structCurve* crntCurve = crntContour->pListCurves->first();
			crntContour->pListCurves->removeFirst();
			while (crntCurve->pvectorPoint.size())
			{
				structPoint* crntPoint = crntCurve->pvectorPoint.first();
				crntCurve->pvectorPoint.removeFirst();
				delete crntPoint;
			}
			delete crntCurve;
		}
		delete crntContour->pListCurves;
		delete crntContour;
	}
	delete m_listContours;
}

// ���ô˺������ͷŽڵ�
void ASContourData::DeleteNode()
{
	delete this;
}

// ���������ж�
// �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
bool ASContourData::isTypeInherited(const int c_Type)
{
	if (c_Type == DataType_ContourData || ASMarkData::isTypeInherited(c_Type))
	{
		return true;
	}
	return false;
}
bool ASContourData::isTypeAbsolute(const int c_Type)
{
	if (c_Type == DataType_ContourData)
	{
		return true;
	}
	return false;
}
bool ASContourData::isTypeInheritedStatic(const int c_Type)
{
	if (c_Type == DataType_ContourData || ASMarkData::isTypeInheritedStatic(c_Type))
	{
		return true;
	}
	return false;
}
// �½�������
int ASContourData::NewContour(const QString c_name, const int c_lable, const QColor c_color)
{
	int Label = c_lable;
	QColor crntColor = c_color;
	int numOfContours = m_listContours->size();
	if (Label == -1)
	{
		// �Զ�ѡ��label����ɫ
		bool f;
		do
		{
			Label++;
			f = false;
			for (int i = 0; i < numOfContours; i++)
			{
				if (m_listContours->at(i)->label == Label)
				{
					f = true;
					break;
				}
			}
		} while (f);
		crntColor.setRed(qrand() % 256);
		crntColor.setGreen(qrand() % 256);
		crntColor.setBlue(qrand() % 256);
	}

	for (int i = 0; i < numOfContours; i++)
	{
		if (m_listContours->at(i)->label == c_lable || m_listContours->at(i)->name == c_name)
		{
			return -1;
		}
	}
	structContour* crntContour = new structContour;
	crntContour->color = crntColor;
	crntContour->label = Label;
	crntContour->name = c_name;
	crntContour->contourID = GetNewContourID();
	crntContour->isShown = true;
	crntContour->pListCurves = new QList<structCurve *>;
	m_listContours->append(crntContour);
	return crntContour->contourID;
}
// ��������������
int ASContourData::GetNumOfContourData()
{
	return ASContourData::ms_nNumOfContourData;
}
// ��ǩֵ
int ASContourData::getLabel()
{
	return m_nLabel;
}
void ASContourData::setLabel(const int label)
{
	m_nLabel = label;
}
// ����������
int ASContourData::GetNumberOfContour()
{
	if (m_listContours)
	{
		return m_listContours->size();
	}
	else
	{
		return 0;
	}
}
structContour* ASContourData::GetContourAt(const int c_Contour)
{
	return m_listContours->at(c_Contour);
}
structContour* ASContourData::GetContourFromID(const int c_ContourID)
{
	int numOfContour = m_listContours->size();
	for (int i = 0; i < numOfContour; i++)
	{
		if (m_listContours->at(i)->contourID == c_ContourID)
		{
			return m_listContours->at(i);
		}
	}
	return nullptr;
}
void ASContourData::AppandContour(structContour* NewContour)
{
	m_listContours->append(NewContour);
}
// �õ����ݷ�Χ��double[6]
double* ASContourData::getDataExtent()
{
	return nullptr;
}

// �����߲���
void ASContourData::AddContrlPointsTemp(double* pPosition, const int ViewLabel, 
	double* pSpacing, const int c_ContourID)
{
	//���㵱ǰ��ķ�Χ���Ը÷�Χ��������Ϊͬ��
	double layermin = pPosition[ViewLabel] - 0.5 * pSpacing[ViewLabel];
	double layermax = pPosition[ViewLabel] + 0.5 * pSpacing[ViewLabel];
	structContour* crntContour = this->GetContourFromID(c_ContourID);
	if (!crntContour)
	{
		return;
	}
	// 1 �жϵ�ǰ�����Ƿ���δ�պϵ�����
	int unClosureContour = -1;
	// ��������
	int numOfCurve = crntContour->pListCurves->size();
	for (int ncrntContour = 0; ncrntContour < numOfCurve; ncrntContour++)
	{
		double crntdLayer = crntContour->pListCurves->at(ncrntContour)->dLayer;
		if (crntdLayer >= layermin && crntdLayer < layermax)
		{
			// �ǵ�ǰ��ģ��ж��Ƿ�պ�
			if (crntContour->pListCurves->at(ncrntContour)->isClosure == false)
			{
				unClosureContour = ncrntContour;
				break;
			}
		}
	}

	// 2 �½����Ƶ�
	structPoint* crntpoint = new structPoint;
	crntpoint->dX = pPosition[0];
	crntpoint->dY = pPosition[1];
	crntpoint->dZ = pPosition[2];

	if (unClosureContour == -1)
	{
		// 2.1 ���û��δ�պ����������½�һ������
		structCurve* newContour = new structCurve;
		newContour->dLayer = pPosition[ViewLabel];
		newContour->isClosure = false;
		newContour->ViewLabel = ViewLabel;
		newContour->pvectorPoint.append(crntpoint);
		newContour->haveTemporary = true;
		crntContour->pListCurves->append(newContour);
	}
	else
	{
		// 2.2 �����δ�պ�������ֱ�����һ�����Ƶ�
		if (crntContour->pListCurves->at(unClosureContour)->haveTemporary)
		{
			// ����ʱ���Ƶ���ɾ��ԭ��ʱ���Ƶ�
			delete crntContour->pListCurves->at(unClosureContour)->pvectorPoint.last();
			crntContour->pListCurves->at(unClosureContour)->pvectorPoint.removeLast();
		}
		crntContour->pListCurves->at(unClosureContour)->haveTemporary = true;
		crntContour->pListCurves->at(unClosureContour)->pvectorPoint.append(crntpoint);
	}
}
void ASContourData::AddContrlPoints(double* pPosition, const int ViewLabel, 
	double* pSpacing, const int c_ContourID)
{
	//���㵱ǰ��ķ�Χ���Ը÷�Χ��������Ϊͬ��
	double layermin = pPosition[ViewLabel] - 0.5 * pSpacing[ViewLabel];
	double layermax = pPosition[ViewLabel] + 0.5 * pSpacing[ViewLabel];
	structContour* crntContour = this->GetContourFromID(c_ContourID);
	if (!crntContour)
	{
		return;
	}
	// 1 �жϵ�ǰ�����Ƿ���δ�պϵ�����
	int unClosureContour = -1;
	// ��������
	int numOfCurve = crntContour->pListCurves->size();
	for (int ncrntContour = 0; ncrntContour < numOfCurve; ncrntContour++)
	{
		double crntdLayer = crntContour->pListCurves->at(ncrntContour)->dLayer;
		if (crntdLayer >= layermin && crntdLayer < layermax)
		{
			// �ǵ�ǰ��ģ��ж��Ƿ�պ�
			if (crntContour->pListCurves->at(ncrntContour)->isClosure == false)
			{
				unClosureContour = ncrntContour;
				break;
			}
		}
	}
	if (unClosureContour == -1)
	{
		// 2.1 ���û��δ�պ�����
		return;
	}
	else
	{
		// 2.2 �����δ�պ�������ֱ�����һ�����Ƶ�
		if (crntContour->pListCurves->at(unClosureContour)->haveTemporary)
		{
			structPoint* crntpoint = new structPoint;
			crntpoint->dX = pPosition[0];
			crntpoint->dY = pPosition[1];
			crntpoint->dZ = pPosition[2];
			crntContour->pListCurves->at(unClosureContour)->pvectorPoint.append(crntpoint);
		}
	}
}
void ASContourData::MoveContrlPoints(double* pPosition, const int c_ViewLabel, double* pSpacing, 
	const int c_ContourID,	const int c_IndexOfContour, const int c_IndexOfHandle)
{
	//���㵱ǰ��ķ�Χ���Ը÷�Χ��������Ϊͬ��
	double layermin = pPosition[c_ViewLabel] - 0.5 * pSpacing[c_ViewLabel];
	double layermax = pPosition[c_ViewLabel] + 0.5 * pSpacing[c_ViewLabel];
	structContour* crntContour;
	if (c_ContourID == -1)
	{
		int id = ASTransContour::GetCrntContourID();
		crntContour = this->GetContourFromID(id);
	} 
	else
	{
		crntContour = this->GetContourFromID(c_ContourID);
	}
	if (!crntContour)
	{
		return;
	}
	// �ı���Ƶ�����
	int numOfCurve = crntContour->pListCurves->size();
	if (c_IndexOfContour == -1)
	{
		int unClosureContour = -1;
		// �жϵ�ǰ�����Ƿ���δ�պϵ�����
		for (int ncrntContour = 0; ncrntContour < numOfCurve; ncrntContour++)
		{
			double crntdLayer = crntContour->pListCurves->at(ncrntContour)->dLayer;
			if (crntdLayer >= layermin && crntdLayer < layermax)
			{
				// �ǵ�ǰ��ģ��ж��Ƿ�պ�
				if (crntContour->pListCurves->at(ncrntContour)->isClosure == false)
				{
					unClosureContour = ncrntContour;
					break;
				}
			}
		}
		// �ҵ���ǰ����δ�պ����������һ�����Ƶ�
		if (unClosureContour == -1)
		{
			return;
		}
		structPoint* crntpoint = crntContour->pListCurves->at(unClosureContour)->pvectorPoint.last();
		crntpoint->dX = pPosition[0];
		crntpoint->dY = pPosition[1];
		crntpoint->dZ = pPosition[2];
	}
	else
	{
		// �жϿ��Ƶ��Ƿ�Ϸ�
		structCurve* crntCurve = crntContour->pListCurves->at(c_IndexOfContour);
		if (crntCurve->ViewLabel != c_ViewLabel)
		{
			return;
		}
		if (crntCurve->dLayer >= layermin && crntCurve->dLayer < layermax)
		{
			if (c_IndexOfHandle >= 0 && c_IndexOfHandle < crntCurve->pvectorPoint.size())
			{
				structPoint* crntpoint = crntCurve->pvectorPoint.at(c_IndexOfHandle);
				crntpoint->dX = pPosition[0];
				crntpoint->dY = pPosition[1];
				crntpoint->dZ = pPosition[2];
			}
		}
	}
}
void ASContourData::DeleteContrlPointsTemp(double* pPosition, const int c_ViewLabel, double* pSpacing,
	const int c_ContourID)
{
	//���㵱ǰ��ķ�Χ���Ը÷�Χ��������Ϊͬ��
	double layermin = pPosition[c_ViewLabel] - 0.5 * pSpacing[c_ViewLabel];
	double layermax = pPosition[c_ViewLabel] + 0.5 * pSpacing[c_ViewLabel];
	structContour* crntContour = this->GetContourFromID(c_ContourID);
	if (!crntContour)
	{
		return;
	}
	int unClosureContour = -1;
	// �жϵ�ǰ�����Ƿ���δ�պϵ�����
	int numOfCurve = crntContour->pListCurves->size();
	for (int ncrntContour = 0; ncrntContour < numOfCurve; ncrntContour++)
	{
		double crntdLayer = crntContour->pListCurves->at(ncrntContour)->dLayer;
		if (crntdLayer >= layermin && crntdLayer < layermax)
		{
			// �ǵ�ǰ��ģ��ж��Ƿ�պ�
			if (crntContour->pListCurves->at(ncrntContour)->isClosure == false)
			{
				unClosureContour = ncrntContour;
				break;
			}
		}
	}
	// �ҵ���ǰ����δ�պ����������һ�����Ƶ�
	if (unClosureContour == -1)
	{
		return;
	}
	structCurve* crntCurve = crntContour->pListCurves->at(unClosureContour);
	if (crntCurve->haveTemporary == false)
	{
		return;
	}
	crntCurve->haveTemporary = false;
	delete crntCurve->pvectorPoint.last();
	crntCurve->pvectorPoint.removeLast();
	if (crntCurve->pvectorPoint.size() == 0)
	{
		// ���ɾ���������һ����
		crntContour->pListCurves->removeOne(crntCurve);
		delete crntCurve;
	}
}
void ASContourData::SetContourClosed(const int c_viewlabel, const int c_indexOfContour, 
	const int c_indexOfHandle, const bool c_Closed, const int c_ContourID)
{
	// ����������ŵõ�����
	structContour* crntContour = this->GetContourFromID(c_ContourID);
	if (!crntContour)
	{
		return;
	}
	structCurve* crntCurve = crntContour->pListCurves->at(c_indexOfContour);
	if (crntCurve->ViewLabel == c_viewlabel && c_indexOfHandle == 0)
	{
		crntCurve->isClosure = c_Closed;
	}
}
void ASContourData::DeleteContrlPoints(const int c_ViewLabel, double* pSpacing, const int c_ContourID, 
	const int c_IndexOfContour, const int c_IndexOfHandle)
{
	// ����������ŵõ�����
	structContour* crntContour;
	if (c_ContourID == -1)
	{
		int id = ASTransContour::GetCrntContourID();
		crntContour = this->GetContourFromID(id);
	}
	else
	{
		crntContour = this->GetContourFromID(c_ContourID);
	}
	if (!crntContour)
	{
		return;
	}
	structCurve* crntCurve = crntContour->pListCurves->at(c_IndexOfContour);
	if (crntCurve->ViewLabel == c_ViewLabel)
	{
		crntCurve->pvectorPoint.removeAt(c_IndexOfHandle);
	}
	if (crntCurve->pvectorPoint.size() == 0)
	{
		// ���ɾ���������һ����
		crntContour->pListCurves->removeOne(crntCurve);
		delete crntCurve;
	}
}
void ASContourData::InsertContrlPoints(double* pPosition, const int c_ViewLabel, double* pSpacing, 
	const int c_ContourID, const int c_IndexOfContour, const int c_IndexOfHandle)
{
	//���㵱ǰ��ķ�Χ���Ը÷�Χ��������Ϊͬ��
	double layermin = pPosition[c_ViewLabel] - 0.5 * pSpacing[c_ViewLabel];
	double layermax = pPosition[c_ViewLabel] + 0.5 * pSpacing[c_ViewLabel];
	structContour* crntContour = this->GetContourFromID(c_ContourID);
	if (!crntContour)
	{
		return;
	}
	double position[3];
	position[0] = pPosition[0];
	position[1] = pPosition[1];
	position[2] = pPosition[2];

	structCurve* crntCurve = crntContour->pListCurves->at(c_IndexOfContour);
	if (crntCurve->ViewLabel != c_ViewLabel)
	{
		return;
	}
	position[c_ViewLabel] = crntCurve->dLayer;
	//������Ƶ�
	structPoint* newPoint = new structPoint;
	newPoint->dX = position[0];
	newPoint->dY = position[1];
	newPoint->dZ = position[2];

	crntCurve->pvectorPoint.insert(c_IndexOfHandle + 1, newPoint);
}
void ASContourData::DeleteContour(const int c_viewlabel, const int c_indexOfContour, 
	const int c_indexOfHandle, const int c_ContourID)
{
	// ����������ŵõ�����
	structContour* crntContour = this->GetContourFromID(c_ContourID);
	if (!crntContour)
	{
		return;
	}
	structCurve* crntCurve = crntContour->pListCurves->at(c_indexOfContour);
	if (crntCurve->ViewLabel == c_viewlabel)
	{
		foreach(structPoint* crntPoint, crntCurve->pvectorPoint)
		{
			delete crntPoint;
		}
	}
	crntContour->pListCurves->removeOne(crntCurve);
	delete crntCurve;
}
void ASContourData::DeleteWholeContour(const int c_ContourID)
{
	structContour* crntContour = this->GetContourFromID(c_ContourID);
	if (!crntContour)
	{
		return;
	}
	m_listContours->removeOne(crntContour);
	while (crntContour->pListCurves->size())
	{
		structCurve* crntCurve = crntContour->pListCurves->first();
		crntContour->pListCurves->removeFirst();
		while (crntCurve->pvectorPoint.size())
		{
			structPoint* crntPoint = crntCurve->pvectorPoint.first();
			crntCurve->pvectorPoint.removeFirst();
			delete crntPoint;
		}
		delete crntCurve;
	}
	delete crntContour->pListCurves;
	delete crntContour;
}
// �õ�һ���µĲ��ظ�ID
int ASContourData::GetNewContourID()
{
	int newid = 0;
	bool f = false;
	int sz = m_listContours->size();
	do
	{
		f = false;
		for (int i = 0; i < sz; i++)
		{
			if (m_listContours->at(i)->contourID == newid)
			{
				newid++;
				f = true;
				break;
			}
		}
	} while (f);
	return newid;
}
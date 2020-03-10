#include "ASPolyImageData.h"
#include <QFileInfo>
#include <QColor>

ASPolyImageData::ASPolyImageData()
{
	m_Datatype = DataType_PolyImageData;
}

ASPolyImageData::~ASPolyImageData()
{
}

// ���ô˺������ͷŽڵ�
void ASPolyImageData::DeleteNode()
{
	QMutexLocker Locker(m_Mutex);
	delete this;
}

// ���������ж�
// �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
bool ASPolyImageData::isTypeInherited(const int c_Type)
{
	if (c_Type == DataType_PolyImageData || ASImageData::isTypeInherited(c_Type))
	{
		return true;
	}
	return false;
}
bool ASPolyImageData::isTypeAbsolute(const int c_Type)
{
	QMutexLocker Locker(m_Mutex);
	if (c_Type == DataType_PolyImageData)
	{
		return true;
	}
	return false;
}
bool ASPolyImageData::isTypeInheritedStatic(const int c_Type)
{
	if (c_Type == DataType_PolyImageData || ASImageData::isTypeInheritedStatic(c_Type))
	{
		return true;
	}
	return false;
}

// �õ�ͼ������
QColor ASPolyImageData::getColor()
{
	QMutexLocker Locker(m_Mutex);
	return m_Color;
}
// ������ɫ�� 0~255
void ASPolyImageData::setColor(const QColor c_Color)
{
	QMutexLocker Locker(m_Mutex);
	m_Color = c_Color;
}
int ASPolyImageData::getOpacity()
{
	QMutexLocker Locker(m_Mutex);
	return m_nOpacity;
}
void ASPolyImageData::setOpacity(const int opacity)
{
	QMutexLocker Locker(m_Mutex);
	m_nOpacity = opacity;
}
vtkPolyData* ASPolyImageData::getPolyImageData()
{
	QMutexLocker Locker(m_Mutex);
	return m_PolyData;
}
void ASPolyImageData::setPolyData(vtkPolyData* pPolyData)
{
	QMutexLocker Locker(m_Mutex);
	if (m_PolyData == nullptr)
	{
		m_PolyData = vtkSmartPointer<vtkPolyData>::New();
	}	
	m_PolyData->SetPoints(pPolyData->GetPoints());
	m_PolyData->SetPolys(pPolyData->GetPolys());
	//m_PolyData->DeepCopy(pPolyData);
}
// �������ݺ�����ݳ�ʼ��
void ASPolyImageData::DataInitAfterLoad()
{
	this->setShown(true);
	this->setBeingProcess(false);
	QMutexLocker Locker(m_Mutex);
	this->m_nOpacity = 100;
	m_PolyData->GetBounds(m_adDataExtent);

	// 2 ��ʼ��ɫ���Ƚ������ֱ��䣬���ɹ����ʼΪ�ص���ɫ�����������ɫ��
	if (m_FileName.contains("all"))
	{
		// ������ ��ɫ
		m_Color.setRgb(255, 255, 255);

	}
	else if (m_FileName.contains("heart") || m_FileName.contains("Heart"))
	{
		// ���� 
		m_Color.setRgb(250, 50, 50);
	}
	else if (m_FileName.contains("liver") || m_FileName.contains("Liver"))
	{
		// ����
		m_Color.setRgb(50, 255, 50);
	}
	else if (m_FileName.contains("lkidney"))
	{
		// ����
		m_Color.setRgb(255, 128, 0);
	}
	else if (m_FileName.contains("lungs"))
	{
		// ��
		m_Color.setRgb(255, 255, 50);
	}
	else if (m_FileName.contains("rkidney"))
	{
		// ����
		m_Color.setRgb(50, 255, 255);
	}
	else if (m_FileName.contains("skeleton") || m_FileName.contains("Skeleton"))
	{
		// ����
		m_Color.setRgb(90, 90, 255);
	}
	else if (m_FileName.contains("skin") || m_FileName.contains("Skin"))
	{
		// Ƥ��
		m_Color.setRgb(255, 255, 255);
	}
	else if (m_FileName.contains("spleen") || m_FileName.contains("Spleen"))
	{
		// Ƣ
		m_Color.setRgb(255, 50, 255);
	}
	else
	{
		// Ĭ�ϰ�ɫ
		m_Color.setRgb(255, 255, 255);
	}
}

//// �����α�ģ��
//void ASPolyImageData::setPolyDeformationChoosen(const bool isChoosen)
//{
//	m_isPolyDeformationChoosen = isChoosen;
//}
//bool ASPolyImageData::isPolyDeformationChoosen()
//{
//	return m_isPolyDeformationChoosen;
//}
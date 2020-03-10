#include "ASArrayImageData.h"
#include "ASDataStructureWalker.h"
#include "ASColorMap.h"
#include <vtkImageImport.h>
#include <QMessageBox>
#include <QFileInfo>

#pragma comment(lib,"itkImageReader.lib")
extern "C" __declspec(dllimport)  float itkImageReader(int argc, void* argv[]);

typedef struct { unsigned short slen; unsigned short stype; char *s; } IDL_STRING;

int ASArrayImageData::ms_nNumOfArrayImageData = 0;
int ASArrayImageData::ms_nNumberOfArrayImageDataShown = 0;

template<typename TIn>
double PosCheckWithoutValue(const int c_x, const int c_y, const int c_z, vtkImageData* pImageData)
{
	TIn* ptrScalar = static_cast<TIn *>(pImageData->GetScalarPointer(c_x, c_y, c_z));
	return *ptrScalar;
}

ASArrayImageData::ASArrayImageData()
{
	ASArrayImageData::ms_nNumOfArrayImageData += 1;	// ����������1
	m_Datatype = DataType_ArrayImageData;
	m_ColorMode = ColorMode_Grayscale;
}

ASArrayImageData::~ASArrayImageData()
{
	ASArrayImageData::ms_nNumOfArrayImageData -= 1;
	m_pImageData = nullptr;
	m_pTransform = nullptr;
}

// ���ô˺������ͷŽڵ�
void ASArrayImageData::DeleteNode()
{
	QMutexLocker Locker(m_Mutex);
	delete this;
}

// ���������ж�
// �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
bool ASArrayImageData::isTypeInherited(const int c_Type)
{
	if (c_Type == DataType_ArrayImageData || ASImageData::isTypeInherited(c_Type))
	{
		return true;
	}
	return false;
}
bool ASArrayImageData::isTypeAbsolute(const int c_Type)
{
	QMutexLocker Locker(m_Mutex);
	if (c_Type == DataType_ArrayImageData)
	{
		return true;
	}
	return false;
}
bool ASArrayImageData::isTypeInheritedStatic(const int c_Type)
{
	if (c_Type == DataType_ArrayImageData || ASImageData::isTypeInheritedStatic(c_Type))
	{
		return true;
	}
	return false;
}

// �õ�ͼ������
int ASArrayImageData::getColorMap()
{
	QMutexLocker Locker(m_Mutex);
	return m_nColorMap;
}
// ������ɫ�� �궨��:ColorMap_
void ASArrayImageData::setColorMap(const int colormap)
{
	QMutexLocker Locker(m_Mutex);
	m_nColorMap = colormap;
}
int ASArrayImageData::getLayer()
{
	QMutexLocker Locker(m_Mutex);
	return m_nLayer;
}
void ASArrayImageData::setLayer(const int c_Layer)
{
	QMutexLocker Locker(m_Mutex);
	m_nLayer = c_Layer;
}
double* ASArrayImageData::getWindowLevel()
{
	QMutexLocker Locker(m_Mutex);
	return m_adWindowLevel;
}
void ASArrayImageData::setWindowLevel()
{
	// �ж�����m_pImageData�Ƿ�ΪCTͼ�񣬸���m_adWindowLevel
	checkDataIsCTOrNot();
}
void ASArrayImageData::setWindowLevel(const double window, const double level)
{
	QMutexLocker Locker(m_Mutex);
	m_adWindowLevel[0] = window;
	m_adWindowLevel[1] = level;
}
double* ASArrayImageData::getImageExtent()
{
	QMutexLocker Locker(m_Mutex);
	return this->m_adDataExtent;
}
// ��͸����
int ASArrayImageData::getOpacity()
{
	QMutexLocker Locker(m_Mutex);
	return m_nOpacity;
}
void ASArrayImageData::setOpacity(const int opacity)
{
	QMutexLocker Locker(m_Mutex);
	m_nOpacity = opacity;
}

vtkImageData* ASArrayImageData::getArrayImageData()
{
	QMutexLocker Locker(m_Mutex);
	return this->m_pImageData;
}
void ASArrayImageData::copyArrayImageDataFrom(const int c_ID)
{
	QMutexLocker Locker(m_Mutex);
	if (m_pImageData != nullptr)
	{
		m_pImageData = nullptr;
	}
	m_pImageData = vtkSmartPointer<vtkImageData>::New();

	ASArrayImageData* pTemplateData = (ASArrayImageData*)ASAbstractData::getDataNodeFromID(c_ID);
	vtkImageData* targetData = pTemplateData->getArrayImageData();
	m_pImageData->SetDimensions(targetData->GetDimensions());
	m_pImageData->SetSpacing(targetData->GetSpacing());
	m_pImageData->SetExtent(targetData->GetExtent());
	m_pImageData->AllocateScalars(targetData->GetScalarType(), 1);
	this->m_nColorMap = pTemplateData->getColorMap();
	this->m_adWindowLevel[0] = pTemplateData->getWindowLevel()[0];
	this->m_adWindowLevel[1] = pTemplateData->getWindowLevel()[1];
	Locker.unlock();
	// 4 ��������
	this->setShown(true);
	this->setBeingProcess(false);
	this->getName() = pTemplateData->getName() + "_copy";
	this->m_nLayer = ASArrayImageData::ms_nNumOfArrayImageData;		//������Ϊ��ǰͼ��������������ʾ����
	this->m_NumberOfFrames = m_pImageData->GetNumberOfScalarComponents();

}
enumArrayImageDataType ASArrayImageData::getArrayImageDataType()
{
	QMutexLocker Locker(m_Mutex);
	return m_ArrayImageDataType;
}
void ASArrayImageData::setArrayImageDataType(const enumArrayImageDataType type)
{
	QMutexLocker Locker(m_Mutex);
	m_ArrayImageDataType = type;
}
// ɫ��ģʽ
void ASArrayImageData::SetColorMode(const int c_mode)
{
	m_ColorMode = c_mode;
}
int ASArrayImageData::GetColorMode()
{
	return m_ColorMode;
}


// ��������
void ASArrayImageData::setArrayImageData(vtkImageData* ImageData)
{
	QMutexLocker Locker(m_Mutex);
	if (this->m_pImageData == nullptr)
	{
		this->m_pImageData = vtkSmartPointer<vtkImageData>::New();
	}
	this->m_pImageData->DeepCopy(ImageData);
}
// �������ݺ�����ݳ�ʼ��
void ASArrayImageData::DataInitAfterLoad()
{
	// 1 ��������
	this->setShown(true);
	this->setBeingProcess(false);
	QMutexLocker Locker(m_Mutex);
	this->m_NumberOfFrames = m_pImageData->GetNumberOfScalarComponents();	
	// 2 ����ͼ��Χ
	Locker.unlock();
	this->checkDataExtent();	
	// 3 �жϻҶ�ͼ�ͱ�ǩͼ��ͨ���жϲ�ͬ����ֵ������
	this->checkDataTypeAndColorMap();
	// 4 �жϸ�ͼ���Ƿ�ΪCTͼ�����ΪCTͼ���趨��CT����ʵĴ�λ��������λΪ�Ҷ�ֵ����λ��������Ϊ�Ҷ�ֵ��Χ��һ��
	this->checkDataIsCTOrNot();
}

void ASArrayImageData::setShown(const bool shown)
{
	QMutexLocker Locker(m_Mutex);
	if (this->isShown() == shown)
	{
		return;
	}
	if (shown)
	{
		ms_nNumberOfArrayImageDataShown += 1;
	}
	else
	{
		ms_nNumberOfArrayImageDataShown -= 1;
	}
	Locker.unlock();
	ASAbstractData::setShown(shown);
}

// ��̬����
// �õ���ǰ�Ѿ�������������
int ASArrayImageData::getNumOfArrayImageData()
{
	return ASArrayImageData::ms_nNumOfArrayImageData;
}
// �õ���ǰ�Ѿ���ʾ����������
int ASArrayImageData::getNumberOfArrayImageDataShown()
{
	return ASArrayImageData::ms_nNumberOfArrayImageDataShown;
}
// �õ���ǰ������ʾ�����ݣ�û�з���nullptr
ASArrayImageData* ASArrayImageData::getTopLayerDisplayingArrayImageData()
{
	ASArrayImageData* TopLayerDisplayingArrayImageData = nullptr;
	int crntTopLayer = -1;
	for (ASAbstractData* item = ASDataStructureWalker::bigen_inherit(DataType_ArrayImageData); item != nullptr; item = ASDataStructureWalker::next_inherit(DataType_ArrayImageData))
	{
		ASArrayImageData* crntDataNode = (ASArrayImageData*)item;
		if (crntDataNode->isShown() && crntDataNode->getLayer() > crntTopLayer)
		{
			crntTopLayer = crntDataNode->getLayer();
			TopLayerDisplayingArrayImageData = crntDataNode;
		}
	}
	return TopLayerDisplayingArrayImageData;
}

// �ж�����m_pImageData�ǻҶ�ͼ���Ǳ�ǩͼ������m_ArrayImageDataType��m_nColorMap����ȡ����ʱʹ��
void ASArrayImageData::checkDataTypeAndColorMap()
{
	QMutexLocker Locker(m_Mutex);
	int Datatype = this->m_pImageData->GetScalarType();
	int dim[3];
	this->m_pImageData->GetDimensions(dim);

	double ValuePool[100];
	int ValueSize = 0;
	double crntValue;
	bool b;
	for (int pix = 0; pix < dim[0]; pix += 3)
	{
		for (int piy = 0; piy < dim[1]; piy += 3)
		{
			for (int piz = 0; piz < dim[2]; piz += 3)
			{
				switch (m_pImageData->GetScalarType())
				{
					vtkTemplateMacro(crntValue = PosCheckWithoutValue<VTK_TT>(pix, piy, piz, m_pImageData));
				default:
					break;
				}
				b = false;
				for (int i = 0; i < ValueSize; i++)
				{
					if (crntValue == ValuePool[i])
					{
						b = true;
						break;
					}
				}
				if (b == false)
				{
					ValuePool[ValueSize++] = crntValue;
				}
				if (ValueSize >= 100)
				{
					this->m_ArrayImageDataType = EMGrayscaleImage;
					this->m_nColorMap = ColorMap_Gray;
					return;
				}
			}
		}
	}
	this->m_ArrayImageDataType = EMMultiLabelImage;
	this->m_nColorMap = ColorMap_Multilabel;
	//if (ValueSize == 2)
	//{
	//	this->m_ArrayImageDataType = EMMultiLabelImage;
	//	this->m_nColorMap = ColorMap_Mask;
	//}
	//else
	//{
	//	this->m_ArrayImageDataType = EMMultiLabelImage;
	//	this->m_nColorMap = ColorMap_Multilabel;
	//}
}
// �������ݷ�Χ������m_adImageExtent����ȡ����ʱʹ��
void ASArrayImageData::checkDataExtent()
{
	QMutexLocker Locker(m_Mutex);
	double* pOrigin = this->m_pImageData->GetOrigin();
	double* pSpace = this->m_pImageData->GetSpacing();
	int*    pExtent = this->m_pImageData->GetExtent();

	this->m_adDataExtent[0] = pOrigin[0];
	this->m_adDataExtent[1] = pOrigin[0] + pSpace[0] * (pExtent[1] - pExtent[0]);
	this->m_adDataExtent[2] = pOrigin[1];
	this->m_adDataExtent[3] = pOrigin[1] + pSpace[1] * (pExtent[3] - pExtent[2]);
	this->m_adDataExtent[4] = pOrigin[2];
	this->m_adDataExtent[5] = pOrigin[2] + pSpace[2] * (pExtent[5] - pExtent[4]);

	this->m_NumberOfFrames = this->m_pImageData->GetNumberOfScalarComponents();
}
// �ж�����m_pImageData�Ƿ�ΪCTͼ�񣬸���m_adWindowLevel����ȡ����ʱʹ��
void ASArrayImageData::checkDataIsCTOrNot()
{
	QMutexLocker Locker(m_Mutex);
	double dMin = this->m_pImageData->GetScalarRange()[0];
	double dMax = this->m_pImageData->GetScalarRange()[1];
	if (this->m_ArrayImageDataType == EMGrayscaleImage && dMin < -800 && dMax > 800)  // �жϸ�Ӱ��ΪCT
	{
		this->m_adWindowLevel[0] = 800;
		this->m_adWindowLevel[1] = 80;
	}
	else
	{
		this->m_adWindowLevel[0] = (dMax - dMin) / 2;	//window
		this->m_adWindowLevel[1] = (dMin + dMax) / 2;	//level
	}
}
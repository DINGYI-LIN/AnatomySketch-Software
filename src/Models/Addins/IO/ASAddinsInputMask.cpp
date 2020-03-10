#include "ASAddinsInputMask.h"
#include "ASArrayImageData.h"
#include "ASAbstractData.h"
#include "ASDataStructureWalker.h"
#include "ASVisualizationManager.h"
#include "ASArrayImageData.h"
#include "ASAddinsComboBox.h"
#include "ASTransAddins.h"
#include "ASAddinsBase.h"
#include "ASOperation.h"
#include <vtkImageIterator.h>
#include <vtkImageExtractComponents.h>
#include <vtkMetaImageWriter.h>
#include <QFileInfo>
#include <QDir>
#include <QTextCodec>

using namespace std::placeholders;
template<typename TIn>
void ValueFilling(vtkImageData* WorkingData, float* target)
{
	vtkImageIterator<TIn>it(WorkingData, WorkingData->GetExtent());
	unsigned long int index = 0;
	while (!it.IsAtEnd())
	{
		TIn* inSI = it.BeginSpan();
		TIn* inSIEnd = it.EndSpan();
		while (inSI != inSIEnd)
		{
			target[index] = (float)*inSI;
			++index;
			++inSI;
		}
		it.NextSpan();
	}
}

ASAddinsInputMask::ASAddinsInputMask(ASAddinsBase* parent)
	: ASAddinsInputNode(parent)
{
	m_Type = AddinInput_Mask;
	m_Combobox = new ASAddinsComboBox();
	Fun f = std::bind(&ASAddinsInputMask::ComboBoxCallBack, this, _1);
	m_Combobox->SetCallBack(f);
}

ASAddinsInputMask::~ASAddinsInputMask()
{
	m_Combobox->deleteLater();
}

// DataNode
void ASAddinsInputMask::SetImageData(ASArrayImageData* data)
{
	this->m_ImageData = data;
}
// Combobox
QComboBox* ASAddinsInputMask::GetCombobox()
{
	return this->m_Combobox;
}
// ImageData
ASArrayImageData* ASAddinsInputMask::GetImageData()
{
	if (m_ImageData)
	{
		return m_ImageData;
	}
	// 1 ��Ӧ����
	ASArrayImageData* ArrayImage = nullptr;
	for (ASAbstractData* item = ASDataStructureWalker::bigen_inherit(DataType_ArrayImageData);
		item != nullptr;
		item = ASDataStructureWalker::next_inherit(DataType_ArrayImageData))
	{
		if (item->getName() == m_Combobox->currentText())
		{
			ArrayImage = static_cast<ASArrayImageData*>(item);
		}
	}
	if (ArrayImage == nullptr)
	{
		return nullptr;
	}
	return ArrayImage;
}
// �õ���ָ�룬����argc��sΪ����
void* ASAddinsInputMask::GetVoidPoint(const QString s)
{
	bool unMask = (m_Combobox->currentIndex() == 2);
	vtkSmartPointer<vtkImageData> data;
	if (unMask)
	{
		// ������
		ASAbstractData* Target = this->m_Parent->GetHost()->getFather();
		if (!Target->isTypeInherited(DataType_ArrayImageData))
		{
			return nullptr;
		}
		ASArrayImageData* TargetImg = static_cast<ASArrayImageData*>(Target);
		data = TargetImg->getArrayImageData();
	} 
	else
	{
		ASArrayImageData* datanode = this->GetImageData();
		if (!datanode)
		{
			return nullptr;
		}
		data = datanode->getArrayImageData();
	}
	if (s == "Array")
	{
		vtkSmartPointer<vtkImageData> crntData = nullptr;
		int Components = data->GetNumberOfScalarComponents();
		if (Components > 1)
		{
			vtkSmartPointer<vtkImageExtractComponents> ext =
				vtkSmartPointer<vtkImageExtractComponents>::New();
			ext->SetInputData(data);
			int F = ASVisualizationManager::GetDisplayFrame();
			if (F >= Components)
			{
				F = Components - 1;
			}
			ext->SetComponents(F);
			ext->Update();
			crntData = ext->GetOutput();
		}
		else
		{
			crntData = data;
		}
		int dim[3];
		crntData->GetDimensions(dim);
		unsigned long int sz = dim[0] * dim[1] * dim[2];
		m_Data = new float[sz];
		if (unMask)
		{
			// ������
			for (unsigned long int i = 0; i < sz; i++)
			{
				m_Data[i] = 1;
			}
		} 
		else
		{
			switch (crntData->GetScalarType())
			{
				vtkTemplateMacro(ValueFilling<VTK_TT>(crntData, m_Data));
			default:
				break;
			}
		}
		return m_Data;
	}
	else if (s == "Dimensions")
	{
		data->GetDimensions(m_Dim);
		return m_Dim;
	}
	else if (s == "Origin")
	{
		data->GetOrigin(m_Origin);
		return m_Origin;
	}
	else if (s == "Spacing")
	{
		data->GetSpacing(m_Spacing);
		return m_Spacing;
	}
	else
	{
		return nullptr;
	}
}
// �������뵽Python�����е���ʱ�ļ�.1�ɹ���-1ʧ��
int ASAddinsInputMask::PythonInputGenerate()
{
	ASArrayImageData* datanode = this->GetImageData();
	vtkSmartPointer<vtkImageData> data = datanode->getArrayImageData();
	vtkSmartPointer<vtkImageData> crntData = nullptr;
	if (datanode->GetColorMode() == ColorMode_RGB)
	{
		crntData = data;
	}
	else
	{
		int Components = data->GetNumberOfScalarComponents();
		if (Components > 1)
		{
			vtkSmartPointer<vtkImageExtractComponents> ext =
				vtkSmartPointer<vtkImageExtractComponents>::New();
			ext->SetInputData(data);
			int F = ASVisualizationManager::GetDisplayFrame();
			if (F >= Components)
			{
				F = Components - 1;
			}
			ext->SetComponents(F);
			ext->Update();
			crntData = ext->GetOutput();
		}
		else
		{
			crntData = data;
		}
	}
	QString path = _pgmptr;
	QFileInfo fi = QFileInfo(path);
	QString file_path = fi.absolutePath();
	file_path = file_path + "/Plugins/_datacacke";
	QDir dir(file_path);
	if (dir.exists() == false)
	{
		dir.mkpath(file_path);
	}
	file_path = file_path + "/" + this->GetName() + ".mhd";
	vtkSmartPointer<vtkMetaImageWriter> MetaImageWriter = vtkSmartPointer<vtkMetaImageWriter>::New();
	MetaImageWriter->SetInputData(crntData);
	MetaImageWriter->SetCompression(false); // ��ѹ��
	std::string strStd = file_path.toStdString();
	QTextCodec *code = QTextCodec::codecForName("gb18030");
	if (code) strStd = code->fromUnicode(file_path).data();
	MetaImageWriter->SetFileName(strStd.data());
	MetaImageWriter->Write();
	return 1;
}

// ������ͷ�����
void ASAddinsInputMask::FreeMemory()
{
	if (m_Data)
	{
		delete m_Data;
		m_Data = nullptr;
	}
}
void ASAddinsInputMask::RefreshCombo(int datatype)
{
	if (!ASArrayImageData::isTypeInheritedStatic(datatype))
	{
		return;
	}
	QString oriStr = m_Combobox->currentText();
	m_Combobox->clear();
	m_Combobox->addItem(QObject::tr(u8"��ѡ������"));
	m_Combobox->addItem(QObject::tr(u8"�½�����"));
	m_Combobox->addItem(QObject::tr(u8"������"));
	for (ASAbstractData* item = ASDataStructureWalker::bigen_inherit(DataType_ArrayImageData);
		item != nullptr;
		item = ASDataStructureWalker::next_inherit(DataType_ArrayImageData))
	{
		m_Combobox->addItem(item->getName());
	}
	int i = m_Combobox->findText(oriStr);
	if (i >= 2)
	{
		m_Combobox->setCurrentIndex(i);
	}
	else
	{
		m_Combobox->setCurrentIndex(2);
	}
}
// ComboBox�ص�����
void ASAddinsInputMask::ComboBoxCallBack(ASAddinsComboBox* sender)
{
	if (sender == m_Combobox && m_Combobox->currentIndex() == 1)
	{
		ASAbstractData* ParentImgData = this->m_Parent->GetHost()->getFather();
		QString oriname = "Mask_Threshold";
		QString name = "Mask_Threshold";
		bool f = false;
		int n = 1;
		QList<ASAbstractData*>* children = ParentImgData->getChild();
		do 
		{
			f = false;
			for (int i = 0; i < children->size(); i++)
			{
				if (children->at(i)->getName() == name)
				{
					f = true;
					name = oriname + "_" + QString::number(n++);
				}
			}
		} while (f);
		if (ParentImgData->isTypeInherited(DataType_ArrayImageData))
		{
			Fun1 f = std::bind(&ASAddinsInputMask::NewMaskFinishCallBack, this);
			ASTransAddins::NewMask(ParentImgData, name, f);
			m_CallbackName = name + "_result";
		}		
	}
}
// �½�������ɻص�����
void ASAddinsInputMask::NewMaskFinishCallBack()
{
	m_Combobox->setCurrentText(m_CallbackName);
}
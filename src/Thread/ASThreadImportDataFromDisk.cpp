#include "ASThreadImportDataFromDisk.h"
#include "ASArrayImageData.h"
#include "ASPolyImageData.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QTextCodec>
#include <vtkImageImport.h>
#include <vtkMetaImageReader.h>
#include <vtkNIFTIImageReader.h>
#include <vtkBMPReader.h>
#include <vtkJPEGReader.h>
#include <vtkPNGReader.h>
#include <vtkImageReslice.h>

ASThreadImportDataFromDisk::ASThreadImportDataFromDisk(QObject *parent)
	: ASThreadBase(parent)
{
	this->setTerminationEnabled();
}

ASThreadImportDataFromDisk::~ASThreadImportDataFromDisk()
{

}

void ASThreadImportDataFromDisk::SetFileName(const QString c_FileName)
{
	m_FileName = c_FileName;
}

void ASThreadImportDataFromDisk::run()
{
	// ��ȡ�ļ���׺�������ж��ļ�����
	QFileInfo pFileInfo = QFileInfo(m_FileName);
	QString qstrSuffix = pFileInfo.suffix();
	if (qstrSuffix == "gz")
	{
		qstrSuffix = pFileInfo.completeSuffix();
	}

	//�ж��ļ�����
	if (qstrSuffix == "mhd" || qstrSuffix == "nii" || qstrSuffix == "nii.gz")
	{
		// ������
		ASArrayImageData* newData = this->LoadArrayImageData(m_FileName);
		emit signalDataLoadFinished(newData, DataType_ArrayImageData);
	}
	else if (strcmp(qstrSuffix.toStdString().c_str(), "stl") == 0 || strcmp(qstrSuffix.toStdString().c_str(), "ply") == 0 || strcmp(qstrSuffix.toStdString().c_str(), "obj") == 0)
	{
		// ������
		ASPolyImageData* newData = this->LoadPolyImageDate(m_FileName);
		emit signalDataLoadFinished(newData, DataType_PolyImageData);
	}
	else if (qstrSuffix == "bmp" || qstrSuffix == "png" || qstrSuffix == "jpg")
	{
		// ��ά����
		ASArrayImageData* newData = this->Load2DImageData(m_FileName);
		emit signalDataLoadFinished(newData, DataType_ArrayImageData);
	}

	//else if (strcmp(qstrSuffix.toStdString().c_str(), "dcm") == 0)
	//{
	//	//DICOM-RT����
	//	QString fileName = QFileInfo(filename).fileName();
	//	if (fileName.at(0) != 'R' || fileName.at(1) != 'S' || fileName.at(2) != '.')	//	����ļ�����ǰ׺�Ƿ�Ϊ"RS."
	//	{
	//		//��ǰ׺������"RS."
	//		int ret = QMessageBox::question(0, tr("message"), tr("The file name does not meet the DICOM-RT requirements. Whether to continue?"), QMessageBox::Yes, QMessageBox::Cancel);
	//		if (ret == QMessageBox::Cancel)
	//		{
	//			return;
	//		}
	//	}
	//	//����һ����������ȷ��RT��ԭ��ߴ�������Ϣ
	//	QStringList lst;
	//	QList<int> IDofLst;
	//	for (ASAbstractData* item = ASDataStructureWalker::bigen_inherit(EMArrayImageData); item != nullptr; item = ASDataStructureWalker::next_inherit(EMArrayImageData))
	//	{
	//		lst << item->getName();
	//		IDofLst << item->getDataNodeID();
	//	}
	//	//����ѯ�ʶԻ���
	//	bool ok = false;
	//	QString rtnstring = QInputDialog::getItem(0, tr("message"), tr("Choose an array image data to set coordinate information: "), lst, 0, true, &ok);
	//	if (ok)
	//	{
	//		vtkImageData* crntImageData = ((ASArrayImageData*)ASAbstractData::getDataNodeFromID(IDofLst.at(lst.indexOf(rtnstring))))->getArrayImageData();
	//		ASDICOMRTLoader Loader;
	//		Loader.setDataTree(m_DataTree);
	//		Loader.setFatherID(IDofLst.at(lst.indexOf(rtnstring)));
	//		Loader.setFileName(filename);
	//		if (Loader.update())
	//		{
	//			emit signalAddDICOMRTDisplay();
	//		}
	//	}
	//}
}

// ����������
ASArrayImageData* ASThreadImportDataFromDisk::LoadArrayImageData(const QString c_FileName)
{
	// 0 �½�һ��������
	ASArrayImageData* NewData = new ASArrayImageData();
	// 1 ��������
	vtkImageData* pImageData;
	QString filesuffix = QFileInfo(c_FileName).suffix();	//����ļ���׺
	if (filesuffix == "gz")
	{
		filesuffix = QFileInfo(c_FileName).completeSuffix();
	}
	if (filesuffix == "mhd")
	{
		// ʹ��vtkMetaImageReader����ͼ�����ݵĶ�ȡ
		vtkSmartPointer<vtkMetaImageReader> pMetaImageReader = vtkSmartPointer<vtkMetaImageReader>::New();
		std::string strStd = c_FileName.toStdString();
		QTextCodec *code = QTextCodec::codecForName("gb18030");
		if (code) strStd = code->fromUnicode(c_FileName).data();
		pMetaImageReader->SetFileName(strStd.data());
		pMetaImageReader->Update();
		pImageData = pMetaImageReader->GetOutput();
		NewData->setArrayImageData(pImageData);
		pMetaImageReader = nullptr;
	}
	else if (filesuffix == "nii" || filesuffix == "nii.gz")
	{
		// ʹ��vtkNIFTIImageReader ����ͼ�����ݵĶ�ȡ
		vtkSmartPointer<vtkNIFTIImageReader> pNIFTIImageReader = vtkSmartPointer<vtkNIFTIImageReader>::New();
		std::string strStd = c_FileName.toStdString();
		QTextCodec *code = QTextCodec::codecForName("gb18030");
		if (code) strStd = code->fromUnicode(c_FileName).data();
		pNIFTIImageReader->SetFileName(strStd.data());
		pNIFTIImageReader->Update();
		// ��ת
		vtkMatrix4x4* SFormM = pNIFTIImageReader->GetSFormMatrix();
		vtkMatrix4x4* QFormM = pNIFTIImageReader->GetQFormMatrix();
		if (QFormM)
		{
			pImageData = pNIFTIImageReader->GetOutput();
			// �õ������任����任֮�������ͼ�񣬱��浽������
			vtkSmartPointer<vtkImageReslice> ImageReslice = vtkSmartPointer<vtkImageReslice>::New();
			ImageReslice->SetInputData(pNIFTIImageReader->GetOutput());
			ImageReslice->SetInformationInput(pNIFTIImageReader->GetOutput());
			vtkSmartPointer<vtkMatrix4x4> transResult = vtkSmartPointer<vtkMatrix4x4>::New();
			vtkMatrix4x4::Invert(QFormM, transResult);
			double d = transResult->GetElement(0, 3);
			for (int i = 0; i < 3; i++)
			{
				transResult->SetElement(i, 0, -transResult->GetElement(i, 0));
				transResult->SetElement(i, 1, -transResult->GetElement(i, 1));
				
			}			
			ImageReslice->SetResliceAxes(transResult);
			ImageReslice->SetInterpolationModeToNearestNeighbor();
			ImageReslice->Update();
			NewData->setArrayImageData(ImageReslice->GetOutput());
		}
		else
		{
			NewData->setArrayImageData(pNIFTIImageReader->GetOutput());
		}
		pNIFTIImageReader = nullptr;
	}
	pImageData = nullptr;
	// 4 ��������
	NewData->setFileName(c_FileName);
	NewData->setLayer(ASArrayImageData::getNumOfArrayImageData());
	NewData->setName(QFileInfo(c_FileName).baseName());
	NewData->setVoidNode(false);
	NewData->DataInitAfterLoad();
	return NewData;
}
// ������������
ASPolyImageData* ASThreadImportDataFromDisk::LoadPolyImageDate(const QString c_FileName)
{
	// �½�һ����������
	ASPolyImageData* NewPolyData = new ASPolyImageData();

	// ��������
	vtkPolyData* pPolyData;
	QString filesuffix = QFileInfo(c_FileName).suffix();	//����ļ���׺
	if (strcmp(filesuffix.toStdString().c_str(), "stl") == 0)
	{
		// ʹ��vtkSTLReader����ͼ�����ݵĶ�ȡ
		vtkSmartPointer<vtkSTLReader> pSTLReader = vtkSmartPointer<vtkSTLReader>::New();
		std::string strStd = c_FileName.toStdString();
		QTextCodec *code = QTextCodec::codecForName("gb18030");
		if (code) strStd = code->fromUnicode(c_FileName).data();
		pSTLReader->SetFileName(strStd.data());
		pSTLReader->Update();
		pPolyData = pSTLReader->GetOutput();
		NewPolyData->setPolyData(pPolyData);
		pSTLReader = nullptr;
	}
	else if (strcmp(filesuffix.toStdString().c_str(), "ply") == 0)
	{
		// ʹ��vtkSTLReader����ͼ�����ݵĶ�ȡ
		m_pPLYReader = vtkSmartPointer<vtkPLYReader>::New();
		std::string strStd = c_FileName.toStdString();
		QTextCodec *code = QTextCodec::codecForName("gb18030");
		if (code) strStd = code->fromUnicode(c_FileName).data();
		m_pPLYReader->SetFileName(strStd.data());
		m_pPLYReader->Update();
		pPolyData = m_pPLYReader->GetOutput();
		NewPolyData->setPolyData(pPolyData);
		m_pPLYReader = nullptr;
	}
	else if (strcmp(filesuffix.toStdString().c_str(), "obj") == 0)
	{
		// ʹ��vtkOBJReader����ͼ�����ݵĶ�ȡ
		m_pOBJReader = vtkSmartPointer<vtkOBJReader>::New();
		std::string strStd = c_FileName.toStdString();
		QTextCodec *code = QTextCodec::codecForName("gb18030");
		if (code) strStd = code->fromUnicode(c_FileName).data();
		m_pOBJReader->SetFileName(strStd.data());
		m_pOBJReader->Update();
		pPolyData = m_pOBJReader->GetOutput();
		NewPolyData->setPolyData(pPolyData);
		m_pOBJReader = nullptr;
	}
	pPolyData = nullptr;

	// 3 ��������
	NewPolyData->setFileName(c_FileName);
	NewPolyData->setName(QFileInfo(c_FileName).baseName());
	NewPolyData->setVoidNode(false);

	NewPolyData->DataInitAfterLoad();

	return NewPolyData;
}
// �����ά����
ASArrayImageData* ASThreadImportDataFromDisk::Load2DImageData(const QString c_FileName)
{
	// 0 �½�һ��������
	ASArrayImageData* NewData = new ASArrayImageData();
	// 1 ��������
	vtkImageData* pImageData;
	QString filesuffix = QFileInfo(c_FileName).completeSuffix();	//����ļ���׺
	if (filesuffix == "bmp")
	{
		// ʹ��vtkBMPReader����ͼ�����ݵĶ�ȡ
		vtkSmartPointer<vtkBMPReader> pBMPReader = vtkSmartPointer<vtkBMPReader>::New();
		std::string strStd = c_FileName.toStdString();
		QTextCodec *code = QTextCodec::codecForName("gb18030");
		if (code) strStd = code->fromUnicode(c_FileName).data();
		pBMPReader->SetFileName(strStd.data());
		pBMPReader->Update();
		pImageData = pBMPReader->GetOutput();
		NewData->setArrayImageData(pImageData);
		if (pImageData->GetNumberOfScalarComponents() == 3)
		{
			NewData->SetColorMode(ColorMode_RGB);
		}
		pBMPReader = nullptr;
	}
	else if (filesuffix == "jpg")
	{
		// ʹ��vtkJPEGReader����ͼ�����ݵĶ�ȡ
		vtkSmartPointer<vtkJPEGReader> pJPEGReader = vtkSmartPointer<vtkJPEGReader>::New();
		std::string strStd = c_FileName.toStdString();
		QTextCodec *code = QTextCodec::codecForName("gb18030");
		if (code) strStd = code->fromUnicode(c_FileName).data();
		pJPEGReader->SetFileName(strStd.data());
		pJPEGReader->Update();
		pImageData = pJPEGReader->GetOutput();
		NewData->setArrayImageData(pImageData);
		if (pImageData->GetNumberOfScalarComponents() == 3)
		{
			NewData->SetColorMode(ColorMode_RGB);
		}
		pJPEGReader = nullptr;
	}
	else if (filesuffix == "png")
	{
		// ʹ��vtkPNGReader����ͼ�����ݵĶ�ȡ
		vtkSmartPointer<vtkPNGReader> pPNGReader = vtkSmartPointer<vtkPNGReader>::New();
		std::string strStd = c_FileName.toStdString();
		QTextCodec *code = QTextCodec::codecForName("gb18030");
		if (code) strStd = code->fromUnicode(c_FileName).data();
		pPNGReader->SetFileName(strStd.data());
		pPNGReader->Update();
		pImageData = pPNGReader->GetOutput();
		NewData->setArrayImageData(pImageData);
		if (pImageData->GetNumberOfScalarComponents() == 3)
		{
			NewData->SetColorMode(ColorMode_RGB);
		}
		pPNGReader = nullptr;
	}
	// ��������
	NewData->setFileName(c_FileName);
	NewData->setLayer(ASArrayImageData::getNumOfArrayImageData());
	NewData->setName(QFileInfo(c_FileName).baseName());
	NewData->setVoidNode(false);
	NewData->DataInitAfterLoad();
	return NewData;
}
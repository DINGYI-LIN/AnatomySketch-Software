//#include "ASSegmentation.h"
//#include <ASAddinsBase.h>
//#include <ASAddinsSegmentation.h>
//#include <QSettings>
//#include <QStringList>
//
//// �̳�ʱ��Ҫ�ڹ��캯�����趨 m_Datatype�� ����дwalkerCheck����
//
//ASSegmentation::ASSegmentation()
//{
//	m_Datatype = DataType_Segmentation;
//}
//
//ASSegmentation::~ASSegmentation()
//{
//}
//
//// ���ô˺������ͷŽڵ�
//void ASSegmentation::DeleteNode()
//{
//	delete this;
//}
//
//// ���������ж�
//// �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
//bool ASSegmentation::isTypeInherited(const int c_Type)
//{
//	if (c_Type == DataType_Segmentation || ASOperation::isTypeInherited(c_Type))
//	{
//		return true;
//	}
//	return false;
//}
//bool ASSegmentation::isTypeAbsolute(const int c_Type)
//{
//	if (c_Type == DataType_Segmentation)
//	{
//		return true;
//	}
//	return false;
//}
//bool ASSegmentation::isTypeInheritedStatic(const int c_Type)
//{
//	if (c_Type == DataType_Segmentation || ASOperation::isTypeInheritedStatic(c_Type))
//	{
//		return true;
//	}
//	return false;
//}
//// ��ʼ������
//void ASSegmentation::InitMethod(const QString c_name, const QString c_path)
//{
//	if (m_Addin)
//	{
//		delete m_Addin;
//		m_Addin = nullptr;
//	}
//	QSettings* configIniRead = new QSettings(c_path, QSettings::IniFormat);
//	QString s = configIniRead->value("Model/Type").toString();
//	// 1 Group: Model
//	// 1.0 Type
//	if (configIniRead->value("Model/Type").toString() == "Segmentation")
//	{
//		m_Addin = new ASAddinsSegmentation(this);
//	}		
//	else
//	{
//		qDebug("error: bad type. From ASSegmentation.cpp");
//		return;
//	}
//	// 1.1 Name
//	m_Addin->SetName(configIniRead->value("Model/Name").toString());
//	// 1.2 Interface
//	QString qstrType = configIniRead->value("Model/Interface").toString();
//	if (qstrType == "DLL")
//	{
//		m_Addin->SetInterfaceType(InterfaceType_DLL);
//		m_Addin->SetDLL(configIniRead->value("Model/DLL").toString());
//	} 
//	else if (qstrType == "Python")
//	{
//		m_Addin->SetInterfaceType(InterfaceType_Python);
//		m_Addin->SetPython(configIniRead->value("Model/Python").toString());
//	}	
//	// 1.3 Description
//	if (configIniRead->contains("Model/Description"))
//	{
//		m_Addin->SetDescription(configIniRead->value("Model/Description").toString());
//	}
//	// 2 Group: Input
//	configIniRead->beginGroup("Input");
//	QStringList crntKeys = configIniRead->childKeys();
//	QStringList keyWords;
//	keyWords << "ArrayImage" << "PolyImage" << "Mask" << "ROI" << "Seed" << "Contour" << "Landmark" << 
//		"Switch" << "Parameter";
//	for (int k = 0; k < keyWords.size(); k++)
//	{
//		int i = crntKeys.indexOf(keyWords.at(k));
//		if (i >= 0)
//		{
//			QStringList sl = configIniRead->value(crntKeys.at(i)).toStringList();
//			m_Addin->AddInput(crntKeys.at(i), sl);
//		}
//	}
//	int numofkeys = crntKeys.size();
//	QStringList sl;
//	sl << "ParentImage";
//	m_Addin->AddInput("ArrayImage", sl);
//	configIniRead->endGroup();
//	// 3 Group: Output
//	configIniRead->beginGroup("Output");
//	crntKeys = configIniRead->childKeys();
//	numofkeys = crntKeys.size();
//	for (int i = 0; i < numofkeys; i++)
//	{
//		QStringList sl = configIniRead->value(crntKeys.at(i)).toStringList();
//		for (int item = 0; item < sl.size(); item++)
//		{
//			m_Addin->AddOutput(crntKeys.at(i), sl.at(item));
//		}
//	}
//	configIniRead->endGroup();
//		
//	// 4 Group: Interface
//	if (qstrType == "DLL")
//	{
//		QStringList argv = configIniRead->value("Interface/argv").toStringList();
//		for (int i = 0; i < argv.size(); i++)
//		{
//			m_Addin->AppendInterface(argv.at(i), 0); // append argv
//		}
//	}
//	else if (qstrType == "Python")
//	{
//		QStringList py_entrence = configIniRead->value("Interface/py_entrence").toStringList();
//		for (int i = 0; i < py_entrence.size(); i++)
//		{
//			m_Addin->AppendInterface(py_entrence.at(i), 1); // append PYEntrence
//		}
//		QStringList py_export = configIniRead->value("Interface/py_export").toStringList();
//		for (int i = 0; i < py_export.size(); i++)
//		{
//			m_Addin->AppendInterface(py_export.at(i), 2); // append PYExport
//		}
//	}
//}
//void ASSegmentation::ClearMethod()
//{
//	if (m_Addin)
//	{
//		delete m_Addin;
//		m_Addin = nullptr;
//	}
//}
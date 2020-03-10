#include "ASFModelAddins.h"
#include "ASAddinsBase.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfoList>
#include <QSettings>

ASFModelAddins* ASFModelAddins::ms_SelfPointer = nullptr;

ASFModelAddins::ASFModelAddins(QObject *parent)
	: ASFunctionModelBase(parent)
{
	ms_SelfPointer = this;
	m_listAddins = new QList<structAddin *>;

	this->InitConfigurationFile();
}

ASFModelAddins::~ASFModelAddins()
{

}
// addin ����
int ASFModelAddins::GetNumOfAddins()
{
	return ms_SelfPointer->m_listAddins->size();
}
structAddin* ASFModelAddins::GetAddinAt(const int c_index)
{
	return ms_SelfPointer->m_listAddins->at(c_index);
}
// ��ǰ����
void ASFModelAddins::SetCrntOperation(ASOperation* opera)
{
	m_CrntOperation = opera;
}
ASOperation* ASFModelAddins::GetCrntOperation()
{
	return m_CrntOperation;
}

// ��ȡ�����ļ���ʼ��
void ASFModelAddins::InitConfigurationFile()
{
	QString ConfPath = QCoreApplication::applicationDirPath() + "/Plugins";
	QDir dir(ConfPath);
	if (!dir.exists())
	{
		return;
	}
	dir.setFilter(QDir::Files | QDir::NoSymLinks); //�������͹�������ֻΪ�ļ���ʽ
	QStringList filters;
	filters << "*.ini";
	dir.setNameFilters(filters);  //�����ļ����ƹ�����
	QFileInfoList list = dir.entryInfoList();
	int NumOfFiles = list.size();
	for (int crntFile = 0; crntFile < NumOfFiles; crntFile++)
	{
		structAddin* crntAddin;
		QString filename = ConfPath + "/" + list.at(crntFile).fileName();
		QSettings* configIniRead = new QSettings(filename, QSettings::IniFormat);
		QString s = configIniRead->value("Model/Type").toString();
		if (configIniRead->value("Model/Type").toString() == "ImgProcessing")
		{
			crntAddin = new structAddin;
			crntAddin->type = AddinType_ImgProcess;
		}
		else if (configIniRead->value("Model/Type").toString() == "MeshProcessing")
		{
			crntAddin = new structAddin;
			crntAddin->type = AddinType_MeshProcess;
		}
		else if (configIniRead->value("Model/Type").toString() == "Segmentation")
		{
			crntAddin = new structAddin;
			crntAddin->type = AddinType_Segmentation;
		}		
		else
		{
			continue;
		}
		crntAddin->path = filename;
		crntAddin->name = configIniRead->value("Model/Name").toString();
		m_listAddins->append(crntAddin);
	}
}
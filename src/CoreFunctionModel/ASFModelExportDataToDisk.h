#pragma once
#include "ASFunctionModelBase.h"

class ASThreadExportDataToDisk;
class ASAbstractData;

class ASFModelExportDataToDisk : public ASFunctionModelBase
{
	Q_OBJECT

public:
	ASFModelExportDataToDisk(QObject *parent = 0);
	~ASFModelExportDataToDisk();

	void WriteDataToDisk(const QString c_FileName, ASAbstractData* DataNode);
	void CancelWriteData(); // д�뱻ȡ��������д��

private:
	ASThreadExportDataToDisk* m_ThreadExportDataToDisk = nullptr;

	QString m_FileName;

private slots:
	
	// ���ݱ������
	void slotSaveDataFromDiskFinished();
};

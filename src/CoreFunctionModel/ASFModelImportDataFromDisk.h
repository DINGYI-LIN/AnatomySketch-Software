#pragma once
#include "ASFunctionModelBase.h"
#include <QString>

class ASThreadImportDataFromDisk;
class ASAbstractData;

class ASFModelImportDataFromDisk : public ASFunctionModelBase
{
	Q_OBJECT

public:
	ASFModelImportDataFromDisk(QObject *parent = 0);
	~ASFModelImportDataFromDisk();

	void LoadDataFromDisk(const QString c_FileName);
	void CancelLoadData(); // ��ȡ��ȡ����������ȡ

private:
	ASThreadImportDataFromDisk* m_ThreadImportDataFromDisk = nullptr;

private slots:
	
	// ���ݶ������
	void slotLoadDataFromDiskFinished(ASAbstractData* NewDataNode, int Type);
};

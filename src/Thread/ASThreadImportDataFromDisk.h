#pragma once
#include "ASThreadBase.h"
#include "ASAbstractData.h"
#include "ASPolyImageData.h"
#include "ASArrayImageData.h"
#include <vtkSmartPointer.h>
#include <vtkSTLReader.h>
#include <vtkPLYReader.h>
#include <vtkOBJReader.h>

class ASThreadImportDataFromDisk : public ASThreadBase
{
	Q_OBJECT

public:
	ASThreadImportDataFromDisk(QObject *parent = 0);
	~ASThreadImportDataFromDisk();

	void SetFileName(const QString c_FileName);

protected:
	void run();

private:
	// �ļ�·��
	QString m_FileName;

	vtkSmartPointer<vtkPLYReader> m_pPLYReader = nullptr;
	vtkSmartPointer<vtkOBJReader> m_pOBJReader = nullptr;

	// ����������
	ASArrayImageData* LoadArrayImageData(const QString c_FileName);
	// ������������
	ASPolyImageData* LoadPolyImageDate(const QString c_FileName);
	// �����ά����
	ASArrayImageData* Load2DImageData(const QString c_FileName);

signals:

	// ���ݶ�ȡ�ɹ�
	void signalDataLoadFinished(ASAbstractData* NewDataNode, int Type);

};

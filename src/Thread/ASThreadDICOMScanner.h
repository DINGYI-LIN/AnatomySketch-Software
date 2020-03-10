#pragma once
#include "ASThreadBase.h"
#include <vtkSmartPointer.h>
#include <vtkDICOMDirectory.h>
#include <QString>
#include <QMutex>

class ASThreadDICOMScanner : public ASThreadBase
{
	Q_OBJECT

public:
	ASThreadDICOMScanner(QObject *parent = 0);
	~ASThreadDICOMScanner();

	void SetScanPath(const QString c_ScanPath);
	void SetDICOMDirectory(vtkDICOMDirectory* DICOMDirectory);
	void SetMutex(QMutex* Mutex);

protected:
	void run();

private:

	// ɨ��·��
	QString m_ScanningPath;
	// DICOMDirectory
	vtkSmartPointer<vtkDICOMDirectory> m_DICOMDirectory;
	// �߳���������DICOMDirectory
	QMutex* m_MutexForDICOMDirectory;

signals:

	// ɨ�����
	void signalScanningFinished();
};

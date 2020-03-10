#pragma once
#include "ASThreadBase.h"
#include <vtkDICOMDirectory.h>
#include <vtkSmartPointer.h>

class ASDICOMData;
class ASAbstractData;

class ASThreadDICOMLoader : public ASThreadBase
{
	Q_OBJECT

public:
	ASThreadDICOMLoader(QObject *parent = 0);
	~ASThreadDICOMLoader();

	void SetDICOMDirSeries(vtkDICOMDirectory* dir, const int c_Series);

protected:
	void run();

private:
	vtkSmartPointer<vtkDICOMDirectory> m_DICOMDirectory;
	int m_Series;

signals:

	// ���ݶ�ȡ�ɹ���NewDataNode = nullptr��ʾ��ȡʧ��
	void signalDataLoadFinished(ASAbstractData* NewDataNode, int Type);

};

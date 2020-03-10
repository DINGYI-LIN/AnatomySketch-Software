#pragma once

#include "ASAddinsInputNode.h"
#include <vtkImageData.h>
#include <QComboBox>

class ASAddinsComboBox;
class ASArrayImageData;

class ASAddinsInputMask : public ASAddinsInputNode
{
public:
	ASAddinsInputMask(ASAddinsBase* parent);
	~ASAddinsInputMask();

	// DataNode
	void SetImageData(ASArrayImageData* data);
	// Combobox
	QComboBox* GetCombobox();
	// ImageData
	ASArrayImageData* GetImageData();
	// �õ���ָ�룬����argc��sΪ����
	virtual void* GetVoidPoint(const QString s);
	// �������뵽Python�����е���ʱ�ļ�.1�ɹ���-1ʧ��
	virtual int PythonInputGenerate();
	// ������ͷ�����
	virtual void FreeMemory();
	// Combo
	virtual void RefreshCombo(int datatype);
	// ComboBox�ص�����
	void ComboBoxCallBack(ASAddinsComboBox* sender);
	// �½�������ɻص�����
	void NewMaskFinishCallBack();

private:
	
	ASAddinsComboBox* m_Combobox = nullptr;
	ASArrayImageData* m_ImageData = nullptr;
	int m_Dim[3];
	double m_Origin[3];
	double m_Spacing[3];
	double m_WinLevel[2];

	float* m_Data = nullptr;
	QString m_CallbackName;

};

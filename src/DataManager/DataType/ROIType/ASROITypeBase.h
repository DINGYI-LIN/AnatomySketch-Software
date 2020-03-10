#pragma once
#include <QString>
#include <QColor>

// ROI����
#define ROIType_Base		0
#define ROIType_Cube		1

class ASROITypeBase
{
public:
	ASROITypeBase();
	~ASROITypeBase();
	virtual void DeleteNode();	// ���ô˺������ͷŽڵ�

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type); // �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
	virtual bool isTypeAbsolute(const int c_Type);
	static bool isTypeInheritedStatic(const int c_Type);
	int GetROIType();
	// �õ���������
	virtual void GetCenter(double* center);

	// ROIID
	void SetROIID(const int c_nID);
	int GetROIID();
	// Name
	void SetName(const QString c_Name);
	QString GetName();
	// Shown
	void SetShown(const bool c_shown);
	bool isShown();
	// Color
	void SetColor(QColor color);
	QColor GetColor();

protected:

	int	m_ROIType;	// ��������
	int m_ROIID;	// ͬһ��ROI�ļ��е�ID������ͬ
	QString m_Name; // ����
	bool m_isShown = true;
	QColor m_Color;
};

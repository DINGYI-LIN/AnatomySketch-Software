#pragma once

#include "ASAbstractData.h"

//���������ͣ��Ҷ�ͼ����ǩͼ
enum enumArrayImageDataType
{
	EMGrayscaleImage,
	EMMultiLabelImage
};

// �̳�ʱ��Ҫ�ڹ��캯�����趨 m_Datatype�� ����дwalkerCheck����

class ASImageData : public ASAbstractData
{
public:
	ASImageData();
	~ASImageData();
	virtual void DeleteNode();	// ���ô˺������ͷŽڵ�
	// ���������ж�
	virtual bool isTypeInherited(const int c_Type); // �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
	virtual bool isTypeAbsolute(const int c_Type);
	static bool isTypeInheritedStatic(const int c_Type);
};

#pragma once

#include "ASAbstractData.h"

class ASAddinsBase;

class ASOperation : public ASAbstractData
{
public:
	ASOperation();
	~ASOperation();
	virtual void DeleteNode();	// ���ô˺������ͷŽڵ�

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type); // �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
	virtual bool isTypeAbsolute(const int c_Type);
	static bool isTypeInheritedStatic(const int c_Type);

	void SetAddinType(const int c_Type);
	int GetAddinType();
	// method type
	ASAddinsBase* GetAddin();
	void InitMethod(const QString c_name, const QString c_path);
	void ClearMethod();

protected:

	ASAddinsBase* m_Addin = nullptr;
	int m_AddinType = 0; //AddinType_ImgProcess

};

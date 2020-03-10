#pragma once
#include "ASPipelineBase.h"
#include <vtkSmartPointer.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <QList>

typedef struct structTextPipe
{
	int textID;
	int VeiwLabel;
	vtkSmartPointer<vtkTextProperty> pTexProper;
	vtkSmartPointer<vtkTextActor> textActor;
}structTextPipe;

class ASPipelineText : public ASPipelineBase
{
public:
	ASPipelineText(const int c_ID);
	~ASPipelineText();

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type);
	virtual bool isTypeAbsolute(const int c_Type);
	virtual void DeleteNode();	// ���ô˺������ͷŹ���

	// �麯������ͼ����ı�
	virtual void Update2DTransformMatrix();

	// ��ʾ���֣���������ID����������ʱ��Ҫʹ��
	static int ShowText(const int c_ViewLabel, const QString c_text, double* pos1, double* pos2);
	// �Ƴ�����
	static void DeleteText(const int c_TextID);

private:

	// �ù�����Ψһ�ģ�Ψһ����
	static ASPipelineText* ms_SelfPointer;

	QList<structTextPipe*>* m_listTextPipe;
	
};

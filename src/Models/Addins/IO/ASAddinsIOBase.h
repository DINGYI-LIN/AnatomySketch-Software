#pragma once
#include <QString>

class ASAddinsBase;

#define AddinInput_Base			100
#define AddinInput_Node			101
#define AddinInput_ArrayImage	102
#define AddinInput_PolyImage	103
#define AddinInput_Mask			104
#define AddinInput_Landmark		105
#define AddinInput_Contour		106
#define AddinInput_Seed			107
#define AddinInput_ROI			108
#define AddinInput_Parameter	109
#define AddinInput_Switch		110

#define AddinOutput_Base		200
#define AddinOutput_Node		201
#define AddinOutput_ArrayImage	202
#define AddinOutput_PolyImage	203
#define AddinOutput_Parameter	204

class ASAddinsIOBase
{
public:
	ASAddinsIOBase(ASAddinsBase* parent);
	~ASAddinsIOBase();

	// Type
	int GetType();
	virtual bool isInput();
	// Name
	void SetName(const QString c_name);
	QString GetName();
	// �õ���ָ�룬����argc��sΪ����
	virtual void* GetVoidPoint(const QString s);
	// �������뵽Python�����е���ʱ�ļ�.1�ɹ���-1ʧ��
	virtual int PythonInputGenerate();
	// ������ͷ�����
	virtual void FreeMemory();

protected:

	int m_Type;
	QString m_Name;

	ASAddinsBase* m_Parent = nullptr;

private:


};

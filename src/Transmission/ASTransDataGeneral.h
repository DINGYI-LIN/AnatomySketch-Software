#pragma once
#include "ASTransmissionBase.h"

class ASAbstractData;
class ASArrayImageData;
class ASAnnotation;

class ASTransDataGeneral : public ASTransmissionBase
{
	Q_OBJECT

public:
	ASTransDataGeneral(QObject *parent = 0);
	~ASTransDataGeneral();

	// Ψһ����
	static ASTransDataGeneral* GetSelfPointer();

	// ����ĳ������Ϊ��ǰ����
	static void SetGeneratingData(ASAbstractData* crntData);
	static ASAbstractData* GetGeneratingData();
	static void ResetGeneratingData(); // ���º͵�ǰ�������

	// �������
	static ASAnnotation* NewAnnotationData(ASAbstractData* parent); // �½��������


private:
	// Ψһ����
	static ASTransDataGeneral* ms_SelfPointer;

	static ASArrayImageData* m_GeneratingData;


signals :
	void signalRefreshCrntData();
};

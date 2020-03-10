#pragma once
#include "ASTransmissionBase.h"
#include <functional>

class ASAbstractData;
class ASOperation;
class ASFModelAddins;

typedef std::function<void()> Fun1;

class ASTransAddins : public ASTransmissionBase
{
	Q_OBJECT

public:
	ASTransAddins(QObject *parent = 0);
	~ASTransAddins();

	// Ψһ����
	static ASTransAddins* GetSelfPointer();

	// �½��������
	static void NewAddinOperation(ASAbstractData* pParent, const int c_Type);
	// ��ǰ�ָ�
	static void SetCrntOperation(ASAbstractData* opera);
	static ASOperation* GetCrntOperation();
	// �����ݱ��Ƴ�
	static void DataRemoved(ASAbstractData* opera);

	// �½�����
	static void NewMask(ASAbstractData* pParent, QString name, Fun1 f);
	static void NewMaskFinish();

private:

	// Ψһ����
	static ASTransAddins* ms_SelfPointer;
	// �½����ֵķָ�
	ASOperation* m_NewMaskGenerating = nullptr;
	// �½�������ɻص�����
	Fun1 m_f = nullptr;
	// Model
	ASFModelAddins* m_Addins;

signals:

	// ˢ�·ָ���棬�����ɾ��֮��
	void signalRefreshWidget();
	// ��ǰ�ָ���仯
	void signalCurrentSegChanged();
	// ���õ�ǰ����
	void signalSetCurrentMethod(QString s);

};

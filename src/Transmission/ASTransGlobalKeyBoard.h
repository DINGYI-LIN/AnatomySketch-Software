#pragma once
#include "ASTransmissionBase.h"
#include <QKeyEvent>

class ASTransGlobalKeyBoard : public ASTransmissionBase
{
	Q_OBJECT

public:
	ASTransGlobalKeyBoard(QObject *parent = 0);
	~ASTransGlobalKeyBoard();

	// ȫ�ֶ���
	static ASTransGlobalKeyBoard* GetSelfPointer();
	// ���뺯��
	static void GlobalKeyBoard(QKeyEvent* pKeyEvent);

private:
	// Ψһ����
	static ASTransGlobalKeyBoard* ms_GlobalKeyBoard;

signals:
	// ����ȫ�ּ����ź�
	void signalGlobalKeyBoard(QKeyEvent* pKeyEvent);
};

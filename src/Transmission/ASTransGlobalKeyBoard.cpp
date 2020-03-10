#include "ASTransGlobalKeyBoard.h"

ASTransGlobalKeyBoard* ASTransGlobalKeyBoard::ms_GlobalKeyBoard = nullptr;

ASTransGlobalKeyBoard::ASTransGlobalKeyBoard(QObject *parent)
	: ASTransmissionBase(parent)
{
	ms_GlobalKeyBoard = this;
}

ASTransGlobalKeyBoard::~ASTransGlobalKeyBoard()
{

}

// ȫ�ֶ���
ASTransGlobalKeyBoard* ASTransGlobalKeyBoard::GetSelfPointer()
{
	return ms_GlobalKeyBoard;
}
// ���뺯��
void ASTransGlobalKeyBoard::GlobalKeyBoard(QKeyEvent* pKeyEvent)
{
	emit ms_GlobalKeyBoard->signalGlobalKeyBoard(pKeyEvent);
}

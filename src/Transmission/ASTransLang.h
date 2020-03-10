#pragma once
#include "ASTransmissionBase.h"

class ASTransLang : public ASTransmissionBase
{
	Q_OBJECT

public:
	ASTransLang(QObject* parent = nullptr);
	~ASTransLang();

	// Ψһ����
	static ASTransLang* GetSelfPointer();
	// Ĭ������
	static bool GetLang();
	static void SetLang(bool checked);

	// ���Ը���
	static void LanguageChange(bool checked);


private:

	// Ψһ����
	static ASTransLang* ms_LangChange;
	// Ĭ������
	static bool default_lang;


signals:

	// �������Ը����ź�
	void signalLanguageChange(bool checked);

};

#pragma once
#include "ASTransmissionBase.h"

class ASTransTheme : public ASTransmissionBase
{
Q_OBJECT

public:
	ASTransTheme(QObject* parent = nullptr);
	~ASTransTheme();

	// Ψһ����
	static ASTransTheme* GetSelfPointer();
	// Ĭ������
	static bool GetTheme();
	static int GetToolBtnDown();
	static void SetToolBtnDown(int crntBtnDown);
	static void SetTheme(bool checked);

	// �������
	static void QSSChange(bool checked);
	static void BackgroundChange(bool checked);
	static void OperationbarThemeChange(bool checked);
	static void SidebarChange(bool checked);


private:

	// Ψһ����
	static ASTransTheme* ms_ThemeChange;
	// Ĭ������
	static bool default_theme;
	// ���°�ť
	static int toolBtnDown;


signals:

	// ������������ź�
	void signalQSSChange(bool checked);
	void signalOperationbarThemeChange(bool checked);
	void signalBackgroundChange(bool checked);
	void signalSidebarChange(bool checked);
};

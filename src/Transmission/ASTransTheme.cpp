#include "ASTransTheme.h"
#include "ASTransSetting.h"
#include <QSettings>

ASTransTheme* ASTransTheme::ms_ThemeChange = nullptr;
bool ASTransTheme::default_theme = NULL;
int ASTransTheme::toolBtnDown = -1;

ASTransTheme::ASTransTheme(QObject* parent)
	: ASTransmissionBase(parent)
{
	ms_ThemeChange = this;
	// ��ȡ��������
	default_theme = ASTransSetting::GetSetting()->value("DefaultTheme").toBool();
}

ASTransTheme::~ASTransTheme()
{
}

// Ψһ����
ASTransTheme* ASTransTheme::GetSelfPointer()
{
	return ms_ThemeChange;
}

int ASTransTheme::GetToolBtnDown()
{
	return toolBtnDown;
}

bool ASTransTheme::GetTheme()
{
	return default_theme;
}

void ASTransTheme::SetToolBtnDown(int crntBtnDown)
{
	toolBtnDown = crntBtnDown;
}

void ASTransTheme::SetTheme(bool checked)
{
	default_theme = checked;
}

// ������������ź�
void ASTransTheme::QSSChange(bool checked)
{
	emit ms_ThemeChange->signalQSSChange(checked);
}

void ASTransTheme::BackgroundChange(bool checked)
{
	emit ms_ThemeChange->signalBackgroundChange(checked);
}

void ASTransTheme::OperationbarThemeChange(bool checked)
{
	emit ms_ThemeChange->signalOperationbarThemeChange(checked);
}

void ASTransTheme::SidebarChange(bool checked)
{
	emit ms_ThemeChange->signalSidebarChange(checked);
}

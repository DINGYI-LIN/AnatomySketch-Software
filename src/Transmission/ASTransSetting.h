#pragma once
#include "ASTransmissionBase.h"
class QSettings;

class ASTransSetting : public ASTransmissionBase
{
Q_OBJECT

public:
	ASTransSetting(QObject* parent = nullptr);
	~ASTransSetting();

	// Ψһ����
	static ASTransSetting* GetSelfPointer();

	// ��ȡ��д������
	static QSettings* GetSetting();

private:
	// Ψһ����
	static ASTransSetting* ms_Setting;

	static QSettings* SettingConfig;
};

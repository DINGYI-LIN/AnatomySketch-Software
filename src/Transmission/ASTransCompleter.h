#pragma once
#include "ASTransmissionBase.h"
#include <QSettings>
#include <QColor>

typedef struct structCompleterItem
{
	QString name;
	int id;
	QColor color;
}structCompleterItem;

class ASTransCompleter : public ASTransmissionBase
{
	Q_OBJECT

public:
	ASTransCompleter(QObject *parent = 0);
	~ASTransCompleter();

	// ȫ�ֶ���
	static ASTransCompleter* GetSelfPointer();
	static QList<structCompleterItem*>* GetLandmarkList();
	static QList<structCompleterItem*>* GetStructureList();

private:
	// Ψһ����
	static ASTransCompleter* ms_SelfPointer;

	void InitConfiguration();
	// �ڲ�����
	void UpdateGroup(QSettings* settings, QString group, QList<structCompleterItem*>* plist); 
	
	QList<structCompleterItem*>* m_plistLandmarksItems;
	QList<structCompleterItem*>* m_plistStructuresItems;

signals:

};

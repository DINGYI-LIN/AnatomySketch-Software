#pragma once

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QColor>

class ASDataManager;

class ASDialogNewSeedsFile : public QDialog
{
	Q_OBJECT

public:
	ASDialogNewSeedsFile(QWidget *parent);
	~ASDialogNewSeedsFile();

	QString m_NameOfNewSeeds;
	int m_nLabel = 0;
	QColor m_Color;

private:

	//����Ԫ��
	QLabel*				m_LabelName;				// "Name:"
	QLabel*				m_LabelValue;				// "Value:"
	QLabel*				m_LabelColor;				// "Color:"
	QLineEdit*			m_LineEditNameInput;		// �����ǩ��
	QSpinBox*			m_SpinBoxValueInput;		// �����ǩֵ
	QLabel*				m_LabelColorDisplay;		// ��ʾ��ǰ��ǩ����Ӧ����ɫ
	QPushButton*		m_PushButtonCancel;			// ȡ��
	QPushButton*		m_PushButtonOK;				// ����

	//GUI init
	void UIInit();
	//ˢ����ɫ��ʾlabel
	void refreshColorDisplay();

private slots:

	void slotLineEdittextChanged();
	void slotSpinBoxValueChanged();

};

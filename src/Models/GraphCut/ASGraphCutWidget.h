#pragma once

#include "ASWidgetInSideBarBase.h"
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QListWidget>

class ASGraphCutWidget : public ASWidgetInSideBarBase
{
	Q_OBJECT

public:
	ASGraphCutWidget(QWidget *parent);
	~ASGraphCutWidget();

private:

	// ����Ԫ��
	QComboBox* m_ComboBoxImageFile;
	QListWidget* m_ListWidgetSeeds;
	QLineEdit* m_LineEditOutput;	
	QDoubleSpinBox* m_DSpinBoxLambda;
	QDoubleSpinBox* m_DSpinBoxDelta;
	QComboBox* m_ComboBoxNeighbor;
	QLineEdit* m_LineEditPostProcessing;
	QCheckBox* m_CheckboxMarchingCub;
	QSpinBox* m_SmoothIterations;
	QCheckBox* m_CheckboxQuery;
	QPushButton* m_PushButtonGenerate;
	// �����ʼ��
	void UIInit();
	//������������index��Ӧ��ID,�ļ�����ʱorder���ܻᷢ���仯
	QList<int> m_listIDImageFileIndex;
	QList<int> m_listIDSeedsListIndex;
	int m_ncrntIDOfImageFile = -1;
	//������Ŀ�Ĳ���Ч�ı�־λ����ˢ����Ŀ����ʱ��ʹ��ʧЧ
	bool isEnabelforslotComboBoxCurrentIndexChanged = true;
	// ˢ������ѡ��
	void UpdateComboBoxImage();
	// ˢ�����ӵ��б�
	void UpdateSeedsList();

private slots:

	// ���ɽ������checkbox
	void slotMarchingCubChecked(int state);
	// ���ɰ�ť����
	void slotGenerateClicked();
	// ˢ���ļ�����ѡ��
	void slotRefreshDataComboBox(int c_AffectType);
	// ����ѡ��仯
	void slotComboBoxChanged(int Index);
	// ����ģ��ʹ��״̬�л�
	void slotMaskEnabledChanged();
};

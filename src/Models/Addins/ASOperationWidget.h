#pragma once

#include "ASWidgetInSideBarBase.h"
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class ASAddinsBase;

class ASOperationWidget : public ASWidgetInSideBarBase
{
	Q_OBJECT

public:
	ASOperationWidget(QWidget *parent);
	~ASOperationWidget();

	virtual void SetEnabled(const bool c_bEnabled);

private:

	// ����Ԫ��
	QComboBox* m_Combox;
	QPushButton* m_GeneButn;
	QLabel* m_Description;
	QPushButton* m_BtnFinish;
	QVBoxLayout* m_mainlayout;
	void ComboInit(const int c_AddinType);
	void RemoveLayout(QLayout* layout);

	ASAddinsBase* m_crntOperation= nullptr;
	bool m_FlagFromAddin = false;

	// ���ݵ�ǰ����ˢ�½���
	void RefreshCrntOperationUI();

protected:

	bool m_GeneratingCombo = false; // �����������ɷ��������˵��ı�־λ
	

private slots :

	// combobox 
	void slotComboxChanged();
	// PushButton
	void slotGenerate();
	// ˢ�£���ɾ�����ݺ�
	void slotRefreshWidget();
	// ������ǰ����
	void slotCrntOperationChanged();
	// �����б�仯��ˢ��combobox
	void slotUpdateDataNodeLists(int Type);
	// ���õ�ǰ����
	void slotSetCurrentMethod(QString s);
	// Finish
	void slotFinish();

signals:

};

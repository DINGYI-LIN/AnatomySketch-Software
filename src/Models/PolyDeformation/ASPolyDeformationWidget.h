#pragma once

#include "ASWidgetInSideBarBase.h"
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QListWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QDoubleSpinBox>
#include <QTimer>

class ASAbstractData;

typedef struct structPolyDeformationInputDataItem
{
	QListWidgetItem* listWedgetItem;
	QCheckBox *checkboxInItem;	//qListWidget��ÿһ�е�checkbox
	int ID;						//qListWidget��item��Ӧ��ID
}structPolyDeformationInputDataItem;


class ASPolyDeformationWidget : public ASWidgetInSideBarBase
{
	Q_OBJECT

public:
	ASPolyDeformationWidget(QWidget *parent);
	~ASPolyDeformationWidget();

	virtual void SetEnabled(const bool c_bEnabled);

	// ���տ�ݼ������źţ������������
	//void HotKeyPolyAdjustment(enumHotKeyPolyAdj hotK);

private:

	QList<structPolyDeformationInputDataItem*>* m_listItemOfListWidget;

	//������Ŀ�Ĳ���Ч�ı�־λ����ˢ����Ŀ����ʱ���ǲ�ʧЧ
	bool isEnabelforslotComboBoxCurrentIndexChanged = true;
	
	bool m_isZoomSameOperating = false;
	bool m_isZoomValueChangedDisabled = false;
	//QTimer* m_timerForZoom;

	//-------------------- ����Ԫ�� --------------------
	//����
	QLabel*				m_LabelInput;
	QListWidget*		m_pListWidget;
	QPushButton*		m_PushButtonUndo;

	//�����ʼ��
	void UIInit();
	//���б��е�QListWidgetItem��ַ�õ�InputDataItem��ַ
	structPolyDeformationInputDataItem* getInputDataItemFromQListWidgetItem(QListWidgetItem* pItem);

protected:
	//void keyPressEvent(QKeyEvent * event);

private slots:

	// ˢ���ļ�����ѡ��
	void slotRefreshDataComboBox(int c_AffectType);
	//����������
	void slotUndoClicked();
	//checkbox״̬�ı�
	void slotFFDCheckBoxChecked(int s);
	// �����ǰ������ʽ�ı�
	void slotInteractorStyle2DChanged(int interactor);
	// ����ѡ��״̬�ı�
	void slotChoosnChanged(int ID);
	// ����ȫ�ּ����ź�
	void slotGlobalKeyBoard(QKeyEvent* pKeyEvent);
	// ʹ��Alt+���ѡ��polyDeformation�������棬��������ASDisplay2D��ID
	void slotPolyDeformationChoosePolyData(int nID);
	// �����Ƿ���ʾ״̬�ı�
	void slotDataShownChanged(ASAbstractData* DataNode);

signals:

	// ѡ��PolyDeformation��������ʱ�޸������߿��ˢ����������ʾ
	// ˢ���ļ���ʾ����������ɫ���Ƿ���ʾ�ȣ���ͨ���˷���ˢ��
	void signalRefreshDataDisplay(ASAbstractData* datanode);
};

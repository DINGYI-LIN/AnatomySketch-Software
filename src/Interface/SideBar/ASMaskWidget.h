#pragma once

#include "ASWidgetInSideBarBase.h"
#include <QLabel>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QTabWidget>

class ASSignalLinker;
class ASDataManager;

class ASMaskWidget : public ASWidgetInSideBarBase
{
	Q_OBJECT

public:
	ASMaskWidget(QWidget *parent);
	~ASMaskWidget();

	virtual void SetEnabled(const bool c_bEnabled);

private:

	ASSignalLinker* m_SignalLinker;	//�����ͨ���ź�������
	ASDataManager* m_pDataManager;	//���ݹ������ĵ�ַ

	//������������index��Ӧ��ID,�ļ�����ʱorder���ܻᷢ���仯
	QList<int> m_listIDForIndex;
	QList<int> m_listIDForIndexMData;

	int m_crntIDOfComboBox = -1;
	int m_crntIDOfMdata = -1;
	//������Ŀ�Ĳ���Ч�ı�־λ����ˢ����Ŀ����ʱ��ʹ��ʧЧ
	bool isEnabelforslotComboBoxCurrentIndexChanged = true;
	//�����������ʱ��ʹˢ����ʾ���ź�ʧЧ
	bool isEnabelforslotSettingValueChanged = true;


	//����Ԫ��
	QDoubleSpinBox*		m_DSBoxCoRange[6]; // 0: XMin 1: XMax 2: YMin 3: YMax 4: ZMin 5: ZMax
	QPushButton*		m_PushButtonCoRange[6]; // 0: XMin 1: XMax 2: YMin 3: YMax 4: ZMin 5: ZMax
	QComboBox*			m_ComboBoxInput;
	QTabWidget*			m_TabWidget;
	// ֱ�ӻҶ�ֵ��Χ
	QDoubleSpinBox*		m_DSBoxGrayRange[2]; //0: min 1: max
	// ѡ������ͼ�����Ҷ�ֵ��Χ
	QComboBox*			m_ComboBoxMDataInput;
	QDoubleSpinBox*		m_DSBoxMDataGrayRange[2]; //0: min 1: max
	QLabel*				m_LabelMDataStatus;

	//�����ʼ��
	void UIInit();
	// ���¿ؼ�����Χ����ǰֵ
	void UpdataSpinBox();
	// �ж�����ͼ���Ƿ����Ҫ��
	void MDataCheck();

private slots:

	//�ļ�����ѡ��ѡ��ı�
	void slotCrntIndexChanged(int index);
	void slotCrntIndexChangedMData(int index);
	//�������ò����ı䣬������������
	void slotSettingValueChanged();
	//ˢ�������ļ�����ѡ��
	void slotRefreshDataComboBox(int c_AffectType);
	// ����ͼ��ѡ������
	void slotSelectFromView(bool b);
	// �����ǰ������ʽ�ı�
	void slotInteractorStyle2DChanged(int interactor);
	// ������������
	void slotSetMaskInteractor(double x, double y, double z);
	// ��ҳ�л�
	void slotTabCurrentChanged(int index);

signals:

	//���ָ��º�ˢ����ʾ
	void signalRefreshMaskDisplay();
	//����ʹ��״̬�ı�������ʾ
	void signalMaskStateChanged();

};

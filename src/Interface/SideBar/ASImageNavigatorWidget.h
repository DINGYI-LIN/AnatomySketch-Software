#pragma once

#include "ASWidgetInSideBarBase.h"
#include <QLabel>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>

class ASSignalLinker;
class ASDataManager;

class ASImageNavigatorWidget : public ASWidgetInSideBarBase
{
	Q_OBJECT

public:
	ASImageNavigatorWidget(QWidget *parent);
	~ASImageNavigatorWidget();

private:
	ASSignalLinker* m_SignalLinker;	//�����ͨ���ź�������
	ASDataManager* m_pDataManager;	//���ݹ������ĵ�ַ

	//����Ԫ��
	QDoubleSpinBox*	m_LocationDoubleSpinBox[3];		// ���㣬��������ϵ
	QSpinBox*		m_FocusSpinBox[3];				// ���㣬��������ϵ
	QSlider*		m_FocusSlider[3];				// ���㣬������
	QSpinBox*		m_TimeSpinBox;					// ʱ��
	QSlider*		m_TimeSlider;					// ʱ�䣬������
	QDoubleSpinBox* m_LevelWindowDoubleSpinBox[2];	// ��λ����
	QLabel*			m_Label[7];						// Label. 0:Location; 1:Axial; 2:Sagittal; 3:Coronal; 5:Level 6:Window

	//��ʾ��Χ
	double m_ImageExtent[6];
	double m_ImageLocation[3];		//ͼ�񽹵㣬��������ϵ
	double m_ImageSpace[3];
	int m_NumOfFrames = 1;
	int m_crntFrame;

	bool isValueChanging = false;

	//�����ʼ��
	void GUIInit();
	//���µĽ�����µ��ؼ���ʾ
	void GeneratePosition();

private slots:

	//�ؼ�ֵ�ı�
	// ����
	void slotLocationXValueChanged(double d);
	void slotLocationYValueChanged(double d);
	void slotLocationZValueChanged(double d);
	void slotFocusXValueChanged(int i);
	void slotFocusYValueChanged(int i);
	void slotFocusZValueChanged(int i);
	void slotSliderXValueChanged(int i);
	void slotSliderYValueChanged(int i);
	void slotSliderZValueChanged(int i);
	// ֡
	void slotTimeValueChanged(int i);
	// ��λ����
	void slotLevelValueChanged(double d);
	void slotWindowValueChanged(double d);

public slots:

	// �������½���
	void slotSetDisplayPosition(double PosX, double PosY, double PosZ);
	// ��������֡
	void slotSetDisplayFrame(const int c_Frame);
	// �������سߴ�
	void slotSetImageSpacing(double* Spacing);
	// ����ͼ��Χ��֡��
	void slotSetDisplayExtent(double* Extent, const int c_NumOfFrames);
	// �������´�λ����
	void slotSetWindowLevel(double window, double level);
	void slotUpdateWindow();
	void slotUpdateLevel();

signals:
};

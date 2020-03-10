#pragma once

#include <QWidget>
#include <QGridLayout>

//class ASSignalLinker;
class ASDiplayFrame;
class ASQVTKWidget;

//���������ֱ��
#define OpeBarLayoutLabel_Default	0		//���������ֱ��,Ĭ�ϲ���
#define OpeBarLayoutLabel_Sagittal	1		//���������ֱ��,ʸ״�棬Sagittal
#define OpeBarLayoutLabel_Coronal	2		//���������ֱ��,��״�棬Coronal
#define OpeBarLayoutLabel_Axial		3		//���������ֱ��,����棬Axial
#define OpeBarLayoutLabel_3D		4		//���������ֱ��,��ά��ͼ��3D

class ASOperationBar : public QWidget
{
Q_OBJECT

public:
	ASOperationBar(QWidget* parent);
	~ASOperationBar();

	// ��̬�������õ��ĸ�QVTKWidget��ָ��
	static void GetQVTKWidget(ASQVTKWidget** pQVTKWidget);

protected:
	// ���Ʊ߿�
	void paintEvent(QPaintEvent* e);

private:

	//ASSignalLinker* SignalLinker;	//�����ͨ���ź�������

	//�����ʼ�����������ִ��ڲ���
	void GUIInit();
	// ��̬������Ӧ��Ψһ�����еĺ���
	void fGetQVTKWidget(ASQVTKWidget** pQVTKWidget);
	// Ψһ�����ָ��
	static ASOperationBar* ms_pOperationBar;

	QGridLayout* m_OperationbarLayout;
	ASDiplayFrame* m_apDisplayFrame[4];

	int m_LayoutMode = OpeBarLayoutLabel_Default;

	void setLayoutMode(int mode);

private slots:

	void slotButtonLayoutClicked(int viewlabel);
	void slotCrossShairClicked(int viewlabel);

public slots:
	void slotBackgroundColorChange(bool checked);

};

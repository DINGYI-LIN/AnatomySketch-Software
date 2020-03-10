#pragma once

#include <QWidget>
#include <QList>
#include <QStackedWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QSplitter>
#include <QScrollArea>

class ASSignalLinker;

#define SIDEBAR_MINWIDTH			3         // �������С���
#define SIDEBAR_MAXWIDTH			500         // ����������

#define HSPLITTERHANDLEWIDTH			10			// ��������ȣ������ݹ��������·����ߵľ���

class ASDataManagerWidget;
class ASImageNavigatorWidget;
class ASMaskWidget;
class ASPaintingSeedsWidget;
class ASPaintingContourWidget;
class ASPaintingLandmarkWidget;
class ASPolyDeformationWidget;
class ASGraphCutWidget;
class ASOperationWidget;
class ASROIWidget;
class ASWidgetInSideBarBase;

typedef struct structWidgetInSideBarBelow
{
	int		ID;			
	ASWidgetInSideBarBase*	pWidget;
	QGroupBox* pGroupbox;
	QHBoxLayout* pLayout;
}structWidgetInSideBarBelow;

class ASSideBar : public QWidget
{
	Q_OBJECT

public:
	ASSideBar(QWidget *parent);
	~ASSideBar();

private:

	ASSignalLinker* m_SignalLinker;	//�����ͨ���ź�������

	//ģ��
	ASDataManagerWidget*		m_DataManagerWidget;		// ���ݹ����б�
	ASImageNavigatorWidget*		m_ImageNavigatorWidget;		// ͼ�񵼺�������ͼ�񽹵㡢��λ����
	//ASMaskWidget*				m_MaskWidget;				// ����
	ASPaintingSeedsWidget*		m_PaintingSeedsWidgets;		// ���ӵ�
	ASPaintingContourWidget*	m_PaintingContourWidget;	// ������
	ASPaintingLandmarkWidget*	m_PaintingLandmarkWidget;	// �궨��
	ASGraphCutWidget*			m_GraphCut;					// ͼ���㷨	
	ASPolyDeformationWidget*	m_PolyDeformation;			// �����ݱ���
	ASOperationWidget*			m_Operation;				// �������
	ASROIWidget*				m_ROI;						// ROI

	//�洢������ṹ�������
	QList<structWidgetInSideBarBelow*>* m_listWidgetInSideBarBelow;
	//����Ԫ��
	QScrollArea* m_ScrollArea;
	QWidget* m_BaseWidget;
	QGroupBox* m_GroupboxDatamanager;
	QHBoxLayout* m_SidebarLayout;
	QSplitter*  m_Splitter;

	//�����ʼ��
	void GUIInit();
	//��ģ���ʼ��
	void SubModuleInit();

public slots:

	//ͨ��������ѡ�������·���Widget
	void slotSetWidgetBelow(int IDOfWidget, bool isShown);
	// ����ı�
	void slotSidebarChange(bool checked);

signals:

	// �������������Ƿ���Ա�ʰȡ����������������
	void signalSetPolyDataContourPickable(bool pickable);
};

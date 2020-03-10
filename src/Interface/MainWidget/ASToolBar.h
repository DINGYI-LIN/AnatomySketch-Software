#pragma once

#include <QToolBar>
#include <QToolButton>
#include <QList>
#include <QString>

class AboutWidget;
class ASHelpWidget;

#define TOOLBAR_SIZE 60   // �������߶�;

//������ID���޸�ID���Ե�����ť����ʾ˳��ID���������Ҳ��ظ�
//#define TOOLBAR_OPEN				0		// ��
//#define TOOLBAR_DICOM				1		// ��DICOM
//#define TOOLBAR_CLOSEALL			2		// �ر���������
//#define TOOLBAR_EXPORT				3		// ����
#define ToolBar_ImageNavigator		0		// ������λ����ͽ���Ĺ���
#define TOOLBAR_ROI					1		// ����
#define TOOLBAR_PaintSeeds			2		// �������ӵ�
#define TOOLBAR_PaintContours		3		// ����������
#define TOOLBAR_PaintLandmarks		4		// ���Ʊ궨��
#define TOOLBAR_PolyDeformation		5		// PolyDeformation
//#define TOOLBAR_GraphCuts			10		// GraphCuts
//#define TOOLBAR_Help				11		// Help
//#define TOOLBAR_About				12		// About

typedef struct structTools {
	int ID;
	bool isBelowWidget = false;
	QToolButton *toolButton;
}structTools;

class ASToolBar : public QToolBar
{
	Q_OBJECT

public:
	ASToolBar(QWidget *parent);
	~ASToolBar();

protected:
	// ����Բ��
	void paintEvent(QPaintEvent* e);

private:

	//���水ť�Ͷ�ӦID
	QList<structTools*>* m_Tools;

	//���߰�ť��ʼ��
	void ToolsInit();
	//���߰�ťˢ����ʾ
	void ToolsDisplayRefresh();
	//��ID�õ�����
	structTools* gettool(int ID);
	// ��ǰ���µİ�ť
	void SetCrntTool(int ID, bool checked);

public slots:

	//�ڵ�ǰ������ʽͨ��ѡ���ļ��仯����Ҫ�ı�ʱ�������ź��ù������ı䰴ť״̬����datamanager����
	//void slotRefreshSeedsCuntourPushButtonState();

private slots:

	// �ر�ȫ��
	//void slotCloseAll();
	//// ����
	//void slotExport();
	// �������ӵ㹤��
	void slotPaintSeeds(bool checked);
	// ���������߹���
	void slotPaintContours(bool checked);
	// ���Ʊ궨�㹤��
	void slotPaintLandmarks(bool checked);
	// ������λ����ͽ���Ĺ���
	void slotImageNavigator(bool checked);
	// ROI
	void slotROI(bool checked);
	// PolyDeformation
	void slotPolyDeformation(bool checked);
	// GraphCuts
	void slotGraphCuts(bool checked);
	// �л���ǰ���߰�ť״̬
	void slotSetSideBarBelowWidget(int c_WidgetType, bool c_isShown);

	void slotBtnRst();
};

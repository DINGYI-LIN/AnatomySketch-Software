#include "ASToolBar.h"
//#include "ASTransAddDeleteData.h"
//#include "ASTransDICOMLoader.h"
#include "ASTransSidebarGeneral.h"
#include "ASMainWidget.h"
//#include "AboutWidget.h"
//#include "ASHelpWidget.h"
//#include "ASTransSeeds.h"
//#include "ASTransContour.h"
//#include "ASTransLandmark.h"
#include "ASAbstractData.h"
#include "ASTransTheme.h"
#include <QFileDialog>
#include <QDebug>
#include <QPainter>
#include <QMessageBox>

ASToolBar::ASToolBar(QWidget *parent)
	: QToolBar(parent)
{

	setContentsMargins(0, 0, 0, 0);
	//setFixedHeight(TOOLBAR_SIZE);
	//setFixedWidth(TOOLBAR_SIZE);
	this->setObjectName("Toolbar");
	this->setIconSize(QSize(TOOLBAR_SIZE, TOOLBAR_SIZE));
	this->setOrientation(Qt::Vertical);
	//�����û�е��ʱ��������ƶ������ڴ��ڱ߽�����
	setMouseTracking(true);

	m_Tools = new QList<structTools*>;
	ToolsInit();
	ToolsDisplayRefresh();

	connect(ASTransSidebarGeneral::GetSelfPointer(), SIGNAL(signalBtnRst()), this, SLOT(slotBtnRst()));
	connect(ASTransSidebarGeneral::GetSelfPointer(), SIGNAL(signalSetSideBarBelowWidget(int, bool)),
		this, SLOT(slotSetSideBarBelowWidget(int, bool)));
	////�ӽ���
	//m_AboutWidget = new AboutWidget();
	//m_HelpWidget = new ASHelpWidget();
}

ASToolBar::~ASToolBar()
{
}

//���߰�ť��ʼ��
void ASToolBar::ToolsInit()
{
	bool default_theme = ASTransTheme::GetTheme();
	//// �ر���������
	//structTools* toolCloseAll = new structTools;
	//toolCloseAll->ID = TOOLBAR_CLOSEALL;
	//toolCloseAll->isBelowWidget = false;
	//toolCloseAll->toolButton = new QToolButton();
	//toolCloseAll->toolButton->setToolTip(QString::fromLocal8Bit("Close All"));
	//toolCloseAll->toolButton->setIcon(QIcon(":/Icon/ToolBar_CloseAll"));
	//connect(toolCloseAll->toolButton, SIGNAL(clicked()), this, SLOT(slotCloseAll()));
	//m_Tools->append(toolCloseAll);

	//// ����
	//structTools* toolExport = new structTools;
	//toolExport->ID = TOOLBAR_EXPORT;
	//toolExport->isBelowWidget = false;
	//toolExport->toolButton = new QToolButton();
	//toolExport->toolButton->setToolTip(QString::fromLocal8Bit("Export"));
	//toolExport->toolButton->setIcon(QIcon(":/Icon/ToolBar_Export"));
	//connect(toolExport->toolButton, SIGNAL(clicked()), this, SLOT(slotExport()));
	//m_Tools->append(toolExport);

	// �������ӵ㹤��
	structTools* toolPaintSeeds = new structTools;
	toolPaintSeeds->ID = TOOLBAR_PaintSeeds;
	toolPaintSeeds->isBelowWidget = false;
	toolPaintSeeds->toolButton = new QToolButton(this);
	toolPaintSeeds->toolButton->setMouseTracking(true);
	toolPaintSeeds->toolButton->setObjectName("PaintSeeds");
	toolPaintSeeds->toolButton->setMouseTracking(true);
	toolPaintSeeds->toolButton->setToolTip(QString::fromLocal8Bit("Paint seeds"));
	toolPaintSeeds->toolButton->setCheckable(true);
	toolPaintSeeds->toolButton->setChecked(false);
	toolPaintSeeds->toolButton->setMinimumHeight(80);
	connect(toolPaintSeeds->toolButton, SIGNAL(clicked(bool)), this, SLOT(slotPaintSeeds(bool)));
	m_Tools->append(toolPaintSeeds);

	// ���������߹���
	structTools* toolPaintContours = new structTools;
	toolPaintContours->ID = TOOLBAR_PaintContours;
	toolPaintContours->isBelowWidget = false;
	toolPaintContours->toolButton = new QToolButton(this);
	toolPaintContours->toolButton->setMouseTracking(true);
	toolPaintContours->toolButton->setObjectName("PaintContours");
	toolPaintContours->toolButton->setMouseTracking(true);
	toolPaintContours->toolButton->setToolTip(QString::fromLocal8Bit("Paint contour"));
	toolPaintContours->toolButton->setCheckable(true);
	toolPaintContours->toolButton->setChecked(false);
	toolPaintContours->toolButton->setMinimumHeight(80);
	connect(toolPaintContours->toolButton, SIGNAL(clicked(bool)), this, SLOT(slotPaintContours(bool)));
	m_Tools->append(toolPaintContours);

	// ���Ʊ궨�㹤��
	structTools* toolPaintLandmarks = new structTools;
	toolPaintLandmarks->ID = TOOLBAR_PaintLandmarks;
	toolPaintLandmarks->isBelowWidget = false;
	toolPaintLandmarks->toolButton = new QToolButton(this);
	toolPaintLandmarks->toolButton->setMouseTracking(true);
	toolPaintLandmarks->toolButton->setObjectName("PaintLandmarks");
	toolPaintLandmarks->toolButton->setMouseTracking(true);
	toolPaintLandmarks->toolButton->setToolTip(QString::fromLocal8Bit("Paint landmarks"));
	toolPaintLandmarks->toolButton->setCheckable(true);
	toolPaintLandmarks->toolButton->setChecked(false);
	toolPaintLandmarks->toolButton->setMinimumHeight(80);
	connect(toolPaintLandmarks->toolButton, SIGNAL(clicked(bool)), this, SLOT(slotPaintLandmarks(bool)));
	m_Tools->append(toolPaintLandmarks);

	// ������λ����ͽ���Ĺ���
	structTools* toolImageNavigator = new structTools;
	toolImageNavigator->ID = ToolBar_ImageNavigator;
	toolImageNavigator->isBelowWidget = true;
	toolImageNavigator->toolButton = new QToolButton(this);
	toolImageNavigator->toolButton->setMouseTracking(true);
	toolImageNavigator->toolButton->setObjectName("ImageNavigator");
	toolImageNavigator->toolButton->setMouseTracking(true);
	toolImageNavigator->toolButton->setToolTip(QString::fromLocal8Bit("Image navigator"));
	toolImageNavigator->toolButton->setCheckable(true);
	toolImageNavigator->toolButton->setChecked(false);
	toolImageNavigator->toolButton->setMinimumHeight(80);
	connect(toolImageNavigator->toolButton, SIGNAL(clicked(bool)), this, SLOT(slotImageNavigator(bool)));
	m_Tools->append(toolImageNavigator);

	// ����
	structTools* toolROI = new structTools;
	toolROI->ID = TOOLBAR_ROI;
	toolROI->isBelowWidget = true;
	toolROI->toolButton = new QToolButton(this);
	toolROI->toolButton->setMouseTracking(true);
	toolROI->toolButton->setObjectName("ROI");
	toolROI->toolButton->setMouseTracking(true);
	toolROI->toolButton->setToolTip(QString::fromLocal8Bit("ROI"));
	toolROI->toolButton->setCheckable(true);
	toolROI->toolButton->setChecked(false);
	toolROI->toolButton->setMinimumHeight(80);
	connect(toolROI->toolButton, SIGNAL(clicked(bool)), this, SLOT(slotROI(bool)));
	m_Tools->append(toolROI);

	// PolyDeformation
	structTools* toolPolyDeformation = new structTools;
	toolPolyDeformation->ID = TOOLBAR_PolyDeformation;
	toolPolyDeformation->isBelowWidget = true;
	toolPolyDeformation->toolButton = new QToolButton(this);
	toolPolyDeformation->toolButton->setMouseTracking(true);
	toolPolyDeformation->toolButton->setObjectName("PolyDeformation");
	toolPolyDeformation->toolButton->setMouseTracking(true);
	toolPolyDeformation->toolButton->setToolTip(QString::fromLocal8Bit("PolyDeformation"));
	toolPolyDeformation->toolButton->setCheckable(true);
	toolPolyDeformation->toolButton->setChecked(false);
	toolPolyDeformation->toolButton->setMinimumHeight(80);
	connect(toolPolyDeformation->toolButton, SIGNAL(clicked(bool)), this, SLOT(slotPolyDeformation(bool)));
	m_Tools->append(toolPolyDeformation);

	//// GraphCuts
	//structTools* toolGraphCuts = new structTools;
	//toolGraphCuts->ID = TOOLBAR_GraphCuts;
	//toolGraphCuts->isBelowWidget = true;
	//toolGraphCuts->toolButton = new QToolButton();
	//toolGraphCuts->toolButton->setToolTip(QString::fromLocal8Bit("Graph Cuts"));
	//toolGraphCuts->toolButton->setIcon(QIcon(":/Icon/ToolBar_GraphCuts"));
	//toolGraphCuts->toolButton->setCheckable(true);
	//toolGraphCuts->toolButton->setChecked(false);
	//connect(toolGraphCuts->toolButton, SIGNAL(clicked(bool)), this, SLOT(slotGraphCuts(bool)));
	//m_Tools->append(toolGraphCuts);
}

//���߰�ťˢ����ʾ
void ASToolBar::ToolsDisplayRefresh()
{
	int NumofAllTools = m_Tools->length();
	for (size_t CurrentToolID = 0; CurrentToolID < NumofAllTools; CurrentToolID++)
	{
		for (int i = 0; i != m_Tools->size(); ++i)
		{
			if (m_Tools->at(i)->ID == CurrentToolID)
			{
				this->addWidget(m_Tools->at(i)->toolButton);
			}
		}
	}
}
//��ID�õ�����
structTools* ASToolBar::gettool(int ID)
{
	int numOfTools = m_Tools->size();
	for (int crntTool = 0; crntTool < numOfTools; crntTool++)
	{
		if (m_Tools->at(crntTool)->ID == ID)
		{
			return (m_Tools->at(crntTool));
		}
	}
	return NULL;
}
// ��ǰ���µİ�ť
void ASToolBar::SetCrntTool(int ID, bool checked)
{
	int numOfTools = m_Tools->size();
	for (int crntTool = 0; crntTool < numOfTools; crntTool++)
	{
		if (m_Tools->at(crntTool)->ID == ID)
		{
			if (checked)
			{
				m_Tools->at(crntTool)->toolButton->setChecked(true);
				ASTransTheme::SetToolBtnDown(ID);
			}
			else
			{
				ASTransTheme::SetToolBtnDown(-1);
			}
		}
		else
		{
			m_Tools->at(crntTool)->toolButton->setChecked(false);
		}
	}
	repaint();
}

// �������ӵ㹤��
void ASToolBar::slotPaintSeeds(bool checked)
{
	ASTransSidebarGeneral::SetSidebarBelowWidget(SIDEBAR_PaintingSeeds, checked);
	//this->SetCrntTool(TOOLBAR_PaintSeeds, checked);	
}
// ���������߹���
void ASToolBar::slotPaintContours(bool checked)
{
	ASTransSidebarGeneral::SetSidebarBelowWidget(SIDEBAR_PaintingContour, checked);
	//this->SetCrntTool(TOOLBAR_PaintContours, checked);	
}
// ���Ʊ궨�㹤��
void ASToolBar::slotPaintLandmarks(bool checked)
{
	ASTransSidebarGeneral::SetSidebarBelowWidget(SIDEBAR_PaintingLandmark, checked);
	//this->SetCrntTool(TOOLBAR_PaintLandmarks, checked);	
}

// ������λ����ͽ���Ĺ���
void ASToolBar::slotImageNavigator(bool checked)
{
	ASTransSidebarGeneral::SetSidebarBelowWidget(SIDEBAR_IMAGENAVIGATOR, checked);
	//this->SetCrntTool(ToolBar_ImageNavigator, checked);	
}
// ����
void ASToolBar::slotROI(bool checked)
{
	ASTransSidebarGeneral::SetSidebarBelowWidget(SIDEBAR_ROI, checked);
	//this->SetCrntTool(TOOLBAR_ROI, checked);	
}
// FPolyDeformation
void ASToolBar::slotPolyDeformation(bool checked)
{
	ASTransSidebarGeneral::SetSidebarBelowWidget(SIDEBAR_PolyDeformation, checked);
	//this->SetCrntTool(TOOLBAR_PolyDeformation, checked);
}	
	
// GraphCuts
void ASToolBar::slotGraphCuts(bool checked)
{
	ASTransSidebarGeneral::SetSidebarBelowWidget(SIDEBAR_GraphCuts, checked);
}
// �л���ǰ���߰�ť״̬
void ASToolBar::slotSetSideBarBelowWidget(int c_WidgetType, bool c_isShown)
{
	switch (c_WidgetType)
	{
	case SIDEBAR_PaintingSeeds:
		this->SetCrntTool(SIDEBAR_PaintingSeeds, c_isShown);
		break;
	case SIDEBAR_PaintingContour:
		this->SetCrntTool(TOOLBAR_PaintContours, c_isShown);
		break;
	case SIDEBAR_PaintingLandmark:
		this->SetCrntTool(TOOLBAR_PaintLandmarks, c_isShown);
		break;
	case SIDEBAR_IMAGENAVIGATOR:
		this->SetCrntTool(ToolBar_ImageNavigator, c_isShown);
		break;
	case SIDEBAR_ROI:
		this->SetCrntTool(TOOLBAR_ROI, c_isShown);
		break;
	case SIDEBAR_PolyDeformation:
		this->SetCrntTool(TOOLBAR_PolyDeformation, c_isShown);
		break;
	default:
		break;
	}
}

void ASToolBar::slotBtnRst()
{
	this->SetCrntTool(TOOLBAR_PolyDeformation, false);
	this->SetCrntTool(TOOLBAR_ROI, false);
	this->SetCrntTool(ToolBar_ImageNavigator, false);
	this->SetCrntTool(TOOLBAR_PaintLandmarks, false);
	this->SetCrntTool(TOOLBAR_PaintContours, false);
	this->SetCrntTool(TOOLBAR_PaintSeeds, false);
}

// ���Ʊ߿�
void ASToolBar::paintEvent(QPaintEvent* e)
{
	QWidget::paintEvent(e);
	bool themechoice = ASTransTheme::GetTheme();
	int crntBtnDown = ASTransTheme::GetToolBtnDown();
	
	// ���ƻ���ToolBar
	QPainter painter(this);
	if (themechoice)
	{
		painter.setPen(QPen(QColor("#16181C"), 1));
		painter.setBrush(QColor("#21252B"));
	}	
	else
	{
		painter.setPen(QPen(QColor("#A0A0A0"), 1));
		painter.setBrush(QColor("#F5F5F5"));
	}
	painter.drawRect(0, 0, width()-1, height()-1);

	// ������Բ��
	if (themechoice)
	{
		switch (crntBtnDown)
		{
		case ToolBar_ImageNavigator:
			painter.drawPixmap(0, 0, QPixmap(":/Icon/Border-top-dark"));
			break;
		case TOOLBAR_ROI:
			painter.drawPixmap(0, 80, QPixmap(":/Icon/Border-dark"));
			break;
		case TOOLBAR_PaintSeeds:
			painter.drawPixmap(0, 160, QPixmap(":/Icon/Border-dark"));
			break;
		case TOOLBAR_PaintContours:
			painter.drawPixmap(0, 240, QPixmap(":/Icon/Border-dark"));
			break;
		case TOOLBAR_PaintLandmarks:
			painter.drawPixmap(0, 320, QPixmap(":/Icon/Border-dark"));
			break;
		case TOOLBAR_PolyDeformation:
			painter.drawPixmap(0, 400, QPixmap(":/Icon/Border-dark"));
			break;
		default:
			;
		}
	}
	else
	{
		switch (crntBtnDown)
		{
		case ToolBar_ImageNavigator:
			painter.drawPixmap(0, 0, QPixmap(":/Icon/Border-top"));
			break;
		case TOOLBAR_ROI:
			painter.drawPixmap(0, 80, QPixmap(":/Icon/Border"));
			break;
		case TOOLBAR_PaintSeeds:
			painter.drawPixmap(0, 160, QPixmap(":/Icon/Border"));
			break;
		case TOOLBAR_PaintContours:
			painter.drawPixmap(0, 240, QPixmap(":/Icon/Border"));
			break;
		case TOOLBAR_PaintLandmarks:
			painter.drawPixmap(0, 320, QPixmap(":/Icon/Border"));
			break;
		case TOOLBAR_PolyDeformation:
			painter.drawPixmap(0, 400, QPixmap(":/Icon/Border"));
			break;
		default:
			;
		}
	}
}
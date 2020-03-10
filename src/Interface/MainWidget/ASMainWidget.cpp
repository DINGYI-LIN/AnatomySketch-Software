#include "ASMainWidget.h"
#include "ASTitleWidget.h"
#include "ASToolBar.h"
#include "ASSideBar.h"
#include "ASOperationBar.h"
#include "ASStatusBar.h"
#include "ASTransSetting.h"
#include <QIcon>
#include <QSplitter>
#include <QSettings>
#include <QColor>
#include <QVBoxLayout>
#include <QCoreApplication>

QWidget* ASMainWidget::m_FatherWidget = nullptr;

ASMainWidget::ASMainWidget(QWidget *parent)
	: ASDropShadowWidget(parent)
{
	m_FatherWidget = this;

	// ��ȡ����λ�ô�С��Ϣ
	this->resize(ASTransSetting::GetSetting()->value("mainWindowSize").toSize());
	this->move(ASTransSetting::GetSetting()->value("mainWindowPosition").toPoint());
	
	setMinimumSize(900, 600);
	setWindowIcon(QIcon(":/Icon/AnatomySketch"));
	showMaximized();

	//ʵ������ģ��
	m_TitleWidget = new ASTitleWidget(this);
	m_ToolBar = new ASToolBar(this);
	m_SideBar = new ASSideBar(this);
	m_OperationBar = new ASOperationBar(0);
	m_StatusBar = new ASStatusBar(this);

	this->UIInit();

	//-----------------------�źŲ�----------------------
	connect(m_TitleWidget, SIGNAL(showMin()), this, SLOT(showMinimized()));
	connect(m_TitleWidget, SIGNAL(showMax()), this, SLOT(showMaximized()));	
	connect(m_TitleWidget, SIGNAL(ShowNormal()), this, SLOT(showNormal()));
	connect(m_TitleWidget, SIGNAL(programexit()), this, SLOT(close()));
	connect(m_TitleWidget, SIGNAL(movewindow(int, int)), this, SLOT(moveWindow(int, int)));
}

ASMainWidget::~ASMainWidget()
{
}
// �õ������ڵ�ָ�룬ʵ����������ʱ��
QWidget* ASMainWidget::GetMainWidget()
{
	return m_FatherWidget;
}

void ASMainWidget::closeEvent(QCloseEvent * e)
{
	// д�봰�ڴ�Сλ����Ϣ
	if (!isMaximized())
	{
		ASTransSetting::GetSetting()->setValue("mainWindowPosition", pos());
		ASTransSetting::GetSetting()->setValue("mainWindowSize", size());
		ASTransSetting::GetSetting()->sync();
	}
	QCoreApplication::quit(); // �˳�����
}

void ASMainWidget::UIInit()
{
	//-----------------���ڲ���---------------------

	QVBoxLayout* mainLayout = new QVBoxLayout();

	//������
	mainLayout->addWidget(m_TitleWidget);
	//������
	//QHBoxLayout* layout1 = new QHBoxLayout();
	//layout1->addWidget(m_ToolBar);

	//�����&��ʾ��������
	QSplitter*  pSplitter = new QSplitter(Qt::Horizontal, this);	// ���÷���������������������϶������ӿؼ���С	
	pSplitter->setObjectName("pSplitter");
	pSplitter->setHandleWidth(VSPLITTERHANDLEWIDTH);					// ���÷��������
	pSplitter->setMouseTracking(true);								//�����û�е���Ǹ�������ƶ������ڴ��ڱ߽�����	
	pSplitter->setAutoFillBackground(true);							// ���÷�����͸��
	QPalette PaletteOfSplitter = pSplitter->palette();
	PaletteOfSplitter.setColor(pSplitter->backgroundRole(), QColor(0, 0, 0, 0));
	pSplitter->setPalette(PaletteOfSplitter);
	pSplitter->setChildrenCollapsible(false);						//�Ӳ��������۵�

	pSplitter->addWidget(m_SideBar);			// ��ӷ������ӿؼ��������	
	pSplitter->addWidget(m_OperationBar);		// ��ӷ������ӿؼ���������
	pSplitter->setStretchFactor(0, 1);
	pSplitter->setStretchFactor(1, 3);
	
	//layout1->addWidget(pSplitter);
	//mainLayout->addLayout(layout1);
	mainLayout->addWidget(pSplitter);
	//״̬��
	mainLayout->addWidget(m_StatusBar);

	mainLayout->setContentsMargins(0, SHADOW_WIDTH, 0, 0);	//������߿�
	mainLayout->setSpacing(0);	//���������ؼ�֮��ľ���
	setLayout(mainLayout);
}

void ASMainWidget::moveWindow(int ax, int ay)
{
	this->move(ax, ay);
}
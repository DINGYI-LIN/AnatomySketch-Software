#include "ASPaintingSeedsWidget.h"
#include "ASTransSeeds.h"
#include "ASDataStructureWalker.h"
#include "ASSeedData.h"
#include "ASFModelSeeds.h"
#include "ASTransGlobalKeyBoard.h"
#include "ASInteractorStyleManager.h"
#include "ASTransInteractorStyle.h"
#include "ASTransCompleter.h"
#include "ASArrayImageData.h"
#include "ASTransDataGeneral.h"
#include "ASMainWidget.h"
#include "ASTransContour.h"
#include "ASTransSidebarGeneral.h"
#include <QVBoxLayout>
#include <QMessageBox>

ASPaintingSeedsWidget::ASPaintingSeedsWidget(QWidget *parent)
	: ASWidgetInSideBarBase(parent)
{
	this->UIInit();
	this->setStyleSheet("padding: 2px;");
	this->CompleterInit();

	// ����transmission�ź�
	connect(ASTransInteractorStyle::GetSelfPointer(), SIGNAL(signalInteractorStyle2DChanged(int)), 
		this, SLOT(slotInteractorStyle2DChanged(int)));
	connect(ASTransSidebarGeneral::GetSelfPointer(), SIGNAL(signalNewFromAddin(int, QString, int, QColor)),
		this, SLOT(slotNewFromAddin(int, QString, int, QColor)));
}

ASPaintingSeedsWidget::~ASPaintingSeedsWidget()
{

}

void ASPaintingSeedsWidget::SetEnabled(const bool c_bEnabled)
{
	if (c_bEnabled == ASFModelSeeds::GetSeedsModleEnabled())
	{
		return;
	}
	if (!c_bEnabled && m_FlagFromAddin)
	{
		m_FlagFromAddin = false;
		m_BtnFinish->hide();
	}
	ASTransSeeds::SetModelEnabled(c_bEnabled);
}

// �����ʼ��
void ASPaintingSeedsWidget::UIInit()
{
	// 1 new
	QLabel* label10 = new QLabel(tr("New Seed Point"), this);
	m_LineENewData = new QLineEdit(this);
	QHBoxLayout* layout1 = new QHBoxLayout();
	layout1->addWidget(label10);
	layout1->addWidget(m_LineENewData);
	connect(m_LineENewData, SIGNAL(returnPressed()), this, SLOT(slotSeedNameReturn()));
	// 2 undo
	m_PushBUndo = new QPushButton(tr("Undo"), this);
	connect(m_PushBUndo, SIGNAL(clicked()), this, SLOT(slotUndo()));
	// 3 Finish
	m_BtnFinish = new QPushButton(tr(u8"���"), this);
	m_BtnFinish->hide();
	connect(m_BtnFinish, SIGNAL(clicked()), this, SLOT(slotFinish()));
	// 0 mainlayout
	QVBoxLayout* mainlayout = new QVBoxLayout();
	mainlayout->addLayout(layout1);
	mainlayout->addWidget(m_PushBUndo);
	mainlayout->addWidget(m_BtnFinish);
	mainlayout->addStretch();
	this->setLayout(mainlayout);
}
void ASPaintingSeedsWidget::CompleterInit()
{
	QList<structCompleterItem*>* pList = ASTransCompleter::GetStructureList();
	QStringList StrList;
	for (int index = 0; index < pList->size(); index++)
	{
		StrList << pList->at(index)->name;
	}
	m_StrLiMo = new QStringListModel();
	m_StrLiMo->setStringList(StrList);
	m_Cmlt = new QCompleter();
	m_Cmlt->setModel(m_StrLiMo);
	m_Cmlt->setCaseSensitivity(Qt::CaseInsensitive);
	EventFilterSeeds* filter = new EventFilterSeeds(m_LineENewData);
	m_Cmlt->popup()->installEventFilter(filter);
	m_LineENewData->setCompleter(m_Cmlt);
	connect(filter, SIGNAL(EnterPress()), this, SLOT(slotSeedNameReturn()));
}
void ASPaintingSeedsWidget::NewSeed(QString name, int label, QColor color)
{
	//ASArrayImageData* GenData = static_cast<ASArrayImageData*>(
	//	ASTransDataGeneral::GetGeneratingData());
	//if (!GenData)
	//{
	//	// �޵�ǰ���ݣ��½�ʧ��
	//	QMessageBox::information(ASMainWidget::GetMainWidget(), tr("New Contour"),
	//		tr("Please set current greyscale data."), QMessageBox::Ok, QMessageBox::Ok);
	//	return;
	//}
	//// �ж��Ƿ���Ҫ�½����ӵ��ļ�
	//ASSeedData* SeedData = ASTransSeeds::GetCurrentSeedData();
	//if (!SeedData)
	//{
	//	SeedData = ASTransSeeds::NewSeedsData();
	//	if (!SeedData)
	//	{
	//		qDebug("Error: Null pointer of current SeedsData. From ASPaintingSeedsWidget.");
	//		return;
	//	}
	//}
	//int id = SeedData->NewSeed(name, label, color);
	//if (id == -1)
	//{
	//	qDebug("error: Bad new seed id in ASPaintingSeedsWidget.cpp");
	//	return;
	//}
	//ASTransSeeds::SetCrntSeedsID(id);
	//// ˢ��
	//ASTransSeeds::UpdateListsOfSeedData();
}
// �½��ļ�
void ASPaintingSeedsWidget::slotSeedNameReturn()
{
	QList<structCompleterItem*>* pList = ASTransCompleter::GetStructureList();
	QString NewName = m_LineENewData->text();

	// ֻ��ʹ���б��е�����
	//bool bbb = false;
	//for (int index = 0; index < pList->size(); index++)
	//{
	//	if (pList->at(index)->name == NewName)
	//	{
	//		bbb = true;
	//		break;
	//	}
	//}
	//if (bbb == false)
	//{
	//	return;
	//}

	if (NewName.size() == 0)
	{
		return;
	}
	m_LineENewData->clear();
	m_LineENewData->setText("");
	int contourid = -1;
	QColor c(Qt::red);
	for (int index = 0; index < pList->size(); index++)
	{
		if (pList->at(index)->name == NewName)
		{
			contourid = pList->at(index)->id;
			c = pList->at(index)->color;
			break;
		}
	}
	this->NewSeed(NewName, contourid, c);
}
// ������ť
void ASPaintingSeedsWidget::slotUndo()
{
	if (ASFModelSeeds::GetSeedsModleEnabled())
	{
		ASTransSeeds::UndoPaintingSedds();
	}
}

// ����ȫ�ּ����ź�
void ASPaintingSeedsWidget::slotGlobalKeyBoard(QKeyEvent* pKeyEvent)
{
	if (ASFModelSeeds::GetSeedsModleEnabled() != true)
	{
		return;
	}
	// ���ּ��л��������ӵ㣬Ctrl+z����
	switch (pKeyEvent->key())
	{
	case Qt::Key_Z:
		if (pKeyEvent->modifiers() == Qt::ControlModifier)
		{
			this->slotUndo();
		}
		break;
	default:
		break;
	}
}
// �����ǰ������ʽ�ı�
void ASPaintingSeedsWidget::slotInteractorStyle2DChanged(int interactor)
{
	//if (interactor == InterStyle2D_PaintingSeeds)
	//{
	//	this->SetEnabled(true);
	//}
	//else
	//{
	//	this->SetEnabled(false);
	//}
}
// �Ӳ���������½�����
//void ASPaintingSeedsWidget::slotNewFromAddin(int c_Type, QString name, int label, QColor color)
//{
//	if (c_Type == SIDEBAR_PaintingSeeds)
//	{
//		//ASTransSidebarGeneral::SetSidebarBelowWidget(SIDEBAR_PaintingSeeds, true);
//		//this->m_BtnFinish->show();
//		//this->m_FlagFromAddin = true;
//		ASTransSeeds::NewSeedsData(name, label, color);
//	}
//}
// Finish
void ASPaintingSeedsWidget::slotFinish()
{
	ASTransSidebarGeneral::SetSidebarBelowWidget(SIDEBAR_Operation, true);
}

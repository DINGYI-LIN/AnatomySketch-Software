#include "ASDataManagerView.h"
#include "ASDataManagerModel.h"
#include "ASAbstractData.h"
#include "ASDataManagerDelegate.h"
#include "ASAbstructItemWidget.h"
#include "ASDataNodeRClickMenu.h"
#include "ASMarkEleRClickMenu.h"
#include <QHeaderView>

ASDataManagerView::ASDataManagerView(QWidget *parent)
	: QTreeView(parent)
{

	this->setObjectName("DataManagerView");
	this->setStyleSheet(
		"QTreeView"
	);
	this->header()->hide(); // ���ر�ͷ
	this->setEditTriggers(QAbstractItemView::NoEditTriggers); // ��Ԫ�񲻿ɱ༭
	QHeaderView* headerView = this->header();
	headerView->setSectionResizeMode(QHeaderView::ResizeToContents);

	//�Ϸ�
	setDragEnabled(true);
	setDragDropMode(QAbstractItemView::InternalMove);
	setAcceptDrops(true);
	setDropIndicatorShown(true);

	// �Ҽ��˵�
	m_DataNodeRClickMenu = new ASDataNodeRClickMenu(this);
	m_MarkEleRClickMenu = new ASMarkEleRClickMenu(this);
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), 
		this, SLOT(slotShowContextMenu(const QPoint&)));
	connect(this, SIGNAL(clicked(const QModelIndex&)), 
		this, SLOT(slotDevTreeClicked(const QModelIndex &)));
	connect(this, SIGNAL(collapsed(const QModelIndex&)), 
		this, SLOT(slotDevTreeClicked(const QModelIndex &)));
	connect(this, SIGNAL(expanded(const QModelIndex&)), 
		this, SLOT(slotDevTreeClicked(const QModelIndex &)));
}

ASDataManagerView::~ASDataManagerView()
{
}

QStandardItem* ASDataManagerView::getDragDropStartItem()
{
	return m_pDragDropStartItem;
}

void ASDataManagerView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) 
	{
		m_DragStartPos = event->pos();
	}
	QStandardItemModel* pmodel = (QStandardItemModel*)model();
	m_pDragDropStartItem = pmodel->itemFromIndex(indexAt(m_DragStartPos));

	QTreeView::mousePressEvent(event);

}
void ASDataManagerView::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->pos() == m_DragStartPos)
	{
		QStandardItemModel* pmodel = (QStandardItemModel*)model();
		QStandardItem* crntItem = pmodel->itemFromIndex(indexAt(event->pos()));
		if (crntItem)
		{
			emit signalItemClicked(crntItem);
		}		
	}
	QTreeView::mouseReleaseEvent(event);
}
void ASDataManagerView::wheelEvent(QWheelEvent * event)
{
	if (event->modifiers() & Qt::ControlModifier)
	{
		int nOffset = event->delta() / 120;
		ASDataManagerDelegate* Delegate = static_cast<ASDataManagerDelegate*>(this->itemDelegate());
		Delegate->setSizeOffset(nOffset);
		emit signalRefreshDataManagerWidget();
	}
}

//�Ҽ������Ӧ������ʵ���Ҽ��˵�
void ASDataManagerView::slotShowContextMenu(const QPoint& pos)
{
	ASDataManagerModel* pModel = (ASDataManagerModel*)this->model();

	// 1 �жϷ����Ҽ�������ID
	QPoint globalPos = this->mapToGlobal(pos);
	QModelIndex ContextMenuItemIndex = this->indexAt(pos);
	QStandardItem* crntItem = pModel->itemFromIndex(ContextMenuItemIndex);
	if (crntItem == nullptr)
	{
		return;
	}

	// 2 �����Ҽ��˵�
	ASAbstructItemWidget* crntItemWidget = pModel->getItemWidgetFromItem(crntItem);
	if (crntItemWidget->GetItemType() == ItemType_DataNode)
	{
		// �õ������Ҽ��˵������ݽڵ�
		ASAbstractData* crntDataNode = ASAbstractData::getDataNodeFromID(crntItemWidget->GetID());
		// �����Ҽ��˵�
		m_DataNodeRClickMenu->Generate(globalPos, crntDataNode);
	}
	else if (crntItemWidget->IsMarkEle())
	{
		// �õ������Ҽ��˵������ݽڵ�
		ASAbstractData* crntDataNode = ASAbstractData::getDataNodeFromID(crntItemWidget->GetID());
		// �����Ҽ��˵�
		m_MarkEleRClickMenu->Generate(globalPos, crntDataNode, crntItemWidget->getMarkEleID());
	}
}

void ASDataManagerView::slotDevTreeClicked(const QModelIndex &index)
{
	this->resizeColumnToContents(0);
}
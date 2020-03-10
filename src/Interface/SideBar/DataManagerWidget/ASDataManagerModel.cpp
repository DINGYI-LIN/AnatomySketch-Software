#include "ASDataManagerModel.h"
#include "ASDataNodeItemWidget.h"
#include "ASAbstructItemWidget.h"
#include <QDebug>

ASDataManagerModel::ASDataManagerModel(QObject *parent)
	: QStandardItemModel(parent)
{
	m_plistItemWidget = new QList<ASAbstructItemWidget*>;

}

ASDataManagerModel::~ASDataManagerModel()
{
}

// ����б�
void ASDataManagerModel::RemoveAllItem()
{
	this->clear();
	while (m_plistItemWidget->size() > 0)
	{
		//QStandardItemModel���Զ������Ѿ��������еĸ���Item���ڴ棬���Ե�ǰ�����clear()ʱ��Item���ڴ��Ѿ����ͷ�
		delete m_plistItemWidget->first();
		m_plistItemWidget->removeFirst();
	}
}
// ���б������һ���ṹ��
void ASDataManagerModel::addItemWidget(ASAbstructItemWidget* structitem)
{
	m_plistItemWidget->append(structitem);
}

ASAbstructItemWidget* ASDataManagerModel::getItemWidgetFromItem(QStandardItem* item)
{
	int numOfItem = m_plistItemWidget->size();
	for (int crntItem = 0; crntItem < numOfItem; crntItem++)
	{
		ASAbstructItemWidget* crntItemWidget = m_plistItemWidget->at(crntItem);
		if (crntItemWidget->GetListWidgetItem() == item)
		{
			return crntItemWidget;
		}
	}
	return nullptr;
}
// ��IDֵ�����õ��ṹ�屾���ָ��
ASAbstructItemWidget* ASDataManagerModel::getItemWidgetFromID(int ID)
{
	int numOfItem = m_plistItemWidget->size();
	for (int crntItem = 0; crntItem < numOfItem; crntItem++)
	{
		ASAbstructItemWidget* crntItemWidget = m_plistItemWidget->at(crntItem);
		if (crntItemWidget->IsMarkEle())
		{
			continue;
		}
		if (crntItemWidget->GetID() == ID)
		{
			return crntItemWidget;
		}
	}
	return nullptr;
}
// �õ����нṹ��������
QList<ASAbstructItemWidget*>* ASDataManagerModel::getListItemInListWidget()
{
	return m_plistItemWidget;
}

bool ASDataManagerModel::dropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent)
{
	bool a = QStandardItemModel::dropMimeData(data, action, row, column, parent);
	emit signalDragDropFinished(row, column, &parent);
	return a;
}
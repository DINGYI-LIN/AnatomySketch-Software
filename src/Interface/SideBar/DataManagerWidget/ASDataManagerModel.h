#pragma once

#include <QStandardItemModel>
#include <QStandardItem>

class ASAbstructItemWidget;
class ASDataNodeItemWidget;

class ASDataManagerModel : public QStandardItemModel
{
	Q_OBJECT

public:
	ASDataManagerModel(QObject *parent);
	~ASDataManagerModel();

	// ����б�
	void RemoveAllItem();
	// ���б������һ���ṹ��
	void addItemWidget(ASAbstructItemWidget* structitem);
	// �ɽṹ����QStandardItem��ֵ�ñ����õ��ṹ�屾���ָ��
	ASAbstructItemWidget* getItemWidgetFromItem(QStandardItem* item);
	// ��IDֵ�����õ��ṹ�屾���ָ��
	ASAbstructItemWidget* getItemWidgetFromID(int ID);
	// �õ����нṹ��������
	QList<ASAbstructItemWidget*>* getListItemInListWidget();

private:

	//�����б���Ԫ�ص�����
	QList<ASAbstructItemWidget*>* m_plistItemWidget;
	
	Qt::DropActions ASDataManagerModel::supportedDropActions() const
	{
		return Qt::MoveAction;
	}

	bool dropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent);

signals:

	//�ϷŲ������ʱ������Ӧ����
	void signalDragDropFinished(int row, int column, const QModelIndex* parent);
};

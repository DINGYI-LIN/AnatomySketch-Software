#pragma once

#include "ASDataManagerAction.h"
#include <QTreeView>
#include <QStandardItem>
#include <QWheelEvent>
#include <QStandardItemModel>

class ASAbstractData;
class ASDataNodeRClickMenu;
class ASMarkEleRClickMenu;

class ASDataManagerView : public QTreeView
{
	Q_OBJECT

public:
	ASDataManagerView(QWidget *parent);
	~ASDataManagerView();

	QStandardItem* getDragDropStartItem();

protected:

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

private:
	
	ASDataNodeRClickMenu* m_DataNodeRClickMenu;
	ASMarkEleRClickMenu* m_MarkEleRClickMenu;
	QPoint m_DragStartPos;
	QStandardItem* m_pDragDropStartItem;

private slots:

	// �Ҽ������Ӧ������ʵ���Ҽ��˵�
	void slotShowContextMenu(const QPoint& pos);
	void slotDevTreeClicked(const QModelIndex &index);

signals:

	// ���źţ�Qt�����ź���Ҫ��������������Ч
	void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
	// ����������ˢ�������б�
	void signalRefreshDataManagerWidget();
	// �����л���ǰ����
	void signalItemClicked(QStandardItem* item);
};

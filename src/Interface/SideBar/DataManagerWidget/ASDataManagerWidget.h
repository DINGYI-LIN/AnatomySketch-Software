#pragma once

#include "ASDataManagerAction.h"
#include <QTreeView>
#include <QWidget>
#include <QStandardItemModel>

class ASDataManagerView;
class ASDataManagerModel;
class ASDataManagerDelegate;
class ASAbstractData;

class ASDataManagerWidget : public QWidget
{
	Q_OBJECT

public:
	ASDataManagerWidget(QWidget *parent);
	~ASDataManagerWidget();

private:

	QTreeView* m_pDataTreeView;
	QStandardItemModel* m_pDataItemModel;

	// MVC��ɲ���
	ASDataManagerView* m_pDataManagerView;
	ASDataManagerModel* m_pDataManagerModel;
	ASDataManagerDelegate* m_pDataManagerDelegate;

	// ����������ˢ�������б���ʾʱ�ȸ��������ĵ�������
	void addNoteDisplay(ASAbstractData* note, int IDOfFather, QStandardItem* fatherItem);
	// ����������ˢ��Seed�����ݵ�����Ŀ
	void refreshMarkEleNode(ASAbstractData* note, QStandardItem* crntItem);
	// ����������ȡ��ĳ��MarkEle��ѡ��
	void ResetMarkEleFocus(const int c_Type);
	// ������������QKeyEvent�еõ�����
	int GetNumFromKeyEvent(QKeyEvent* pKeyEvent);

signals:

private slots:

	// ˢ���ļ�����ʾ
	void slotRefreshDataManagerWidget();
	// �ϷŲ������
	void slotDragDropFinished(int row, int column, const QModelIndex* parent);
	// ��ǰѡ��item�����ı�
	void slotCrntItemSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
	// ˢ�µ�ǰ������ʾ�������л���ǰ����ʱ
	void slotRefreshCrntData();
	// �����л���ǰ����
	void slotItemClicked(QStandardItem* item);
	// �����Ƿ���ʾ�����ı�
	void slotDataShownChanged(ASAbstractData* DataNode);
	// ����ȫ�ּ����ź�
	void slotGlobalKeyBoard(QKeyEvent* pKeyEvent);
};

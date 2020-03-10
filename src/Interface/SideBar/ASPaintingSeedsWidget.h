#pragma once

#include "ASWidgetInSideBarBase.h"
#include "ASSeedItemWidget.h"
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QStringListModel>
#include <QCompleter>
#include <QEvent>
#include <QKeyEvent>

class ASPaintingSeedsWidget : public ASWidgetInSideBarBase
{
	Q_OBJECT

public:
	ASPaintingSeedsWidget(QWidget *parent);
	~ASPaintingSeedsWidget();

	virtual void SetEnabled(const bool c_bEnabled);

private:
	// ����Ԫ��
	QLineEdit* m_LineENewData;
	QPushButton* m_PushBUndo;
	QCompleter*	m_Cmlt;
	QStringListModel* m_StrLiMo;
	QPushButton* m_BtnFinish;

	bool m_FlagFromAddin = false;
	// ��ʼ��
	void UIInit();
	void CompleterInit();
	void NewSeed(QString name, int label, QColor color);

signals:

private slots :

	// �½��ļ�
	void slotSeedNameReturn();
	// ������ť
	void slotUndo();
	// ����ȫ�ּ����ź�
	void slotGlobalKeyBoard(QKeyEvent* pKeyEvent);
	// �����ǰ������ʽ�ı�
	void slotInteractorStyle2DChanged(int interactor);
	// �Ӳ���������½�����
	//void slotNewFromAddin(int c_Type, QString name, int label, QColor color);
	// Finish
	void slotFinish();
};

/*
QlineEdit �Զ���ȫʱ�����в�ȫ�����˵�ʱ���»س����ȴ���LineEdit��editingFinished�źţ�
�󴥷�QCompleter��activated�źš�activated�¼��ὫLineEdit�е����ݲ��룬���Դ�ʱ��
editingFinished��Ӧ�Ĳ������QlineEdit��������Ч�ġ�
����ʹ���¼���������activated�¼���Ч�����»س������ᴥ��activated�źţ����������źŸ�
���QlineEdit���ݵĲۣ������ղ�����
*/

class EventFilterSeeds : public QObject
{
	Q_OBJECT
public:
	EventFilterSeeds(QLineEdit* lineEdit, QObject* parent = NULL)
		:QObject(parent)
		, mLineEdit(lineEdit)
	{ }
	virtual ~EventFilterSeeds()
	{ }

	bool eventFilter(QObject* watched, QEvent* event)
	{
		QAbstractItemView* view = qobject_cast<QAbstractItemView*>(watched);
		if (event->type() == QEvent::KeyPress)
		{
			QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key_Return ||
				keyEvent->key() == Qt::Key_Enter)
			{
				//mLineEdit->clear();
				view->hide();
				emit EnterPress();
				return true;
			}
		}
		return false;
	}

private:
	QLineEdit* mLineEdit;
signals:
	void EnterPress();
};
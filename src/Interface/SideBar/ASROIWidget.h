#pragma once

#include "ASWidgetInSideBarBase.h"
#include <QComboBox>
#include <QListWidget>
#include <QTabWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QCompleter>
#include <QStringListModel>
#include <QEvent>
#include <QKeyEvent>
#include <QPoint>
#include <QMenu>
#include <QAction>

class ASROIData;
class ASROIItemWidget;

class ASROIWidget : public ASWidgetInSideBarBase
{
	Q_OBJECT

public:
	ASROIWidget(QWidget *parent);
	~ASROIWidget();

	virtual void SetEnabled(const bool c_bEnabled);

private:

	// ����Ԫ��
	// 0
	QTabWidget*		m_TabWTools;
	// 1 ����ROI
	QLineEdit*		m_CubeName;
	QCompleter*		m_CubeCmlt;
	QStringListModel* m_CubeStrLiMo;
	QDoubleSpinBox*	m_CubeRange[6]; // 0: XMin 1: XMax 2: YMin 3: YMax 4: ZMin 5: ZMax
	QPushButton* m_BtnFinish;

	bool m_FlagFromAddin = false;
	// ��ʼ������
	void UIInit();
	void CompleterInit();
	void NewROI(QString name, int label, QColor color);
	

private slots:

	// Cube ROI �½�ROI
	void slotCubeNameReturn();
	// ˢ��Cubeҳ
	void slotRefreshCubeWidget();
	// Cubeҳ�������
	void slotCubeValueChanged();
	// �Ӳ���������½�����
	//void slotNewFromAddin(int c_Type, QString name, int label, QColor color);
	// Finish
	void slotFinish();

signals:

};

/*
QlineEdit �Զ���ȫʱ�����в�ȫ�����˵�ʱ���»س����ȴ���LineEdit��editingFinished�źţ�
�󴥷�QCompleter��activated�źš�activated�¼��ὫLineEdit�е����ݲ��룬���Դ�ʱ��
editingFinished��Ӧ�Ĳ������QlineEdit��������Ч�ġ�
����ʹ���¼���������activated�¼���Ч�����»س������ᴥ��activated�źţ����������źŸ�
���QlineEdit���ݵĲۣ������ղ�����
*/

class EventFilterROI : public QObject
{
	Q_OBJECT
public:
	EventFilterROI(QLineEdit* lineEdit, QObject* parent = NULL)
		:QObject(parent)
		, mLineEdit(lineEdit)
	{ }
	virtual ~EventFilterROI()
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
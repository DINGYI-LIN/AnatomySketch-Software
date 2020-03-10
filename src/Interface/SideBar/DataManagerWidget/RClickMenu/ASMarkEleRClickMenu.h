#pragma once

#include <QObject>
#include "ASDataManagerAction.h"

class ASDataManagerAction;
class ASAbstractData;

class ASMarkEleRClickMenu : public QObject
{
	Q_OBJECT

public:
	ASMarkEleRClickMenu(QObject *parent = nullptr);
	~ASMarkEleRClickMenu();

	void Generate(const QPoint c_pos, ASAbstractData* DataNode, const int c_MarkEleID);

private:

	// �Ҽ��˵�
	ASDataManagerAction* m_RARemove;
	ASDataManagerAction* m_RAFocusOn;
	// �½�����
	ASDataManagerAction* m_RANewContour;
	ASDataManagerAction* m_RANewSeeds;
	ASDataManagerAction* m_RANewROI;

	// �Ҽ��˵���ʼ��
	void RightClickInit();
	// �Ҽ��˵�����
	void RightClickMenuAction(ASAbstractData* DataNode, enumActionInContextMenu action, 
		const int c_MarkEleID);

signals:


private slots:


};

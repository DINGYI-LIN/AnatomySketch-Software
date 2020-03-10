#pragma once

#include <QObject>
#include <QWidgetAction>
#include <QPushButton>
#include <QSlider>
#include <QPoint>
#include "ASDataManagerAction.h"

class ASAbstractData;

class ASDataNodeRClickMenu : public QObject
{
	Q_OBJECT

public:
	ASDataNodeRClickMenu(QObject *parent = nullptr);
	~ASDataNodeRClickMenu();

	void Generate(const QPoint c_pos, ASAbstractData* DataNode);

private:

	// �Ҽ��˵�
	ASDataManagerAction* m_RASave;
	ASDataManagerAction* m_RARemove;
	ASDataManagerAction* m_RARemoveAll;
	ASDataManagerAction* m_RAReinit;
	ASDataManagerAction* m_RAMoveto;
	ASDataManagerAction* m_RACuttentData;
	QMenu* m_RMDataType;
	ASDataManagerAction* m_RADataType[2];
	QMenu* m_RMColorMap;
	ASDataManagerAction* m_RAColorMap[14];
	ASDataManagerAction* m_RANewAnnotation;
	ASDataManagerAction* m_RANewSeg;
	ASDataManagerAction* m_RANewImgProcess;
	ASDataManagerAction* m_RANewMeshProcess;
	QMenu* m_RMContourInterStyle;
	ASDataManagerAction* m_RAContourIS_Mouse;
	ASDataManagerAction* m_RAContourIS_MouseSerial;
	ASDataManagerAction* m_RAContourIS_Stylus;
	// �½�����
	ASDataManagerAction* m_RANewContour;
	ASDataManagerAction* m_RANewSeeds;
	ASDataManagerAction* m_RANewROI;
	ASDataManagerAction* m_RANewLandmark;
	// ��͸���Ȼ�����
	QWidgetAction* m_RWAOpacity;
	QSlider* m_RSliderOpacity;
	// ��ɫѡ��
	QWidgetAction* m_RWAColor;
	QPushButton* m_RButtonColor;

	ASAbstractData* m_pGeneratingDataNode = nullptr; // �����Ҽ��˵��Ľڵ�

	// �Ҽ��˵���ʼ��
	void RightClickInit();
	// �Ҽ��˵�����
	void RightClickMenuAction(ASAbstractData* DataNode, enumActionInContextMenu action);
	// ���Ҽ��˵������õ���ɫ�����
	int getColorMapFromAction(enumActionInContextMenu actor);

signals:


private slots:

	// �Ҽ��˵���������ɫ�Ͳ�͸����
	void slotOpacityPolyContextMenu(int value);
	void slotColorPolyContextMenu();


};

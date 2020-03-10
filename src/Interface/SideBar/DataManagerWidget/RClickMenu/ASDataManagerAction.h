#pragma once

#include <QAction>

// �Ҽ��˵��г��ֵ���Ŀ

enum enumActionInContextMenu
{
	EMActSave,					// save
	EMActRemove,				// Remove
	EMActRemoveAll,				// RemoveAll
	EMActReinit,				// Reinit
	EMActMoveto,				// Moveto
	EMActNewAnnotation,			// NewAnnotation
	EMActNewSeg,				// NewSeg
	EMActNewImgProcess,			// NewImgProcess
	EMActNewMeshProcess,		// NewMeshProcess
	EMActCurrentData,			// CurrentData
	EMActProperty,				// Property
	EMActFocusOn,				// FocusOn
	EMActNewContour,			// �½�������
	EMActNewSeed,				// �½����ӵ�
	EMActNewROI,				// �½�ROI
	EMActNewLandmark,			// �½��궨��
	EMActDataType_GrayScale,	// �������ͣ��Ҷ�ͼ
	EMActDataType_LabelMap,		// �������ͣ���ǩͼ
	EMActColorMap_Gray,			// ColorMap, Default
	EMActColorMap_MultiLabel,	// ColorMap, MapMultiLabel
	EMActColorMap_Mask,			// ColorMap, Mask
	EMActColorMap_Cold,			// ColorMap, Cold
	EMActColorMap_Hot,			// ColorMap, Hot
	EMActColorMap_Cool,			// ColorMap, Cool
	EMActColorMap_Bronson,		// ColorMap, Bronson
	EMActColorMap_SplitBBR,		// ColorMap, Split_BBR
	EMActColorMap_UCLA,			// ColorMap, UCLA
	EMActColorMap_Red,			// ColorMap, Red
	EMActColorMap_Green,		// ColorMap, Green
	EMActColorMap_Blue,			// ColorMap, Blue
	EMActColorMap_HeartVR,		// ColorMap, HeartVR
	EMActColorMap_HeadVR,		// ColorMap, HeadVR
	EMActCntrIS_Mouse,			// �����߽�����ʽ�����
	EMActCntrIS_MouseSerial,	// �����߽�����ʽ���������
	EMActCntrIS_Stylus			// �����߽�����ʽ�����ر�
};

class ASDataManagerAction : public QAction
{
	Q_OBJECT

public:
	ASDataManagerAction(QObject * parent, enumActionInContextMenu action);
	ASDataManagerAction(const QString & text, QObject * parent, enumActionInContextMenu action);
	ASDataManagerAction(const QIcon & icon, const QString & text, QObject * parent, enumActionInContextMenu action);
	~ASDataManagerAction();

	enumActionInContextMenu getAction();

private:

	enumActionInContextMenu m_Action;

};

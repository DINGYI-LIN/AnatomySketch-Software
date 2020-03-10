#pragma once

#include <QObject>
#include <QDialog>

class ASMainWidget;
class ASTransmissionManager;
class ASDataManager;
class ASVisualizationManager;
class ASInteractorStyleManager;

class ASLauncher : public QObject
{
	Q_OBJECT

public:
	ASLauncher(QObject *parent = 0);
	~ASLauncher();

	// ȫ�ּ����¼�
	//void GlobalKeyboardEvent(QKeyEvent* event);

private:
	ASMainWidget*			theMainWidget;
	ASTransmissionManager*	theTransmissionManager;
	ASDataManager*			theDataManager;
	ASVisualizationManager*	theVisualizationManager;
	ASInteractorStyleManager* theInteractorStyleManager;

};

/*
������ 
*/

#pragma once

//#include "common.h"
#include "ASDropShadowWidget.h"
//#include <QWidget>

class ASTitleWidget;
class ASToolBar;
class ASSideBar;
class ASOperationBar;
class ASStatusBar;
//class ASSignalLinker;

#define VSPLITTERHANDLEWIDTH			3         // ��������ȣ���������Ͳ�����֮���϶�Ŀ��

class ASMainWidget : public ASDropShadowWidget
{
	Q_OBJECT

public:
	ASMainWidget(QWidget *parent = 0);
	~ASMainWidget();

	// �õ������ڵ�ָ�룬ʵ����������ʱ��
	static QWidget* GetMainWidget();

protected:
	virtual void closeEvent(QCloseEvent * e);

public slots:

	void moveWindow(int ax, int ay);

private slots:

private:

	ASTitleWidget* m_TitleWidget;	//������
	ASToolBar* m_ToolBar;			//������
	ASSideBar* m_SideBar;			//�����
	ASOperationBar* m_OperationBar; //��������
	ASStatusBar* m_StatusBar;		//״̬��

	void UIInit();

	// ������ָ��
	static QWidget* m_FatherWidget;
};

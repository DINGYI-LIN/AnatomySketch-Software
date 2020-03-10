/*
����  ��������С�����رյ�
*/
#pragma once
#ifdef WIN32
#pragma  execution_character_set("utf-8")
#endif

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
#include <QPushButton>

class ASPushButtonInTitleWidget;
class AboutWidget;
class ASHelpWidget;

#define BUTTON_WIDTH 32         // ��ť���;
#define BUTTON_HEIGHT 26        // ��ť�߶�;
#define TITLE_HEIGHT 30         // �������߶�;

class ASTitleWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ASTitleWidget(QWidget *parent = 0);
	~ASTitleWidget();
	
protected:

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);

private:

	QPoint m_press_point;//��갴��ȥ�ĵ�

	bool is_move;
	bool is_Maximized = true;

	QPoint move_point; //�ƶ��ľ���
	bool mouse_press; //����������

	ASPushButtonInTitleWidget* m_min_button; //��С��
	ASPushButtonInTitleWidget* m_max_button; //���
	ASPushButtonInTitleWidget* m_close_button; //�ر�

	QPushButton* m_BtnOpen;
	QPushButton* m_BtnDICOM;
	QPushButton* m_BtnHelp;
	QPushButton* m_BtnAbout; 
	QPushButton* m_BtnTheme;
	QPushButton* m_BtnLang;
	
	void UIInit();

	// �ӽ���
	AboutWidget* m_AboutWidget;
	ASHelpWidget* m_HelpWidget;

private slots:

	void maxClicked();//��󻯰�ť���£���Ҫ�ж���󻯻���ȡ�����

	// ��
	void slotOpen();
	// DICOM
	void slotDICOM();
	// Help
	void slotHelp();
	// About
	void slotAbout();
	// Theme
	void slotQSSChange(bool checked);
	void slotOperationbarThemeChange(bool checked);
	void slotBackgroundChange(bool checked);
	void slotSidebarChange(bool checked);

	// Lang
	void slotLanguageChange(bool checked);

signals:

	void showMin();
	void showMax();
	void ShowNormal();
	void programexit();
	void movewindow(int ax, int ay);

};

#pragma once

#include <QApplication>
#include <QObject>

class ASApplication : public QApplication
{
	Q_OBJECT
public:
     ASApplication(int&argc,char **argv);
     ~ASApplication();

     bool notify(QObject*, QEvent *);

	 // ��ASLauncher����֮����������źŲ�
	 void connectsns();

private:
	QWidget* mainWindow;
	QTranslator *zhTranslator;

public slots:

	// �����Ĳ�
	void slotQSSChange(bool checked);
	// �����ԵĲ�
	void slotLangChange(bool checked);

};

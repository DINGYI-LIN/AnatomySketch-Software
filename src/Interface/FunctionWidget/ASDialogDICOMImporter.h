#pragma once

#include <vtkSmartPointer.h>
#include <vtkDICOMDirectory.h>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QList>
#include <QStackedWidget>
#include <QTextBrowser>

class ASSignalLinker;
class ASDataManager;

class ASDialogDICOMImporter : public QDialog
{
	Q_OBJECT

public:
	ASDialogDICOMImporter(QWidget *parent);
	~ASDialogDICOMImporter();

	// ����Ƿ�Ϊ�գ����Ϊ���Զ���ѡ·���Ի���
	void CheckVoid();
	// ɨ�����
	void DiskScanningFinished(vtkDICOMDirectory* DICOMDirectory);

protected:
	virtual void closeEvent(QCloseEvent * e);

private:

	//����Ԫ��
	QPushButton*		m_PushButtonScanDirectory;		// ѡ��·����ť
	QLineEdit*			m_LineEditScanDirectory;		// ��ʾ��ǰ·��
	QStackedWidget*		m_StackedWidget;				// �������������л�
	QTableWidget*		m_TableWidgetSeriesDisplay;		// ��ʾ������������
	QTextBrowser*		m_TextBrowserOutput;			// �������
	QPushButton*		m_PushButtonCancel;				// ȡ��
	QPushButton*		m_PushButtonLoad;				// ����
	//�����ʼ��
	void UIInit();
	// ɨ����
	vtkSmartPointer<vtkDICOMDirectory> m_DICOMDirectory;

	// �Ƿ�����ɨ��
	bool m_isScanning = false;

private slots:

	//ѡ�ļ��еİ�ť����
	void slotScanDirectory();
	//ȡ���İ�ť����
	void slotCancel();
	//����İ�ť����
	void slotLoad();
};

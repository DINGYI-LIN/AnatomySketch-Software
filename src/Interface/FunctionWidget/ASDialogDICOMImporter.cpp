#include "ASDialogDICOMImporter.h"
#include "ASTransDICOMLoader.h"
#include "ASTransSetting.h"
#include <vtkDICOMItem.h>
#include <vtkDICOMValue.h>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QStringList>
#include <QRegExp>
#include <QByteArray>
#include <QHeaderView>
#include <QDir>
#include <QTextCodec>
#include <QHeaderView>
#include <QSettings>

ASDialogDICOMImporter::ASDialogDICOMImporter(QWidget *parent)
	: QDialog(parent)
{
	this->resize(QSize(800, 600));
	UIInit();

	//�źŲ�
	connect(m_PushButtonScanDirectory, SIGNAL(clicked()), this, SLOT(slotScanDirectory()));
	connect(m_PushButtonCancel, SIGNAL(clicked()), this, SLOT(slotCancel()));
	connect(m_PushButtonLoad, SIGNAL(clicked()), this, SLOT(slotLoad()));
}

ASDialogDICOMImporter::~ASDialogDICOMImporter()
{
}

// ����Ƿ�Ϊ�գ����Ϊ���Զ���ѡ·���Ի���
void ASDialogDICOMImporter::CheckVoid()
{
	if (m_TableWidgetSeriesDisplay->rowCount() == 0)
	{
		this->slotScanDirectory();
	}
}
// ɨ�����
void ASDialogDICOMImporter::DiskScanningFinished(vtkDICOMDirectory* DICOMDirectory)
{
	this->m_DICOMDirectory = DICOMDirectory;
	// �л�Ϊ�����б�
	m_StackedWidget->setCurrentWidget(m_TableWidgetSeriesDisplay);
	// ����б�
	while (m_TableWidgetSeriesDisplay->rowCount())
	{
		m_TableWidgetSeriesDisplay->removeRow(0);
	}
	// ����б�
	m_TableWidgetSeriesDisplay->setRowCount(DICOMDirectory->GetNumberOfSeries());
	// Iterate through all of the studies that are present.
	int NumOfStudy = DICOMDirectory->GetNumberOfStudies();
	for (int crntStudy = 0; crntStudy < NumOfStudy; crntStudy++)
	{
		// Get information related to the patient study
		vtkDICOMItem patient = DICOMDirectory->GetPatientRecordForStudy(crntStudy);
		vtkDICOMItem study = DICOMDirectory->GetStudyRecord(crntStudy);
		// Iterate through all of the series in this study.
		int j1 = DICOMDirectory->GetFirstSeriesForStudy(crntStudy);
		int j2 = DICOMDirectory->GetLastSeriesForStudy(crntStudy);
		for (int cuntSeries = j1; cuntSeries <= j2; cuntSeries++)
		{
			vtkDICOMItem series = DICOMDirectory->GetSeriesRecord(cuntSeries);
			QTableWidgetItem *item0 = new QTableWidgetItem;
			item0->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			item0->setCheckState(Qt::Checked);
			m_TableWidgetSeriesDisplay->setItem(cuntSeries, 0, item0);
			QTableWidgetItem* item1 = new QTableWidgetItem(series.GetAttributeValue(DC::SeriesNumber).GetCharData());
			item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			item1->setFlags(item1->flags() & (~Qt::ItemIsEditable)); // ���õ�Ԫ�񲻿ɱ༭
			item1->setFlags(item1->flags() & (~Qt::ItemIsSelectable)); // ���õ�Ԫ�񲻿�ѡ��
			m_TableWidgetSeriesDisplay->setItem(cuntSeries, 1, item1);
			QTableWidgetItem* item2 = new QTableWidgetItem(series.GetAttributeValue(DC::Modality).GetCharData());
			item2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			item2->setFlags(item2->flags() & (~Qt::ItemIsEditable)); // ���õ�Ԫ�񲻿ɱ༭
			item2->setFlags(item2->flags() & (~Qt::ItemIsSelectable)); // ���õ�Ԫ�񲻿�ѡ��
			m_TableWidgetSeriesDisplay->setItem(cuntSeries, 2, item2);
			QTableWidgetItem* item3 = new QTableWidgetItem(series.GetAttributeValue(DC::SeriesDate).GetCharData());
			item3->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			item3->setFlags(item3->flags() & (~Qt::ItemIsEditable)); // ���õ�Ԫ�񲻿ɱ༭
			item3->setFlags(item3->flags() & (~Qt::ItemIsSelectable)); // ���õ�Ԫ�񲻿�ѡ��
			m_TableWidgetSeriesDisplay->setItem(cuntSeries, 3, item3);
			QTableWidgetItem* item4 = new QTableWidgetItem(study.GetAttributeValue(DC::StudyID).GetCharData());
			item4->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			item4->setFlags(item4->flags() & (~Qt::ItemIsEditable)); // ���õ�Ԫ�񲻿ɱ༭
			item4->setFlags(item4->flags() & (~Qt::ItemIsSelectable)); // ���õ�Ԫ�񲻿�ѡ��
			m_TableWidgetSeriesDisplay->setItem(cuntSeries, 4, item4);
			QTableWidgetItem* item5 = new QTableWidgetItem(patient.GetAttributeValue(DC::PatientName).GetCharData());
			item5->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			item5->setFlags(item5->flags() & (~Qt::ItemIsEditable)); // ���õ�Ԫ�񲻿ɱ༭
			item5->setFlags(item5->flags() & (~Qt::ItemIsSelectable)); // ���õ�Ԫ�񲻿�ѡ��
			m_TableWidgetSeriesDisplay->setItem(cuntSeries, 5, item5);
			QTableWidgetItem* item6 = new QTableWidgetItem(patient.GetAttributeValue(DC::PatientID).GetCharData());
			item6->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			item6->setFlags(item6->flags() & (~Qt::ItemIsEditable)); // ���õ�Ԫ�񲻿ɱ༭
			item6->setFlags(item6->flags() & (~Qt::ItemIsSelectable)); // ���õ�Ԫ�񲻿�ѡ��
			m_TableWidgetSeriesDisplay->setItem(cuntSeries, 6, item6);
		}
	}
	m_PushButtonLoad->setEnabled(true);
	m_isScanning = false;
}

void ASDialogDICOMImporter::closeEvent(QCloseEvent * e)
{
	// �������ɨ�裬ȡ��ɨ��
	if (m_isScanning)
	{
		ASTransDICOMLoader::ScanningDiskStopManualy();

		// �л�Ϊ�����б�
		m_StackedWidget->setCurrentWidget(m_TableWidgetSeriesDisplay);
		// ����б�
		while (m_TableWidgetSeriesDisplay->rowCount())
		{
			m_TableWidgetSeriesDisplay->removeRow(0);
		}
		m_LineEditScanDirectory->clear();
		m_PushButtonLoad->setEnabled(true);
		m_isScanning = false;
	}
	QDialog::closeEvent(e);
}

//�����ʼ��
void ASDialogDICOMImporter::UIInit()
{
	// 1
	QHBoxLayout* HBoxLayout1 = new QHBoxLayout();
	m_PushButtonScanDirectory = new QPushButton(this);
	m_LineEditScanDirectory = new QLineEdit(this);
	HBoxLayout1->addWidget(m_PushButtonScanDirectory);
	HBoxLayout1->addWidget(m_LineEditScanDirectory);
	m_PushButtonScanDirectory->setText("Scan Directory");
	m_PushButtonScanDirectory->setMinimumWidth(100);
	m_LineEditScanDirectory->setFocusPolicy(Qt::NoFocus);//���������ܻ�ý��㣬�ﵽ���ɱ༭��Ч��

	// 2
	m_StackedWidget = new QStackedWidget(this);
	m_TableWidgetSeriesDisplay = new QTableWidget(this);
	m_TextBrowserOutput = new QTextBrowser(this);
	m_StackedWidget->addWidget(m_TableWidgetSeriesDisplay);
	m_StackedWidget->addWidget(m_TextBrowserOutput);
	m_StackedWidget->setCurrentWidget(m_TableWidgetSeriesDisplay);

	// 3
	QHBoxLayout* HBoxLayout3 = new QHBoxLayout();
	m_PushButtonCancel = new QPushButton(this);
	m_PushButtonLoad = new QPushButton(this);
	HBoxLayout3->addStretch();
	HBoxLayout3->addWidget(m_PushButtonCancel);
	HBoxLayout3->addWidget(m_PushButtonLoad);
	m_PushButtonCancel->setText(tr("Cancel Scanning"));
	m_PushButtonCancel->setEnabled(false);
	m_PushButtonLoad->setText(tr("Import Data"));

	// 0
	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainLayout->addLayout(HBoxLayout1);
	mainLayout->addWidget(m_StackedWidget);
	mainLayout->addLayout(HBoxLayout3);
	this->setLayout(mainLayout);

	//����������
	QStringList header;
	header.append(" ");
	header.append("SeriesNumber");
	header.append("Modality");
	header.append("SeriesDate");
	header.append("StudyID");
	header.append("PatientsName");
	header.append("PatientID");
	m_TableWidgetSeriesDisplay->verticalHeader()->hide();
	m_TableWidgetSeriesDisplay->setColumnCount(7);
	m_TableWidgetSeriesDisplay->setColumnWidth(0, 25);
	m_TableWidgetSeriesDisplay->setColumnWidth(1, 122);
	m_TableWidgetSeriesDisplay->setColumnWidth(2, 122);
	m_TableWidgetSeriesDisplay->setColumnWidth(3, 122);
	m_TableWidgetSeriesDisplay->setColumnWidth(4, 122);
	m_TableWidgetSeriesDisplay->setColumnWidth(5, 122);
	m_TableWidgetSeriesDisplay->setColumnWidth(6, 122);
	m_TableWidgetSeriesDisplay->setHorizontalHeaderLabels(header);
	m_TableWidgetSeriesDisplay->setShowGrid(false);
	m_TableWidgetSeriesDisplay->setFrameShape(QFrame::NoFrame); //�����ޱ߿�
	m_TableWidgetSeriesDisplay->setEditTriggers(QAbstractItemView::NoEditTriggers); //���ò��ɱ༭
	m_TableWidgetSeriesDisplay->setFocusPolicy(Qt::NoFocus);
}

//ѡ�ļ��еİ�ť����
void ASDialogDICOMImporter::slotScanDirectory()
{
	QString lastPath = ASTransSetting::GetSetting()->value("LastFilePath").toString();
	//���ļ���׼�Ի���
	QString OperatingDirectoryName = QFileDialog::getExistingDirectory(
		this,						// ָ������
		"Directory",				// �ļ��Ի������������
		lastPath);					// ָ�����ļ�Ŀ¼
	//�ж��Ƿ���ļ�
	if (OperatingDirectoryName.size() == 0)
	{
		return;
	}
	QFileInfo fi(OperatingDirectoryName);
	//ASTransSetting::GetSetting()->setValue("LastFilePath", QVariant(fi.path()));
	ASTransSetting::GetSetting()->setValue("LastFilePath", QVariant(OperatingDirectoryName));
	m_LineEditScanDirectory->setText(OperatingDirectoryName);

	// �л�Ϊ�������
	m_StackedWidget->setCurrentWidget(m_TextBrowserOutput);
	m_TextBrowserOutput->clear();
	m_TextBrowserOutput->append(tr(" - Starting scanning disk..."));
	m_PushButtonLoad->setEnabled(false);
	m_PushButtonCancel->setEnabled(true);
	m_isScanning = true;
	// ɨ��Ӳ��
	ASTransDICOMLoader::ScanDisk(OperatingDirectoryName);
}

//ȡ���İ�ť����
void ASDialogDICOMImporter::slotCancel()
{
	// �������ɨ�裬ȡ��ɨ��
	if (m_isScanning)
	{
		ASTransDICOMLoader::ScanningDiskStopManualy();

		// �л�Ϊ�����б�
		m_StackedWidget->setCurrentWidget(m_TableWidgetSeriesDisplay);
		// ����б�
		while (m_TableWidgetSeriesDisplay->rowCount())
		{
			m_TableWidgetSeriesDisplay->removeRow(0);
		}
		m_LineEditScanDirectory->clear();
		m_PushButtonLoad->setEnabled(true);
		m_PushButtonCancel->setEnabled(false);
		m_isScanning = false;
	}	
}
//����İ�ť����
void ASDialogDICOMImporter::slotLoad()
{
	// ���checkbox���Ƿ���Ҫ��������
	QList<int>* listSeriesList = new QList<int>; // ��Ҫ����������б�
	int numOfSeries = m_TableWidgetSeriesDisplay->rowCount();
	for (int crntSeries = 0; crntSeries < numOfSeries; crntSeries++)
	{
		if (m_TableWidgetSeriesDisplay->item(crntSeries, 0)->checkState() == Qt::Checked)
		{
			// ��Ҫ���������
			listSeriesList->append(crntSeries);
		}		
	}
	// ��������
	if (ASTransDICOMLoader::LoadDICOMData(this->m_DICOMDirectory, listSeriesList))
		this->hide();
}
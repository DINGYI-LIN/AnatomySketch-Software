#include "ASGraphCutWidget.h"
#include "ASFModelGraphCut.h"
#include "ASArrayImageData.h"
#include "ASSeedData.h"
#include "ASDataStructureWalker.h"
#include "ASTransSidebarGeneral.h"
#include "ASFModelMask.h"
#include "ASTransGraphCut.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QString>
#include <QListWidgetItem>

ASGraphCutWidget::ASGraphCutWidget(QWidget *parent)
	: ASWidgetInSideBarBase(parent)
{
	// �����ʼ��
	this->UIInit();
	// ����Transmission�ź�
	//connect(ASTransSidebarGeneral::GetSelfPointer(), SIGNAL(signalRefreshDataComboBox(int)), this, SLOT(slotRefreshDataComboBox(int)));
	//connect(ASTransSidebarGeneral::GetSelfPointer(), SIGNAL(signalMaskEnabledChanged()), this, SLOT(slotMaskEnabledChanged()));
}

ASGraphCutWidget::~ASGraphCutWidget()
{

}

void ASGraphCutWidget::UIInit()
{
	// 1 Files
	QLabel* label11 = new QLabel(tr("Data:"), this);
	// 2 Image
	QLabel* label21 = new QLabel(tr("Image"), this);
	label21->setMaximumWidth(60);
	m_ComboBoxImageFile = new QComboBox(this);
	connect(m_ComboBoxImageFile, SIGNAL(currentIndexChanged(int)), this, SLOT(slotComboBoxChanged(int)));
	QHBoxLayout* layout2 = new QHBoxLayout();
	layout2->addWidget(label21);
	layout2->addWidget(m_ComboBoxImageFile);
	// 3 Seed
	QLabel* label31 = new QLabel(tr("Seed Point:"), this);
	// 4 List Widget
	m_ListWidgetSeeds = new QListWidget(this);
	// 5 Output
	QLabel* label51 = new QLabel(tr("Output"), this);
	label51->setMaximumWidth(60);
	m_LineEditOutput = new QLineEdit(this);
	QHBoxLayout* layout5 = new QHBoxLayout();
	layout5->addWidget(label51);
	layout5->addWidget(m_LineEditOutput);
	// 6 Option
	QLabel* label61 = new QLabel(tr("Parameter Setting:"), this);
	// 7 Lambda Delta
	QLabel* label71 = new QLabel(tr("Lambda"), this);
	label71->setMaximumWidth(60);
	m_DSpinBoxLambda = new QDoubleSpinBox(this);
	m_DSpinBoxLambda->setValue(0.0);
	QLabel* label72 = new QLabel(tr("Delta"), this);
	label72->setMaximumWidth(60);
	m_DSpinBoxDelta = new QDoubleSpinBox(this);
	m_DSpinBoxDelta->setValue(1.0);
	QHBoxLayout* layout7 = new QHBoxLayout();
	layout7->addWidget(label71);
	layout7->addWidget(m_DSpinBoxLambda);
	layout7->addSpacing(5);
	layout7->addWidget(label72);
	layout7->addWidget(m_DSpinBoxDelta);
	// 8 nNeighbor
	QLabel* label81 = new QLabel(tr("nNeighbor"), this);
	label81->setMaximumWidth(60);
	m_ComboBoxNeighbor = new QComboBox(this);
	m_ComboBoxNeighbor->addItem(tr("6"));
	m_ComboBoxNeighbor->addItem(tr("26"));
	m_ComboBoxNeighbor->setCurrentIndex(0);
	QHBoxLayout* layout8 = new QHBoxLayout();
	layout8->addWidget(label81);
	layout8->addWidget(m_ComboBoxNeighbor);
	// 9 Post Processing
	QLabel* label91 = new QLabel(tr("Post Processing"), this);
	label91->setMaximumWidth(60);
	m_LineEditPostProcessing = new QLineEdit(this);
	QHBoxLayout* layout9 = new QHBoxLayout();
	layout9->addWidget(label91);
	layout9->addWidget(m_LineEditPostProcessing);
	// 10 Marching cub
	m_CheckboxMarchingCub = new QCheckBox(tr("Generate the result curved surface"), this);
	connect(m_CheckboxMarchingCub, SIGNAL(stateChanged(int)), this, SLOT(slotMarchingCubChecked(int)));
	QLabel* label101 = new QLabel(tr("Smoothness index:"), this);
	label101->setAlignment(Qt::AlignRight);
	m_SmoothIterations = new QSpinBox(this);
	m_SmoothIterations->setMinimum(0);
	m_SmoothIterations->setMaximum(1000);
	m_SmoothIterations->setEnabled(false);
	QHBoxLayout* layout10 = new QHBoxLayout();
	layout10->addWidget(m_CheckboxMarchingCub);
	layout10->addWidget(label101);
	layout10->addWidget(m_SmoothIterations);
	// 11 Query
	m_CheckboxQuery = new QCheckBox(tr("Do not ask whether to overwrite the result"), this);
	// 12 Generate
	m_PushButtonGenerate = new QPushButton(tr("Generate"), this);
	connect(m_PushButtonGenerate, SIGNAL(clicked()), this, SLOT(slotGenerateClicked()));

	// 0 mainlayout
	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainLayout->addWidget(label11);
	mainLayout->addLayout(layout2);
	mainLayout->addSpacing(10);
	mainLayout->addWidget(label31);
	mainLayout->addWidget(m_ListWidgetSeeds);
	mainLayout->addLayout(layout5);
	mainLayout->addSpacing(10);
	mainLayout->addWidget(label61);
	mainLayout->addLayout(layout7);
	mainLayout->addLayout(layout8);	
	mainLayout->addSpacing(10);
	mainLayout->addLayout(layout9);
	mainLayout->addLayout(layout10);
	mainLayout->addSpacing(10);
	mainLayout->addWidget(m_CheckboxQuery);
	mainLayout->addWidget(m_PushButtonGenerate);
	mainLayout->addStretch();
	this->setLayout(mainLayout);
}
// ˢ������ѡ��
void ASGraphCutWidget::UpdateComboBoxImage()
{
	//�ֽ�ԭ���������
	m_ComboBoxImageFile->clear();
	while (m_listIDImageFileIndex.size())
	{
		m_listIDImageFileIndex.removeFirst();
	}
	//�������ݣ������������
	bool haveBeforIndex = false;
	for (ASAbstractData* item = ASDataStructureWalker::bigen_inherit(DataType_ArrayImageData); item != nullptr; item = ASDataStructureWalker::next_inherit(DataType_ArrayImageData))
	{
		ASArrayImageData* crntDataNode = (ASArrayImageData*)item;
		m_listIDImageFileIndex.append(crntDataNode->getDataNodeID());
		m_ComboBoxImageFile->addItem(crntDataNode->getName());
		if (crntDataNode->getDataNodeID() == m_ncrntIDOfImageFile)
		{
			//�ҵ���ˢ��֮ǰ��ͬ���ļ�
			m_ComboBoxImageFile->setCurrentIndex(m_listIDImageFileIndex.size() - 1);
			haveBeforIndex = true;
		}
	}
	if (haveBeforIndex == false)
	{
		//û�ҵ�֮ǰ��ͬ���ļ�
		if (m_ComboBoxImageFile->count() == 0)
		{
			//��ĿΪ�գ�û�д򿪵��ļ�
			m_ncrntIDOfImageFile = -1;
		}
		else
		{
			//��Ŀ��Ϊ��
			m_ComboBoxImageFile->setCurrentIndex(0);
			m_ncrntIDOfImageFile = m_listIDImageFileIndex.at(0);
		}
	}
}
// ˢ�����ӵ��б�
void ASGraphCutWidget::UpdateSeedsList()
{
	// ��ǰѡ�����ӵ�ID�б�
	QList<int> crntChoosenSeeds;
	int numOfItems = m_ListWidgetSeeds->count();
	for (int ncrntItem = 0; ncrntItem < numOfItems; ncrntItem++)
	{
		if (m_ListWidgetSeeds->item(ncrntItem)->checkState() == Qt::Checked)
		{
			crntChoosenSeeds.append(m_listIDSeedsListIndex.at(ncrntItem));
		}
	}
	// �������
	while (m_ListWidgetSeeds->count())
	{
		delete m_ListWidgetSeeds->item(0);
		m_ListWidgetSeeds->takeItem(0);
	}
	m_ListWidgetSeeds->clear();
	m_listIDSeedsListIndex.clear();
	// ��������
	for (ASAbstractData* item = ASDataStructureWalker::bigen_inherit(DataType_SeedData); item != nullptr; item = ASDataStructureWalker::next_inherit(DataType_SeedData))
	{
		ASSeedData* crntDataNode = (ASSeedData*)item;
		QListWidgetItem* crntWidgetItem = new QListWidgetItem(m_ListWidgetSeeds);
		if (crntChoosenSeeds.indexOf(crntDataNode->getDataNodeID()) >= 0)
		{
			crntWidgetItem->setCheckState(Qt::Checked);
		}
		else
		{
			crntWidgetItem->setCheckState(Qt::Unchecked);
		}		
		crntWidgetItem->setText(crntDataNode->getName());
		m_ListWidgetSeeds->addItem(crntWidgetItem);
		m_listIDSeedsListIndex.append(crntDataNode->getDataNodeID());
	}
}
// ���ɽ������checkbox
void ASGraphCutWidget::slotMarchingCubChecked(int state)
{
	if (state == Qt::Checked)
	{
		m_SmoothIterations->setEnabled(true);
	}
	else
	{
		m_SmoothIterations->setEnabled(false);
	}
}
// ���ɰ�ť����
void ASGraphCutWidget::slotGenerateClicked()
{
	// ����ͼ��
	if (m_ComboBoxImageFile->currentIndex() < 0)
	{
		QMessageBox::information(NULL, "Anatomy Sketch", tr("Please select the input image."), QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	int IDOfImageFile = m_listIDImageFileIndex.at(m_ComboBoxImageFile->currentIndex());
	// ���ӵ�
	QList<int> crntChoosenSeeds;
	int numOfItems = m_ListWidgetSeeds->count();
	for (int ncrntItem = 0; ncrntItem < numOfItems; ncrntItem++)
	{
		if (m_ListWidgetSeeds->item(ncrntItem)->checkState() == Qt::Checked)
		{
			crntChoosenSeeds.append(m_listIDSeedsListIndex.at(ncrntItem));
		}
	}
	if (crntChoosenSeeds.size() < 2)
	{
		QMessageBox::information(NULL, "Anatomy Sketch", tr("Please input at least 2 seed points."), QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	// ���
	if (m_LineEditOutput->text().isEmpty())
	{
		QMessageBox::information(NULL, "Anatomy Sketch", tr("Please enter the output file name."), QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	// nNeighbor
	int nNeighbor;
	if (m_ComboBoxNeighbor->currentIndex() == 0)
	{
		nNeighbor = 6;
	}
	else
	{
		nNeighbor = 26;
	}
	// Marching cubs
	ASTransGraphCut::SetMarchingCubs(m_CheckboxMarchingCub->isChecked(), m_SmoothIterations->value());
	// ������������� :)
	ASTransGraphCut::GraphCutGenerate(IDOfImageFile, crntChoosenSeeds, m_LineEditOutput->text(), 
		m_DSpinBoxLambda->value(), m_DSpinBoxDelta->value(), nNeighbor, m_LineEditPostProcessing->text(),
		m_CheckboxQuery->checkState());
}

//ˢ���ļ�����ѡ��
void ASGraphCutWidget::slotRefreshDataComboBox(int c_AffectType)
{
	qDebug("slotRefreshDataComboBox of ASGraphCut Widget");
	isEnabelforslotComboBoxCurrentIndexChanged = false;
	if (ASArrayImageData::isTypeInheritedStatic(c_AffectType))
	{
		// ˢ��Image��Mask����ѡ��
		qDebug("UpdateComboBoxImage");
		this->UpdateComboBoxImage();
		qDebug("UpdateComboBoxImage pass");
	}
	if (ASSeedData::isTypeInheritedStatic(c_AffectType))
	{
		// ˢ�����ӵ��б�
		qDebug("UpdateSeedsList");
		this->UpdateSeedsList();
		qDebug("UpdateSeedsList pass");
	}
	isEnabelforslotComboBoxCurrentIndexChanged = true;
	qDebug("slotRefreshDataComboBox of ASGraphCut Passed");
}
// ����ѡ��仯
void ASGraphCutWidget::slotComboBoxChanged(int Index)
{
	if (isEnabelforslotComboBoxCurrentIndexChanged == false)
	{
		return;
	}
	QComboBox *Combo = qobject_cast<QComboBox*>(sender());
	if (Combo == m_ComboBoxImageFile)
	{
		if (Index == -1)
		{
			m_ncrntIDOfImageFile = -1;
		}
		else
		{
			m_ncrntIDOfImageFile = m_listIDImageFileIndex.at(Index);
		}
	}
}
// ����ģ��ʹ��״̬�л�
void ASGraphCutWidget::slotMaskEnabledChanged()
{
	isEnabelforslotComboBoxCurrentIndexChanged = false;
	isEnabelforslotComboBoxCurrentIndexChanged = true;
}
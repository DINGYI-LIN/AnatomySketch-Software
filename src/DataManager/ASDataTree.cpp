#include "ASDataTree.h"
#include "ASAbstractData.h"
#include "ASArrayImageData.h"
#include "ASPolyImageData.h"
#include "ASDICOMData.h"
#include "ASDICOMRTData.h"
#include "ASSeedData.h"
#include "ASDataStructureWalker.h"
#include "ASTransAddDeleteData.h"

ASAbstractData* ASDataTree::ms_RootDataNote = nullptr;
ASDataTree* ASDataTree::m_DataTree = nullptr;

ASDataTree::ASDataTree(QObject *parent)
	: QObject(parent)
{
	m_DataTree = this;
	ms_RootDataNote = new ASAbstractData();
	ms_RootDataNote->setFather(nullptr);
	ASAbstractData::setRootDataNode(ms_RootDataNote);
	m_DataStructureWalker = new ASDataStructureWalker(ms_RootDataNote);

	connect(ASTransAddDeleteData::GetSelfPointer(), SIGNAL(signalRemoveNode(ASAbstractData*)), this, SLOT(slotRemoveNode(ASAbstractData*)));
}

ASDataTree::~ASDataTree()
{

}

// ��̬��Ա����
// ��̬������ȡ���ڵ㣬���ڵõ��������������ݽṹ����ʾʱ��Ҫ�õ�
ASAbstractData* ASDataTree::getRootDataNote()
{
	return ms_RootDataNote;
}
// ���ݵ�ǰ������״���¼��������ݲ㼶
void ASDataTree::RefreshArrayDataLayer()
{
	m_DataTree->m_CrntLayer = 0;
	// ���������ȸ�������ʹ�õݹ鷽��
	m_DataTree->FollowUpTraversalToRefreshLayer(ms_RootDataNote);
}
// �½��ڵ�
void ASDataTree::NewDataNode(ASAbstractData* DataNode, ASAbstractData* Father)
{
	ASAbstractData* FatherNode = Father;
	if (FatherNode == nullptr)
	{
		FatherNode = ms_RootDataNote;
	}
	FatherNode->addChild(DataNode);
	DataNode->setFather(FatherNode);
}

// �ݹ麯�����ȸ����������������¼��������ݲ㼶
void ASDataTree::FollowUpTraversalToRefreshLayer(ASAbstractData* DataNode)
{
	if (DataNode->isTypeInherited(DataType_ArrayImageData))
	{
		((ASArrayImageData*)DataNode)->setLayer(m_CrntLayer);
		m_CrntLayer++;
	}
	// �õ����ӽڵ�
	QList<ASAbstractData*>* ChildrenNode = DataNode->getChild();
	for (int crntChild = ChildrenNode->size() - 1; crntChild >= 0; crntChild--)
	{
		FollowUpTraversalToRefreshLayer(ChildrenNode->at(crntChild));
	}
}

// ɾ���ڵ�
int ASDataTree::slotRemoveNode(ASAbstractData* DataNode)
{
	DataNode->getFather()->removeChild(DataNode);
	DataNode->DeleteNode();	//delete data;
	return 0;
}
#pragma once

//#include "common.h"
#include <QObject>
#include <QList>
#include "ASAbstractData.h"

class ASArrayImageData;
class ASPolyImageData;
class ASDataStructureWalker;

class ASDataTree : public QObject
{
	Q_OBJECT

public:
	ASDataTree(QObject *parent = 0);
	~ASDataTree();

	//// ��̬��Ա����

	// ��ȡ���ڵ㣬���ڵõ��������������ݽṹ����ʾʱ��Ҫ�õ�
	static ASAbstractData* getRootDataNote();
	// ���ݵ�ǰ������״���¼��������ݲ㼶
	static void RefreshArrayDataLayer();
	// �½��ڵ�
	static void NewDataNode(ASAbstractData* DataNode, ASAbstractData* Father);

private:

	// ����Ψһ����
	static ASDataTree* m_DataTree;
	// ��������򿪵����ݾ�������һ���������ݽṹ�У����ڵ��ÿһ����������һ��һ�������ݣ����Ϊ���̣�project�������ڵ㱾������ʾ�κ����ݡ�
	static ASAbstractData* ms_RootDataNote;
	// ��Ҫʵ��һ����Ա��������г�ʼ��
	ASDataStructureWalker* m_DataStructureWalker; 

	// �ݹ麯�����ȸ����������������¼��������ݲ㼶
	void FollowUpTraversalToRefreshLayer(ASAbstractData* DataNode);
	int m_CrntLayer = 0; // ����ˢ�������ݲ㼶
	

private slots:

	// ɾ���ڵ�
	int slotRemoveNode(ASAbstractData* DataNode);

};

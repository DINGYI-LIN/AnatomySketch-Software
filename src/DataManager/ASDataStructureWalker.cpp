#include "ASDataStructureWalker.h"
#include "ASAbstractData.h"

ASAbstractData* ASDataStructureWalker::ms_pRootNode = nullptr;
std::queue<ASAbstractData*>* ASDataStructureWalker::ms_pQueue = nullptr;

ASDataStructureWalker::ASDataStructureWalker(ASAbstractData* rootNode)
{
	ASDataStructureWalker::ms_pRootNode = rootNode;
	ms_pQueue = new std::queue<ASAbstractData*>;
}

ASDataStructureWalker::~ASDataStructureWalker()
{
}

ASAbstractData* ASDataStructureWalker::bigen_inherit(int type)
{
	// ��ն���
	while (ms_pQueue->size())
	{
		ms_pQueue->pop();
	}
	// ��ʼ���б��������ص�һ������Ҫ��ڵ��ָ�룬���û�з���Ҫ��Ľڵ㣬����nullprt
	ms_pRootNode->Traverse(ms_pQueue);
	if (ms_pQueue->size() == 0)
	{
		return nullptr;
	}
	else
	{
		ASAbstractData* crntNode;
		do
		{
			crntNode = ms_pQueue->front();
			crntNode->Traverse(ms_pQueue);
			ms_pQueue->pop();
			if (crntNode->isTypeInherited(type))
			{
				return crntNode;
			}
		} while (ms_pQueue->size());
	}
	return nullptr;
}
ASAbstractData* ASDataStructureWalker::bigen_single(int type)
{
	// ��ն���
	while (ms_pQueue->size())
	{
		ms_pQueue->pop();
	}
	// ��ʼ���б��������ص�һ������Ҫ��ڵ��ָ�룬���û�з���Ҫ��Ľڵ㣬����nullprt
	ms_pRootNode->Traverse(ms_pQueue);
	if (ms_pQueue->size() == 0)
	{
		return nullptr;
	}
	else
	{
		ASAbstractData* crntNode;
		do
		{
			crntNode = ms_pQueue->front();
			crntNode->Traverse(ms_pQueue);
			ms_pQueue->pop();
			if (crntNode->getDataType() == type)
			{
				return crntNode;
			}
		} while (ms_pQueue->size());
	}
	return nullptr;
}
ASAbstractData* ASDataStructureWalker::next_inherit(int type)
{
	ASAbstractData* crntNode;
	while (ms_pQueue->size())
	{
		crntNode = ms_pQueue->front();
		crntNode->Traverse(ms_pQueue);
		ms_pQueue->pop();
		if (crntNode->isTypeInherited(type))
		{
			return crntNode;
		}
	}
	return nullptr;
}
ASAbstractData* ASDataStructureWalker::next_single(int type)
{
	ASAbstractData* crntNode;
	while (ms_pQueue->size())
	{
		crntNode = ms_pQueue->front();
		crntNode->Traverse(ms_pQueue);
		ms_pQueue->pop();
		if (crntNode->getDataType() == type)
		{
			return crntNode;
		}
	}
	return nullptr;
}
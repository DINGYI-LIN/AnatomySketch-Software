#pragma once

//#include "common.h"
#include <queue>
#include "ASAbstractData.h"

// �������ݴ洢�ṹ�ı���
// ���� for (ASAbstractData* item = ASDataStructureWalker::bigen_single(DataType_ArrayImageData); item != nullptr; item = ASDataStructureWalker::next_single(DataType_ArrayImageData)){}
//      for (ASAbstractData* item = ASDataStructureWalker::bigen_inherit(DataType_ArrayImageData); item != nullptr; item = ASDataStructureWalker::next_inherit(DataType_ArrayImageData)){}

class ASDataStructureWalker
{
public:
	ASDataStructureWalker(ASAbstractData* rootNode);
	~ASDataStructureWalker();

	static ASAbstractData* bigen_inherit(int type);
	static ASAbstractData* bigen_single(int type);
	static ASAbstractData* next_inherit(int type);
	static ASAbstractData* next_single(int type);
private:

	//�����ȸ�������ʹ�õĶ���FIFO
	static std::queue<ASAbstractData*>* ms_pQueue;
	static ASAbstractData* ms_pRootNode;

};

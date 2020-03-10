#include "ASAbstractData.h"
#include <QMutexLocker>
//#include "common.h"

ASAbstractData* ASAbstractData::ms_RootDataNode = nullptr;
int ASAbstractData::ms_nNumberOfData = -1;		//���ڵ㽨��ʱ���ù��캯����ʹ���ּ�1
int ASAbstractData::ms_nNumberOfDataShown = 0;

ASAbstractData::ASAbstractData()
{
	m_pChildren = new QList<ASAbstractData*>;
	m_nDataNoteID = ASAbstractData::getNewDataNodeID();
	ms_nNumberOfData += 1;

	m_Datatype = DataType_AbstractData; // ���캯��ִ��˳��Ϊ��ִ�л���Ĺ��캯����ִ��������Ĺ��캯�������Ը����ͻᱻ���ǡ�

	m_Mutex = new QMutex();
}

ASAbstractData::~ASAbstractData()
{
	ms_nNumberOfData -= 1;
	int numOfChildren = m_pChildren->size();
	for (int ncrntChild = 0; ncrntChild < numOfChildren; ncrntChild++)
	{
		ASAbstractData* crntDataNode = m_pChildren->at(ncrntChild);
		this->removeChild(crntDataNode);
		delete crntDataNode;
	}
	m_pChildren->clear();
	delete m_pChildren;
}

// ���ô˺������ͷŽڵ�
void ASAbstractData::DeleteNode()
{
	QMutexLocker Locker(m_Mutex);
	delete this;
}
// ����ӽڵ��Ƿ�Ϊֻ��
bool ASAbstractData::isChildrenBeingProcess()
{
	int numOfChildren = m_pChildren->size();
	for (int ncrntChild = 0; ncrntChild < numOfChildren; ncrntChild++)
	{
		if (m_pChildren->at(ncrntChild)->isBeingProcess())
		{
			return true;
		}
	}
	return false;
}

// ���������ж�
// �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
bool ASAbstractData::isTypeInherited(const int c_Type)
{
	if (c_Type == DataType_AbstractData)
	{
		return true;
	}
	return false;
}
bool ASAbstractData::isTypeAbsolute(const int c_Type)
{
	QMutexLocker Locker(m_Mutex);
	if (c_Type == DataType_AbstractData)
	{
		return true;
	} 
	return false;
}
bool ASAbstractData::isTypeInheritedStatic(const int c_Type)
{
	if (c_Type == DataType_AbstractData)
	{
		return true;
	}
	return false;
}

// ���ݽṹ�Ĳ���
void ASAbstractData::addChild(ASAbstractData* child)
{
	QMutexLocker Locker(m_Mutex);
	//m_pChildren->append(child);
	m_pChildren->insert(0, child); // ���뵽��ǰ��
}
void ASAbstractData::addChild(ASAbstractData* child, int insertPos)
{
	QMutexLocker Locker(m_Mutex);
	m_pChildren->insert(insertPos, child);
}
// ɾ���ӽڵ�
void ASAbstractData::removeChild(ASAbstractData* child)
{
	QMutexLocker Locker(m_Mutex);
	m_pChildren->removeOne(child);
}
void ASAbstractData::removeChild(int removePos)
{
	QMutexLocker Locker(m_Mutex);
	m_pChildren->removeAt(removePos);
}
// �õ��ӽڵ㣬���ڵ�
QList<ASAbstractData*>* ASAbstractData::getChild()
{
	QMutexLocker Locker(m_Mutex);
	return m_pChildren;
}
// �õ���һ��ĳ���͵��ӽڵ�
ASAbstractData* ASAbstractData::getChild(const int c_Type)
{
	QMutexLocker Locker(m_Mutex);
	int numOfChildren = m_pChildren->size();
	for (int i = 0; i < numOfChildren; i++)
	{
		ASAbstractData* crntChild = m_pChildren->at(i);
		if (crntChild->isTypeInherited(c_Type))
		{
			return crntChild;
		}
	}
	return nullptr;
}
ASAbstractData* ASAbstractData::getFather()
{
	QMutexLocker Locker(m_Mutex);
	return m_pFather;
}
void ASAbstractData::setFather(ASAbstractData* father)
{
	QMutexLocker Locker(m_Mutex);
	m_pFather = father;
}
// �õ����ڵ㣬����һ�������ݽڵ�
ASAbstractData* ASAbstractData::getRoot()
{
	if (this->getFather()->getDataNodeID() < 0)
	{
		return this;
	}
	else
	{
		return this->getFather()->getRoot();
	}
}
// �Ƿ�Ϊ�սڵ�
bool ASAbstractData::isVoidNode()
{
	QMutexLocker Locker(m_Mutex);
	return this->m_isVoidNode;
}
void ASAbstractData::setVoidNode(const bool c_isVoidNode)
{
	QMutexLocker Locker(m_Mutex);
	this->m_isVoidNode = c_isVoidNode;
}

// ��������
int ASAbstractData::getDataType()
{
	QMutexLocker Locker(m_Mutex);
	return m_Datatype;
}
// �ڼ�������
int ASAbstractData::getOrderInBrother(ASAbstractData* child)
{
	QMutexLocker Locker(m_Mutex);
	return m_pChildren->indexOf(child);
}
// �����Ƿ����ڱ�����
void ASAbstractData::setBeingProcess(const bool isBeingProcess)
{
	QMutexLocker Locker(m_Mutex);
	m_isBeingProcess = isBeingProcess;
}
bool ASAbstractData::isBeingProcess()
{
	QMutexLocker Locker(m_Mutex);
	return m_isBeingProcess;
}
// �����Ƿ���ʾ
void ASAbstractData::setShown(const bool shown)
{
	QMutexLocker Locker(m_Mutex);
	if (m_isShown == shown)
	{
		return;
	}
	m_isShown = shown;
	if (m_isShown)
	{
		ms_nNumberOfDataShown += 1;
	}
	else
	{
		ms_nNumberOfDataShown -= 1;
	}
}
bool ASAbstractData::isShown()
{
	return m_isShown;
}
// �õ��ýڵ��ID
int ASAbstractData::getDataNodeID()
{
	QMutexLocker Locker(m_Mutex);
	return m_nDataNoteID;
}
// Name
void ASAbstractData::setName(QString name)
{
	QMutexLocker Locker(m_Mutex);
	m_Name = name;
}
QString ASAbstractData::getName()
{
	QMutexLocker Locker(m_Mutex);
	return m_Name;
}
void ASAbstractData::setFileName(QString filename)
{
	QMutexLocker Locker(m_Mutex);
	m_FileName = filename;
}
QString ASAbstractData::getFileName()
{
	QMutexLocker Locker(m_Mutex);
	return m_FileName;
}
// ���ݷ�Χ
double* ASAbstractData::getDataExtent()
{
	QMutexLocker Locker(m_Mutex);
	return m_adDataExtent;
}
int ASAbstractData::getNumberOfFrame()
{
	QMutexLocker Locker(m_Mutex);
	return m_NumberOfFrames;
}
// ���߳�
QMutex* ASAbstractData::GetMutex()
{
	return m_Mutex;
}
// ��̬��Ա����
// ��ID���ؽڵ�
ASAbstractData* ASAbstractData::getDataNodeFromID(int id)
{
	if (ms_RootDataNode == nullptr)
	{
		return nullptr;
	}
	return ms_RootDataNode->findID(id);
}
// �õ���ǰ�Ѿ��򿪵��ļ�����
int ASAbstractData::getNumberOfData()
{
	return ASAbstractData::ms_nNumberOfData;
}
// �õ���ǰ�Ѿ���ʾ���ļ�����
int ASAbstractData::getNumberOfDataShown()
{
	return ms_nNumberOfDataShown;
}

// ���Ҿ��и�ID�Ľڵ㣬�ú���Ϊ��������
ASAbstractData* ASAbstractData::findID(int nID)
{
	QMutexLocker Locker(m_Mutex);
	if (nID == m_nDataNoteID)
	{
		return this;
	}
	int numOfChildren = m_pChildren->size();
	for (int ncrntChild = 0; ncrntChild < numOfChildren; ncrntChild++)
	{
		ASAbstractData* p = m_pChildren->at(ncrntChild)->findID(nID);
		if (p != nullptr)
		{
			return p;
		}
	}
	return nullptr;
}
// �ú���ֻ���Ա�ASDataStructureWalker���ã��������ݵı�����ʵ�ֵĹ���ֻ����Ӹýڵ���ӽڵ㵽�����Ķ�����
void ASAbstractData::Traverse(std::queue<ASAbstractData*>* queue)
{
	QMutexLocker Locker(m_Mutex);
	for (int crntChild = 0; crntChild < m_pChildren->size(); crntChild++)
	{
		queue->push(m_pChildren->at(crntChild));
	}
}

//��̬��Ա�;�̬��Ա����
// �趨���ڵ�
void ASAbstractData::setRootDataNode(ASAbstractData* node)
{
	ASAbstractData::ms_RootDataNode = node;
}
// �õ��µ�ID��������ID�����ظ���
int ASAbstractData::getNewDataNodeID()
{
	int newID = 0;
	if (ms_RootDataNode == nullptr)
	{
		//��ʱ���ڵ㻹û��ʵ�������Ըýڵ���Ǹ��ڵ㣬��IDΪ-1
		return -1;
	}
	while (ms_RootDataNode->findID(newID) != nullptr)
	{
		newID++;
	}
	return newID;
}
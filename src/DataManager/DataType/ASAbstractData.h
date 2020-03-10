#pragma once

//#include "common.h"
#include <QString>
#include <QList>
#include <queue>
#include <QMutex>

//��������
#define DataType_AbstractData		0
#define DataType_ArrayImageData		1
#define DataType_ContourData		2
#define DataType_DICOMData			3
#define DataType_DICOMRTData		4
#define DataType_ImageData			5
#define DataType_MarkData			6
#define DataType_PolyImageData		7
#define DataType_SeedData			8
#define DataType_LandmarkData		9
#define DataType_Operation			10
#define DataType_ROI				11
#define DataType_Annotation			12

// �̳�ʱ��Ҫ�ڹ��캯�����趨 m_Datatype�� ����дwalkerCheck����

class ASAbstractData
{
public:
	ASAbstractData();
	~ASAbstractData();
	virtual void DeleteNode();	// ���ô˺������ͷŽڵ�
	bool isChildrenBeingProcess(); // ����ӽڵ��Ƿ�Ϊֻ��

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type); // �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
	virtual bool isTypeAbsolute(const int c_Type);
	static bool isTypeInheritedStatic(const int c_Type);
	// ���ݽṹ�Ĳ���
	// ����ӽڵ�
	void addChild(ASAbstractData* child);
	void addChild(ASAbstractData* child, int insertPos);
	// ɾ���ӽڵ�
	void removeChild(ASAbstractData* child);
	void removeChild(int removePos);
	// �õ��ӽڵ�
	QList<ASAbstractData*>* getChild();
	// �õ���һ��ĳ���͵��ӽڵ�
	ASAbstractData* getChild(const int c_Type);
	// �õ����ڵ㣬���¸��ڵ�
	ASAbstractData* getFather();
	void setFather(ASAbstractData* father);
	// �õ����ڵ㣬����һ�������ݽڵ�
	ASAbstractData* getRoot();
	// �Ƿ�Ϊ�սڵ�
	bool isVoidNode();
	void setVoidNode(const bool c_isVoidNode);
	// �Ƿ���ʾ
	virtual void setShown(const bool shown);					
	bool isShown();
	// ��������		
	int getDataType();
	// �ڼ�������
	int getOrderInBrother(ASAbstractData* child);
	// �Ƿ����ڱ�����
	void setBeingProcess(const bool isBeingProcess);	
	bool isBeingProcess();
	// �ýڵ��ID
	int getDataNodeID(); 
	// Name
	void setName(QString name);
	QString getName();
	void setFileName(QString filename);
	QString getFileName();
	// ���ݷ�Χ��ʱ�䷶Χ
	virtual double* getDataExtent(); // �õ����ݷ�Χ��double[6]
	int getNumberOfFrame(); // �õ������м�֡

	// ���߳�
	QMutex* GetMutex();

	// ��̬��Ա����
	// ��ID���ؽڵ�
	static ASAbstractData* getDataNodeFromID(int id);
	// �õ���ǰ�Ѿ��򿪵��ļ�����
	static int getNumberOfData();
	// �õ���ǰ�Ѿ���ʾ���ļ�����
	static int getNumberOfDataShown();

	// ---------------------- ���ⲿ�ӿں��� ----------------------
	// ���ݽṹ
	static void setRootDataNode(ASAbstractData* node); // �趨���ڵ�
	ASAbstractData* findID(int nID); // ���Ҿ��и�ID�Ľڵ㣬�ú���Ϊ��������������ʵ�ָ���ID���ҽڵ�Ĺ��ܹ��ܡ�
	void Traverse(std::queue<ASAbstractData*>* queue); // �ú���ֻ���Ա�ASDataStructureWalker���ã��������ݵı�����ʵ�ֵĹ���ֻ����Ӹýڵ���ӽڵ㵽�����Ķ�����

private:
	bool			m_isShown;				// �Ƿ���ʾ
	bool			m_isBeingProcess;		// �Ƿ����ڱ����㣬����״̬��Ϊֻ��	

	static int ms_nNumberOfData;			// ��ǰ�򿪵����ݵ�����
	static int ms_nNumberOfDataShown;		// ��ǰ��ʾ�����ݵ�����

protected:
	int				m_Datatype;				// ��������
	//�ýڵ�Ψһ�ı�ʾ��
	int m_nDataNoteID;
	//��������
	bool			m_isVoidNode;			// �Ƿ�Ϊ�սڵ㣬����������
	QString			m_Name;					// ������
	QString			m_FileName;				// ·�����������ļ���
	double			m_adDataExtent[6];		// ��Χ����������ϵ
	int				m_NumberOfFrames = 1;	// �������м�֡
	//���ݽṹ����
	ASAbstractData* m_pFather;				// ���ڵ�
	QList<ASAbstractData*>* m_pChildren;	// ��״�洢�ṹ�еĺ���

	QMutex* m_Mutex; // ���߳��߳���

	//��̬��Ա�;�̬��Ա����
	static ASAbstractData* ms_RootDataNode; // ���ڵ�
	static int getNewDataNodeID(); // �õ��µ�ID��������ID�����ظ���

};

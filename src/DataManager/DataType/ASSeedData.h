#pragma once

#include "ASMarkData.h"
#include "GlobelDeclaration.h"

// �̳�ʱ��Ҫ�ڹ��캯�����趨 m_Datatype�� ����дwalkerCheck����

typedef struct structLine {
	QList<structPoint*> pvectorPoint;
	int ViewLabel; //0:sagittal  1 : coronal   2 : axial DimensionsOfImage
	double dLayer;
	int nSerial;//���滭�ߵ��Ⱥ�˳�����ڳ�����
}structLine;
typedef struct structSeeds
{
	int seedId;
	QColor color;
	QString name;
	int label;
	bool isShown;
	QList<structLine*>* pListSeedsData;
}structSeeds;

class ASSeedData : public ASMarkData
{
public:
	ASSeedData();
	~ASSeedData();
	virtual void DeleteNode();	// ���ô˺������ͷŽڵ�

	// ���������ж�
	virtual bool isTypeInherited(const int c_Type); // �ж����ͣ��ɼ̳еģ��磺ASDICOMData->isTypeInherited(DataType_ArrayImageData)Ϊ��
	virtual bool isTypeAbsolute(const int c_Type);
	static bool isTypeInheritedStatic(const int c_Type);

	// �½����ӵ�
	int NewSeed(const QString c_name, const int c_lable, const QColor c_color);

	// ���ӵ���������
	static int GetNumOfSeedsData();
	// ��ǩֵ
	int getLabel(); // ����
	void setLabel(const int label); // ����
	// ���ӵ����ݵķ���
	int getNumberOfSeeds() {
		return m_listSeedsData->size();
	}
	void AppandLine(structLine* NewLine);
	// ������������QList�е�λ�ã������ߵĽṹ��
	structSeeds* getSeedsAt(int atN) {
		return m_listSeedsData->at(atN);
	}
	structSeeds* getSeedsFromID(const int c_SeedsID);
	// ����
	void AddOperaSequence(const int c_SeedsID);
	bool UndoALine();
	// ����
	virtual double* getDataExtent(); // �õ����ݷ�Χ��double[6]

	// �����ӵ�
	void StartPaintingSeeds(double* pPosition, const int ViewLabel, const int c_SeedID);
	void ContinuePaintingSeeds(double* pPosition, const int ViewLabel);
	void EndPaintingSeeds();

	// ɾ�����ӵ�
	void DeleteWholeSeeds(const int c_SeedID);

protected:

	int m_nLabel; // ��ǩֵ // ����

private:

	// �������ӵ�����
	QList<structSeeds*>* m_listSeedsData;
	QList<int>* m_listOperaSequence;
	structLine* m_pWorkingSeedsLine; // �������ߣ����ڻ�����
	int m_crntSerialOfSeeds = 0; // ������ţ����ڳ���

	static int ms_nNumOfSeedsData;				// ��ǰ�򿪵����ӵ����ݵ�����

	// �õ�һ���µĲ��ظ�ID
	int GetNewSeedsID();
};

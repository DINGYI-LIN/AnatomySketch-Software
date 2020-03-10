#pragma once

#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPointPicker.h>
#include <vtkSmartPointer.h>
#include <vtkProp.h>

class ASArrayImageData;

#define PickRadius		0.01       // ʰȡ������ʱʹ�õ�ʰȡ�뾶

class ASInteractorStyle2DGeneral : public vtkInteractorStyleTrackballCamera
{
public:
	static ASInteractorStyle2DGeneral *New();
	vtkTypeMacro(ASInteractorStyle2DGeneral, vtkInteractorStyleTrackballCamera);

	// Description:
	// Event bindings controlling the effects of pressing mouse buttons
	// or moving the mouse.
	virtual void OnMouseMove();
	virtual void OnLeftButtonDown();
	virtual void OnLeftButtonUp();
	virtual void OnMiddleButtonDown();
	virtual void OnMiddleButtonUp();
	virtual void OnRightButtonDown();
	virtual void OnRightButtonUp();
	virtual void OnMouseWheelForward();
	virtual void OnMouseWheelBackward();

	//������ͼ
	virtual void setViewLabel(int ViewLabel);

	// ����ƽ��
	void TouchPan(double* pos);
	// ��������
	void TouchZoom(double factor);
	// �����в�
	void TouchWheel(double dis);

protected:
	int	m_ViewLabel;
	vtkSmartPointer<vtkPointPicker> m_picker;	

	bool m_haveActorDisplaying = false;		//��ǰ�Ƿ���������ʾ��־λ
	bool m_isLeftButtonDown = false;		//������±�־λ
	bool m_isMiddleButtonDown = false;		//���ְ��±�־λ
	bool m_isRightButtonDown = false;		//�Ҽ����±�־λ

	ASInteractorStyle2DGeneral();
	~ASInteractorStyle2DGeneral();

	//��vtkPointPicker�õ��������z����0��������ΪvtkImageReslice��ͼ��ı任����Ҫ���ݱ任������л��㡣
	void getPickPosFinal(double* posfinal, double* PointPickerOutput);

	// ��ͣ���
	void HoverDetection(const int c_x, const int c_y);
	// ���д�λ����ı�־λ
	bool m_IsWinlev = false;
	// ��λ����
	void WinLevStart();
	void WinLevContinue();
	// ��Ӧ
	virtual void Move_Panning(const int c_x, const int c_y); // ����ƶ�ƽ��
	virtual void Move_Zooming(const int c_x, const int c_y); // ����ƶ�����

private:
	//��λ�������
	double m_LevelWindowInitial[2];
	double m_LevelWindowStartPosition[2];
	double m_LevelWindowCurrentPosition[2];
	// ��ǰ����������
	ASArrayImageData* m_crntTopData;

};

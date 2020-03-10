#pragma once

#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSmartPointer.h>
#include <vtkCellPicker.h>

#define PickRadius		0.01       // ʰȡ������ʱʹ�õ�ʰȡ�뾶

class ASInteractorStyle3DGeneral : public vtkInteractorStyleTrackballCamera
{
public:
	static ASInteractorStyle3DGeneral *New();
	vtkTypeMacro(ASInteractorStyle3DGeneral, vtkInteractorStyleTrackballCamera);

	// Description:
	// Event bindings controlling the effects of pressing mouse buttons
	// or moving the mouse.
	virtual void OnLeftButtonDown();

	// ����ƽ��
	void TouchPan(double* pos);
	// ��������
	void TouchZoom(double factor);

protected:

	vtkSmartPointer<vtkCellPicker> m_picker;

	ASInteractorStyle3DGeneral();
	~ASInteractorStyle3DGeneral();

};

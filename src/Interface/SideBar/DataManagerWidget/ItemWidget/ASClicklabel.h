#pragma once

#include <QLabel>
#include <QMouseEvent>

class ASClicklabel : public QLabel
{
	Q_OBJECT
public:
	explicit ASClicklabel(QWidget *parent = 0);
	~ASClicklabel();
signals:
	void clicked();//�Զ���clicked()�ź�,��mousePressEvent�¼�����ʱ����
protected:
	virtual void mousePressEvent(QMouseEvent* event);//��дmousePressEvent�¼�
};


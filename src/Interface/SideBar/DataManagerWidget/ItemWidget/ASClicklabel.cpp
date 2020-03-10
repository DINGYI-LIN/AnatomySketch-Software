#include "ASClicklabel.h"

ASClicklabel::ASClicklabel(QWidget* parent)
	: QLabel(parent)
{
}

ASClicklabel::~ASClicklabel()
{
}

void ASClicklabel::mousePressEvent(QMouseEvent *event)//��дmousePressEvent�¼�,����¼������ǲ��ǵ����������
{
	//��������˾ʹ���clicked�ź�
	if (event->button() == Qt::LeftButton) {
		//����clicked�ź�
		emit clicked();
	}
	//�����¼��������ദ��
	QLabel::mousePressEvent(event);
}
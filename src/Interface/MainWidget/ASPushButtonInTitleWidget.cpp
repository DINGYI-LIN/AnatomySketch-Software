#include "ASPushButtonInTitleWidget.h"
#include <QPainter>

ASPushButtonInTitleWidget::ASPushButtonInTitleWidget(QWidget *parent)
	: QPushButton(parent)
{
	status = NORMAL;
	mouse_press = false;

	//�����û�е���Ǹ�������ƶ������ڴ��ڱ߽�����
	setMouseTracking(true);
}

ASPushButtonInTitleWidget::~ASPushButtonInTitleWidget()
{

}

void ASPushButtonInTitleWidget::setPicName(QString pic_name)
{
	this->pic_name = pic_name;
	if (m_btn_height == 0 && m_btn_width == 0)
	{
		setFixedSize(QPixmap(pic_name).size());
	}
}

void ASPushButtonInTitleWidget::setButtomSize(const int width, const int height)
{
	setFixedSize(width, height);
	m_btn_width = width;
	m_btn_height = height;
}

void ASPushButtonInTitleWidget::enterEvent(QEvent *)
{
	status = ENTER;
	update();
}

void ASPushButtonInTitleWidget::mousePressEvent(QMouseEvent *event)
{
	//�����������
	if (event->button() == Qt::LeftButton)
	{
		mouse_press = true;
		status = PRESS;
		update();
	}
}

void ASPushButtonInTitleWidget::mouseReleaseEvent(QMouseEvent *event)
{
	//�����������
	if (mouse_press  && this->rect().contains(event->pos()))
	{
		mouse_press = false;
		status = ENTER;
		update();
		emit clicked();
	}
}

void ASPushButtonInTitleWidget::leaveEvent(QEvent *)
{
	status = NORMAL;
	update();
}

void ASPushButtonInTitleWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	QPixmap pixmap;
	switch (status)
	{
	case NORMAL:
	{
		pixmap.load(pic_name);
		break;
	}
	case ENTER:
	{
		pixmap.load(pic_name + QString("_hover"));
		break;
	}
	case PRESS:
	{
		pixmap.load(pic_name + QString("_pressed"));
		break;
	}
	case NOSTATUS:
	{
		pixmap.load(pic_name);
		break;
	}
	default:
		pixmap.load(pic_name);
	}

	painter.drawPixmap(rect(), pixmap);
}


/*
��� ��С�� �رյȰ�ť
*/
#pragma once

#include <QPushButton>
#include <QMouseEvent>

class ASPushButtonInTitleWidget : public QPushButton
{
	Q_OBJECT

public:
	explicit ASPushButtonInTitleWidget(QWidget *parent = 0);
	~ASPushButtonInTitleWidget();

	//���ð�ť�ı���ͼƬ
	void setPicName(QString pic_name);

	//���ð�ť�ߴ�
	void setButtomSize(const int width, const int height);

protected:

	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *);

private:

	//ö�ٰ�ť�ļ���״̬
	enum ButtonStatus { NORMAL, ENTER, PRESS, NOSTATUS };
	ButtonStatus status;
	QString pic_name;

	int m_btn_width = 0; //��ť��ȣ�0Ϊδָ�����ߴ�����ΪͼƬ�ߴ�
	int m_btn_height = 0; //��ť�߶ȣ�0Ϊδָ�����ߴ�����ΪͼƬ�ߴ�
	bool mouse_press; //��ť����Ƿ���
};

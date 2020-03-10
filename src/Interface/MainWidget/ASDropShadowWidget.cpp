#include "ASDropShadowWidget.h"
#include "ASTransTheme.h"
#include <QPainter>
#include <qmath.h>
#include <QSettings>

ASDropShadowWidget::ASDropShadowWidget(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	//setAttribute(Qt::WA_TranslucentBackground,true);


	//-----------------�߽��϶�--------------------
	m_isLeftPressDown = false;
	m_currentDir = NONE;
	setMouseTracking(true);
	m_BorderDragEnabled = true;

	connect(ASTransTheme::GetSelfPointer(), SIGNAL(signalBackgroundChange(bool)), this, SLOT(slotBackgroundChange(bool)));
}

ASDropShadowWidget::~ASDropShadowWidget()
{

}

void ASDropShadowWidget::setBorderDragEnabled(bool enabel)
{
	m_BorderDragEnabled = enabel;
}

void ASDropShadowWidget::paintEvent(QPaintEvent *)
{
	// ���ñ���ͼƬ
	bool default_theme = ASTransTheme::GetTheme();
	slotBackgroundChange(default_theme);
	if (this->isMaximized())	//	ȫ��ģʽ
	{
		this->setBorderDragEnabled(false);		
	}
	else	// ��ȫ��ģʽ
	{
		this->setBorderDragEnabled(true);
		
	}
}

void ASDropShadowWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		m_isLeftPressDown = false;
		if (m_currentDir != NONE) {
			this->releaseMouse();
			this->setCursor(QCursor(Qt::ArrowCursor));
		}
	}
}

void ASDropShadowWidget::mousePressEvent(QMouseEvent *event)
{
	switch (event->button()) {
	case Qt::LeftButton:
		m_isLeftPressDown = true;
		if (m_currentDir != NONE) {
			this->mouseGrabber();
		}
		else {
			m_dragPosition = event->globalPos() - this->frameGeometry().topLeft();
		}
		break;
	case Qt::RightButton:
		break;
	default:
		QDialog::mousePressEvent(event);
	}

}

void ASDropShadowWidget::mouseMoveEvent(QMouseEvent *event)
{
	QPoint gloPoint = event->globalPos();
	QRect rect = this->rect();
	QPoint tl = mapToGlobal(rect.topLeft());
	QPoint rb = mapToGlobal(rect.bottomRight());

	if (m_BorderDragEnabled)
	{
		if (!m_isLeftPressDown) 
		{
			this->getRregion(gloPoint);
		}
		else 
		{
			if (m_currentDir != NONE) 
			{
				QRect rMove(tl, rb);

				switch (m_currentDir) 
				{
				case LEFT:
					if (rb.x() - gloPoint.x() <= this->minimumWidth())
						rMove.setX(tl.x());
					else
						rMove.setX(gloPoint.x());
					break;
				case RIGHT:
					rMove.setWidth(gloPoint.x() - tl.x());
					break;
				case UP:
					if (rb.y() - gloPoint.y() <= this->minimumHeight())
						rMove.setY(tl.y());
					else
						rMove.setY(gloPoint.y());
					break;
				case DOWN:
					rMove.setHeight(gloPoint.y() - tl.y());
					break;
				case LEFTTOP:
					if (rb.x() - gloPoint.x() <= this->minimumWidth())
						rMove.setX(tl.x());
					else
						rMove.setX(gloPoint.x());
					if (rb.y() - gloPoint.y() <= this->minimumHeight())
						rMove.setY(tl.y());
					else
						rMove.setY(gloPoint.y());
					break;
				case RIGHTTOP:
					rMove.setWidth(gloPoint.x() - tl.x());
					rMove.setY(gloPoint.y());
					break;
				case LEFTBOTTOM:
					rMove.setX(gloPoint.x());
					rMove.setHeight(gloPoint.y() - tl.y());
					break;
				case RIGHTBOTTOM:
					rMove.setWidth(gloPoint.x() - tl.x());
					rMove.setHeight(gloPoint.y() - tl.y());
					break;
				default:
					break;
				}
				this->setGeometry(rMove);
			}
			else {
				//move(event->globalPos() - m_dragPosition);
				event->accept();
			}
		}
	}

	QDialog::mouseMoveEvent(event);
}


//�������Ļ������������ڵ����������϶��߽繦��
void ASDropShadowWidget::getRregion(const QPoint &cursorGlobalPoint)
{
	// ��ȡ��������Ļ�ϵ�λ������tlΪtopleft�㣬rbΪrightbottom��
	QRect rect = this->rect();
	QPoint tl = mapToGlobal(rect.topLeft());
	QPoint rb = mapToGlobal(rect.bottomRight());

	int x = cursorGlobalPoint.x();
	int y = cursorGlobalPoint.y();

	if (tl.x() + PADDING >= x && tl.x() < x && tl.y() + PADDING >= y && tl.y() < y) {
		// ���Ͻ�
		m_currentDir = LEFTTOP;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));  // ���������״
	}
	else if (x >= rb.x() - PADDING && x < rb.x() && y >= rb.y() - PADDING && y < rb.y()) {
		// ���½�
		m_currentDir = RIGHTBOTTOM;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));
	}
	else if (x <= tl.x() + PADDING && x > tl.x() && y >= rb.y() - PADDING && y < rb.y()) {
		//���½�
		m_currentDir = LEFTBOTTOM;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (x < rb.x() && x >= rb.x() - PADDING && y > tl.y() && y <= tl.y() + PADDING) {
		// ���Ͻ�
		m_currentDir = RIGHTTOP;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (x <= tl.x() + PADDING && x > tl.x()) {
		// ���
		m_currentDir = LEFT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if (x <= rb.x() && x > rb.x() - PADDING) {
		// �ұ�
		m_currentDir = RIGHT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if (y >= tl.y() && y < tl.y() + PADDING) {
		// �ϱ�
		m_currentDir = UP;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else if (y <= rb.y() && y > rb.y() - PADDING) {
		// �±�
		m_currentDir = DOWN;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else {
		// Ĭ��
		m_currentDir = NONE;
		this->setCursor(QCursor(Qt::ArrowCursor));
	}
}


void ASDropShadowWidget::slotBackgroundChange(bool checked)
{
	//���ñ���ͼƬ
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::white);
	QPixmap pixmap;
	if (checked)
		pixmap.load(QString(":/Background/background_dark"));
	else
		pixmap.load(QString(":/Background/background_mainwindow"));
	painter.drawPixmap(QRect(0, 0, this->width(), this->height()), pixmap);
}

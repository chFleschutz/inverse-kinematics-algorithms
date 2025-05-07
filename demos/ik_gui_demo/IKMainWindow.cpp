#include "IKMainWindow.h"

#include <CCD.h>
#include <FABRIK.h>

#include <QGraphicsScene>
#include <QGraphicsView>


TargetItem::TargetItem(float x, float y, float radius, QGraphicsItem* parent)
	: QGraphicsEllipseItem(x - radius, y - radius, radius * 2, radius * 2, parent)
{
	setBrush(Qt::red);
	setPen(Qt::NoPen);
	setFlags(ItemIsMovable | ItemSendsScenePositionChanges);
}

auto TargetItem::itemChange(GraphicsItemChange change, const QVariant& value) -> QVariant
{
	if (change == ItemPositionHasChanged)
	{
		auto newPos = value.toPointF();

		qDebug() << "Target position changed to:" << newPos;
	}

	return QGraphicsEllipseItem::itemChange(change, value);
}




SkeletonItem::SkeletonItem(QGraphicsItem* parent)
	: QGraphicsItem(parent)
{
	m_skeleton.addBone(100.0f, radians(-30.0f));
	m_skeleton.addBone(150.0f, radians(30.0f));
	m_skeleton.addBone(100.0f, radians(30.0f));
	m_skeleton.addBone(50.0f, radians(30.0f));
}

auto SkeletonItem::boundingRect() const -> QRectF
{
	std::vector<Vector2> jointPositions = m_skeleton.computeJointPositions();

	QRectF boundingRect(0, 0, 0, 0);
	for (const auto& pos : jointPositions)
	{
		if (pos.x() < boundingRect.left())
			boundingRect.setLeft(pos.x());
		if (pos.x() > boundingRect.right())
			boundingRect.setRight(pos.x());
		if (pos.y() < boundingRect.top())
			boundingRect.setTop(pos.y());
		if (pos.y() > boundingRect.bottom())
			boundingRect.setBottom(pos.y());
	}

	boundingRect.adjust(-10, -10, 10, 10); // Add some padding
	return boundingRect;
}

void SkeletonItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(QPen(Qt::blue, 3));

	// Draw the bones
	std::vector<Vector2> jointPositions = m_skeleton.computeJointPositions();
	for (size_t i = 0; i < jointPositions.size() - 1; ++i)
	{
		QPoint start(jointPositions[i].x(), jointPositions[i].y());
		QPoint end(jointPositions[i + 1].x(), jointPositions[i + 1].y());
		painter->drawLine(start, end);
		painter->drawEllipse(start, 5, 5);
	}

	// Draw the end effector
	QPointF endPos(jointPositions.back().x(), jointPositions.back().y());
	painter->drawEllipse(endPos, 5, 5); 
}



IKMainWindow::IKMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.CCD_radioButton->setChecked(true);

	QGraphicsScene* scene = new QGraphicsScene(this);
	scene->setSceneRect(-200, -200, 400, 400);
	ui.graphicsView->setScene(scene);

	m_targetItem = new TargetItem(100, 0, 10);
	scene->addItem(m_targetItem);

	m_skeletonItem = new SkeletonItem();
	scene->addItem(m_skeletonItem);
}

IKMainWindow::~IKMainWindow()
{
}

void IKMainWindow::onCCDSelected()
{
	m_ikSolver = std::make_unique<CCD>();
}

void IKMainWindow::onFABRIKSelected()
{
	m_ikSolver = std::make_unique<FABRIK>();
}

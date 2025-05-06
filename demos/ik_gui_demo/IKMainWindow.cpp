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
	return QRectF(-200, -200, 400, 400);
}

void SkeletonItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(QPen(Qt::blue, 3));

	// Draw the skeleton
	Vector2 basePos;
	float currentAngle = 0.0f;
	for (const auto& bone : m_skeleton.bones())
	{
		currentAngle += bone.angle;
		Vector2 endPos = basePos + Vector2::makeVector(bone.length, currentAngle);
		painter->drawLine(QPointF(basePos.x(), basePos.y()), QPointF(endPos.x(), endPos.y()));
		painter->drawEllipse(QPointF(basePos.x(), basePos.y()), 5, 5);
		basePos = endPos;
	}
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

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
	m_skeleton.addBone(100.0f, radians(30.0f));
}

auto SkeletonItem::boundingRect() const -> QRectF
{
	return QRectF(-200, -200, 400, 400);
}

void SkeletonItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(QPen(Qt::blue, 3));

	Bone* bone = m_skeleton.rootBone();
	while (bone)
	{
		Vector2 basePos = m_skeleton.boneBasePosition(bone);
		Vector2 endPos = basePos + Vector2::makeVector(bone->length, bone->angle);

		painter->drawLine(QPointF(basePos.x(), basePos.y()), QPointF(endPos.x(), endPos.y()));
		painter->drawEllipse(QPointF(endPos.x(), endPos.y()), 5, 5);

		bone = bone->child;
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

#include "IKMainWindow.h"

#include <CCD.h>
#include <FABRIK.h>

#include <QGraphicsScene>
#include <QGraphicsView>


TargetItem::TargetItem(float radius, QGraphicsItem* parent)
	: QGraphicsEllipseItem(-radius, -radius, radius * 2, radius * 2, parent)
{
	setBrush(Qt::NoBrush);
	setPen(QPen(Qt::red, 2));
	setFlags(ItemIsMovable | ItemSendsScenePositionChanges);
}

auto TargetItem::itemChange(GraphicsItemChange change, const QVariant& value) -> QVariant
{
	if (change == ItemPositionChange)
	{
		emit targetMoved(value.toPointF());
	}

	return QGraphicsEllipseItem::itemChange(change, value);
}


IKMainWindow::IKMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.CCD_radioButton->setChecked(true);
	onCCDSelected();

	m_scene = new QGraphicsScene(this);
	m_scene->setSceneRect(-200, -200, 400, 400);
	ui.graphicsView->setScene(m_scene);
	ui.graphicsView->setRenderHint(QPainter::Antialiasing);

	m_targetItem = new TargetItem(10);
	m_targetItem->setPos(100, -100);
	m_targetItem->setZValue(1);
	m_scene->addItem(m_targetItem);

	connect(m_targetItem, &TargetItem::targetMoved, this, &IKMainWindow::onTargetMoved);

	m_skeleton.addBone(100.0f, radians(-30.0f));
	m_skeleton.addBone(100.0f, radians(30.0f));

	updateSkeleton();
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

void IKMainWindow::onIterationsChanged(int iterations)
{
	m_iterations = iterations;
}

void IKMainWindow::onEpsilonChanged(double epsilon)
{
	m_epsilon = static_cast<float>(epsilon);
}

void IKMainWindow::onTargetMoved(const QPointF& newPos)
{
	if (!m_ikSolver)
		return;

	Vector2 targetPos(newPos.x(), newPos.y());
	bool result = m_ikSolver->solve(m_skeleton, targetPos, m_iterations, m_epsilon);

	updateSkeleton();
}

void IKMainWindow::updateSkeleton()
{
	// Create bones if missing
	while (m_boneItems.size() < m_skeleton.boneCount())
	{
		auto* boneItem = new QGraphicsLineItem();
		boneItem->setPen(QPen(Qt::blue, 3));
		boneItem->setZValue(-1);
		m_boneItems.push_back(boneItem);
		m_scene->addItem(boneItem);
	}

	// Create joints if missing
	while (m_jointItems.size() < m_skeleton.boneCount() + 1)
	{
		auto* jointItem = new QGraphicsEllipseItem();
		jointItem->setBrush(Qt::white);
		jointItem->setPen(QPen(Qt::blue, 2));
		m_jointItems.push_back(jointItem);
		m_scene->addItem(jointItem);
	}

	std::vector<Vector2> jointPositions = m_skeleton.computeJointPositions();
	for (size_t i = 0; i < jointPositions.size() - 1; ++i)
	{
		QPoint start(jointPositions[i].x(), jointPositions[i].y());
		QPoint end(jointPositions[i + 1].x(), jointPositions[i + 1].y());

		m_boneItems[i]->setLine(start.x(), start.y(), end.x(), end.y());
		m_jointItems[i]->setRect(start.x() - 5, start.y() - 5, 10, 10);
	}

	m_jointItems.back()->setRect(jointPositions.back().x() - 5, jointPositions.back().y() - 5, 10, 10);
}

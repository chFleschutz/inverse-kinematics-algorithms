#include "IKMainWindow.h"

#include <CCD.h>
#include <FABRIK.h>

#include <QGraphicsScene>
#include <QGraphicsView>


TargetItem::TargetItem(float radius, QGraphicsItem* parent)
	: QGraphicsEllipseItem(-radius, -radius, radius * 2, radius * 2, parent)
{
	setBrush(Qt::red);
	setPen(Qt::NoPen);
	setFlags(ItemIsMovable | ItemSendsScenePositionChanges);
}

auto TargetItem::itemChange(GraphicsItemChange change, const QVariant& value) -> QVariant
{
	if (change == ItemPositionChange)
	{
		emit targetMoved();
	}

	return QGraphicsEllipseItem::itemChange(change, value);
}


IKMainWindow::IKMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_scene = new QGraphicsScene(this);
	m_scene->setSceneRect(-200, -200, 400, 400);
	ui.graphicsView->setScene(m_scene);
	ui.graphicsView->setRenderHint(QPainter::Antialiasing);

	m_backgroundColor = ui.graphicsView->palette().color(QPalette::Window);
	m_foregroundColor = ui.graphicsView->palette().color(QPalette::WindowText);

	m_targetItem = new TargetItem(9);
	m_targetItem->setPos(300, -10);
	m_targetItem->setZValue(1);
	m_scene->addItem(m_targetItem);

	connect(m_targetItem, &TargetItem::targetMoved, this, &IKMainWindow::onUpdateIK);

	m_skeleton.addBone(150.0f, glm::radians(-30.0f));
	m_skeleton.addBone(100.0f, glm::radians(30.0f));
	m_skeleton.addBone(100.0f, glm::radians(30.0f));
	updateSkeleton();

	ui.CCD_radioButton->setChecked(true);
	onCCDSelected();
}

IKMainWindow::~IKMainWindow()
{
}

void IKMainWindow::onCCDSelected()
{
	m_ikSolver = std::make_unique<CCD>();
	onUpdateIK();
}

void IKMainWindow::onFABRIKSelected()
{
	m_ikSolver = std::make_unique<FABRIK>();
	onUpdateIK();
}

void IKMainWindow::onIterationsChanged(int iterations)
{
	m_iterations = iterations;
}

void IKMainWindow::onEpsilonChanged(double epsilon)
{
	m_epsilon = static_cast<float>(epsilon);
}

void IKMainWindow::onUpdateIK()
{
	if (!m_ikSolver)
		return;

	glm::vec2 targetPos{ m_targetItem->pos().x(), m_targetItem->pos().y() };
	m_ikSolver->solve(m_skeleton, targetPos, m_iterations, m_epsilon);

	updateSkeleton();
}

void IKMainWindow::updateSkeleton()
{
	// Create bones if missing
	while (m_boneItems.size() < m_skeleton.boneCount())
	{
		auto* boneItem = new QGraphicsLineItem();
		boneItem->setPen(QPen(m_foregroundColor, 3));
		boneItem->setZValue(-1);
		m_boneItems.push_back(boneItem);
		m_scene->addItem(boneItem);
	}

	// Create joints if missing
	while (m_jointItems.size() < m_skeleton.boneCount() + 1)
	{
		auto* jointItem = new QGraphicsEllipseItem();
		jointItem->setBrush(QBrush(m_backgroundColor));
		jointItem->setPen(QPen(m_foregroundColor, 3));
		m_jointItems.push_back(jointItem);
		m_scene->addItem(jointItem);
	}

	std::vector<glm::vec2> jointPositions = m_skeleton.computeJointPositions();
	for (size_t i = 0; i < jointPositions.size() - 1; ++i)
	{
		QPoint start(jointPositions[i].x, jointPositions[i].y);
		QPoint end(jointPositions[i + 1].x, jointPositions[i + 1].y);

		m_boneItems[i]->setLine(start.x(), start.y(), end.x(), end.y());
		m_jointItems[i]->setRect(start.x() - 10, start.y() - 10, 20, 20);
	}

	m_jointItems.back()->setRect(jointPositions.back().x - 10, jointPositions.back().y - 10, 20, 20);
}

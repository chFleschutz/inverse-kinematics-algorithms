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


IKMainWindow::IKMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.CCD_radioButton->setChecked(true);

	QGraphicsScene* scene = new QGraphicsScene(this);
	scene->setSceneRect(-200, -200, 400, 400);
	ui.graphicsView->setScene(scene);

	scene->addLine(-100, -100, 100, 100, QPen(Qt::blue, 3));
	scene->addLine(0, 0, 100, 0, QPen(Qt::red, 3));

	m_targetItem = new TargetItem(100, 0, 10);
	scene->addItem(m_targetItem);

	m_skeleton.addBone(100.0f, radians(30.0f));
	m_skeleton.addBone(100.0f, radians(30.0f));
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

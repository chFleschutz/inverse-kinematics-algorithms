#pragma once

#include "ui_IKMainWindow.h"

#include <IKSolver.h>
#include <Skeleton.h>

#include <QGraphicsEllipseItem>
#include <QMainWindow>

#include <memory>


class TargetItem : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT

public:
	TargetItem(float radius, QGraphicsItem* parent = nullptr);

signals:
	void targetMoved(const QPointF& newPos);

protected:
	auto itemChange(GraphicsItemChange change, const QVariant& value) -> QVariant override;
};


class IKMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	IKMainWindow(QWidget* parent = nullptr);
	~IKMainWindow();

public slots:
	void onCCDSelected();
	void onFABRIKSelected();
	void onIterationsChanged(int iterations);
	void onEpsilonChanged(double epsilon);
	void onTargetMoved(const QPointF& newPos);

private:
	void updateSkeleton();
	
	Ui::IKMainWindowClass ui;

	std::unique_ptr<IKSolver> m_ikSolver;
	Skeleton m_skeleton;
	int m_iterations = 100;
	float m_epsilon = 0.1f;

	QGraphicsScene* m_scene = nullptr;
	std::vector<QGraphicsLineItem*> m_boneItems;
	std::vector<QGraphicsEllipseItem*> m_jointItems;
	TargetItem* m_targetItem = nullptr;
};

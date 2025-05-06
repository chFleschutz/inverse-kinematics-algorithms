#pragma once

#include <QMainWindow>
#include "ui_IKMainWindow.h"

#include <IKSolver.h>
#include <Skeleton.h>

#include <QGraphicsEllipseItem>

#include <memory>


class TargetItem : public QGraphicsEllipseItem
{
public:
	TargetItem(float x, float y, float radius, QGraphicsItem* parent = nullptr);

protected:
	auto itemChange(GraphicsItemChange change, const QVariant& value) -> QVariant override;
};

class SkeletonItem : public QGraphicsItem
{
public:
	SkeletonItem(QGraphicsItem* parent = nullptr);

	auto boundingRect() const -> QRectF override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
	Skeleton m_skeleton;
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

private:
	Ui::IKMainWindowClass ui;

	std::unique_ptr<IKSolver> m_ikSolver;
	SkeletonItem* m_skeletonItem = nullptr;
	TargetItem* m_targetItem = nullptr;
};

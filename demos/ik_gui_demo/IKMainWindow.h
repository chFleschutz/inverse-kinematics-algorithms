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


class IKMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	IKMainWindow(QWidget *parent = nullptr);
	~IKMainWindow();

public slots:
	void onCCDSelected();
	void onFABRIKSelected();

private:
	Ui::IKMainWindowClass ui;

	std::unique_ptr<IKSolver> m_ikSolver;
	Skeleton m_skeleton;
	TargetItem* m_targetItem = nullptr;
};

#pragma once

#include <QMainWindow>
#include "ui_IKMainWindow.h"

class IKMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	IKMainWindow(QWidget *parent = nullptr);
	~IKMainWindow();

private:
	Ui::IKMainWindowClass ui;
};

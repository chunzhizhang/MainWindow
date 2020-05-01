#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

private slots:
	void on_actionAlgParamConfig_triggered();

private:
	Ui::MainWindowClass ui;
	QWidget* m_pAlgParamWidget;
};

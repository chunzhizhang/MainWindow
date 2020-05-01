#include "MainWindow.h"
#include "AlgParamConfigTools_Def.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, m_pAlgParamWidget(nullptr)
{
	ui.setupUi(this);

	ui.actionAlgParamConfig;
}

MainWindow::~MainWindow()
{
	if (m_pAlgParamWidget)
	{
		delete m_pAlgParamWidget;
		m_pAlgParamWidget = nullptr;
	}
}

void MainWindow::on_actionAlgParamConfig_triggered()
{
	if (!m_pAlgParamWidget)
	{
		m_pAlgParamWidget = tools::CreateAlgParamConfigToolsWidget();
	}

	if (m_pAlgParamWidget)
	{
		m_pAlgParamWidget->show();
	}
}

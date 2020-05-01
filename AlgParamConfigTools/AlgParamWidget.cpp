#include "AlgParamWidget.h"

#include <QScrollArea>
#include <QVBoxLayout>

AlgParamWidget::AlgParamWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QVBoxLayout* vLayout = new QVBoxLayout(this);
	QScrollArea *pScrollArea = new QScrollArea(this);

	vLayout->addWidget(pScrollArea);
	this->setLayout(vLayout);

	m_pWidget = new Widget(pScrollArea);
	pScrollArea->setWidget(m_pWidget);
	m_pWidget->setGeometry(0, 0, 360, 460);
}

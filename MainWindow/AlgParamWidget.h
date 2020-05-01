#pragma once

#include <QtWidgets/QWidget>
#include "ui_AlgParamWidget.h"
#include "widget.h"

class AlgParamWidget : public QWidget
{
	Q_OBJECT

public:
	AlgParamWidget(QWidget *parent = Q_NULLPTR);

private:
	Ui::AlgParamWidgetClass ui;
	Widget* m_pWidget;
};

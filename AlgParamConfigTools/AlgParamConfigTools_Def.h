#pragma once
#include <QWidget>
#ifdef ALGPARAMCONFIGTOOLS_EXPORT
#define ALGPARAMCONFIGTOOLS_API _declspec(dllexport)
#else
#define ALGPARAMCONFIGTOOLS_API  _declspec(dllimport)
#endif

namespace tools
{
	extern "C" ALGPARAMCONFIGTOOLS_API QWidget* CreateAlgParamConfigToolsWidget(QWidget* parent = Q_NULLPTR);
}
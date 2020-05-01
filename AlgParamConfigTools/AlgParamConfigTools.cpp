#include "AlgParamConfigTools_Def.h"
#include "AlgParamWidget.h"

namespace tools
{
	QWidget* CreateAlgParamConfigToolsWidget(QWidget* parent)
	{
		return new AlgParamWidget(parent);
	}
}
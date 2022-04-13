
#include "ST_UnitWidget.h"
#include "ST_Unit.h"

void UST_UnitWidget::BindUnit(AST_Unit* Unit)
{
	Owner = Unit;
}

float UST_UnitWidget::GetHPRatio() const
{
	return Owner->GetCurrentStatus().HP / Owner->GetBaseStatus().HP;
}

#include "ST_UnitWidget.h"
#include "ST_Unit.h"

UST_UnitWidget::UST_UnitWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer), Owner(nullptr) {}

void UST_UnitWidget::BindUnit(AST_Unit* Unit)
{
	Owner = Unit;
}

float UST_UnitWidget::GetHPRatio() const
{
	return Owner ? Owner->GetCurrentStatus().HP / Owner->GetBaseStatus().HP : 0.0f;
}

float UST_UnitWidget::GetMPRatio() const
{
	return Owner ? Owner->GetCurrentStatus().MP / Owner->GetBaseStatus().MP : 0.0f;
}
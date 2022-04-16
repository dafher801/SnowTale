
#include "ST_PlayerWidget.h"
#include "Components/Image.h"

UST_PlayerWidget::UST_PlayerWidget(const FObjectInitializer& ObjectInitializer)
	: UST_UnitWidget(ObjectInitializer)
{
	
}

void UST_PlayerWidget::PushHealItemImage()
{
	HealItemImageArray.Push(NewObject<UImage>());
}

void UST_PlayerWidget::PopHealItemImage()
{
	HealItemImageArray.Pop();
}
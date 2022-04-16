
#include "ST_HealItem.h"
#include "ST_SnowWhite.h"
#include "ST_StatusData.h"

AST_HealItem::AST_HealItem()
{
	ItemType = EST_ItemType::HEAL;
}

void AST_HealItem::Interact(class AActor* OtherActor)
{
	Super::Interact(OtherActor);

	if (OtherActor->ActorHasTag("Player"))
	{
		Owner = Cast<AST_SnowWhite>(OtherActor);
		Owner->AcquireHealItem(this);
		SetActivated(false);
	}
}

void AST_HealItem::Heal(float& BaseHP, float& CurrentHP)
{
	CurrentHP += HealAmount;

	if (BaseHP < CurrentHP)
		CurrentHP = BaseHP;
}

float AST_HealItem::GetHealAmount() const
{
	return HealAmount;
}

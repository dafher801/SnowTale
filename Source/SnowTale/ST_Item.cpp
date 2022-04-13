
#include "ST_Item.h"
#include "ST_SnowWhite.h"

AST_Item::AST_Item()
	: ItemType(EST_ItemType::BEGIN)
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AST_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AST_Item::Interact(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		Owner = Cast<AST_SnowWhite>(OtherActor);
		Owner->AcquireItem(this);
		SetActivated(false);
	}
}

void AST_Item::UseItem()
{
	
}

EST_ItemType AST_Item::GetItemType() const
{
	return ItemType;
}

void AST_Item::BeginPlay()
{
	Super::BeginPlay();
}

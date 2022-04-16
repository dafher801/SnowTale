
#include "ST_Item.h"

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

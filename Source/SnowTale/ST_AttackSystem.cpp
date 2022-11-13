
#include "ST_AttackSystem.h"

AST_AttackSystem::AST_AttackSystem()
{
	PrimaryActorTick.bCanEverTick = true;

	SetActivated(true);
}

void AST_AttackSystem::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);
}

void AST_AttackSystem::Attack()
{

}

void AST_AttackSystem::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
}

bool AST_AttackSystem::IsActivated() const
{
	return bActivated;
}

void AST_AttackSystem::SetActivated(bool Activated)
{
	bActivated = Activated;

	SetActorHiddenInGame(!bActivated);
	SetActorTickEnabled(bActivated);
	SetActorEnableCollision(bActivated);
}

void AST_AttackSystem::BeginPlay()
{
	Super::BeginPlay();
}


#include "ST_AttackSystem.h"

AST_AttackSystem::AST_AttackSystem()
	: bActivated(false)
	, SpawnLocation(FVector::ZeroVector)
	, SpawnRotation(FRotator::ZeroRotator) {}

void AST_AttackSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AST_AttackSystem::Attack()
{

}

bool AST_AttackSystem::GetActivated() const
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

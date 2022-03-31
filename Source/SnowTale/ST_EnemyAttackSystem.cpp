
#include "ST_EnemyAttackSystem.h"

void AST_EnemyAttackSystem::Attack()
{
	SpawnLocation = GetOwner()->GetActorLocation();
	SpawnRotation = GetOwner()->GetActorRotation();

	Super::Attack();
}
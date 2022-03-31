
#include "ST_SnowWhiteAttackSystem.h"

void AST_SnowWhiteAttackSystem::Attack()
{
	SpawnLocation = GetOwner()->GetActorLocation();
	SpawnRotation = GetOwner()->GetActorRotation();

	Super::Attack();
}

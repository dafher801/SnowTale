
#include "ST_EnemyAttackSystem.h"
#include "Kismet/GameplayStatics.h"

void AST_EnemyAttackSystem::Attack()
{
	FVector PlayerLocation = Cast<AActor>(UGameplayStatics::
		GetPlayerCharacter(GetWorld(), 0))->GetActorLocation();

	SpawnLocation = GetOwner()->GetActorLocation();
	SpawnRotation = (PlayerLocation - SpawnLocation).Rotation();

	Super::Attack();
}
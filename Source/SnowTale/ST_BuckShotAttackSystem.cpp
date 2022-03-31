
#include "ST_BuckShotAttackSystem.h"

void AST_BuckShotAttackSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AST_BuckShotAttackSystem::Attack()
{
	if (!bActivated)
		return;

	SpawnLocation = GetOwner()->GetActorLocation();
	SpawnRotation.Yaw = GetOwner()->GetActorRotation().Yaw + (NumberWhenAttack - 1) * SpreadAngle / 2.0f;

	for (int i = 0; i < NumberWhenAttack; i++)
	{
		Super::Attack();
		SpawnRotation.Yaw -= SpreadAngle;
	}
}

void AST_BuckShotAttackSystem::BeginPlay()
{
	Super::BeginPlay();
}

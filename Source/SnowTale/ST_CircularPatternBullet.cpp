
#include "ST_CircularPatternBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"

void AST_CircularPatternBullet::Init(FVector SpawnLocation, FRotator SpawnRotation)
{
	Super::Init(SpawnLocation, SpawnRotation);
}

void AST_CircularPatternBullet::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);
}

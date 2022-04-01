
#include "ST_CircularPatternBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"

void AST_CircularPatternBullet::Init(FVector SpawnLocation, FRotator SpawnRotation)
{
	Movement->Velocity = FVector::ZeroVector;

	Super::Init(SpawnLocation, SpawnRotation);
}

void AST_CircularPatternBullet::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);

	if ((CurrentMovementDistance += (DeltaTime * SpinningCenterMovement->MaxSpeed)) > MaxMovementDistance)
		SetActivated(false);
}

void AST_CircularPatternBullet::SetCenterInfo(class UProjectileMovementComponent* CenterMovement, float CenterSpinPerTick)
{
	SpinningCenterMovement = CenterMovement;
	SpinPerTick = CenterSpinPerTick;
}

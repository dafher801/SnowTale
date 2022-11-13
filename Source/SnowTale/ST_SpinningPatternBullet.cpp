
#include "ST_SpinningPatternBullet.h"
#include "ST_SpinningPatternCenter.h"
#include "GameFramework/ProjectileMovementComponent.h"

void AST_SpinningPatternBullet::Init(FVector SpawnLocation, FRotator SpawnRotation)
{
	Super::Init(SpawnLocation, SpawnRotation);

	Movement->InitialSpeed = 2.0f * PI * SpinningCenter->GetRadius() * SpinningCenter->GetRotatingAmount();
	Movement->MaxSpeed = 2.0f * PI * SpinningCenter->GetRadius() * SpinningCenter->GetRotatingAmount();
}

void AST_SpinningPatternBullet::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	AddActorWorldRotation(FRotator(0.0f, SpinningCenter->GetRotatingAmount() * DeltaTime * 360.0f, 0.0f));

	Movement->Velocity = GetActorForwardVector().GetSafeNormal() * Movement->MaxSpeed;

	Movement->Velocity += SpinningCenter->GetMovement()->Velocity;
	Movement->Velocity.Z = 0.0f;

	AActor::Tick(DeltaTime);
}

void AST_SpinningPatternBullet::SetBulletCenter(AST_SpinningPatternCenter* SpinningPatternCenter)
{
	SpinningCenter = SpinningPatternCenter;
}


#include "ST_GuidedProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"

void AST_GuidedProjectile::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);

	float Radian = PI / 180.0f * TurningLimitPerTick;

	FVector DirectionToPlayer = (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->
		GetActorLocation() - GetActorLocation()).Rotation().Vector() * Movement->MaxSpeed;
	
	FVector ClockWiseVector = FVector::ZeroVector;
	FVector CounterClockWiseVector = FVector::ZeroVector;

	ClockWiseVector.X = FMath::Cos(Radian) * Movement->Velocity.X + FMath::Sin(Radian) * Movement->Velocity.Y;
	ClockWiseVector.Y = FMath::Cos(Radian) * Movement->Velocity.Y - FMath::Sin(Radian) * Movement->Velocity.X;
	
	if (Movement->Velocity.X * DirectionToPlayer.X + Movement->Velocity.Y * DirectionToPlayer.Y
		>= Movement->Velocity.X * ClockWiseVector.X + Movement->Velocity.Y * ClockWiseVector.Y)
	{
		SetActorRotation(DirectionToPlayer.Rotation());
	}
	else
	{
		CounterClockWiseVector.X = FMath::Cos(Radian) * Movement->Velocity.X - FMath::Sin(Radian) * Movement->Velocity.Y;
		CounterClockWiseVector.Y = FMath::Cos(Radian) * Movement->Velocity.Y + FMath::Sin(Radian) * Movement->Velocity.X;

		if (DirectionToPlayer.X * ClockWiseVector.X + DirectionToPlayer.Y * ClockWiseVector.Y >=
			DirectionToPlayer.X * CounterClockWiseVector.X + DirectionToPlayer.Y * CounterClockWiseVector.Y)
		{
			AddActorWorldRotation(FRotator(0.0f, -TurningLimitPerTick, 0.0f));
		}
		else
		{
			AddActorWorldRotation(FRotator(0.0f, TurningLimitPerTick, 0.0f));
		}
	}

	Movement->Velocity = GetActorRotation().Vector() * Movement->MaxSpeed;
}

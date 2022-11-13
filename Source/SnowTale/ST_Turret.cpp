
#include "ST_Turret.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void AST_Turret::Tick(float DeltaTime)
{
	if (!bActivated || !IsValid(Player))
		return;

	AST_Unit::Tick(DeltaTime);

	if (1.0f / CurrentStatus.AttackSpeed - TimeElapsedSinceAttack <= 0)
	{
		TimeElapsedSinceAttack = 0.0f;

		Attack();
	}
}

float AST_Turret::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount -= CurrentStatus.DEF;

	if (DamageAmount > 0)
		CurrentStatus.HP -= DamageAmount;
	else
		DamageAmount = 0;

	if (CurrentStatus.HP <= 0.0f)
	{
		SetActivated(false);

		if (IsValid(DestroyParticleSystem))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
				DestroyParticleSystem, GetActorLocation(), GetActorRotation());
		}

		if (IsValid(DestroySound))
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), DestroySound, GetActorLocation());
	}

	return ACharacter::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}


#include "ST_LongRangeAttackSystem.h"
#include "ST_Projectile.h"

void AST_LongRangeAttackSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AST_LongRangeAttackSystem::Attack()
{
	if (!bActivated)
		return;

	if (CurrentProjectileNum >= MaxProjectileNum)
		CurrentProjectileNum = 0;

	for (int i = CurrentProjectileNum++; i < MaxProjectileNum; i++)
	{
		if (!ProjectileArray[i]->GetActivated())
		{
			ProjectileArray[i]->Init(SpawnLocation, SpawnRotation);
			return;
		}
	}
}

void AST_LongRangeAttackSystem::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = Cast<class APawn>(GetOwner());
	SpawnParameters.Owner = this;

	for (int i = 0; i < MaxProjectileNum; i++)
	{
		ProjectileArray.Add(GetWorld()->SpawnActor<AST_Projectile>(ProjectileClass, SpawnParameters));
	}
}

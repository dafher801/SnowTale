
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
		if (!ProjectileArray[i]->IsActivated())
		{
			// 발사체를 생성함
			ProjectileArray[i]->Init(SpawnLocation, SpawnRotation);
			return;
		}
	}
}

void AST_LongRangeAttackSystem::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);

	for (int i = 0; i < ProjectileArray.Num(); i++)
	{
		ProjectileArray[i]->SetInstigator(Cast<APawn>(GetOwner()));
		ProjectileArray[i]->SetOwner(this);
	}
}

void AST_LongRangeAttackSystem::SetSpawnLocation(FVector Location)
{
	SpawnLocation = Location;
}

void AST_LongRangeAttackSystem::SetSpawnRotation(FRotator Rotation)
{
	SpawnRotation = Rotation;
}

void AST_LongRangeAttackSystem::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(ProjectileClass))
	{
		for (int i = 0; i < MaxProjectileNum; i++)
			ProjectileArray.Add(GetWorld()->SpawnActor<AST_Projectile>(ProjectileClass));
	}

	SpawnLocation = GetActorLocation();
	SpawnRotation = GetActorRotation();
}

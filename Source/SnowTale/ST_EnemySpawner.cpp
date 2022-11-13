
#include "ST_EnemySpawner.h"
#include "ST_Enemy.h"
#include "ST_Portal.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AST_EnemySpawner::AST_EnemySpawner()
	: EnemyNum(0)
	, bSpawned(false)
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AST_EnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AST_EnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AST_EnemySpawner::Interact(AActor* OtherActor)
{
	if (bSpawned)
		return;

	Super::Interact(OtherActor);

	bSpawned = true;

	SpawnEnemy();
}

void AST_EnemySpawner::SpawnEnemy()
{
	for (int i = 0; i < EnemyArray.Num(); i++)
	{
		if (IsValid(EnemyArray[i]) && !EnemyArray[i]->IsDead() && !EnemyArray[i]->IsActivated())
		{
			EnemyArray[i]->SetActivated(true);
			EnemyArray[i]->SetEnemySpawner(this);
		}
	}
}

void AST_EnemySpawner::DeadMonsterEvent()
{
	if (IsValid(Portal))
	{
		for (int i = 0; i < EnemyArray.Num(); i++)
		{
			if (IsValid(EnemyArray[i]) && !EnemyArray[i]->IsDead())
				return;
		}

		Portal->SetActivated(true);
	}

	/*if (IsValid(Obstacle) && EnemyNum <= 0)
	{
		if (IsValid(ObstacleExplosionParticleSystem))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
				ObstacleExplosionParticleSystem, Obstacle->GetActorLocation(), Obstacle->GetActorRotation());
		}

		if (IsValid(ObstacleExplosionSound))
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ObstacleExplosionSound, GetActorLocation());

		Obstacle->Destroy();
	}*/
}

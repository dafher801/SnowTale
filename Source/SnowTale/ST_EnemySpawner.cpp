
#include "ST_EnemySpawner.h"
#include "ST_Enemy.h"

AST_EnemySpawner::AST_EnemySpawner()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AST_EnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < EnemyArray.Num(); i++)
	{
		EnemyArray[i]->SetActivated(false);
	}
}

void AST_EnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AST_EnemySpawner::SpawnEnemy()
{
	for (int i = 0; i < EnemyArray.Num(); i++)
	{
		EnemyArray[i]->SetActivated(true);
	}
}

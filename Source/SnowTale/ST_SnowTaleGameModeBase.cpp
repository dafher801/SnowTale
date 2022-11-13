
#include "ST_SnowTaleGameModeBase.h"
#include "ST_Enemy.h"
#include "Kismet/GameplayStatics.h"

void AST_SnowTaleGameModeBase::StartPlay()
{
	Super::StartPlay();

	TArray<AActor*> InstancingActorArray;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AST_Enemy::StaticClass(), InstancingActorArray);

	for (int i = 0; i < InstancingActorArray.Num(); i++)
		EnemyArray.Add(Cast<AST_Enemy>(InstancingActorArray[i]));

	bFightBoss = false;
}

void AST_SnowTaleGameModeBase::SetFightBoss(bool FightBoss)
{
	bFightBoss = FightBoss;
}

void AST_SnowTaleGameModeBase::GameOver_Implementation() const
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("GameOver"));
}

void AST_SnowTaleGameModeBase::GameClear() const
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("GameClear"));
}

const TArray<AST_Enemy*>& AST_SnowTaleGameModeBase::GetEnemyArray() const
{
	return EnemyArray;
}
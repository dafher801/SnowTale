
#include "ST_PursuitPlayerAttackSystem.h"
#include "ST_Bomb.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

void AST_PursuitPlayerAttackSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AST_PursuitPlayerAttackSystem::Attack()
{
	if (!bActivated)
		return;

	if (CurrentBombNum >= MaxBombNum)
		CurrentBombNum = 0;

	for (int i = CurrentBombNum++; i < MaxBombNum; i++)
	{
		if (!BombArray[i]->GetActivated() && IsValid(Player))
		{
			FVector SpawnLocation = Player->GetActorLocation();
			SpawnLocation -= FVector(0.0f, 0.0f, Player->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

			SpawnLocation.X += FRandomStream(FMath::Rand()).FRandRange(-RandomDistance, RandomDistance);
			SpawnLocation.Y += FRandomStream(FMath::Rand()).FRandRange(-RandomDistance, RandomDistance);

			BombArray[i]->Init(SpawnLocation);
			return;
		}
	}
}

void AST_PursuitPlayerAttackSystem::BeginPlay()
{
	Super::BeginPlay();

	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (IsValid(BombClass))
	{
		for (int i = 0; i < MaxBombNum; i++)
			BombArray.Add(GetWorld()->SpawnActor<AST_Bomb>(BombClass));
	}
}

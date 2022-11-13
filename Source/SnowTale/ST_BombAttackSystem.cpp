
#include "ST_BombAttackSystem.h"
#include "ST_Bomb.h"

void AST_BombAttackSystem::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);
}

void AST_BombAttackSystem::Attack()
{
	for (int i = 0; i < BombArray.Num(); i++)
	{
		if (IsValid(BombArray[i]))
			BombArray[i]->Init(BombArray[i]->GetActorLocation(), BombArray[i]->GetActorRotation());
	}
}

void AST_BombAttackSystem::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);

	for (int i = 0; i < BombArray.Num(); i++)
	{
		if (IsValid(BombArray[i]))
		{
			BombArray[i]->SetOwner(this);
			BombArray[i]->SetInstigator(Cast<APawn>(GetOwner()));
		}
	}
}

void AST_BombAttackSystem::BeginPlay()
{
	Super::BeginPlay();
}

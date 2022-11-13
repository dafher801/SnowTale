
#include "ST_Enemy.h"
#include "ST_EnemyController.h"
#include "ST_EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AST_Enemy::AST_Enemy()
{
	Tags.Add(FName("Enemy"));
}

void AST_Enemy::Tick(float DeltaTime)
{
	if (!bActivated || !IsValid(Player))
		return;

	if (bDead)
	{
		AST_Unit::Tick(DeltaTime);
		return;
	}

	FVector TargetLocation = Player->GetActorLocation();

	LookAtTarget(TargetLocation);
	Move(TargetLocation);

	Super::Tick(DeltaTime);

	BeginAttack();
}

void AST_Enemy::LookAtTarget(FVector TargetLocation)
{
	Super::LookAtTarget(TargetLocation - GetActorLocation());
}

void AST_Enemy::Move(FVector TargetLocation)
{
	if (!IsVisibleFromPlayer() || IsAccessible())
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), TargetLocation);
	else
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), GetActorLocation());
}

void AST_Enemy::ExitMove()
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), GetActorLocation());
}

void AST_Enemy::BeginAttack()
{
	if (1.0f / CurrentStatus.AttackSpeed - TimeElapsedSinceAttack <= 0)
	{
		Super::BeginAttack();
	}
}

void AST_Enemy::Attack()
{
	Super::Attack();
}

void AST_Enemy::ExitAttack()
{
	Super::ExitAttack();
}

float AST_Enemy::GetAccessibleDistanceToPlayer() const
{
	return AccessibleDistanceToPlayer;
}

bool AST_Enemy::IsVisibleFromPlayer() const
{
	FHitResult HitResult;
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);

	bool bVisibleFromPlayer = !(GetWorld()->LineTraceSingleByObjectType(HitResult, 
		GetActorLocation(), Player->GetActorLocation(), CollisionObjectQueryParams));

	return bVisibleFromPlayer;
}

bool AST_Enemy::IsAccessible() const
{
	return AccessibleDistanceToPlayer < FVector::Distance(GetActorLocation(), Player->GetActorLocation());
}

void AST_Enemy::SetEnemySpawner(AST_EnemySpawner* Spawner)
{
	EnemySpawner = Spawner;
}

void AST_Enemy::SetDead(bool Dead)
{
	Super::SetDead(Dead);

	if (IsValid(EnemySpawner))
		EnemySpawner->DeadMonsterEvent();
}

void AST_Enemy::BeginPlay()
{
	Super::BeginPlay();

	SetActivated(false);

	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
}

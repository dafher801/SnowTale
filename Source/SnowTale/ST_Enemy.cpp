
#include "ST_Enemy.h"
#include "ST_EnemyController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AST_Enemy::AST_Enemy()
	: NavSystem(nullptr)
{

}

void AST_Enemy::Init()
{
	SpawnDefaultController();

	SetActivated(true);
}

void AST_Enemy::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);
}

void AST_Enemy::LookAtTarget(FVector TargetLocation)
{
	BodyRotation = (TargetLocation - GetActorLocation()).Rotation();

	SetActorRotation(BodyRotation + RotationErrorCalculation);
}

void AST_Enemy::Move(FVector TargetLocation)
{
	Super::Move(TargetLocation);
}

void AST_Enemy::BeginAttack()
{
	if (1.0f  / CurrentStatus.AttackSpeed - TimeElapsedSinceAttack <= 0)
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

void AST_Enemy::OnHit(UPrimitiveComponent* OtherComp, AActor* OtherActor, UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit)
{
	if (OtherActor->ActorHasTag("PlayerProjectile"))
		SetActivated(false);
}

float AST_Enemy::GetAccessibleDistanceToPlayer() const
{
	return AccessibleDistanceToPlayer;
}

void AST_Enemy::BeginPlay()
{
	Super::BeginPlay();

	NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AST_Enemy::OnHit);
}

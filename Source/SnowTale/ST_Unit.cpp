
#include "ST_Unit.h"
#include "ST_AttackSystem.h"
#include "ST_ABP_SampleUnit.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AST_Unit::AST_Unit()
	: AttackSystem(nullptr)
	, bAttacking(false)
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AST_Unit::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);

	TimeElapsedSinceAttack += DeltaTime;
}

void AST_Unit::LookAtTarget(FVector TargetLocation)
{
	FVector2D UnitScreenLocation;
	FVector2D TargetScreenLocation;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController)
	{
		PlayerController->ProjectWorldLocationToScreen(GetActorLocation(), UnitScreenLocation, true);
		PlayerController->ProjectWorldLocationToScreen(TargetLocation, TargetScreenLocation, true);
	}
	else
		return;

	BodyRotation = FVector(TargetScreenLocation - UnitScreenLocation, 0.0f).Rotation();

	SetActorRotation(BodyRotation + RotationErrorCalculation);
}

void AST_Unit::Move(FVector TargetLocation)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), TargetLocation);
}

void AST_Unit::ExitMove()
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), GetActorLocation());
}

void AST_Unit::BeginAttack()
{
	if (!bAttacking)
	{
		bAttacking = true;
		TimeElapsedSinceAttack = 0.0f;
		Cast<UST_ABP_SampleUnit>(GetMesh()->GetAnimInstance())->PlayAttackMontage();
	}
}

void AST_Unit::Attack()
{
	AttackSystem->Attack();
}

void AST_Unit::ExitAttack()
{
	bAttacking = false;
}

void AST_Unit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AST_Unit::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount -= CurrentStatus.DEF;

	if (DamageAmount > 0)
		CurrentStatus.HP -= DamageAmount;
	else
		DamageAmount = 0;

	if (CurrentStatus.HP <= 0.0f)
	{
		SetActivated(false);
		DetachFromControllerPendingDestroy();
	}

	return DamageAmount;
}

FST_Status AST_Unit::GetBaseStatus() const
{
	return BaseStatus;
}

FST_Status AST_Unit::GetCurrentStatus() const
{
	return CurrentStatus;
}

bool AST_Unit::GetActivated() const
{
	return bActivated;
}

void AST_Unit::SetActivated(bool Activated)
{
	bActivated = Activated;
	GetCharacterMovement()->SetActive(bActivated);
	SetActorHiddenInGame(!bActivated);
	SetActorTickEnabled(bActivated);
	SetActorEnableCollision(bActivated);
}

bool AST_Unit::IsAttacking() const
{
	return bAttacking;
}

void AST_Unit::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;

	AttackSystem = GetWorld()->SpawnActor<AST_AttackSystem>(AttackSystemClass, SpawnParameters);

	CurrentStatus = BaseStatus;
	GetCharacterMovement()->MaxWalkSpeed = CurrentStatus.MoveSpeed;

	TimeElapsedSinceAttack = 1.0f / CurrentStatus.AttackSpeed;
}


#include "ST_Unit.h"
#include "ST_ABP_Unit.h"
#include "ST_AttackSystem.h"
#include "ST_UnitWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AST_Unit::AST_Unit()
	: bAttacking(false)
	, bDead(false)
	, bDisappear(false)
{
 	PrimaryActorTick.bCanEverTick = true;

	UnitWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("UnitWidget"));
	UnitWidget->SetupAttachment(GetMesh());
}

void AST_Unit::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);

	TimeElapsedSinceAttack += DeltaTime;
}

void AST_Unit::LookAtTarget(FVector VectorToTarget)
{
	BodyRotation = VectorToTarget.Rotation();

	SetActorRotation(BodyRotation + RotationRevisionCalculation);
}

void AST_Unit::BeginAttack()
{
	if (bAttacking)
		return;
	
	UST_ABP_Unit* UnitABP = Cast<UST_ABP_Unit>(GetMesh()->GetAnimInstance());

	bAttacking = true;
	TimeElapsedSinceAttack = 0.0f;

	if (IsValid(UnitABP))
		UnitABP->PlayAttackStartMontage(CurrentStatus.AttackSpeed);
}

void AST_Unit::Attack()
{
	if (IsValid(AttackSystem))
		AttackSystem->Attack();
}

void AST_Unit::ExitAttack()
{
	DeactiveAttackAnim();
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
		UST_ABP_Unit* UnitAnim = nullptr;

		if (IsValid(GetMesh()) && IsValid(GetMesh()->GetAnimInstance()))
			UnitAnim = Cast<UST_ABP_Unit>(GetMesh()->GetAnimInstance());

		if (IsValid(UnitAnim))
			Cast<UST_ABP_Unit>(GetMesh()->GetAnimInstance())->PlayDeadMontage();
		else
			SetActivated(false);
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

FST_Status AST_Unit::GetBaseStatus() const
{
	return BaseStatus;
}

FST_Status AST_Unit::GetCurrentStatus() const
{
	return CurrentStatus;
}

float AST_Unit::GetHPRatio() const
{
	return CurrentStatus.HP / BaseStatus.HP;
}

float AST_Unit::GetMPRatio() const
{
	return CurrentStatus.MP / BaseStatus.MP;
}

bool AST_Unit::IsActivated() const
{
	return bActivated;
}

void AST_Unit::SetActivated(bool Activated)
{
	bActivated = Activated;

	if (IsValid(AttackSystem))
		AttackSystem->SetActivated(bActivated);

	GetCharacterMovement()->SetActive(bActivated);

	SetActorHiddenInGame(!bActivated);
	SetActorTickEnabled(bActivated);
	SetActorEnableCollision(bActivated);

	if (Activated)
		SpawnDefaultController();
	else
		DetachFromControllerPendingDestroy();
}

bool AST_Unit::IsStartingAttack() const
{
	return bStartingAttack;
}

void AST_Unit::ActiveStartingAttack()
{
	bStartingAttack = true;
	bAttacking = false;
	bEndingAttack = false;
}

bool AST_Unit::IsAttacking() const
{
	return bAttacking;
}

void AST_Unit::ActiveAttacking()
{
	bStartingAttack = false;
	bAttacking = true;
	bEndingAttack = false;
}

bool AST_Unit::IsEndingAttack() const
{
	return bEndingAttack;
}

void AST_Unit::ActiveEndingAttack()
{
	bStartingAttack = false;
	bAttacking = false;
	bEndingAttack = true;
}

void AST_Unit::DeactiveAttackAnim()
{
	bStartingAttack = false;
	bAttacking = false;
	bEndingAttack = false;
}

bool AST_Unit::IsDead() const
{
	return bDead;
}

void AST_Unit::SetDead(bool Dead)
{
	bDead = Dead;

	SetActorEnableCollision(!Dead);
	GetCharacterMovement()->SetActive(!Dead);
}

void AST_Unit::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(AttackSystemClass))
	{
		AttackSystem = GetWorld()->SpawnActor<AST_AttackSystem>(AttackSystemClass);
		AttackSystem->SetOwner(this);
	}
	
	if (IsValid(UnitWidget->GetWidget()))
		Cast<UST_UnitWidget>(UnitWidget->GetWidget())->BindUnit(this);

	CurrentStatus = BaseStatus;
	GetCharacterMovement()->MaxWalkSpeed = CurrentStatus.MoveSpeed;

	TimeElapsedSinceAttack = 1.0f / CurrentStatus.AttackSpeed;
}


#include "ST_SnowWhite.h"
#include "ST_HealItem.h"
#include "ST_PlayerWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AST_SnowWhite::AST_SnowWhite()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void AST_SnowWhite::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);

	LookAtTarget();
	Move();

	if (bInvincible)
		Invincible();
	else
	{
		BeginAttack();

		if (CurrentStatus.MP < BaseStatus.MP)
			CurrentStatus.MP += MPRecoveryAmountPerTick;
	}
}

void AST_SnowWhite::LookAtTarget(FVector TargetLocation)
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->
		DeprojectMousePositionToWorld(TargetLocation, WorldDirection);

	Super::LookAtTarget(TargetLocation);
}

void AST_SnowWhite::Move(FVector MoveVector)
{
	MoveVector = FVector(CurrentForwardValue, CurrentRightValue, 0.0f);

	if (MoveVector.SizeSquared() > 0.0f)
	{
		AddMovementInput(MoveVector);
	}
}

void AST_SnowWhite::BeginAttack()
{
	if (bPressedLeftMouse && !bAttacking && 
		1.0f / CurrentStatus.AttackSpeed - TimeElapsedSinceAttack <= 0)
	{
		TimeElapsedSinceAttack = 0.0f;
		bAttacking = true;

		Attack();
	}
}

void AST_SnowWhite::Attack()
{
	Super::Attack();
	ExitAttack();
}

void AST_SnowWhite::ExitAttack()
{
	Super::ExitAttack();
}

void AST_SnowWhite::Invincible()
{
	if (CurrentStatus.MP >= InvincibeMPConsumptionPerTick)
		CurrentStatus.MP -= InvincibeMPConsumptionPerTick;
	else
		bInvincible = false;
}

void AST_SnowWhite::AcquireHealItem(AST_HealItem* HealItem)
{
	AcquireHealItemDelegate.Execute();
	HealItemArray.Push(HealItem);
}

void AST_SnowWhite::UseHealItem(FKey Key)
{
	if (HealItemArray.Num() > 0)
	{
		HealItemArray.Pop()->Heal(BaseStatus.HP, CurrentStatus.HP);
	}

	UseHealItemDelegate.Execute();
}

void AST_SnowWhite::ActiveInvincible()
{
	bInvincible = true;
}

void AST_SnowWhite::DeactiveInvincible()
{
	bInvincible = false;
}

void AST_SnowWhite::InputForward(float NewForwardValue)
{
	CurrentForwardValue = NewForwardValue;
}

void AST_SnowWhite::InputRight(float NewRightValue)
{
	CurrentRightValue = NewRightValue;
}

void AST_SnowWhite::PressedLeftMouse(FKey Key)
{
	bPressedLeftMouse = true;
}

void AST_SnowWhite::ReleasedLeftMouse(FKey Key)
{
	bPressedLeftMouse = false;
}

void AST_SnowWhite::PressedRightMouse(FKey Key)
{
	ActiveInvincible();
}

void AST_SnowWhite::ReleasedRightMouse(FKey Key)
{
	DeactiveInvincible();
}

void AST_SnowWhite::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &AST_SnowWhite::InputForward);
	InputComponent->BindAxis("MoveRight", this, &AST_SnowWhite::InputRight);

	InputComponent->BindAction("Attack", IE_Pressed, this, &AST_SnowWhite::PressedLeftMouse);
	InputComponent->BindAction("Attack", IE_Released, this, &AST_SnowWhite::ReleasedLeftMouse);

	InputComponent->BindAction("UseHeal", IE_Pressed, this, &AST_SnowWhite::UseHealItem);

	InputComponent->BindAction("Invincibility", IE_Pressed, this, &AST_SnowWhite::PressedRightMouse);
	InputComponent->BindAction("Invincibility", IE_Released, this, &AST_SnowWhite::ReleasedRightMouse);
}

float AST_SnowWhite::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return bInvincible ? 0.0f : Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AST_SnowWhite::BeginPlay()
{
	Super::BeginPlay();

	SetActivated(true);
}

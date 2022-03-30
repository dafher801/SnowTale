
#include "ST_SnowWhite.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

AST_SnowWhite::AST_SnowWhite()
{
	SetActivated(true);
}

void AST_SnowWhite::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);

	LookAtTarget();
	Move();
	BeginAttack();
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

void AST_SnowWhite::InputForward(float NewForwardValue)
{
	CurrentForwardValue = NewForwardValue;
}

void AST_SnowWhite::InputRight(float NewRightValue)
{
	CurrentRightValue = NewRightValue;
}

void AST_SnowWhite::PressedLeftMouse(FKey key)
{
	bPressedLeftMouse = true;
}

void AST_SnowWhite::ReleasedLeftMouse(FKey key)
{
	bPressedLeftMouse = false;
}

void AST_SnowWhite::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &AST_SnowWhite::InputForward);
	InputComponent->BindAxis("MoveRight", this, &AST_SnowWhite::InputRight);

	InputComponent->BindAction("Attack", IE_Pressed, this, &AST_SnowWhite::PressedLeftMouse);
	InputComponent->BindAction("Attack", IE_Released, this, &AST_SnowWhite::ReleasedLeftMouse);
}

void AST_SnowWhite::BeginPlay()
{
	Super::BeginPlay();
}

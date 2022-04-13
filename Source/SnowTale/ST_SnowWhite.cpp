
#include "ST_SnowWhite.h"
#include "ST_HealItem.h"
#include "Kismet/GameplayStatics.h"
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

void AST_SnowWhite::AcquireItem(AST_Item* Item)
{
	ItemArray[static_cast<int>(Item->GetItemType())].Push(Item);
}

void AST_SnowWhite::Heal(FKey Key)
{
	int HealType = static_cast<int>(EST_ItemType::HEAL);

	if (ItemArray[HealType].Num() > 0)
	{
		Cast<AST_HealItem>(ItemArray[HealType].Pop())->Heal(BaseStatus.HP, CurrentStatus.HP);
	}
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

void AST_SnowWhite::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &AST_SnowWhite::InputForward);
	InputComponent->BindAxis("MoveRight", this, &AST_SnowWhite::InputRight);

	InputComponent->BindAction("Attack", IE_Pressed, this, &AST_SnowWhite::PressedLeftMouse);
	InputComponent->BindAction("Attack", IE_Released, this, &AST_SnowWhite::ReleasedLeftMouse);

	InputComponent->BindAction("UseHeal", IE_Pressed, this, &AST_SnowWhite::Heal);
}

void AST_SnowWhite::BeginPlay()
{
	Super::BeginPlay();

	for (int ItemType = static_cast<int>(EST_ItemType::BEGIN);
		ItemType < static_cast<int>(EST_ItemType::END); ItemType++)
	{
		ItemArray.Add(TArray<AST_Item*>());
	}

	SetActivated(true);
}

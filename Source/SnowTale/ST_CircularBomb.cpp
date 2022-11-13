
#include "ST_CircularBomb.h"
#include "ST_BombAttackSystem.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"

AST_CircularBomb::AST_CircularBomb()
{
	BombShape = CreateDefaultSubobject<USphereComponent>(TEXT("BombShape"));
	RootComponent = BombShape;

	AttackFloorSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("AttackFloorSprite"));
	AttackFloorSprite->AddLocalRotation(FRotator(0.0f, 0.0f, 90.0f));
	AttackFloorSprite->SetCollisionProfileName(FName("NoCollision"));
	AttackFloorSprite->SetupAttachment(RootComponent);

	WarningFloorSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("NoticeFloorSprite"));
	WarningFloorSprite->SetWorldLocation(AttackFloorSprite->GetComponentLocation() + FVector(0.0f, 0.0f, 1.0f));
	WarningFloorSprite->SetWorldRotation(AttackFloorSprite->GetComponentRotation());
	WarningFloorSprite->SetWorldScale3D(FVector::ZeroVector);
	WarningFloorSprite->SetCollisionProfileName(FName("NoCollision"));
	WarningFloorSprite->SetupAttachment(RootComponent);
}

void AST_CircularBomb::Init(FVector SpawnLocation, FRotator SpawnRotation)
{
	Super::Init(SpawnLocation, SpawnRotation);

	WarningFloorSprite->SetWorldLocation(AttackFloorSprite->GetComponentLocation() + FVector(0.0f, 0.0f, 1.0f));
	WarningFloorSprite->SetWorldRotation(AttackFloorSprite->GetComponentRotation());
	WarningFloorSprite->SetWorldScale3D(FVector::ZeroVector);
}

void AST_CircularBomb::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);
}

void AST_CircularBomb::AddFloorScale()
{
	WarningFloorSprite->SetWorldScale3D(WarningFloorSprite->GetComponentScale() + FloorAddingScalePerTick);

	if (WarningFloorSprite->GetComponentScale().Size() >= AttackFloorSprite->GetComponentScale().Size())
	{
		Attack();
	}
}

void AST_CircularBomb::BeginPlay()
{
	Super::BeginPlay();
}


#include "ST_RectangularBomb.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"

AST_RectangularBomb::AST_RectangularBomb()
{
	BombShape = CreateDefaultSubobject<UBoxComponent>(TEXT("BombShape"));
	RootComponent = BombShape;

	AttackFloorSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("AttackFloorSprite"));
	AttackFloorSprite->SetCollisionProfileName(FName("NoCollision"));
	AttackFloorSprite->SetupAttachment(RootComponent);

	WarningFloorSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("WarningFloorSprite"));
	WarningFloorSprite->SetCollisionProfileName(FName("NoCollision"));
	WarningFloorSprite->SetupAttachment(RootComponent);
}

void AST_RectangularBomb::Init(FVector SpawnLocation, FRotator SpawnRotation)
{
	Super::Init(SpawnLocation, SpawnRotation);

	FVector AttackFloorSpriteScale = AttackFloorSprite->GetComponentScale();
	AttackFloorSpriteScale.X = 0.0f;

	WarningFloorSprite->SetWorldScale3D(AttackFloorSpriteScale);
	WarningFloorSprite->SetWorldLocation(AttackFloorSprite->GetComponentLocation() + FVector(0.0f, 0.0f, 1.0f));
}

void AST_RectangularBomb::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);
}

void AST_RectangularBomb::AddFloorScale()
{
	FVector FloorAddingScale = WarningFloorSprite->GetComponentScale();
	FloorAddingScale.X = WarningFloorSprite->GetComponentScale().X + FloorAddingScalePerTick;

	WarningFloorSprite->SetWorldScale3D(FloorAddingScale);

	if (WarningFloorSprite->GetComponentScale().X >= AttackFloorSprite->GetComponentScale().X)
	{
		Attack();
	}
}

void AST_RectangularBomb::BeginPlay()
{
	Super::BeginPlay();
}

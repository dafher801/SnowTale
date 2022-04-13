
#include "ST_CircularPatternCenter.h"
#include "ST_CircularPatternBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"

void AST_CircularPatternCenter::Init(FVector SpawnLocation, FRotator SpawnRotation)
{
	Super::Init(SpawnLocation, SpawnRotation);

	FVector SpnningBulletLocation = SpawnLocation;

	for (int i = 0; i < SpinningBulletNum; i++)
	{
		SpnningBulletLocation.X = SpawnLocation.X + Radius * FMath::Cos(i * Radian);
		SpnningBulletLocation.Y = SpawnLocation.Y + Radius * FMath::Sin(i * Radian);

		BulletArray[i]->Init(SpnningBulletLocation, SpawnRotation);
		BulletArray[i]->GetMovement()->Velocity = FVector::ZeroVector;
	}
}

void AST_CircularPatternCenter::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	AActor::Tick(DeltaTime);

	if ((CurrentMovementDistance += (DeltaTime * Movement->MaxSpeed)) > MaxMovementDistance)
	{
		SetActivated(false);
		Clear();
	}
	else
		AddActorLocalRotation(FRotator(0.0f, SpinPerTick, 0.0f));
}

void AST_CircularPatternCenter::SetActivated(bool Activated)
{
	Super::SetActivated(Activated);
}

void AST_CircularPatternCenter::Clear() const
{
	for (int i = 0; i < SpinningBulletNum; i++)
		BulletArray[i]->SetActivated(false);
}

void AST_CircularPatternCenter::BeginPlay()
{
	Super::BeginPlay();

	Radian = PI * 2 / SpinningBulletNum;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = GetInstigator();
	SpawnParameters.Owner = this;

	const FAttachmentTransformRules AttachRules = { EAttachmentRule::KeepRelative, true };

	for (int i = 0; i < SpinningBulletNum; i++)
	{
		BulletArray.Add(GetWorld()->SpawnActor<AST_CircularPatternBullet>(SpinningBulletClass, SpawnParameters));
		BulletArray[i]->AttachToActor(this, AttachRules);
	}
}

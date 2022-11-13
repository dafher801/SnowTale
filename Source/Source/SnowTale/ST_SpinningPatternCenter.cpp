
#include "ST_SpinningPatternCenter.h"
#include "ST_SpinningPatternBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"

void AST_SpinningPatternCenter::Init(FVector SpawnLocation, FRotator SpawnRotation)
{
	Super::Init(SpawnLocation, SpawnRotation);

	FVector SpnningBulletLocation = SpawnLocation;

	for (int i = 0; i < BulletArray.Num(); i++)
	{
		SpnningBulletLocation.X = SpawnLocation.X + Radius * FMath::Cos(i * Radian);
		SpnningBulletLocation.Y = SpawnLocation.Y + Radius * FMath::Sin(i * Radian);

		SpawnRotation.Yaw = i * 360.0f / BulletArray.Num();

		BulletArray[i]->SetBulletCenter(this);
		BulletArray[i]->Init(SpnningBulletLocation, SpawnRotation);
	}
}

void AST_SpinningPatternCenter::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	AActor::Tick(DeltaTime);

	if ((CurrentMovementDistance += (DeltaTime * Movement->MaxSpeed)) > MaxMovementDistance)
	{
		SetActivated(false);
		Clear();
	}
}

void AST_SpinningPatternCenter::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);

	for (int i = 0; i < BulletArray.Num(); i++)
	{
		BulletArray[i]->SetInstigator(GetInstigator());
		BulletArray[i]->SetOwner(this);
	}
}

void AST_SpinningPatternCenter::SetActivated(bool Activated)
{
	Super::SetActivated(Activated);
}

float AST_SpinningPatternCenter::GetRadius() const
{
	return Radius;
}

float AST_SpinningPatternCenter::GetRotatingAmount() const
{
	return RotatingAmount;
}

void AST_SpinningPatternCenter::Clear() const
{
	for (int i = 0; i < BulletArray.Num(); i++)
		BulletArray[i]->SetActivated(false);
}

void AST_SpinningPatternCenter::BeginPlay()
{
	Super::BeginPlay();

	Radian = PI * 2 / SpinningBulletNum;

	if (IsValid(SpinningBulletClass))
	{
		for (int i = 0; i < SpinningBulletNum; i++)
			BulletArray.Add(GetWorld()->SpawnActor<AST_SpinningPatternBullet>(SpinningBulletClass));
	}
}

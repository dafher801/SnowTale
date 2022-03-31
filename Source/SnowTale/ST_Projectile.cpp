
#include "ST_Projectile.h"
#include "ST_Unit.h"
#include "ST_AttackSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AST_Projectile::AST_Projectile()
{
 	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleCollision->SetConstraintMode(EDOFMode::Type::XYPlane);
	RootComponent = CapsuleCollision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Direction = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction"));
	Direction->SetupAttachment(RootComponent);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->ProjectileGravityScale = 0.0f;

	SetActivated(false);
}

void AST_Projectile::Init(FVector SpawnLocation, FRotator SpawnRotation)
{
	SetActorLocation(SpawnLocation);
	SetActorRotation(SpawnRotation);

	Damage =Cast<AST_Unit>(GetInstigator())->GetCurrentStatus().ATK;

	MaxMovementDistance = Cast<AST_Unit>(GetInstigator())->GetCurrentStatus().Range;

	CurrentMovementDistance = 0.0f;

	Movement->MaxSpeed = Movement->InitialSpeed = 5000.0f;
	Movement->Velocity = SpawnRotation.Vector() * Movement->MaxSpeed;

	SetActivated(true);
}

void AST_Projectile::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);

	if ((CurrentMovementDistance += (DeltaTime * Movement->MaxSpeed)) > MaxMovementDistance)
		SetActivated(false);
}

void AST_Projectile::OnHit(UPrimitiveComponent* OtherComp, AActor* OtherActor, UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit)
{
	Damage = Cast<AST_Unit>(GetInstigator())->GetCurrentStatus().ATK;

	UGameplayStatics::ApplyDamage(OtherActor, Damage,
		UGameplayStatics::GetPlayerController(GetWorld(), 0), this, NULL);

	SetActivated(false);
}

bool AST_Projectile::GetActivated() const
{
	return bActivated;
}

void AST_Projectile::SetActivated(bool Activated)
{
	bActivated = Activated;
	Movement->SetActive(bActivated);
	SetActorHiddenInGame(!bActivated);
	SetActorTickEnabled(bActivated);
	SetActorEnableCollision(bActivated);
}

void AST_Projectile::BeginPlay()
{
	Super::BeginPlay();

	CapsuleCollision->OnComponentHit.AddDynamic(this, &AST_Projectile::OnHit);
}

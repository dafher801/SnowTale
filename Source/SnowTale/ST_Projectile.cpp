
#include "ST_Projectile.h"
#include "ST_Unit.h"
#include "ST_AttackSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AST_Projectile::AST_Projectile()
{
 	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleCollision->SetConstraintMode(EDOFMode::Type::XYPlane);
	CapsuleCollision->GetBodyInstance()->MassScale = 0.0f;
	RootComponent = CapsuleCollision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Direction = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction"));
	Direction->SetupAttachment(RootComponent);

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->SetupAttachment(RootComponent);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->ProjectileGravityScale = 0.0f;
}

void AST_Projectile::Init(FVector SpawnLocation, FRotator SpawnRotation)
{
	SetActorLocation(SpawnLocation);
	SetActorRotation(SpawnRotation + RotationRevisionCalculation);

	Damage = Cast<AST_Unit>(GetInstigator())->GetCurrentStatus().ATK;

	MaxMovementDistance = Cast<AST_Unit>(GetInstigator())->GetCurrentStatus().Range;

	CurrentMovementDistance = 0.0f;

	Movement->Velocity = GetActorRotation().Vector() * Movement->MaxSpeed;
	Movement->Velocity.Z = 0.0f;

	SetActivated(true);

	if (IsValid(ProjectileInitSound))
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ProjectileInitSound, GetActorLocation());
}

void AST_Projectile::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);

	if ((CurrentMovementDistance += (DeltaTime * Movement->MaxSpeed)) > MaxMovementDistance)
		SetActivated(false);
}

void AST_Projectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Damage = Cast<AST_Unit>(GetInstigator())->GetCurrentStatus().ATK;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
		OnHitParticleSystem, GetActorLocation(), GetActorRotation());

	UGameplayStatics::ApplyDamage(OtherActor, Damage, 
		Cast<AST_Unit>(GetInstigator())->GetController(), this, NULL);

	SetActivated(false);

	if (IsValid(ProjectileOnHitSound))
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ProjectileOnHitSound, GetActorLocation());
}

bool AST_Projectile::IsActivated() const
{
	return bActivated;
}

void AST_Projectile::SetActivated(bool Activated)
{
	bActivated = Activated;

	SetActorHiddenInGame(!bActivated);
	SetActorTickEnabled(bActivated);
	SetActorEnableCollision(bActivated);

	Particle->SetActive(bActivated);
	Movement->SetActive(bActivated);
}

UProjectileMovementComponent* AST_Projectile::GetMovement() const
{
	return Movement;
}

void AST_Projectile::BeginPlay()
{
	Super::BeginPlay();

	SetActivated(false);

	CapsuleCollision->OnComponentHit.AddDynamic(this, &AST_Projectile::OnHit);
}

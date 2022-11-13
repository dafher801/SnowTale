
#include "ST_Bomb.h"
#include "Components/ShapeComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

AST_Bomb::AST_Bomb()
{
 	PrimaryActorTick.bCanEverTick = true;

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Paritcle"));
	Particle->SetupAttachment(RootComponent);
}

void AST_Bomb::Init(FVector SpawnLocation, FRotator SpawnRotation)
{
	SetActorLocation(SpawnLocation);
	SetActorRotation(SpawnRotation);

	SetActivated(true);
}

void AST_Bomb::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);

	AddFloorScale();
}

void AST_Bomb::Attack()
{
	if (IsValid(AttackSound))
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), AttackSound, GetActorLocation());

	if (IsValid(ParticleSystem))
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(GetActorLocation() + ParticleLocationRevision);
		SpawnTransform.SetRotation((GetActorRotation() + ParticleRotationRevision).Quaternion());
		SpawnTransform.SetScale3D(ParticleScaleRevision);

		Particle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, SpawnTransform);

		Particle->Activate();

		FTimerHandle Timer;

		GetWorldTimerManager().SetTimer(Timer, this,
			&AST_Bomb::DeactivateParticle, TimeForDeactivateParticle, false);

		if (bOverlapPlayer)
		{
			UGameplayStatics::ApplyDamage(UGameplayStatics::GetPlayerPawn(
				GetWorld(), 0), Damage, GetInstigator()->GetController(), this, NULL);
		}
	}

	SetActivated(false);
}

void AST_Bomb::DeactivateParticle()
{
	Particle->Deactivate();
}

bool AST_Bomb::GetActivated() const
{
	return bActivated;
}

void AST_Bomb::SetActivated(bool Activated)
{
	bActivated = Activated;

	SetActorHiddenInGame(!bActivated);
	SetActorTickEnabled(bActivated);
	SetActorEnableCollision(bActivated);
}

void AST_Bomb::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
		bOverlapPlayer = true;
}

void AST_Bomb::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player"))
		bOverlapPlayer = false;
}

void AST_Bomb::BeginPlay()
{
	Super::BeginPlay();

	SetActivated(false);

	BombShape->OnComponentBeginOverlap.AddDynamic(this, &AST_Bomb::OnOverlapBegin);
	BombShape->OnComponentEndOverlap.AddDynamic(this, &AST_Bomb::OnOverlapEnd);
}


#include "ST_InteractiveActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

AST_InteractiveActor::AST_InteractiveActor()
{
 	PrimaryActorTick.bCanEverTick = true;

	BoxOverlap = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxOverlap->SetConstraintMode(EDOFMode::Type::XYPlane);
	RootComponent = BoxOverlap;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetConstraintMode(EDOFMode::Type::XYPlane);
	Mesh->SetupAttachment(RootComponent);
}

void AST_InteractiveActor::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);
}

void AST_InteractiveActor::Interact(class AActor* OtherActor)
{
	if (IsValid(InteractSound))
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), InteractSound, GetActorLocation());
}

void AST_InteractiveActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Result)
{
	Interact(OtherActor);
}

bool AST_InteractiveActor::GetActivated() const
{
	return bActivated;
}

void AST_InteractiveActor::SetActivated(bool Activated)
{
	bActivated = Activated;

	SetActorHiddenInGame(!bActivated);
	SetActorTickEnabled(bActivated);
	SetActorEnableCollision(bActivated);
}

void AST_InteractiveActor::BeginPlay()
{
	Super::BeginPlay();

	SetActivated(true);

	BoxOverlap->OnComponentBeginOverlap.AddDynamic(this, &AST_InteractiveActor::OnOverlapBegin);
}

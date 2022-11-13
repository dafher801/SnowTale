
#include "ST_CameraActor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AST_CameraActor::AST_CameraActor()
{
 	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootScene);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void AST_CameraActor::BeginPlay()
{
	Super::BeginPlay();
}

void AST_CameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

USpringArmComponent* AST_CameraActor::GetSpringArm() const
{
	return SpringArm;
}

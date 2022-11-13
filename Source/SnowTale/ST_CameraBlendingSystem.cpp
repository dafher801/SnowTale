
#include "ST_CameraBlendingSystem.h"
#include "ST_CameraActor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

UST_CameraBlendingSystem::UST_CameraBlendingSystem()
	: CurrentCameraIndex(0)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UST_CameraBlendingSystem::RotateLeft()
{
	CurrentCameraIndex--;

	if (CurrentCameraIndex < 0)
		CurrentCameraIndex = CameraNum - 1;

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->
		SetViewTargetWithBlend(CameraActorArray[CurrentCameraIndex], CameraBlendTime);
}

void UST_CameraBlendingSystem::RotateRight()
{
	CurrentCameraIndex++;

	if (CurrentCameraIndex >= CameraNum)
		CurrentCameraIndex = 0;

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->
		SetViewTargetWithBlend(CameraActorArray[CurrentCameraIndex], CameraBlendTime);
}

void UST_CameraBlendingSystem::BeginPlay()
{
	Super::BeginPlay();

	float CameraRotationYaw = 0.0f;

	if (IsValid(CameraActorClass))
	{
		FAttachmentTransformRules AttachmentTransformRules = { EAttachmentRule::KeepRelative, true };

		for (int i = 0; i < CameraNum; i++)
		{
			CameraActorArray.Add(GetWorld()->SpawnActor<AST_CameraActor>(CameraActorClass));
			CameraActorArray[i]->GetSpringArm()->SetWorldRotation(FRotator(-45.0f, CameraRotationYaw, 0.0f));
			CameraRotationYaw += CameraAngle;

			CameraActorArray[i]->AttachToComponent(this, AttachmentTransformRules);
		}

		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTarget(CameraActorArray[CurrentCameraIndex]);
	}
}

void UST_CameraBlendingSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

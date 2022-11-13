
#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ST_CameraBlendingSystem.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SNOWTALE_API UST_CameraBlendingSystem : public USceneComponent
{
	GENERATED_BODY()

public:	

	UST_CameraBlendingSystem();

public:

	void RotateLeft();

	void RotateRight();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
		TArray<class AST_CameraActor*> CameraActorArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
		TSubclassOf<class AST_CameraActor> CameraActorClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
		int CameraNum;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
		float CameraAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
		float CameraBlendTime;

	int CurrentCameraIndex;

};

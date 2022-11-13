
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ST_CameraActor.generated.h"

UCLASS()
class SNOWTALE_API AST_CameraActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AST_CameraActor();

public:

	virtual void Tick(float DeltaTime) override;

	class USpringArmComponent* GetSpringArm() const;

protected:

	virtual void BeginPlay() override;

protected:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
		class USceneComponent* RootScene;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
		class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
		class UCameraComponent* Camera;

};

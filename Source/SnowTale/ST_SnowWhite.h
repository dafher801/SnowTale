
#pragma once

#include "CoreMinimal.h"
#include "ST_Unit.h"
#include "Containers/Array.h"
#include "ST_SnowWhite.generated.h"

UCLASS()
class SNOWTALE_API AST_SnowWhite : public AST_Unit
{
	GENERATED_BODY()

public:

	AST_SnowWhite();

public:

	virtual void Tick(float DeltaTime) override;

	virtual void LookAtTarget(FVector TargetLocation = FVector::ZeroVector) override;

	virtual void Move(FVector MoveVector = FVector::ZeroVector) override;

	virtual void BeginAttack() override;
	virtual void Attack() override;
	virtual void ExitAttack() override;

	void AcquireItem(class AST_Item* Item);

	void Heal(FKey Key);

	void InputForward(float NewForwardValue);
	void InputRight(float NewRightValue);

	void PressedLeftMouse(FKey Key);
	void ReleasedLeftMouse(FKey Key);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	virtual void BeginPlay() override;

protected:

	TArray<TArray<class AST_Item*>> ItemArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
		class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Camera")
		class UCameraComponent* Camera;

	float CurrentForwardValue;
	float CurrentRightValue;

	bool bPressedLeftMouse;
	float PressedTimeLeftMouse;

	FVector WorldDirection;
	
};

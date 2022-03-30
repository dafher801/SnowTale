
#pragma once

#include "CoreMinimal.h"
#include "ST_Unit.h"
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

	void InputForward(float NewForwardValue);
	void InputRight(float NewRightValue);

	void PressedLeftMouse(FKey key);
	void ReleasedLeftMouse(FKey key);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	virtual void BeginPlay() override;

protected:

	float CurrentForwardValue;
	float CurrentRightValue;

	bool bPressedLeftMouse;
	float PressedTimeLeftMouse;

	FVector WorldDirection;
	
};

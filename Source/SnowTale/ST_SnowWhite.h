
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

	void Invincible();

	void AcquireItem(class AST_Item* Item);

	void Heal(FKey Key);

	void ActiveInvincible();
	void DeactiveInvincible();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	void InputForward(float NewForwardValue);
	void InputRight(float NewRightValue);

	void PressedLeftMouse(FKey Key);
	void ReleasedLeftMouse(FKey Key);

	void PressedRightMouse(FKey Key);
	void ReleasedRightMouse(FKey Key);

protected:

	virtual void BeginPlay() override;

protected:

	TArray<TArray<class AST_Item*>> ItemArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
		class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Camera")
		class UCameraComponent* Camera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MP Amount")
		float InvincibeMPConsumptionPerTick;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MP Amount")
		float MPRecoveryAmountPerTick;

	float CurrentForwardValue;
	float CurrentRightValue;

	bool bPressedLeftMouse;
	float PressedTimeLeftMouse;

	FVector WorldDirection;
	
};

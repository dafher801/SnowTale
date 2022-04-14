
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ST_StatusData.h"
#include "ST_Unit.generated.h"

UCLASS()
class SNOWTALE_API AST_Unit : public ACharacter
{
	GENERATED_BODY()

public:

	AST_Unit();

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void LookAtTarget(FVector TargetLocation);

	virtual void Move(FVector TargetLocation);
	void ExitMove();

	virtual void BeginAttack();
	virtual void Attack();
	virtual void ExitAttack();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	FST_Status GetBaseStatus() const;
	FST_Status GetCurrentStatus() const;

	bool GetActivated() const;
	void SetActivated(bool Activated);

	bool IsAttacking() const;

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY()
		class AST_AttackSystem* AttackSystem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackSystem")
		TSubclassOf<class AST_AttackSystem> AttackSystemClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
		class UWidgetComponent* HPBarWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		FST_Status BaseStatus;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		FST_Status CurrentStatus;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Calculation")
		FRotator RotationErrorCalculation;

	FRotator BodyRotation;

	float TimeElapsedSinceAttack;

	bool bActivated;

	bool bAttacking;

	bool bInvincible;

};

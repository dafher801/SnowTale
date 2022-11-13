
#pragma once

#include "CoreMinimal.h"
#include "ST_Unit.h"
#include "Containers/Array.h"
#include "ST_SnowWhite.generated.h"

DECLARE_DYNAMIC_DELEGATE(FAcquireHealItemDelegate);
DECLARE_DYNAMIC_DELEGATE(FUseHealItemDelegate);

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

	void AcquireHealItem(class AST_HealItem* HealItem);

	void UseHealItem(FKey Key);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	void InputForward(float NewForwardValue);
	void InputRight(float NewRightValue);

	void PressedLeftMouse(FKey Key);
	void ReleasedLeftMouse(FKey Key);

	void PressedRightMouse(FKey Key);
	void ReleasedRightMouse(FKey Key);

	void PressedSpaceBar(FKey Key);
	void ReleasedSpaceBar(FKey Key);

	void RotateCamera(FKey key);

	bool IsInvincible() const;
	void SetInvincible(bool Invincible);

	bool IsUsingLethalSkill() const;
	void SetUsingLethalSkill(bool UsingLethalSkill);

	void BeginInvincibleMontage();
	void ExitInvincibleMontage();

	void BeginLethalSkillMontage();

	void BeginLethalSkill();
	void ExitLethalSkill();

	void CompleteRotatingCamera();

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintReadWrite)
		FAcquireHealItemDelegate AcquireHealItemDelegate;

	UPROPERTY(BlueprintReadWrite)
		FUseHealItemDelegate UseHealItemDelegate;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
		TArray<class AST_HealItem*> HealItemArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
		class UST_CameraBlendingSystem* CameraBlendingSystem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
		float CameraRotatingTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect")
		class UParticleSystemComponent* InvincibleParticle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect")
		class UParticleSystemComponent* LethalSkillParticle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Invincible")
		float InvincibeMPConsumptionPerTick;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MP Amount")
		float MPRecoveryAmountPerTick;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LethalSkill")
		float LethalSkillRange;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LethalSkill")
		float LethalSkillDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LethalSkill")
		float LethalSkillMPAmount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound")
		class USoundWave* InvincibleSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound")
		class USoundWave* LethalSkillSound;

	UPROPERTY()
		class UST_SnowWhiteAnim* SnowWhiteAnim;

	float CurrentForwardValue;
	float CurrentRightValue;

	bool bPressedLeftMouse;
	float PressedTimeLeftMouse;

	bool bPressedRightMouse;

	bool bPressedSpaceBar;

	FVector WorldDirection;
	
	bool bInvincible;
	bool bUsingLethalSkill;

	FRotator CameraRotation;
	bool bRotatingCamera;

};

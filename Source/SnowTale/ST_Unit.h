
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

	// 각 유닛들이 매 프레임마다 실행되는 로직
	virtual void Tick(float DeltaTime) override;

	// 각 유닛들이 타겟을 바라보는 로직
	virtual void LookAtTarget(FVector VectorToTarget);

	// 각 유닛들이 움직이는 로직
	virtual void Move(FVector TargetLocation) {}

	// 각 유닛들의 공격 모션이 시작할 때
	virtual void BeginAttack();

	// 각 유닛들의 AttackSystem에 공격을 요청할 때
	virtual void Attack();

	// 각 유닛들의 공격 모션이 끝날 때
	virtual void ExitAttack();

	// 각 유닛들이 데미지를 받을 때
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FST_Status GetBaseStatus() const;
	FST_Status GetCurrentStatus() const;

	UFUNCTION(BlueprintCallable)
		float GetHPRatio() const;

	UFUNCTION(BlueprintCallable)
		float GetMPRatio() const;

	bool IsActivated() const;
	void SetActivated(bool Activated);

	bool IsStartingAttack() const;
	void ActiveStartingAttack();

	bool IsAttacking() const;
	void ActiveAttacking();

	bool IsEndingAttack() const;
	void ActiveEndingAttack();

	void DeactiveAttackAnim();

	bool IsDead() const;
	virtual void SetDead(bool Dead);

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY()
		class AST_AttackSystem* AttackSystem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackSystem")
		TSubclassOf<class AST_AttackSystem> AttackSystemClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
		class UWidgetComponent* UnitWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		FST_Status BaseStatus;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		FST_Status CurrentStatus;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Calculation")
		FRotator RotationRevisionCalculation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackAnim")
		float StartingAttackTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackAnim")
		float EndingAttackTime;

	FRotator BodyRotation;

	float TimeElapsedSinceAttack;

	bool bActivated;

	UPROPERTY(BlueprintReadWrite)
		bool bStartingAttack;

	UPROPERTY(BlueprintReadWrite)
		bool bAttacking;

	UPROPERTY(BlueprintReadWrite)
		bool bEndingAttack;

	UPROPERTY(BlueprintReadWrite)
		bool bDead;

	bool bDisappear;

};

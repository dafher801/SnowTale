
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

	// �� ���ֵ��� �� �����Ӹ��� ����Ǵ� ����
	virtual void Tick(float DeltaTime) override;

	// �� ���ֵ��� Ÿ���� �ٶ󺸴� ����
	virtual void LookAtTarget(FVector VectorToTarget);

	// �� ���ֵ��� �����̴� ����
	virtual void Move(FVector TargetLocation) {}

	// �� ���ֵ��� ���� ����� ������ ��
	virtual void BeginAttack();

	// �� ���ֵ��� AttackSystem�� ������ ��û�� ��
	virtual void Attack();

	// �� ���ֵ��� ���� ����� ���� ��
	virtual void ExitAttack();

	// �� ���ֵ��� �������� ���� ��
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

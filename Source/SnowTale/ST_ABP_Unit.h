
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ST_ABP_Unit.generated.h"

UCLASS()
class SNOWTALE_API UST_ABP_Unit : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UST_ABP_Unit();

public:

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

	virtual void PlayMontage(class UAnimMontage* Montage, float PlayRate = 1.0f);

	void PlayAttackStartMontage(float AttackSpeed);
	void PlayAttackExitMontage(float AttackSpeed);

	void PlayDeadMontage();

	void DeactiveUnit();

protected:

	UFUNCTION()
		virtual void AnimNotify_StartAttack();

	UFUNCTION()
		virtual void AnimNotify_LoopAttack();

	UFUNCTION()
		virtual void AnimNotify_ExitAttack();

	UFUNCTION()
		void AnimNotify_Dead();

	UFUNCTION()
		void AnimNotify_Disappear();

protected:

	UPROPERTY()
		class AST_Unit* Unit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim")
		class UAnimMontage* AttackStartMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim")
		class UAnimMontage* AttackLoopMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim")
		class UAnimMontage* AttackEndMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim")
		class UAnimMontage* DeadMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Move")
		float CurrentMoveSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Move")
		bool bMoving;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dead")
		float DeadTime;

};

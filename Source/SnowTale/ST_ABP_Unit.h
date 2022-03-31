
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

	virtual void NativeUpdateAnimation(float DeltaTime) override;

	void PlayAttackMontage();

protected:

	UFUNCTION()
		void AnimNotify_Attack();

	UFUNCTION()
		void AnimNotify_ExitAttack();

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attack")
		class UAnimMontage* AttackMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Move")
		float CurrentMoveSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Move")
		bool bMoving;

};

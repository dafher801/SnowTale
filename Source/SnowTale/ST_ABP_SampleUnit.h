
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ST_ABP_SampleUnit.generated.h"

UCLASS()
class SNOWTALE_API UST_ABP_SampleUnit : public UAnimInstance
{
	GENERATED_BODY()

public:

	UST_ABP_SampleUnit();
		
public:

	void PlayAttackMontage();

protected:

	UFUNCTION()
		void AnimNotify_Attack();

	UFUNCTION()
		void AnimNotify_ExitAttack();

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attack")
		class UAnimMontage* AttackMontage;
	
};

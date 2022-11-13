
#pragma once

#include "CoreMinimal.h"
#include "ST_ABP_Unit.h"
#include "ST_QueenAnim.generated.h"

UCLASS()
class SNOWTALE_API UST_QueenAnim : public UST_ABP_Unit
{
	GENERATED_BODY()

public:

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

	void PlayPatternMontage();
	void ExitPatternMontage();

protected:

	UFUNCTION()
		void AnimNotify_StartPattern();

	UFUNCTION()
		void AnimNotify_LoopPattern();

	UFUNCTION()
		void AnimNotify_EndPattern();

protected:

	UPROPERTY()
		class AST_Queen* Queen;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim")
		class UAnimMontage* PatternStartMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim")
		class UAnimMontage* PatternLoopMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim")
		class UAnimMontage* PatternEndMontage;
	
};


#pragma once

#include "CoreMinimal.h"
#include "ST_ABP_Unit.h"
#include "ST_SnowWhiteAnim.generated.h"

UCLASS()
class SNOWTALE_API UST_SnowWhiteAnim : public UST_ABP_Unit
{
	GENERATED_BODY()

public:

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

	void PlayInvincibleStartMontage();
	void ExitInvincibleMontage();

	void PlayLethalSkillMontage();
	void ExitLethalSkillMontage();

protected:

	UFUNCTION()
		void AnimNotify_StartInvincible();

	UFUNCTION()
		void AnimNotify_LoopInvincible();

	UFUNCTION()
		void AnimNotify_EndInvincible();

	UFUNCTION()
		void AnimNotify_StartLethalSkill();

	UFUNCTION()
		void AnimNotify_ExecuteLethalSkill();

	UFUNCTION()
		void AnimNotify_EndLethalSkill();

protected:

	UPROPERTY()
		class AST_SnowWhite* SnowWhite;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim")
		class UAnimMontage* InvincibleStartMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim")
		class UAnimMontage* InvincibleLoopMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim")
		class UAnimMontage* InvincibleEndMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim")
		class UAnimMontage* LethalSkillMontage;
	
};

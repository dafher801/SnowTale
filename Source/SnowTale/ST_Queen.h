
#pragma once

#include "CoreMinimal.h"
#include "ST_Enemy.h"
#include "ST_PatternData.h"
#include "ST_Queen.generated.h"

UCLASS()
class SNOWTALE_API AST_Queen : public AST_Enemy
{
	GENERATED_BODY()

public:

	AST_Queen();

public:

	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	void StartPattern();

	void ExecutePattern();

	void EndPattern();

	bool GetActivePattern() const;
	void SetActivePattern(bool ActivePattern);

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pattern")
		TArray<FST_Pattern> PatternArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect")
		class UParticleSystemComponent* ActivePatternParticle;

	UPROPERTY()
		class UST_QueenAnim* QueenAnim;

	bool bActivePattern;

	int CurrentPatternIndex;

	float TotalPatternDurationTime;

	float TotalPatternWaitingTime;

	float TotalPatternCycleTime;

};

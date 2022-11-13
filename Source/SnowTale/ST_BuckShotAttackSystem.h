
#pragma once

#include "CoreMinimal.h"
#include "ST_LongRangeAttackSystem.h"
#include "ST_BuckShotAttackSystem.generated.h"

UCLASS()
class SNOWTALE_API AST_BuckShotAttackSystem : public AST_LongRangeAttackSystem
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	virtual void Attack() override;

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
		int NumberWhenAttack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
		float SpreadAngle;
	
};

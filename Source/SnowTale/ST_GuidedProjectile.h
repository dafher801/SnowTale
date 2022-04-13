
#pragma once

#include "CoreMinimal.h"
#include "ST_Projectile.h"
#include "ST_GuidedProjectile.generated.h"

UCLASS()
class SNOWTALE_API AST_GuidedProjectile : public AST_Projectile
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GuidedProjectile")
		float TurningLimitPerTick;
	
};

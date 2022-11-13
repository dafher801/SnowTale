
#pragma once

#include "CoreMinimal.h"
#include "ST_Projectile.h"
#include "ST_CircularPatternBullet.generated.h"

UCLASS()
class SNOWTALE_API AST_CircularPatternBullet : public AST_Projectile
{
	GENERATED_BODY()

public:

	virtual void Init(FVector SpawnLocation, FRotator SpawnRotation) override;

	virtual void Tick(float DeltaTime) override;
	
};


#pragma once

#include "CoreMinimal.h"
#include "ST_Projectile.h"
#include "ST_SpinningPatternBullet.generated.h"

UCLASS()
class SNOWTALE_API AST_SpinningPatternBullet : public AST_Projectile
{
	GENERATED_BODY()

public:

	virtual void Init(FVector SpawnLocation, FRotator SpawnRotation) override;

	virtual void Tick(float DeltaTime) override;

	void SetBulletCenter(class AST_SpinningPatternCenter* SpinningPatternCenter);

protected:

	class AST_SpinningPatternCenter* SpinningCenter;
	
};

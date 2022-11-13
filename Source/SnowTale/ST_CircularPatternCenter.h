
#pragma once

#include "CoreMinimal.h"
#include "ST_Projectile.h"
#include "ST_CircularPatternCenter.generated.h"

UCLASS()
class SNOWTALE_API AST_CircularPatternCenter : public AST_Projectile
{
	GENERATED_BODY()

public:

	virtual void Init(FVector SpawnLocation, FRotator SpawnRotation) override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetActivated(bool Activated) override;

	void Clear() const;

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpinningProjectile")
		TArray<class AST_CircularPatternBullet*> BulletArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpinningProjectile")
		TSubclassOf<class AST_CircularPatternBullet> SpinningBulletClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpinningProjectile")
		int SpinningBulletNum;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpinningProjectile")
		float Radius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpinningProjectile")
		float SpinPerTick;

	float Radian;

};

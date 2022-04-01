
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
		TArray<class AST_CircularPatternBullet*> BulletArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
		TSubclassOf<class AST_CircularPatternBullet> SpinningBulletClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
		int SpinningBulletNum;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
		float Radius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
		float SpinPerTick;

	float Radian;

};

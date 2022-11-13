
#pragma once

#include "CoreMinimal.h"
#include "ST_Projectile.h"
#include "ST_SpinningPatternCenter.generated.h"

UCLASS()
class SNOWTALE_API AST_SpinningPatternCenter : public AST_Projectile
{
	GENERATED_BODY()

public:

	virtual void Init(FVector SpawnLocation, FRotator SpawnRotation) override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetOwner(AActor* NewOwner) override;

	virtual void SetActivated(bool Activated) override;

	float GetRadius() const;

	float GetRotatingAmount() const;

	void Clear() const;

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpinningProjectile")
		TArray<class AST_SpinningPatternBullet*> BulletArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpinningProjectile")
		TSubclassOf<class AST_Projectile> SpinningBulletClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpinningProjectile")
		int SpinningBulletNum;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpinningProjectile")
		float Radius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpinningProjectile")
		float RotatingAmount;

	float Radian;

};

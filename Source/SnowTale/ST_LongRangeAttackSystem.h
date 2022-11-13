
#pragma once

#include "CoreMinimal.h"
#include "ST_AttackSystem.h"
#include "ST_LongRangeAttackSystem.generated.h"

UCLASS()
class SNOWTALE_API AST_LongRangeAttackSystem : public AST_AttackSystem
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	virtual void Attack() override;

	virtual void SetOwner(AActor* NewOwner) override;

	void SetSpawnLocation(FVector Location);

	void SetSpawnRotation(FRotator Rotation);

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
		TArray<class AST_Projectile*> ProjectileArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
		TSubclassOf<class AST_Projectile> ProjectileClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
		int MaxProjectileNum;

	int CurrentProjectileNum;

	FVector SpawnLocation;

	FRotator SpawnRotation;
	
};

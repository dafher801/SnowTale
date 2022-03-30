
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ST_EnemySpawner.generated.h"

UCLASS()
class SNOWTALE_API AST_EnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	

	AST_EnemySpawner();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SpawnEnemy();

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
		TArray<class AST_Enemy*> EnemyArray;

};

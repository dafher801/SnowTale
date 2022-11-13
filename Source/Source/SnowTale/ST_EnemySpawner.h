
#pragma once

#include "CoreMinimal.h"
#include "ST_InteractiveActor.h"
#include "ST_EnemySpawner.generated.h"

UCLASS()
class SNOWTALE_API AST_EnemySpawner : public AST_InteractiveActor
{
	GENERATED_BODY()
	
public:	

	AST_EnemySpawner();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		virtual void Interact(class AActor* OtherActor) override;

	UFUNCTION(BlueprintCallable)
		void SpawnEnemy();

	void DeadMonsterEvent();

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
		TArray<class AST_Enemy*> EnemyArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
		class AST_Portal* Portal;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interact")
		class AActor* Obstacle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect")
		class UParticleSystem* ObstacleExplosionParticleSystem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound")
		class USoundWave* ObstacleExplosionSound;

	UPROPERTY(BlueprintReadWrite)
		int EnemyNum;

	bool bSpawned;

};

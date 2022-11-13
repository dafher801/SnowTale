
#pragma once

#include "CoreMinimal.h"
#include "ST_Unit.h"
#include "ST_Enemy.generated.h"

UCLASS()
class SNOWTALE_API AST_Enemy : public AST_Unit
{
	GENERATED_BODY()

public:

	AST_Enemy();

public:

	virtual void Tick(float DeltaTime) override;

	virtual void LookAtTarget(FVector TargetLocation) override;

	virtual void Move(FVector TargetLocation) override;
	void ExitMove();
	
	virtual void BeginAttack() override;
	virtual void Attack() override;
	virtual void ExitAttack() override;

	float GetAccessibleDistanceToPlayer() const;

	bool IsVisibleFromPlayer() const;

	bool IsAccessible() const;

	void SetEnemySpawner(class AST_EnemySpawner* Spawner);

	virtual void SetDead(bool Dead) override;

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY()
		class ACharacter* Player;

	UPROPERTY()
		class UNavigationSystemV1* NavSystem;

	UPROPERTY()
		class AST_EnemySpawner* EnemySpawner;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float AccessibleDistanceToPlayer;
};

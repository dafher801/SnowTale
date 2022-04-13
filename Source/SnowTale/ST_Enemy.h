
#pragma once

#include "CoreMinimal.h"
#include "ST_Unit.h"
#include "ST_Enemy.generated.h"

UCLASS()
class SNOWTALE_API AST_Enemy : public AST_Unit
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	virtual void LookAtTarget(FVector TargetLocation) override;

	virtual void Move(FVector TargetLocation) override;
	
	virtual void BeginAttack() override;
	virtual void Attack() override;
	virtual void ExitAttack() override;

	UFUNCTION() 
		virtual void OnHit(class UPrimitiveComponent* OtherComp, class AActor* OtherActor,
			class UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit);

	float GetAccessibleDistanceToPlayer() const;

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY()
		class UNavigationSystemV1* NavSystem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float AccessibleDistanceToPlayer;
};

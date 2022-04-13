
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ST_Projectile.generated.h"

UCLASS()
class SNOWTALE_API AST_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	

	AST_Projectile();

public:

	virtual void Init(FVector SpawnLocation, FRotator SpawnRotation);

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void OnHit(class UPrimitiveComponent* OtherComp, class AActor* OtherActor,
			class UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit);

	bool GetActivated() const;
	virtual void SetActivated(bool Activated);

	class UProjectileMovementComponent* GetMovement() const;

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
		class UCapsuleComponent* CapsuleCollision;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
		class UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Helper")
		class UArrowComponent* Direction;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement")
		class UProjectileMovementComponent* Movement;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect")
		class UParticleSystem* AttackParticleSystem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Calculation")
		FRotator RotationErrorCalculation;

	int Damage;

	float MaxMovementDistance;
	float CurrentMovementDistance;

	bool bActivated;

};

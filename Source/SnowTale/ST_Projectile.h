
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

	// 발사체 생성시 실행
	virtual void Init(FVector SpawnLocation, FRotator SpawnRotation);

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void OnHit(class UPrimitiveComponent* HitComponent, AActor* OtherActor, 
			class UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	bool IsActivated() const;
	virtual void SetActivated(bool Activated);

	class UProjectileMovementComponent* GetMovement() const;

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
		class UCapsuleComponent* CapsuleCollision;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
		class UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Helper")
		class UArrowComponent* Direction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect")
		class UParticleSystemComponent* Particle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
		class UProjectileMovementComponent* Movement;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect")
		class UParticleSystem* ProjectileParticleSystem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect")
		class UParticleSystem* OnHitParticleSystem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound")
		class USoundWave* ProjectileInitSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound")
		class USoundWave* ProjectileOnHitSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Calculation")
		FRotator RotationRevisionCalculation;

	int Damage;

	float MaxMovementDistance;
	float CurrentMovementDistance;

	bool bActivated;

};

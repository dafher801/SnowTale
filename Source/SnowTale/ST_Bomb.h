
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ST_Bomb.generated.h"

UCLASS()
class SNOWTALE_API AST_Bomb : public AActor
{
	GENERATED_BODY()
	
public:

	AST_Bomb();

public:

	virtual void Init(FVector SpawnLocation = FVector::ZeroVector, FRotator SpawnRotation = FRotator::ZeroRotator);

	virtual void Tick(float DeltaTime) override;

	virtual void AddFloorScale() {}

	virtual void Attack();

	void DeactivateParticle();

	bool GetActivated() const;
	void SetActivated(bool Activated);

	UFUNCTION() 
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, 
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
				int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
		class UShapeComponent* BombShape;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect")
		class UParticleSystem* ParticleSystem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect")
		float TimeForDeactivateParticle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect")
		FVector ParticleLocationRevision;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect")
		FRotator ParticleRotationRevision;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect")
		FVector ParticleScaleRevision;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sprite")
		class UPaperSpriteComponent* AttackFloorSprite;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sprite")
		class UPaperSpriteComponent* WarningFloorSprite;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sprite")
		float FloorAddingScalePerTick;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
		float Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound")
		class USoundWave* AttackSound;

	UPROPERTY()
		class UParticleSystemComponent* Particle;

	bool bActivated;

	bool bOverlapPlayer;

};

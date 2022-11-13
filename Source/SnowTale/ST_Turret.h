
#pragma once

#include "CoreMinimal.h"
#include "ST_Enemy.h"
#include "ST_Turret.generated.h"

UCLASS()
class SNOWTALE_API AST_Turret : public AST_Enemy
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effect")
		class UParticleSystem* DestroyParticleSystem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound")
		class USoundWave* DestroySound;
	
};

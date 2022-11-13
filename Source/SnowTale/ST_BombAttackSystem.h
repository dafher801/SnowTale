
#pragma once

#include "CoreMinimal.h"
#include "ST_AttackSystem.h"
#include "ST_BombAttackSystem.generated.h"

UCLASS()
class SNOWTALE_API AST_BombAttackSystem : public AST_AttackSystem
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	virtual void Attack();

	virtual void SetOwner(AActor* NewOwner) override;

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bomb")
		TArray<class AST_Bomb*> BombArray;

};

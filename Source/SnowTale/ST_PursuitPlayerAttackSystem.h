
#pragma once

#include "CoreMinimal.h"
#include "ST_BombAttackSystem.h"
#include "ST_PursuitPlayerAttackSystem.generated.h"

UCLASS()
class SNOWTALE_API AST_PursuitPlayerAttackSystem : public AST_BombAttackSystem
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	virtual void Attack() override;

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY()
		class ACharacter* Player;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bomb")
		TSubclassOf<class AST_Bomb> BombClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bomb")
		float RandomDistance;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bomb")
		int MaxBombNum;

	int CurrentBombNum;

};

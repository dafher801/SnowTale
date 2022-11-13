
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ST_SnowTaleGameModeBase.generated.h"

UCLASS()
class SNOWTALE_API AST_SnowTaleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void StartPlay() override;

	UFUNCTION(BlueprintNativeEvent)
		void GameOver() const;

	virtual void GameOver_Implementation() const;

	void GameClear() const;

	const TArray<class AST_Enemy*>& GetEnemyArray() const;

	void SetFightBoss(bool FightBoss);

protected:

	TArray<class AST_Enemy*> EnemyArray;

	UPROPERTY(BlueprintReadWrite)
		bool bFightBoss;
	
};

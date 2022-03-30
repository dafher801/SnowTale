
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ST_EnemyController.generated.h"

UCLASS()
class SNOWTALE_API AST_EnemyController : public AAIController
{
	GENERATED_BODY()

public:

	AST_EnemyController();

public:

	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(class APawn* InPawn) override;

public:

	static const FName VisibleFromTargetKey;

	static const FName TargetPosKey;

	static const FName MovableKey;

	static const FName AssailableKey;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
		class UBlackboardData* BlackboardData;
	
};

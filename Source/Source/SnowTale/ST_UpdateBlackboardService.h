
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ST_UpdateBlackboardService.generated.h"

UCLASS()
class SNOWTALE_API UST_UpdateBlackboardService : public UBTService
{
	GENERATED_BODY()

public:

	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData);

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:

	void UpdatePlayerLocation(UBehaviorTreeComponent& OwnerComp);

	void UpdateVisibleFromTarget(UBehaviorTreeComponent& OwnerComp);

	void UpdateMovable(UBehaviorTreeComponent& OwnerComp);

	void UpdateAssailable(UBehaviorTreeComponent& OwnerComp);

protected:

	UPROPERTY()
		class AST_Enemy* Owner;

	UPROPERTY()
		class APawn* Player;

	FVector PlayerLocation;

	bool bVisibleFromTarget;

	bool bAccessibleToPlayer;

	bool bMovable;

	bool bAssailable;

};

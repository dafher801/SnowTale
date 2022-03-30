
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ST_BTS_UpdateBlackboard.generated.h"

UCLASS()
class SNOWTALE_API UST_BTS_UpdateBlackboard : public UBTService
{
	GENERATED_BODY()

public:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:

	void UpdatePlayerLocation(UBehaviorTreeComponent& OwnerComp);

	void UpdateVisibleFromTarget(UBehaviorTreeComponent& OwnerComp);

	bool IsAccessibleToPlayer(UBehaviorTreeComponent& OwnerComp);

	void UpdateMovable(UBehaviorTreeComponent& OwnerComp);

	void UpdateAssailable(UBehaviorTreeComponent& OwnerComp);

protected:

	class AST_Enemy* Owner;

	FVector PlayerLocation;

	bool bVisibleFromTarget;

	bool bAccessibleToPlayer;

	bool bMovable;

	bool bAssailable;

};

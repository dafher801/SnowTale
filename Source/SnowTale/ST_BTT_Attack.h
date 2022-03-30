
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ST_BTT_Attack.generated.h"

UCLASS()
class SNOWTALE_API UST_BTT_Attack : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UST_BTT_Attack();

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaTime) override;
	
};

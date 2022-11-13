
#include "ST_BTT_Stop.h"
#include "ST_EnemyController.h"
#include "ST_Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

EBTNodeResult::Type UST_BTT_Stop::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Cast<AST_Enemy>(OwnerComp.GetAIOwner()->GetCharacter())->ExitMove();

	return EBTNodeResult::Succeeded;
}

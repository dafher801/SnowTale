
#include "ST_BTT_Attack.h"
#include "ST_EnemyController.h"
#include "ST_Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"

UST_BTT_Attack::UST_BTT_Attack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UST_BTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AST_Enemy* AI = Cast<AST_Enemy>(OwnerComp.GetAIOwner()->GetCharacter());
	
	EBTNodeResult::Type NodeResultType = AI->IsAttacking() ? EBTNodeResult::Failed : EBTNodeResult::InProgress;

	AI->BeginAttack();

	return NodeResultType;
}

void UST_BTT_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaTime)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaTime);

	AST_Enemy* AI = Cast<AST_Enemy>(OwnerComp.GetAIOwner()->GetCharacter());

	AI->LookAtTarget(OwnerComp.GetBlackboardComponent()->GetValueAsVector(AST_EnemyController::TargetPosKey));

	if (!AI->IsAttacking())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

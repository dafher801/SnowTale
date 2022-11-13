
#include "ST_BTT_Move.h"
#include "ST_EnemyController.h"
#include "ST_Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UST_BTT_Move::UST_BTT_Move()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UST_BTT_Move::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	FVector TargetPosition = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AST_EnemyController::TargetPosKey);

	Cast<AST_Enemy>(OwnerComp.GetAIOwner()->GetCharacter())->Move(TargetPosition);

	return EBTNodeResult::Succeeded;
}

void UST_BTT_Move::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaTime)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaTime);

	AST_Enemy* AI = Cast<AST_Enemy>(OwnerComp.GetAIOwner()->GetCharacter());

	if (IsVisibleFromTarget(OwnerComp) && !IsAccessibleToTarget(OwnerComp))
	{
		AI->ExitMove();

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	FVector TargetPosition = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AST_EnemyController::TargetPosKey);

	AI->Move(TargetPosition);
}

bool UST_BTT_Move::IsVisibleFromTarget(UBehaviorTreeComponent& OwnerComp)
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsBool(AST_EnemyController::VisibleFromTargetKey);
}

bool UST_BTT_Move::IsAccessibleToTarget(UBehaviorTreeComponent& OwnerComp)
{
	AST_Enemy* AI = Cast<AST_Enemy>(OwnerComp.GetAIOwner()->GetCharacter());
	FVector TargetPosition = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AST_EnemyController::TargetPosKey);

	return AI->GetAccessibleDistanceToPlayer() < FVector::Dist(AI->GetActorLocation(), TargetPosition);
}

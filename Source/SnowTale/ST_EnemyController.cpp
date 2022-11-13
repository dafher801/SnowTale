
#include "ST_EnemyController.h"
#include "ST_Enemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

const FName AST_EnemyController::TargetPosKey = TEXT("PlayerLocation");

const FName AST_EnemyController::VisibleFromTargetKey = TEXT("VisibleFromTarget");

const FName AST_EnemyController::MovableKey = TEXT("Movable");

const FName AST_EnemyController::AssailableKey = TEXT("Assailable");

AST_EnemyController::AST_EnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AST_EnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AST_EnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BlackboardData, Blackboard))
	{
		RunBehaviorTree(BehaviorTree);
	}
}

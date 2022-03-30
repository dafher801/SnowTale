
#include "ST_BTS_UpdateBlackboard.h"
#include "ST_EnemyController.h"
#include "ST_Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void UST_BTS_UpdateBlackboard::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	Owner = Cast<AST_Enemy>(OwnerComp.GetAIOwner()->GetCharacter());
	PlayerLocation = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();

	UpdatePlayerLocation(OwnerComp);
	UpdateVisibleFromTarget(OwnerComp);
	UpdateMovable(OwnerComp);
	UpdateAssailable(OwnerComp);
}

void UST_BTS_UpdateBlackboard::UpdatePlayerLocation(UBehaviorTreeComponent& OwnerComp)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(AST_EnemyController::TargetPosKey, PlayerLocation);
}

void UST_BTS_UpdateBlackboard::UpdateVisibleFromTarget(UBehaviorTreeComponent& OwnerComp)
{
	if (!Owner->GetActivated())
		return;

	FHitResult HitResult;
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);

	bVisibleFromTarget = !(GetWorld()->LineTraceSingleByObjectType(
		HitResult, Owner->GetActorLocation(), PlayerLocation, CollisionObjectQueryParams));

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(
		AST_EnemyController::VisibleFromTargetKey, bVisibleFromTarget);
}

bool UST_BTS_UpdateBlackboard::IsAccessibleToPlayer(UBehaviorTreeComponent& OwnerComp)
{
	float DistanceFromPlayer = FVector::Distance(Owner->GetActorLocation(), PlayerLocation);

	return Owner->GetAccessibleDistanceToPlayer() < DistanceFromPlayer;
}

void UST_BTS_UpdateBlackboard::UpdateMovable(UBehaviorTreeComponent& OwnerComp)
{
	bMovable = Owner->GetActivated() && (IsAccessibleToPlayer(OwnerComp) || !bVisibleFromTarget);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AST_EnemyController::MovableKey, bMovable);
}

void UST_BTS_UpdateBlackboard::UpdateAssailable(UBehaviorTreeComponent& OwnerComp)
{
	bAssailable = Owner->GetActivated() && bVisibleFromTarget;

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AST_EnemyController::AssailableKey, bAssailable);
}
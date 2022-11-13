
#include "ST_UpdateBlackboardService.h"
#include "ST_EnemyController.h"
#include "ST_Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void UST_UpdateBlackboardService::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	Owner = Cast<AST_Enemy>(SearchData.OwnerComp.GetAIOwner()->GetCharacter());
}

void UST_UpdateBlackboardService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!IsValid(Player))
		return;

	PlayerLocation = Player->GetActorLocation();

	UpdatePlayerLocation(OwnerComp);
	UpdateVisibleFromTarget(OwnerComp);
	UpdateMovable(OwnerComp);
	UpdateAssailable(OwnerComp);
}

void UST_UpdateBlackboardService::UpdatePlayerLocation(UBehaviorTreeComponent& OwnerComp)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(AST_EnemyController::TargetPosKey, PlayerLocation);
}

void UST_UpdateBlackboardService::UpdateVisibleFromTarget(UBehaviorTreeComponent& OwnerComp)
{
	if (!Owner->IsActivated())
		return;

	FHitResult HitResult;
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);

	bVisibleFromTarget = !(GetWorld()->LineTraceSingleByObjectType(
		HitResult, Owner->GetActorLocation(), PlayerLocation, CollisionObjectQueryParams));

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(
		AST_EnemyController::VisibleFromTargetKey, bVisibleFromTarget);
}

void UST_UpdateBlackboardService::UpdateMovable(UBehaviorTreeComponent& OwnerComp)
{
	bMovable = Owner->IsActivated() && (!bVisibleFromTarget || 
		Owner->GetAccessibleDistanceToPlayer() < FVector::Distance(Owner->GetActorLocation(), PlayerLocation));

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AST_EnemyController::MovableKey, bMovable);
}

void UST_UpdateBlackboardService::UpdateAssailable(UBehaviorTreeComponent& OwnerComp)
{
	bAssailable = Owner->IsActivated() && bVisibleFromTarget;

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AST_EnemyController::AssailableKey, bAssailable);
}
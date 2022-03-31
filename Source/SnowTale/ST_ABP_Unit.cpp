
#include "ST_ABP_Unit.h"
#include "ST_Unit.h"

UST_ABP_Unit::UST_ABP_Unit()
	: AttackMontage(nullptr)
	, CurrentMoveSpeed(0.0f)
	, bMoving(false)
{

}

void UST_ABP_Unit::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	APawn* Pawn = TryGetPawnOwner();

	if (IsValid(Pawn))
	{
		CurrentMoveSpeed = Pawn->GetVelocity().Size();

		bMoving = CurrentMoveSpeed > 0.0f;
	}
}

void UST_ABP_Unit::PlayAttackMontage()
{
	AST_Unit* Unit = Cast<AST_Unit>(TryGetPawnOwner());

	if (IsValid(Unit) && AttackMontage && !Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, Unit->GetCurrentStatus().AttackSpeed * AttackMontage->GetPlayLength());
	}
}

void UST_ABP_Unit::AnimNotify_Attack()
{
	AST_Unit* Unit = Cast<AST_Unit>(TryGetPawnOwner());

	if (IsValid(Unit))
		Unit->Attack();
}

void UST_ABP_Unit::AnimNotify_ExitAttack()
{
	AST_Unit* Unit = Cast<AST_Unit>(TryGetPawnOwner());

	if (IsValid(Unit))
		Unit->ExitAttack();
}


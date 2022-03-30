
#include "ST_ABP_SampleUnit.h"
#include "ST_Unit.h"

UST_ABP_SampleUnit::UST_ABP_SampleUnit()
	: AttackMontage(nullptr)
{

}

void UST_ABP_SampleUnit::PlayAttackMontage()
{
	AST_Unit* Unit = Cast<AST_Unit>(TryGetPawnOwner());

	if (IsValid(Unit) && AttackMontage && !Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, Unit->GetCurrentStatus().AttackSpeed * AttackMontage->GetPlayLength());
	}
}

void UST_ABP_SampleUnit::AnimNotify_Attack()
{
	AST_Unit* Unit = Cast<AST_Unit>(TryGetPawnOwner());

	if (IsValid(Unit))
		Unit->Attack();
}

void UST_ABP_SampleUnit::AnimNotify_ExitAttack()
{
	AST_Unit* Unit = Cast<AST_Unit>(TryGetPawnOwner());

	if (IsValid(Unit))
		Unit->ExitAttack();
}

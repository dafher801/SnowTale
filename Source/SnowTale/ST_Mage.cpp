
#include "ST_Mage.h"

void AST_Mage::BeginAttack()
{
	ActiveAttacking();

	FTimerHandle Timer;

	GetWorldTimerManager().SetTimer(Timer, this, &AST_Unit::ActiveAttacking, StartingAttackTime, false);
}

void AST_Mage::Attack()
{
	if (bAttacking && 1.0f / CurrentStatus.AttackSpeed - TimeElapsedSinceAttack <= 0)
	{
		Super::Attack();

		TimeElapsedSinceAttack = 0.0f;
	}
}

void AST_Mage::ExitAttack()
{
	if (IsAttacking())
	{
		ActiveEndingAttack();

		FTimerHandle Timer;

		GetWorldTimerManager().SetTimer(Timer, this, &AST_Unit::DeactiveAttackAnim, EndingAttackTime, false);
	}
	else
		DeactiveAttackAnim();
}

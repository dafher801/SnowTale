
#include "ST_ABP_Unit.h"
#include "ST_Unit.h"
#include "Kismet/GameplayStatics.h"

UST_ABP_Unit::UST_ABP_Unit()
	: AttackStartMontage(nullptr)
	, CurrentMoveSpeed(0.0f)
	, bMoving(false)
{
}

void UST_ABP_Unit::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Unit = Cast<AST_Unit>(TryGetPawnOwner());
}

void UST_ABP_Unit::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (IsValid(Unit))
	{
		CurrentMoveSpeed = Unit->GetVelocity().Size();

		bMoving = CurrentMoveSpeed > 0.0f;
	}
}

void UST_ABP_Unit::PlayMontage(UAnimMontage* Montage, float PlayRate)
{
	if (IsValid(Unit) && IsValid(Montage))
	{
		Montage_Play(Montage, PlayRate);
	}
}

void UST_ABP_Unit::PlayAttackStartMontage(float AttackSpeed)
{
	if (IsValid(AttackStartMontage))
	{
		PlayMontage(AttackStartMontage, AttackSpeed * AttackStartMontage->GetPlayLength());
	}
}

void UST_ABP_Unit::PlayAttackExitMontage(float AttackSpeed)
{
	if (!IsValid(Unit))
		return;

	if (Montage_IsPlaying(AttackLoopMontage))
	{
		Unit->ActiveEndingAttack();
	}
	else
	{
		Montage_Stop(Montage_GetPosition(GetCurrentActiveMontage()));
		Unit->DeactiveAttackAnim();
	}
}

void UST_ABP_Unit::PlayDeadMontage()
{
	if (IsValid(DeadMontage) && !Montage_IsPlaying(DeadMontage))
		PlayMontage(DeadMontage);

	if (DeadTime >= 0.0f)
	{
		FTimerHandle Timer;

		Unit->GetWorldTimerManager().SetTimer(Timer, this, &UST_ABP_Unit::DeactiveUnit, DeadTime, false);
	}
}

void UST_ABP_Unit::DeactiveUnit()
{
	if (IsValid(Unit))
	{
		Unit->SetDead(true);
		Unit->SetActivated(false);
	}
}

void UST_ABP_Unit::AnimNotify_StartAttack()
{
	if (!IsValid(Unit))
		return;

	if (IsValid(AttackLoopMontage))
	{
		Unit->ActiveAttacking();
		PlayMontage(AttackLoopMontage);
	}
	else
		Unit->Attack();
}

void UST_ABP_Unit::AnimNotify_LoopAttack()
{
	PlayMontage(AttackLoopMontage);
}

void UST_ABP_Unit::AnimNotify_ExitAttack()
{
	if (IsValid(Unit))
		Unit->ExitAttack();
}

void UST_ABP_Unit::AnimNotify_Dead()
{
	if (IsValid(Unit))
		Unit->SetDead(true);
}

void UST_ABP_Unit::AnimNotify_Disappear()
{
	if (IsValid(Unit))
		Unit->SetActivated(false);
}

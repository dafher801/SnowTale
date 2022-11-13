
#include "ST_SnowWhiteAnim.h"
#include "ST_SnowWhite.h"

void UST_SnowWhiteAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	SnowWhite = Cast<AST_SnowWhite>(TryGetPawnOwner());
}

void UST_SnowWhiteAnim::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
}

void UST_SnowWhiteAnim::PlayInvincibleStartMontage()
{
	PlayMontage(InvincibleStartMontage);
}

void UST_SnowWhiteAnim::ExitInvincibleMontage()
{
	if (!IsValid(SnowWhite))
		return;

	if (Montage_IsPlaying(InvincibleStartMontage))
	{
		Montage_Stop(Montage_GetPosition(GetCurrentActiveMontage()));
		SnowWhite->SetInvincible(false);
	}
	else if (Montage_IsPlaying(InvincibleLoopMontage))
	{
		PlayMontage(InvincibleEndMontage);
	}
	else
		SnowWhite->SetInvincible(false);
}

void UST_SnowWhiteAnim::PlayLethalSkillMontage()
{
	PlayMontage(LethalSkillMontage);
}

void UST_SnowWhiteAnim::ExitLethalSkillMontage()
{

}

void UST_SnowWhiteAnim::AnimNotify_StartInvincible()
{
	if (IsValid(SnowWhite))
		SnowWhite->SetInvincible(true);
}

void UST_SnowWhiteAnim::AnimNotify_LoopInvincible()
{
	PlayMontage(InvincibleLoopMontage);
}

void UST_SnowWhiteAnim::AnimNotify_EndInvincible()
{
	if (IsValid(SnowWhite))
		SnowWhite->SetInvincible(false);
}

void UST_SnowWhiteAnim::AnimNotify_StartLethalSkill()
{
	if (IsValid(SnowWhite))
		SnowWhite->SetUsingLethalSkill(true);
}

void UST_SnowWhiteAnim::AnimNotify_ExecuteLethalSkill()
{
	if (IsValid(SnowWhite))
		SnowWhite->BeginLethalSkill();
}

void UST_SnowWhiteAnim::AnimNotify_EndLethalSkill()
{
	if (IsValid(SnowWhite))
		SnowWhite->SetUsingLethalSkill(false);

	if (IsValid(SnowWhite))
		SnowWhite->ExitLethalSkill();
}

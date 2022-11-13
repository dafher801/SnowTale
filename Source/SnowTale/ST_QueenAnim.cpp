
#include "ST_QueenAnim.h"
#include "ST_Queen.h"

void UST_QueenAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Queen = Cast<AST_Queen>(TryGetPawnOwner());
}

void UST_QueenAnim::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
}

void UST_QueenAnim::PlayPatternMontage()
{
	PlayMontage(PatternStartMontage);
}

void UST_QueenAnim::ExitPatternMontage()
{
	if (IsValid(Queen))
	{
		if (Montage_IsPlaying(PatternStartMontage))
		{
			Montage_Stop(Montage_GetPosition(GetCurrentActiveMontage()));
			Queen->SetActivePattern(false);
		}
		else if (Montage_IsPlaying(PatternLoopMontage))
		{
			PlayMontage(PatternEndMontage);
		}
		else
			Queen->SetActivePattern(false);
	}
}

void UST_QueenAnim::AnimNotify_StartPattern()
{
	if (IsValid(Queen))
		Queen->SetActivePattern(true);
}

void UST_QueenAnim::AnimNotify_LoopPattern()
{
	PlayMontage(PatternLoopMontage);
}

void UST_QueenAnim::AnimNotify_EndPattern()
{
	if (IsValid(Queen))
		Queen->SetActivePattern(false);
}
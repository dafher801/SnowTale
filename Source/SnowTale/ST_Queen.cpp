
#include "ST_Queen.h"
#include "ST_QueenAnim.h"
#include "ST_AttackSystem.h"
#include "ST_EnemySpawner.h"
#include "ST_SnowTaleGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AST_Queen::AST_Queen()
	: bActivePattern(false)
	, CurrentPatternIndex(0)
{
	ActivePatternParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ActivePatternParticle"));
	ActivePatternParticle->SetupAttachment(RootComponent);
	ActivePatternParticle->bAutoActivate = false;
}

void AST_Queen::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	if (bDead)
	{
		Super::Tick(DeltaTime);
		return;
	}

	if (bActivePattern)
	{
		AST_Unit::Tick(DeltaTime);

		ExitMove();

		ExecutePattern();

		TotalPatternCycleTime += DeltaTime;
		TotalPatternDurationTime += DeltaTime;
	}
	else
	{
		AST_Enemy::Tick(DeltaTime);

		StartPattern();

		TotalPatternWaitingTime += DeltaTime;
	}
}

float AST_Queen::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (CurrentStatus.HP <= 0.0f)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		Cast<AST_SnowTaleGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GameClear();
	}

	return DamageAmount;
}

void AST_Queen::StartPattern()
{
	if (PatternArray.IsValidIndex(CurrentPatternIndex) &&
		PatternArray[CurrentPatternIndex].WaitingTime - TotalPatternWaitingTime <= 0)
	{
		if (IsValid(QueenAnim))
			QueenAnim->PlayPatternMontage();

		if (IsValid(ActivePatternParticle))
			ActivePatternParticle->Activate();

		TotalPatternWaitingTime = 0.0f;
	}
}

void AST_Queen::ExecutePattern()
{
	if (!IsValid(PatternArray[CurrentPatternIndex].Pattern))
		return;

	if (PatternArray[CurrentPatternIndex].CycleTime - TotalPatternCycleTime <= 0)
	{
		PatternArray[CurrentPatternIndex].Pattern->Attack();
		TotalPatternCycleTime = 0.0f;
	}
	else if (PatternArray[CurrentPatternIndex].DurationTime - TotalPatternDurationTime <= 0)
	{
		EndPattern();
	}
}

void AST_Queen::EndPattern()
{
	SetActivePattern(false);

	if (IsValid(ActivePatternParticle))
		ActivePatternParticle->Deactivate();

	TotalPatternDurationTime = 0.0f;
	TotalPatternCycleTime = 0.0f;

	CurrentPatternIndex = CurrentPatternIndex + 1 >= PatternArray.Num() ? 0 : ++CurrentPatternIndex;
}

bool AST_Queen::GetActivePattern() const
{
	return bActivePattern;
}

void AST_Queen::SetActivePattern(bool ActivePattern)
{
	bActivePattern = ActivePattern;
}

void AST_Queen::BeginPlay()
{
	Super::BeginPlay();

	SetActivated(true);

	for (int i = 0; i < PatternArray.Num(); i++)
	{
		if (IsValid(PatternArray[i].Pattern))
		{
			PatternArray[i].Pattern->SetActivated(true);
			PatternArray[i].Pattern->SetOwner(this);
		}
	}

	if (IsValid(GetMesh()) && IsValid(GetMesh()->GetAnimInstance()))
		QueenAnim = Cast<UST_QueenAnim>(GetMesh()->GetAnimInstance());
}

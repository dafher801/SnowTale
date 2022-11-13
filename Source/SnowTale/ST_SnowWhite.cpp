
#include "ST_SnowWhite.h"
#include "ST_HealItem.h"
#include "ST_PlayerWidget.h"
#include "ST_SnowWhiteAnim.h"
#include "ST_Enemy.h"
#include "ST_CameraBlendingSystem.h"
#include "ST_SnowTaleGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AST_SnowWhite::AST_SnowWhite()
{
	Tags.Add(FName("Player"));

	CameraBlendingSystem = CreateDefaultSubobject<UST_CameraBlendingSystem>(TEXT("CameraBlendingSystem"));
	CameraBlendingSystem->SetupAttachment(RootComponent);

	InvincibleParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("InvincibleParticle"));
	InvincibleParticle->SetupAttachment(RootComponent);

	LethalSkillParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LethalSkillParticle"));
	LethalSkillParticle->SetupAttachment(RootComponent);
}

void AST_SnowWhite::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	if (bDead)
	{
		Super::Tick(DeltaTime);
		return;
	}

	if (bInvincible)
	{
		LookAtTarget();
		Move();
		Invincible();
	}
	else
	{
		if (CurrentStatus.MP < BaseStatus.MP)
			CurrentStatus.MP += MPRecoveryAmountPerTick;

		if (bUsingLethalSkill)
		{
			SetActorRotation(BodyRotation + RotationRevisionCalculation + CameraRotation);
		}
		else
		{
			LookAtTarget();
			Move();

			if (bAttacking)
				Attack();
		}
	}

	Super::Tick(DeltaTime);
}

void AST_SnowWhite::LookAtTarget(FVector TargetLocation)
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->
		DeprojectMousePositionToWorld(TargetLocation, WorldDirection);

	FVector2D UnitScreenLocation;
	FVector2D TargetScreenLocation;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController)
	{
		PlayerController->ProjectWorldLocationToScreen(GetActorLocation(), UnitScreenLocation, true);
		PlayerController->ProjectWorldLocationToScreen(TargetLocation, TargetScreenLocation, true);
	}
	else
		return;

	Super::LookAtTarget(FVector(TargetScreenLocation - UnitScreenLocation, 0.0f));

	SetActorRotation(GetActorRotation() + CameraRotation);
}

void AST_SnowWhite::Move(FVector MoveVector)
{
	MoveVector = FVector(CurrentForwardValue, CurrentRightValue, 0.0f);

	if (MoveVector.SizeSquared() > 0.0f)
	{
		GetMovementComponent()->Velocity = (CameraRotation + 
			MoveVector.Rotation()).Vector() * CurrentStatus.MoveSpeed;
	}
	else
	{
		GetMovementComponent()->Velocity = FVector::ZeroVector;
	}
}

void AST_SnowWhite::BeginAttack()
{
	if (!IsValid(SnowWhiteAnim))
		return;

	ActiveStartingAttack();

	FTimerHandle Timer;

	GetWorldTimerManager().SetTimer(Timer, this, &AST_Unit::ActiveAttacking, StartingAttackTime, false);
}

void AST_SnowWhite::Attack()
{
	if (bPressedLeftMouse && bAttacking && 1.0f / CurrentStatus.AttackSpeed - TimeElapsedSinceAttack <= 0)
	{
		Super::Attack();

		TimeElapsedSinceAttack = 0.0f;
	}
}

void AST_SnowWhite::ExitAttack()
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

void AST_SnowWhite::Invincible()
{
	if (CurrentStatus.MP >= InvincibeMPConsumptionPerTick)
		CurrentStatus.MP -= InvincibeMPConsumptionPerTick;
	else
		ExitInvincibleMontage();
}

void AST_SnowWhite::AcquireHealItem(AST_HealItem* HealItem)
{
	AcquireHealItemDelegate.Execute();
	HealItemArray.Push(HealItem);
}

void AST_SnowWhite::UseHealItem(FKey Key)
{
	if (HealItemArray.Num() > 0)
		HealItemArray.Pop()->Heal(BaseStatus.HP, CurrentStatus.HP);

	UseHealItemDelegate.Execute();
}

void AST_SnowWhite::InputForward(float NewForwardValue)
{
	CurrentForwardValue = NewForwardValue;
}

void AST_SnowWhite::InputRight(float NewRightValue)
{
	CurrentRightValue = NewRightValue;
}

void AST_SnowWhite::PressedLeftMouse(FKey Key)
{
	bPressedLeftMouse = true;

	BeginAttack();
}

void AST_SnowWhite::ReleasedLeftMouse(FKey Key)
{
	bPressedLeftMouse = false;

	ExitAttack();
}

void AST_SnowWhite::PressedRightMouse(FKey Key)
{
	if (IsUsingLethalSkill())
		return;

	bPressedRightMouse = true;

	BeginInvincibleMontage();
}

void AST_SnowWhite::ReleasedRightMouse(FKey Key)
{
	if (!bPressedRightMouse)
		return;

	bPressedRightMouse = false;

	ExitInvincibleMontage();
}

void AST_SnowWhite::PressedSpaceBar(FKey Key)
{
	bPressedSpaceBar = true;

	if (!bInvincible)
		BeginLethalSkillMontage();
}

void AST_SnowWhite::ReleasedSpaceBar(FKey Key)
{
	bPressedSpaceBar = false;
}

void AST_SnowWhite::RotateCamera(FKey key)
{
	if (bRotatingCamera)
		return;

	float CameraRotatingAmount = key.GetFName().Compare(FName("Q")) ? 90.0f : -90.0f;

	CameraRotation += FRotator(0.0f, CameraRotatingAmount, 0.0f);

	if (!(static_cast<int>(CameraRotation.Yaw) % 360))
		CameraRotation.Yaw = 0;

	if (CameraRotatingAmount > 0)
		CameraBlendingSystem->RotateRight();
	else
		CameraBlendingSystem->RotateLeft();

	bRotatingCamera = true;

	FTimerHandle Timer;

	GetWorldTimerManager().SetTimer(Timer, this,
		&AST_SnowWhite::CompleteRotatingCamera, CameraRotatingTime, false);
}

bool AST_SnowWhite::IsInvincible() const
{
	return bInvincible;
}

void AST_SnowWhite::SetInvincible(bool Invincible)
{
	bInvincible = Invincible;
}

bool AST_SnowWhite::IsUsingLethalSkill() const
{
	return bUsingLethalSkill;
}

void AST_SnowWhite::SetUsingLethalSkill(bool UsingLethalSkill)
{
	bUsingLethalSkill = UsingLethalSkill;
}

void AST_SnowWhite::BeginInvincibleMontage()
{
	if (IsValid(SnowWhiteAnim))
		SnowWhiteAnim->PlayInvincibleStartMontage();

	if (IsValid(InvincibleParticle))
		InvincibleParticle->Activate();
}

void AST_SnowWhite::ExitInvincibleMontage()
{
	if (IsValid(SnowWhiteAnim))
		SnowWhiteAnim->ExitInvincibleMontage();

	if (IsValid(InvincibleParticle))
		InvincibleParticle->Deactivate();
}

void AST_SnowWhite::CompleteRotatingCamera()
{
	bRotatingCamera = false;
}

void AST_SnowWhite::BeginLethalSkillMontage()
{
	if (IsValid(SnowWhiteAnim))
	{
		if (CurrentStatus.MP < LethalSkillMPAmount)
			return;

		CurrentStatus.MP -= LethalSkillMPAmount;
		SnowWhiteAnim->PlayLethalSkillMontage();
	}
}

void AST_SnowWhite::BeginLethalSkill()
{
	if (IsValid(LethalSkillParticle))
		LethalSkillParticle->Activate();

	if (IsValid(LethalSkillSound))
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), LethalSkillSound, GetActorLocation());

	AST_SnowTaleGameModeBase* GameModeBase = Cast<AST_SnowTaleGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	bool ActivatedEnemy;
	bool InRangeEnemy;
	bool VisibleEnemy;

	FHitResult HitResult;
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);

	for (int i = 0; i < GameModeBase->GetEnemyArray().Num(); i++)
	{
		ActivatedEnemy = GameModeBase->GetEnemyArray()[i]->IsActivated();
		InRangeEnemy = LethalSkillRange > FVector::Dist(GetActorLocation(), GameModeBase->GetEnemyArray()[i]->GetActorLocation());
		
		VisibleEnemy = !(GetWorld()->LineTraceSingleByObjectType(HitResult, GetActorLocation(),
			GameModeBase->GetEnemyArray()[i]->GetActorLocation(), CollisionObjectQueryParams));

		if (ActivatedEnemy && InRangeEnemy && VisibleEnemy)
		{
			UGameplayStatics::ApplyDamage(GameModeBase->
				GetEnemyArray()[i], LethalSkillDamage, GetController(), this, NULL);
		}
	}
}

void AST_SnowWhite::ExitLethalSkill()
{
	if (IsValid(LethalSkillParticle))
		LethalSkillParticle->Deactivate();
}

void AST_SnowWhite::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &AST_SnowWhite::InputForward);
	InputComponent->BindAxis("MoveRight", this, &AST_SnowWhite::InputRight);

	InputComponent->BindAction("Attack", IE_Pressed, this, &AST_SnowWhite::PressedLeftMouse);
	InputComponent->BindAction("Attack", IE_Released, this, &AST_SnowWhite::ReleasedLeftMouse);

	InputComponent->BindAction("UseHeal", IE_Pressed, this, &AST_SnowWhite::UseHealItem);

	InputComponent->BindAction("Invincibility", IE_Pressed, this, &AST_SnowWhite::PressedRightMouse);
	InputComponent->BindAction("Invincibility", IE_Released, this, &AST_SnowWhite::ReleasedRightMouse);

	InputComponent->BindAction("LethalSkill", IE_Pressed, this, &AST_SnowWhite::PressedSpaceBar);
	InputComponent->BindAction("LethalSkill", IE_Released, this, &AST_SnowWhite::ReleasedSpaceBar);

	InputComponent->BindAction("RotateCamera", IE_Pressed, this, &AST_SnowWhite::RotateCamera);
}

float AST_SnowWhite::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount =  bInvincible || bUsingLethalSkill ? 0.0f :
		Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (CurrentStatus.HP <= 0.0f)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		Cast<AST_SnowTaleGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GameOver();
	}

	return DamageAmount;
}

void AST_SnowWhite::BeginPlay()
{
	Super::BeginPlay();

	SetActivated(true);

	if (IsValid(GetMesh()) && IsValid(GetMesh()->GetAnimInstance()))
		SnowWhiteAnim = Cast<UST_SnowWhiteAnim>(GetMesh()->GetAnimInstance());
}

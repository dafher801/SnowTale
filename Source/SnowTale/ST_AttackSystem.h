
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ST_AttackSystem.generated.h"

UCLASS()
class SNOWTALE_API AST_AttackSystem : public AActor
{
	GENERATED_BODY()

public:

	AST_AttackSystem();

public:

	// AttackSystem 작동 시 매 프레임마다 실행되는 로직
	virtual void Tick(float DeltaTime) override;

	// Unit으로부터 공격 요청이 들어왔을 때 실행되는 로직
	virtual void Attack();

	// AttackSystem이 가지고 있는 발사체 혹은 
	// 장판에 누가 공격자인지 전부 등록하는 로직
	virtual void SetOwner(AActor* NewOwner) override;

	bool IsActivated() const;
	void SetActivated(bool Activated);

protected:

	virtual void BeginPlay() override;

protected:

	bool bActivated;
	
};

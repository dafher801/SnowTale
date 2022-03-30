
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ST_AttackSystem.generated.h"

UCLASS()
class SNOWTALE_API AST_AttackSystem : public AActor
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	virtual void Attack();

	bool GetActivated() const;
	void SetActivated(bool Activated);

protected:

	virtual void BeginPlay() override;

protected:

	bool bActivated;
	
};

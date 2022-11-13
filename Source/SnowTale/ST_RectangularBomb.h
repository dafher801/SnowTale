
#pragma once

#include "CoreMinimal.h"
#include "ST_Bomb.h"
#include "ST_RectangularBomb.generated.h"

UCLASS()
class SNOWTALE_API AST_RectangularBomb : public AST_Bomb
{
	GENERATED_BODY()

public:

	AST_RectangularBomb();

public:

	virtual void Init(FVector SpawnLocation, FRotator SpawnRotation) override;

	virtual void Tick(float DeltaTime) override;

	virtual void AddFloorScale() override;

protected:

	virtual void BeginPlay() override;

};

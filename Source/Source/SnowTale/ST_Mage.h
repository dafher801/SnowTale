
#pragma once

#include "CoreMinimal.h"
#include "ST_Enemy.h"
#include "ST_Mage.generated.h"

UCLASS()
class SNOWTALE_API AST_Mage : public AST_Enemy
{
	GENERATED_BODY()

public:

	virtual void BeginAttack() override;
	virtual void Attack() override;
	virtual void ExitAttack() override;
	
};

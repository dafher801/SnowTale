
#pragma once

#include "CoreMinimal.h"
#include "ST_InteractiveActor.h"
#include "ST_Portal.generated.h"

UCLASS()
class SNOWTALE_API AST_Portal : public AST_InteractiveActor
{
	GENERATED_BODY()

public:

	//virtual void Interact(class AActor* OtherActor) override;

protected:

	virtual void BeginPlay() override;
	
};

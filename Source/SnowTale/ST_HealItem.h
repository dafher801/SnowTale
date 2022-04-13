
#pragma once

#include "CoreMinimal.h"
#include "ST_Item.h"
#include "ST_HealItem.generated.h"

UCLASS()
class SNOWTALE_API AST_HealItem : public AST_Item
{
	GENERATED_BODY()

public:

	AST_HealItem();

public:

	virtual void Interact(class AActor* OtherActor) override;

	void Heal(float& BaseHP, float& CurrentHP);

	float GetHealAmount() const;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
		float HealAmount;
	
};


#pragma once

#include "CoreMinimal.h"
#include "ST_InteractiveActor.h"
#include "ST_Item.generated.h"

UENUM(BlueprintType)
enum class EST_ItemType : uint8
{
	BEGIN,
	HEAL,
	END
};

UCLASS()
class SNOWTALE_API AST_Item : public AST_InteractiveActor
{
	GENERATED_BODY()
	
public:	

	AST_Item();

public:

	virtual void Tick(float DeltaTime) override;

	virtual void Interact(class AActor* OtherActor) override;

	virtual void UseItem();

	EST_ItemType GetItemType() const;

protected:

	virtual void BeginPlay() override;

protected:

	class AST_SnowWhite* Owner;

	EST_ItemType ItemType;

};

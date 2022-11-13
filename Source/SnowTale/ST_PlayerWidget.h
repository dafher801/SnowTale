
#pragma once

#include "CoreMinimal.h"
#include "ST_UnitWidget.h"
#include "ST_PlayerWidget.generated.h"

UCLASS()
class SNOWTALE_API UST_PlayerWidget : public UST_UnitWidget
{
	GENERATED_BODY()

public:

	UST_PlayerWidget(const FObjectInitializer& ObjectInitializer);

	void PushHealItemImage();

	void PopHealItemImage();

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HealItemImage")
		TArray<class UImage*> HealItemImageArray;
};

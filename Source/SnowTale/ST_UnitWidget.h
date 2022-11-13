
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ST_UnitWidget.generated.h"

UCLASS()
class SNOWTALE_API UST_UnitWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UST_UnitWidget(const FObjectInitializer& ObjectInitializer);

public:

	UFUNCTION(BlueprintCallable)
		float GetHPRatio() const;

	UFUNCTION(BlueprintCallable)
		float GetMPRatio() const;

	void BindUnit(class AST_Unit* Unit);

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit")
		class AST_Unit* Owner;
};


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ST_UnitWidget.generated.h"

UCLASS()
class SNOWTALE_API UST_UnitWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void BindUnit(class AST_Unit* Unit);

	UFUNCTION(BlueprintCallable)
		float GetHPRatio() const;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit")
		class AST_Unit* Owner;
};

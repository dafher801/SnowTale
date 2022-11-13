
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ST_PatternData.generated.h"

USTRUCT()
struct FST_Pattern : public FTableRowBase
{
	GENERATED_BODY()

public:

	FST_Pattern();

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pattern")
		class AST_AttackSystem* Pattern;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pattern")
		float DurationTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pattern")
		float WaitingTime;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pattern")
		float CycleTime;

};

UCLASS()
class SNOWTALE_API UST_PatternData : public UObject
{
	GENERATED_BODY()
};

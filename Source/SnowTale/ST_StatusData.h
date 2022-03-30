
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ST_StatusData.generated.h"

USTRUCT()
struct FST_Status : public FTableRowBase
{
	GENERATED_BODY()

public:

	FST_Status();

public:

	FST_Status& operator=(const FST_Status& Status);

	FST_Status operator+(const FST_Status& Status) const;

	FST_Status operator-(const FST_Status& Status) const;

	FST_Status operator*(float Ratio) const;

	FST_Status operator/(float Ratio) const;

	FST_Status& operator+=(const FST_Status& Status);

	FST_Status& operator-=(const FST_Status& Status);

	FST_Status& operator*=(float Ratio);

	FST_Status& operator/=(float Ratio);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float ATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float DEF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float Range;
};

UCLASS()
class SNOWTALE_API UST_StatusData : public UObject
{
	GENERATED_BODY()
};
